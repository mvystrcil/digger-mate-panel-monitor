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

void *Connection__Connect(void *conn_data){
	int sockfd = 0, n = 0;
    char recvBuff[1024];
	ConnectionData connection_data = *((ConnectionData *)conn_data);

	struct sockaddr_in serv_addr;
	memset(recvBuff, 0, sizeof(recvBuff));
	memset(&serv_addr, 0, sizeof(serv_addr));
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        DBG__ERR_LOG("Cannot get socket fd\n");
        return (void *) 1;
    }

	DBG__LOG("####### Connect to #######");
	DBG__LOG("Port %d", connection_data.port);
	DBG__LOG("Addr: %s", connection_data.address);
	DBG__LOG("File desc: %d", sockfd);
	DBG__LOG("#########################\n");
	
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(connection_data.port);

	if(inet_pton(AF_INET, connection_data.address, &serv_addr.sin_addr)<=0){
		DBG__ERR_LOG("Cannot set server address: %s\n", connection_data.address);
		return (void *) 1;
    }

	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		DBG__ERR_LOG("Cannot connect to server: %s\n, errno %d", connection_data.address, errno);
		return (void *) 1;
    }

	while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0){
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    }

	if(n < 0){
		DBG__ERR_LOG("Read error\n");
    }
	
	return (void *) 0;
}