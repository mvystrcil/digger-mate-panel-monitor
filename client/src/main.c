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

int valid_data = 0;

int main(int argc, char* argv[]){
	ConnectionData conn_data;
	memset(&conn_data, 0, sizeof(conn_data));

	conn_data.port = 2000;
	strcpy(conn_data.address, "127.0.0.1");

	int ret = *((int *)Connection__Connect(&conn_data));
	ret = 4;
	DBG__LOG("Returned %d\n", ret);
	
	return 0;
}
