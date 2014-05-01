/*
 * mutex.c
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

#include <pthread.h>

#include "mutex.h"
#include "logger.h"

pthread_mutex_t xml_file_mutex = PTHREAD_MUTEX_INITIALIZER;

int Mutex__Init(){
	if(pthread_mutex_init(&xml_file_mutex, NULL) != 0){
		DBG__ERR_LOG("Cannot initialize connection mutex\n");
		return FALSE;
	}
	return TRUE;
}

int Mutex__LockFileMutex(){
	pthread_mutex_lock(&xml_file_mutex);
	return TRUE;
}

int Mutex__UnlockFileMutex(){
	pthread_mutex_unlock(&xml_file_mutex);
	return TRUE;
}

void Mutex__DestroyAll(){
	pthread_mutex_destroy(&xml_file_mutex);
}