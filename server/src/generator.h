/*
 * generator.h
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

#ifndef GENERATOR_H
#define GENERATOR_H

typedef struct {
	char xml_file[256];
	char path_to_scripts[256];
	int *stop;
} GeneratorData;

void* Generator__Init(void *generator_data);

#endif