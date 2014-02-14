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

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h> 
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "logger.h"
#include "reader.h"
#include "connection.h"
#include "main.h"

void Connection__HandleConnections(struct sockaddr_in server_data, int server_fd);
void* Connection__ConnectionHandler(void *client_fd);
ConnectionData *data;

void Connection__Connect(void *conn_data){
	data = (ConnectionData *) conn_data;
	char *address = data->ip_address;
	int port = data->port;
	int server_fd, res;
	struct sockaddr_in server_data;
	
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd < 0){
		DBG__LOG("Cannot get file descriptor for Internet Socket\n");
		return;
	} else {
		DBG__LOG("Got sockect fd: %d\n", server_fd);
	}

	bzero(&server_data, sizeof(server_data));
	
	server_data.sin_family = AF_INET;
	server_data.sin_addr.s_addr = INADDR_ANY;
	server_data.sin_port = htons(port);

	res = bind(server_fd, (struct sockaddr *) &server_data, sizeof(server_data));
	listen(server_fd, 5);
	
	/* Handle connections in threads */
	
	if(res < 0){
		DBG__LOG("Cannot bind to socket fd: %d, addr: %s, port: %d\n", server_fd, address, port);
		return;
	} else {
		DBG__LOG("Socket binded to addr:\n");
	}

	Connection__HandleConnections (server_data, server_fd);

	return;
}

void Connection__HandleConnections(struct sockaddr_in server_data, int server_fd){
	int client_fd;
	int *new_sock;
	struct sockaddr_in client_data;
	socklen_t tmp = sizeof(server_data);

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
	printf ("Client accepted\n");
	char *message = "Hello from digger server\n";
	write(*(int*) client_fd, message, sizeof(message));

	printf("Valid data ?: %d\n", data->valid_data);

	message = "Hello from digger server\n";
	write(*(int*) client_fd, message, sizeof(message));

	close(*(int *) client_fd);
	return 0;
}










