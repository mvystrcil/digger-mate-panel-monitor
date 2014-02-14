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

#include "connection.h"
#include "logger.h"
#include "reader.h"

#define SERVER_ADDR "127.0.0.1"


void Main__PrintValues(XMLStruct *values);
int main(int argc, char* argv[]){
	/*XMLStruct *values = Reader__ReadFile ("exclude/test.xml");
	if(values){
		Main__PrintValues(values);
		return (0);
	} else {
		return (-1);
	}*/

	Connection__Connect (SERVER_ADDR, 2000);
	return 0;
}

void Main__PrintValues(XMLStruct *values){
	printf("Machine IP:%s\n", values->ip_address);
	printf("Uptime: %d\n", values->uptime);
	int i;
	printf("Cards temps:\n");
	for(i = 0; i < CARDS_MAX; i++){
		if(values->temperatures[i] > 0){
			printf ("\t%d:%d\n", i, values->temperatures[i]);
		}
	}
}
