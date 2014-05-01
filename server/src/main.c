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
#include <stdlib.h>

#include <unistd.h>

#include "connection.h"
#include "logger.h"
#include "generator.h"
#include "mutex.h"

#define DEFAULT_PORT 2000

#define PATH_TO_SCRIPTS 1
#define XML_FILE 2
#define PORT 3

int valid_data = 0;

void Main__FillStructuresFromArgs(ConnectionData *connection, GeneratorData *generator, int argc, char *argv[]);
void Main__DumpGeneratorData(GeneratorData *data);
void Main__DumpConnectionData(ConnectionData *data);

int stop;
ConnectionData connection_data;
GeneratorData generator_data;

int main(int argc, char* argv[]){	
	pthread_t connection, generate;
	memset(&connection_data, 0, sizeof(connection_data));
	memset(&generator_data, 0, sizeof(generator_data));
	stop = 0;
	
	if(argc < 2){
		/*TODO: write some help.
		 *  arg1: path to scripts
		 *  arg2: path to xml file
		 *  arg3: port
		 */
		DBG__ERR_LOG("Usage: %s path to scripts path where to store xml port\n", argv[0]);
		return -1;
	} else {
		Main__FillStructuresFromArgs(&connection_data, &generator_data, argc, argv);
	}

	Main__DumpConnectionData(&connection_data);
	Main__DumpGeneratorData(&generator_data);

	Mutex__Init();
	
	if(pthread_create(&generate, NULL, Generator__Init, (void *)&generator_data) < 0){
		DBG__LOG("Cannot create Generator Hypervisor thread\n");
	}

	if(pthread_create(&connection, NULL, Connection__Connect, (void *)&connection_data) < 0){
		DBG__LOG("Cannot create Connection Hypervisor thread\n");
		return -1;
	}

	//pthread_join(generate, NULL);
	pthread_join(connection, NULL);
	
	return 0;
}

void Main__DumpGeneratorData(GeneratorData *data){
	DBG__LOG("##### Generator data ##################");
	DBG__LOG("Generator struct addr %p", data);
	DBG__LOG("XML file: %p, %s", data->xml_file, data->xml_file);
	DBG__LOG("Path scr: %p, %s", data->path_to_scripts, data->path_to_scripts);
	//DBG__LOG("Stop    : %d\n", *(data->stop));
	DBG__LOG("#######################################\n");
}

void Main__DumpConnectionData(ConnectionData *data){
	DBG__LOG("##### Connection data ##################");
	DBG__LOG("Connection struct addr %p", data);
	DBG__LOG("XML file:  %p, %s", data->xml_file, data->xml_file);
	DBG__LOG("Port    : %p, %d", &data->port, data->port);
	//DBG__LOG("Stop    : %d\n", data->stop);
	DBG__LOG("########################################\n");
}

void Main__FillStructuresFromArgs(ConnectionData *connection, 
                                  GeneratorData *generator,
                                  int argc,
                                  char *argv[]){
	DBG__LOG("Fill in structure data %s, %s\n", argv[PATH_TO_SCRIPTS], argv[XML_FILE]);
	strcpy(generator->xml_file, argv[XML_FILE]);
	DBG__LOG("Fill path to scripts\n");
	strcpy(generator->path_to_scripts, argv[PATH_TO_SCRIPTS]);
	generator->stop = &stop;

	strcpy(connection->xml_file, argv[XML_FILE]);
	connection->port = atoi(argv[PORT]);
}