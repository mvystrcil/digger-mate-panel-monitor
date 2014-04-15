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
#include <pthread.h>

#include "connection.h"
#include "logger.h"
#include "parser.h"

int valid_data = 0;

int main(int argc, char* argv[]){
	ConnectionData conn_data;
	ParserInputData parser_in_data;
	pthread_t connection, parser;
	
	memset(&conn_data, 0, sizeof(conn_data));
	memset(&parser_in_data, 0, sizeof(parser_in_data));

	conn_data.port = 2000;
	conn_data.refresh = 15;
	conn_data.retry = 1;
	strcpy(conn_data.address, "127.0.0.1");
	strcpy(conn_data.file, "local.xml");

	strcpy(parser_in_data.xml_file, "local.xml");
	
	DBG__LOG("Addr: %p\n", &conn_data.error);

	if(pthread_create(&connection, NULL, Connection__Connect, (void *)&conn_data) < 0){
		DBG__ERR_LOG("Cannot create Connection thread\n");
	}

	if(pthread_create(&parser, NULL, Parser__ParseXMLFile, (void *)&parser_in_data) < 0){
		DBG__ERR_LOG("Cannot create Parser thread\n");
	}
	
	pthread_join(connection, NULL);
	pthread_join(parser, NULL);

	if(conn_data.error != 0){
		DBG__ERR_LOG("Returned error: %d:%s\n", conn_data.error, strerror(conn_data.error));
	}
	
	return 0;
}
