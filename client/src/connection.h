/*
 * connection.h
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

#ifndef CONNECTION_H
#define CONNECTION_H

#include "mutex.h"

#define ESCAPE_SIZE 2
#define ATTEMPTS 5

typedef struct {
	 int port;
	 int refresh;
	 int retry;
	 char address[256];
	 char file[256];
	 int error;
} ConnectionData;

void *Connection__Connect(void *conn_data);
#endif
