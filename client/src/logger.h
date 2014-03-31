/*
 * logger.h
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
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define DBG__LOG(fmt, ...) \
	fprintf(stdout, "[%s:%d]:%s: " fmt "\n",\
	__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__)

#define DBG__ERR_LOG(fmt, ...) \
	fprintf(stdout, "[%s:%d]:%s: " fmt "\n",\
	__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__)


#endif