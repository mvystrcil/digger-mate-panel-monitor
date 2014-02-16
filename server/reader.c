/*
 * reader.c
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

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#include "reader.h"
#include "logger.h"
#include "main.h"

xmlNode* Reader__ParseXMLFile(const char *xmlFile);
void Reader__FillXMLStruct(xmlNode *root, XMLStruct *values);
int Reader__KeyFromString(char *key);
void Reader__FillTemperatures(xmlNode *node, XMLStruct *values);
void Reader__DumpData(XMLStruct *values);
XMLStruct values;

void Reader__ReadFile(void *in_file){
	ReaderData *data = (ReaderData *)in_file;
	const char *file = data->xml_file;
	DBG__LOG("Reading file with fd: %s\n", file);

	LIBXML_TEST_VERSION

	while(TRUE){
		xmlNode *root = Reader__ParseXMLFile(file);
		if(root){
			Reader__FillXMLStruct (root, data->xml_data);
			*(data->valid_data) = TRUE;
		} else {
			*(data->valid_data) = FALSE;
		}

		sleep(100);
	}
}

xmlNode* Reader__ParseXMLFile(const char *xmlFile){
	xmlDoc *doc = xmlReadFile(xmlFile, NULL, 0);

	if(doc == NULL){
		DBG__LOG("Can't read source xml file %s\n", xmlFile);
		return NULL;
	}

	return (xmlDocGetRootElement(doc));
}

void Reader__FillXMLStruct(xmlNode *root, XMLStruct *values){
	DBG__LOG("Fill xml struct for root: %s\n", root->name);
	xmlNode *tmp_node = root->children;	

	while(tmp_node){
		if(tmp_node->type == XML_ELEMENT_NODE){
			switch(Reader__KeyFromString((char *) tmp_node->name)){
				case TEMPERATURES:
					DBG__LOG("Found temperatures block: %s\n", tmp_node->name);
					Reader__FillTemperatures (tmp_node, (XMLStruct *) values);
					break;
				case UPTIME:
					DBG__LOG("Found uptime block: %s\n", tmp_node->name);
					values->uptime = atoi((char *)xmlNodeGetContent(tmp_node));
					break;
				case IP_ADDRESS:
					DBG__LOG("Found ip-address block: %s\n", tmp_node->name);
					values->ip_address = (char *)xmlNodeGetContent(tmp_node);
					break;
				case UNDEFINED:
					DBG__LOG("Undefined value in xml file. %s\n", tmp_node->name);
					break;
				default:
					DBG__LOG("Some exception occured. %s\n", tmp_node->name);
					return;
			}
		}
		tmp_node = tmp_node->next;
	}
}

void Reader__FillTemperatures(xmlNode *node, XMLStruct *values){
	xmlNode *tmp = node->children;
	int index = 0;
	while(tmp){
		if(tmp->type == XML_ELEMENT_NODE){
			xmlChar *id = xmlGetProp(tmp, (xmlChar*)"id");

			if(id){
				//TODO: fix atoi problem with index into array
				//unsigned int index =(unsigned int) atoi((char *) id);
				int temp = atoi((char *) xmlNodeGetContent(tmp));
				values->temperatures[index++] = (int)temp;
			}
		}
		tmp = tmp->next;
	}
}

int Reader__KeyFromString(char *key){
	int i;
	for(i = 0; i < KEYS; i++){
		t_lookupstruct *act = &lookuptable[i];
		if(strcmp(act->key, key) == 0){
			return act->val;
		}
	}
	return UNDEFINED;
}