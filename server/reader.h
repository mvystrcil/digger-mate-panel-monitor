/*
 * reader.h
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
#define CARDS_MAX 10
#define KEYS	 (sizeof(lookuptable)/sizeof(t_lookupstruct))

typedef enum {
	TEMPERATURES,
	UPTIME,
	IP_ADDRESS,
	UNDEFINED   /* Left it last forever */
} Parameters;

typedef struct {char *key; int val;} t_lookupstruct;

static t_lookupstruct lookuptable[] = {
    {"temperatures",  TEMPERATURES},
	{"uptime", UPTIME},
	{"ip-address", IP_ADDRESS}
};

typedef struct {
	int temperatures[CARDS_MAX];
	int uptime;
	char *ip_address;
}XMLStruct;

XMLStruct* Reader__ReadFile(void *file);