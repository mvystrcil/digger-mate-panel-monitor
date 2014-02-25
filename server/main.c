/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2014 Martin Vystr??il <vystrcil.martin@gmail.com>
 * 
 * Digger is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Digger is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <pthread.h>
#include <string.h>

#include "connection.h"
#include "logger.h"
#include "main.h"

#define SERVER_ADDR "127.0.0.1"
#define XML_FILE "../../xml/xml_file.xml"

int valid_data = 0;

int main(int argc, char* argv[]){
	ConnectionData connection_data;	
	pthread_t connection, reader;
	bzero(&connection_data, sizeof(connection_data));

	FILE *xmlFile = fopen(argv[1], "r");

	if(xmlFile == NULL){
		DBG__LOG("Cannot open xml file %s for read\n", argv[1]);
		return -1;
	} else {
		fclose(xmlFile);
	}
	
	connection_data.ip_address = SERVER_ADDR;
	connection_data.port = 2000;
	connection_data.xml_file = argv[1];
	
	if(pthread_create(&connection, NULL, Connection__Connect, &connection_data) < 0){
		DBG__LOG("Cannot create Connection Hypervisor thread\n");
		return -1;
	}

	pthread_join(connection, NULL);
	
	return 0;
}
