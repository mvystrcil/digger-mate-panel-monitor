/*
 * parser.c
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

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "logger.h"
#include "parser.h"

#define NUM_FUNCTIONS 4

void Parser__GetIPAddress(int x, int y){
	DBG__ERR_LOG("Unimplemented %d, %d", x, y);
}

void Parser__GetTemperatures(int x, int y){
	DBG__ERR_LOG("Unimplemented %d, %d", x, y);
}

void Parser__GetCardLoad(int x, int y){
	DBG__ERR_LOG("Unimplemented %d, %d", x, y);
}

void Parser__GetUptime(int x, int y){
	DBG__ERR_LOG("Unimplemented %d, %d", x, y);
}

void *Parser__ParseXMLFile(void *xml_file){
	LIBXML_TEST_VERSION
	
	void (*functions[NUM_FUNCTIONS]) (int x, int y) = {
		Parser__GetIPAddress,
		Parser__GetTemperatures,
		Parser__GetCardLoad,
		Parser__GetUptime
	};

	int i;
	char *file_to_parse = ((char *)xml_file);

	DBG__LOG("%s\n", file_to_parse);
	
	for(i = 0; i < NUM_FUNCTIONS; i++){
		functions[i](1,5);
	}
	
	return NULL;
}








