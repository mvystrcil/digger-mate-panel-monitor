/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2014 Martin Vystrcil <vystrcil.martin@gmail.com>
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
#include <pthread.h>
#include <string.h>

#include "connection.h"
#include "logger.h"
#include "generator.h"
#include "main.h"

#define SERVER_ADDR "127.0.0.1"
#define PORT 2000

#define PATH_TO_SCRIPTS 1
#define XML_FILE 2

int valid_data = 0;

void Main__FillStructuresFromArgs(ConnectionData *connection, GeneratorData *generator, int argc, char *argv[]);

int main(int argc, char* argv[]){
	ConnectionData connection_data;
	GeneratorData generator_data;
	pthread_t connection, generate;
	bzero(&connection_data, sizeof(connection_data));
	bzero(&generator_data, sizeof(generator_data));

	if(argc < 2){
		/*TODO: write some help.
		 *  arg1: path to scripts
		 *  arg2: path to xml file
		 */
		DBG__ERR_LOG("Usage: %s path to scripts [path to store xml]\n", argv[0]);
		return -1;
	} else {
		Main__FillStructuresFromArgs(&connection_data, &generator_data, argc, argv);
	}
	
	if(pthread_create(&generate, NULL, Generator__Init, &generator_data) < 0){
		DBG__LOG("Cannot create Generator Hypervisor thread\n");
	}

	pthread_join(generate, NULL);
	
	/*if(pthread_create(&connection, NULL, Connection__Connect, &connection_data) < 0){
		DBG__LOG("Cannot create Connection Hypervisor thread\n");
		return -1;
	}

	pthread_join(connection, NULL);*/
	
	return 0;
}

void Main__FillStructuresFromArgs(ConnectionData *connection, 
                                  GeneratorData *generator,
                                  int argc,
                                  char *argv[]){	
	generator->xml_file = argv[XML_FILE];
	generator->path_to_scripts = argv[PATH_TO_SCRIPTS];
	
	connection->xml_file = argv[XML_FILE];

	connection->ip_address = SERVER_ADDR;
	connection->port = PORT;
	connection->xml_file = argv[2];
}