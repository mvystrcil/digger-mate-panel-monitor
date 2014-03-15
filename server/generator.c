/*
 * generator.c
 *
 * Copyright (C) 2014 - 
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
#include <dirent.h>
#include <string.h>

#include "generator.h"
#include "main.h"
#include "logger.h"

GeneratorData *data;
void Generator__DumpData(GeneratorData *data);
void Generator__RunScripts(char *path);

void Generator__Init(void *generator_data){
	DBG__LOG("Initializing logs\n");
	data = (GeneratorData*) generator_data;

	Generator__DumpData(data);
	Generator__RunScripts(data->path_to_scripts);
}

void Generator__DumpData(GeneratorData *data){
	DBG__LOG("XML file: %s\n", data->xml_file);
	DBG__LOG("Scripts: %s\n", data->path_to_scripts);
}

void Generator__RunScripts(char *path){
	DIR *curr_dir;
	struct dirent *dir;
	curr_dir = opendir(path);
	if (curr_dir){
		while ((dir = readdir(curr_dir)) != NULL){
			if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
				printf("%s\n", dir->d_name);
			}
		}
		closedir(curr_dir);
	}
}