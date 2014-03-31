LIBS = $(shell pkg-config --libs libxml-2.0) -lpthread
TARGET = digger-client

HEADERS = logger.h connection.h
OBJECTS = $(OBJDIR)/connection.o $(OBJDIR)/main.o
SCRIPT_DIR = scripts

.PHONY: $(OBJDIR) clean

all: $(OBJDIR) $(BINDIR)/$(TARGET)

$(OBJDIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(TARGET): $(OBJECTS) $(BINDIR)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

$(OBJDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR)
	rm -f *~
