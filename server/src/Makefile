LIBS = $(shell pkg-config --libs libxml-2.0) -lpthread
CC = gcc
CFLAGS = -g -Wall -Werror
TARGET = digger-server
OBJDIR = ../build

HEADERS = logger.h connection.h generator.h
OBJECTS = $(OBJDIR)/connection.o $(OBJDIR)/main.o $(OBJDIR)/generator.o

all: $(OBJDIR) $(OBJDIR)/$(TARGET)

$(OBJDIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	rm -f *.o
	rm -f $(TARGET)
	rm -f *~
