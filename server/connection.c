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
void Connection__DumpData();
void Connection__SendInteger(int socket, int integer);
void Connection__SendString(int socket, char *string);
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
	DBG__LOG("Client accepted\n");
	int socket = *(int *)client_fd;

	if(*(data->valid_data)){
		DBG__LOG("Send server data to client\n");
		Connection__DumpData();
		int i;
		XMLStruct *xml_data = data->xml_data;
		Connection__SendString(socket, "Temperatures: ");
		for(i = 0; i < CARDS_MAX; i++){
			if(xml_data->temperatures[i] != 0){
				if(i > 0){
					Connection__SendString(socket, ",");
				}
				Connection__SendInteger(socket, xml_data->temperatures[i]);
			}
		}
		Connection__SendString(socket, "\nIP-address: ");
		Connection__SendString(socket, xml_data->ip_address);
		Connection__SendString(socket, "\nUptime: ");
		Connection__SendInteger(socket, xml_data->uptime);
		Connection__SendString(socket, "\n");
	}
	
	close(*(int *) client_fd);
	return 0;
}

void Connection__DumpData(){
	int i;
	for(i = 0; i < CARDS_MAX; i++){
		if(data->xml_data->temperatures[i] != 0){
			DBG__LOG("Temperature: %d\n", data->xml_data->temperatures[i]);
		}
	}
	
	DBG__LOG("IP address: %s\n", data->xml_data->ip_address);
	DBG__LOG("Uptime: %d\n", data->xml_data->uptime);
	DBG__LOG("Valid data ?: %d\n", *(data->valid_data));
}

void Connection__SendString(int socket, char *string){
	write(socket, string, strlen(string));
}

void Connection__SendInteger(int socket, int integer){
	char buffer[256];
	sprintf(buffer, "%d", integer);
	write(socket, buffer, strlen(buffer)+1);
}








