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
#include "logger.h"
#include "mutex.h"

#define START_TAG "<xml>\n"
#define CLOSE_TAG "</xml>\n"

GeneratorData generator_data;
void Generator__DumpData(GeneratorData *data);
void Generator__RunScripts(const char *path);
void Generator__RunFile(char *file, struct stat *st);

void* Generator__Init(void *gen_data){
	DBG__LOG("Initializing logs\n");
	generator_data = *((GeneratorData*) gen_data);

	const char *path = generator_data.path_to_scripts;
	
	Generator__DumpData(&generator_data);

	while(1){
		Generator__RunScripts(path);
		DBG__LOG("Wait - next cycle\n");
		sleep(10);
	}
	return (void *)1;
}

void Generator__DumpData(GeneratorData *data){
	DBG__LOG("XML file: %p, %s\n", data, data->xml_file);
	DBG__LOG("Scripts: %p, %s\n", data, data->path_to_scripts);
}

void Generator__RunScripts(const char *path){
	DIR *curr_dir;
	struct dirent *dir;
	struct stat st;
	curr_dir = opendir(path);
	char path_buffer[1024];

	DBG__LOG("RunScripts\n");
	
	Generator__DumpData(&generator_data);

	Mutex__LockFileMutex();
	
	/* Init output xml file */
	FILE *xml = fopen(generator_data.xml_file, "w");
	if(!xml){
		DBG__ERR_LOG("Cannot open output xml file %s\n", generator_data.xml_file);
		return;
	}
	fprintf (xml, START_TAG);
	fclose (xml);

	/* Get all scripts from folder and run them */
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
	
	/* Valid close output xml file */
	xml = fopen(generator_data.xml_file, "a");
	if(!xml){
		DBG__ERR_LOG("Cannot open output xml file %s\n", path);
	}
	fprintf(xml, CLOSE_TAG);
	fclose (xml);
	
	Mutex__UnlockFileMutex();
}

void Generator__RunFile(char *file, struct stat *st){
	pid_t pid;
	int ret;
	/* Check if file is runnable */
	if((st->st_mode) & S_IXUSR && !S_ISLNK(st->st_mode)){
		DBG__LOG("Execute script with arguments %s\n", file);
		pid = fork();
		if(pid == 0){
			execl(file, file, generator_data.xml_file, (char*) NULL);
			DBG__LOG("Done\n");
		} else if (pid < 0){
			DBG__ERR_LOG("Cannont fork process\n");
		} else {
			waitpid(pid, &ret, 0);
		}
	}
}