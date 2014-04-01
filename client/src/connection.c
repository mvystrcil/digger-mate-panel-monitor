/*
 * connection.c
 *
 * Copyright (C) 2014 - Martin Vystrčil
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <errno.h>

#include "logger.h"
#include "connection.h"

void Connection__SaveServerData(int sockfd, char *file);
void Connection__DumpData(ConnectionData *connection_data);

void *Connection__Connect(void *conn_data){
	int sockfd = 0;
	int attempts = ATTEMPTS;
	ConnectionData connection_data = *((ConnectionData *)conn_data);

	struct sockaddr_in serv_addr;
	Connection__DumpData(&connection_data);
	
	while(TRUE){
		memset(&serv_addr, 0, sizeof(serv_addr));
	
		if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    		DBG__ERR_LOG("Cannot get socket fd\n");
    		return NULL;
		}
	
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(connection_data.port);

		if(inet_pton(AF_INET, connection_data.address, &serv_addr.sin_addr)<=0){
			DBG__ERR_LOG("Cannot set server address: %s\n", connection_data.address);
			return NULL;
		}

		while(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
			sleep(connection_data.retry);
			attempts--;
			if(attempts <= 0){
				DBG__ERR_LOG("Cannot connect to server: %s, errno %d\n", connection_data.address, errno);
				((ConnectionData *) conn_data)->error = errno;
				return NULL;
			}
		}

		Connection__SaveServerData(sockfd, connection_data.file);
		sleep(connection_data.refresh);
	}
	
	return NULL;
}

void Connection__DumpData(ConnectionData *connection_data){
	DBG__LOG("####### Connect to #######");
	DBG__LOG("Port %d", connection_data->port);
	DBG__LOG("Addr: %s", connection_data->address);
	DBG__LOG("Refresh: %d", connection_data->refresh);
	DBG__LOG("Retry: %d", connection_data->retry);
	DBG__LOG("File: %s", connection_data->file);
	DBG__LOG("Error: %d", connection_data->error);
	DBG__LOG("#########################\n");
}

void Connection__SaveServerData(int sockfd, char *file){
	char recvBuff[1024];
	int recv_size=0;

	FILE *local_file = fopen(file, "w");
	if(!file){
		DBG__ERR_LOG("Cannot open local file: %s\n", file);
		return;
	}

	DBG__LOG("Save to file: %s\n", file);
	
	memset(recvBuff, 0, sizeof(recvBuff));
	
	while((recv_size = read(sockfd, recvBuff, sizeof(recvBuff))) > 0){
		fprintf(local_file, "%s", recvBuff);
	}

	fclose(local_file);
}




