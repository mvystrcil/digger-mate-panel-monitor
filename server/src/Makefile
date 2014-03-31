LIBS = -lpthread
TARGET = digger-server

HEADERS = logger.h connection.h generator.h
OBJECTS = $(OBJDIR)/connection.o $(OBJDIR)/main.o $(OBJDIR)/generator.o
SCRIPT_DIR = scripts

.PHONY: $(OBJDIR) staging clean

all: $(OBJDIR) $(BINDIR)/$(TARGET) staging

$(OBJDIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(TARGET): $(OBJECTS) $(BINDIR)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

$(OBJDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $(BINDIR)

staging:
	mkdir -p $(BINDIR)/$(SCRIPT_DIR)
	cp -r ../$(SCRIPT_DIR)/* $(BINDIR)/$(SCRIPT_DIR)/.

clean:
	rm -rf $(OBJDIR)
	rm -f *~
