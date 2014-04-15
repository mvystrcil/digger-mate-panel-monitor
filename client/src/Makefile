LIBS = $(shell pkg-config --libs libxml-2.0) -lpthread
TARGET = digger-client

HEADERS = connection.h parser.h
OBJECTS = $(OBJDIR)/connection.o $(OBJDIR)/main.o $(OBJDIR)/parser.o
SCRIPT_DIR = scripts

CFLAGS +=-I../../common/src/

.PHONY: $(OBJDIR) clean

all: $(OBJDIR) $(BINDIR)/$(TARGET)

$(OBJDIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(TARGET): $(OBJECTS) $(BINDIR)
	$(CC) $(OBJECTS) $(LIBS) -o $@

$(OBJDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR)
	rm -f *~
