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
#include <unistd.h>

#include "logger.h"
#include "parser.h"

#define NUM_FUNCTIONS 4

void Parser__GetIPAddress(xmlNode *root_element, char *filename){
	xmlNode *cur_node = NULL;

    for (cur_node = root_element; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: %s\n", cur_node->name);
        }
    }
}

void Parser__GetTemperatures(xmlNode *root_element, char *filename){
	xmlNode *cur_node = NULL;

    for (cur_node = root_element; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: %s\n", cur_node->name);
        }
    }
}

void Parser__GetCardLoad(xmlNode *root_element, char *filename){
	xmlNode *cur_node = NULL;

    for (cur_node = root_element; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: %s\n", cur_node->name);
        }
    }
}

void Parser__GetUptime(xmlNode *root_element, char *filename){
	xmlNode *cur_node = NULL;

    for (cur_node = root_element; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: %s\n", cur_node->name);
        }
    }
}

static void
print_element_names(xmlNode *a_node)
{
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: %s\n", cur_node->name);
        }

        print_element_names(cur_node->children);
    }
}

void *Parser__ParseXMLFile(void *xml_file){	
	char *filename = (char *)xml_file;
	void (*functions[NUM_FUNCTIONS]) (xmlNode *root_element, char *filename) = {
		Parser__GetIPAddress,
		Parser__GetTemperatures,
		Parser__GetCardLoad,
		Parser__GetUptime
	};

	sleep(10);
	LIBXML_TEST_VERSION

	xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
	doc = xmlReadFile(filename, NULL, 0);

    if (doc == NULL) {
        DBG__ERR_LOG("Cannot read xml file %s\n", filename);
    }

    root_element = xmlDocGetRootElement(doc);
    print_element_names(root_element);

	int i;
	char *file_to_parse = ((char *)xml_file);

	DBG__LOG("%s\n", file_to_parse);
	
	for(i = 0; i < NUM_FUNCTIONS; i++){
		functions[i](root_element, filename);
	}

	/*free the document */
    xmlFreeDoc(doc);

	/*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
	
	return NULL;
}







