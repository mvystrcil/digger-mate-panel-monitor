LIBS = $(shell pkg-config --libs libxml-2.0) -lpthread
CC = gcc
CFLAGS = -g -Wall
TARGET = digger-server

HEADERS = logger.h connection.h generator.h
OBJECTS = connection.o main.o generator.o

all: $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	rm -f *.o
	rm -f $(TARGET)
	rm -f *~
