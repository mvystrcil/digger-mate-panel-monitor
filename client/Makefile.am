## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g\
	 -I/usr/include/libxml2

bin_PROGRAMS = digger

digger_SOURCES = \
	main.c \
	connection.c \
	connection.h \
	logger.h \
	reader.c \
	reader.h

digger_LDFLAGS =\
	-lxml2

LIBS=$(shell xml2-config --libs)

digger_LDADD =

