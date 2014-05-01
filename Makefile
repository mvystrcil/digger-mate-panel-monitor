CC = gcc
CFLAGS = -g -Wall -Werror -O3
OBJDIR = ../build
BINDIR = $(shell pwd)/staging-area

export CFLAGS
export CC
export OBJDIR
export BINDIR

.PHONY: server client applet clean

all: server client 
	#applet
	@echo "===> All Done"

server:
	cd common; make all
	cd server; make all
	@echo "===> Server Done"

client:
	cd common; make all
	cd client; make client
	@echo "===> Client Done"

applet:
	cd client; make applet
	@echo "===> Applet Done"

clean:
	cd common; make clean
	cd server; make clean
	cd client; make clean
	rm -rf $(BINDIR)
