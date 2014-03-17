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
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdlib.h>

#include "generator.h"
#include "main.h"
#include "logger.h"

GeneratorData *data;
void Generator__DumpData(GeneratorData *data);
void Generator__RunScripts(char *path);
void Generator__RunFile(char *file, struct stat *st);

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
	struct stat st;
	curr_dir = opendir(path);
	char path_buffer[1024];
	
	if (curr_dir){
		while ((dir = readdir(curr_dir)) != NULL){
			/* Filter current dir */
			if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
				/* Full path to file */
				snprintf(path_buffer, sizeof(path_buffer), "%s/%s", path, dir->d_name);
				/* Get info about item from folder */
				DBG__LOG("Found file: %s\n", path_buffer);
				lstat(path_buffer, &st);
				if(!S_ISDIR(st.st_mode)){
					Generator__RunFile(path_buffer, &st);
				}
			}
		}
		closedir(curr_dir);
	}
}

void Generator__RunFile(char *file, struct stat *st){
	pid_t pid;
	int ret;
	/* Check if file is runnable */
	if((st->st_mode) & S_IXUSR && !S_ISLNK(st->st_mode)){
		DBG__LOG("Execute script with arguments %s\n", file);
		pid = fork();
		if(pid == 0){
			execl(file, file, data->xml_file, (char*) NULL);
			DBG__LOG("Done\n");
		} else {
			wait(&ret);
		}
	}
}









