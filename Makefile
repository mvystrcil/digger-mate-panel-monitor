CC = gcc
CFLAGS = -g -Wall -Werror -O2
OBJDIR = ../build
BINDIR = $(shell pwd)/staging-area

export CFLAGS
export CC
export OBJDIR
export BINDIR

.PHONY: server client clean

all: server client
	@echo "===> All Done"

server:
	cd server; make

client:
	cd client; make

clean:
	cd server; make clean
	cd client; make clean
	rm -rf $(BINDIR)