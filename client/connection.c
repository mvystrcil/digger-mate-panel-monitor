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

#include "logger.h"

void Connection__Connect(const char *address, int port){
	int sock_fd;
	struct sockaddr_in in_data;
	struct hostent *hostinfo;
	
	hostinfo = gethostbyname(address);
	if(hostinfo == NULL){
		DBG__LOG("Cannot get hostinfo\n");
		return;
	}

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd < 0){
		DBG__LOG("Cannot get file descriptor for Internet Socket\n");
		return;
	}

	in_data.sin_family = AF_INET;
	in_data.sin_port = htons(port);
}