CC = gcc
CFLAGS = -g -Wall -Werror -O2
OBJDIR = ../build
BINDIR = $(shell pwd)/staging-area

export CFLAGS
export CC
export OBJDIR
export BINDIR

.PHONY: server client applet clean

all: server client applet
	@echo "===> All Done"

server:
	cd server; make
	@echo "===> Server Done"

client:
	cd client; make client
	@echo "===> Client Done"

applet:
	cd client; make applet
	@echo "===> Applet Done"

clean:
	cd server; make clean
	cd client; make clean
	rm -rf $(BINDIR)
