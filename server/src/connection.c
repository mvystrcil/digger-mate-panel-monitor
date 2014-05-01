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
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h> 
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "logger.h"
#include "connection.h"
#include "mutex.h"

void Connection__HandleConnections(struct sockaddr_in server_data, int server_fd);
void* Connection__ConnectionHandler(void *client_fd);
void Connection__SendString(int socket, char *string);
ConnectionData connection_data;
char file[1024];

void* Connection__Connect(void *conn_data){
	connection_data = *((ConnectionData *) conn_data);
	int port = connection_data.port;
	int server_fd, res;
	DBG__LOG("Port: %d\n", port);
	DBG__LOG("PORT: %p, %d\n", &connection_data.port, connection_data.port);
	
	struct sockaddr_in server_data;
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd < 0){
		DBG__LOG("Cannot get file descriptor for Internet Socket\n");
		return (void *)1;
	} else {
		DBG__LOG("Got sockect fd: %d\n", server_fd);
	}
	int optval = 1;
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));

	bzero(&server_data, sizeof(server_data));
	
	server_data.sin_family = AF_INET;
	server_data.sin_addr.s_addr = INADDR_ANY;
	server_data.sin_port = htons(port);

	res = bind(server_fd, (struct sockaddr *) &server_data, sizeof(server_data));
	listen(server_fd, 5);
	/* Handle connections in threads */
	
	if(res < 0){
		DBG__LOG("Cannot bind to socket fd: %d, port: %d\n", server_fd, port);
		return (void *)1;
	} else {
		DBG__LOG("Socket binded to port: %d\n", port);
	}

	Connection__HandleConnections (server_data, server_fd);

	return (void *)0;
}

void Connection__HandleConnections(struct sockaddr_in server_data, int server_fd){
	int client_fd;
	int *new_sock;
	struct sockaddr_in client_data;
	socklen_t tmp = sizeof(server_data);

	DBG__LOG("Dump data %p, %s\n", &connection_data, connection_data.xml_file);
	
	while(1){
		client_fd = accept(server_fd, (struct sockaddr *)&client_data, &tmp);
		if(client_fd < 0){
			DBG__LOG("Cannot get socket fd for accept connection %d\n", client_fd);
			return;
		} else {
			DBG__LOG("Client accepted - handle it\n");
		}
		new_sock = malloc(sizeof(char));
		new_sock = &client_fd;
		pthread_t thread;

		if(pthread_create(&thread, NULL, Connection__ConnectionHandler, (void *) new_sock) < 0){
			DBG__LOG("Cannot create thread for accepting new client\n");
		}
	}
}

void* Connection__ConnectionHandler(void *client_fd){
	DBG__LOG("Client accepted\n");
	int socket = *(int *)client_fd;
	char buffer[BUFF_SIZE];

	Mutex__LockFileMutex();

	FILE *file = fopen(connection_data.xml_file, "r");
	if(file == NULL){
		DBG__LOG("Cannot open file %s for read\n", connection_data.xml_file);
		exit(1);
	}

	DBG__LOG("Dump data %p, %s\n", &connection_data, connection_data.xml_file);
	
	while(fread(buffer, sizeof(char), sizeof(buffer), file) != 0){
		Connection__SendString(socket, buffer);
	}

	fclose(file);

	Mutex__UnlockFileMutex();
	
	close(*(int *) client_fd);
	return 0;
}

void Connection__SendString(int socket, char *string){
	int len;
	len = write(socket, string, strlen(string));

	if(len != strlen(string)){
		DBG__ERR_LOG("Cannot sent all data\n");
	}
}