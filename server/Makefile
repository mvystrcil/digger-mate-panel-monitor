LIBS = $(shell pkg-config --libs libxml-2.0) -lpthread
CC = gcc
CFLAGS = -g -Wall
TARGET = digger-client

HEADERS = reader.h logger.h connection.h
OBJECTS = reader.o connection.o main.o

all: $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	rm -f *.o
	rm -f $(TARGET)