LIBS = -lpthread
TARGET = digger-server

HEADERS = connection.h generator.h
OBJECTS = $(OBJDIR)/connection.o \
	$(OBJDIR)/main.o \
	$(OBJDIR)/generator.o

EXTOBJECTS = ../../common/build/mutex.o
SCRIPT_DIR = scripts

CFLAGS += -I../../common/src

.PHONY: $(OBJDIR) staging clean

all: $(OBJDIR) $(BINDIR)/$(TARGET) staging

$(OBJDIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(TARGET): $(OBJECTS) $(BINDIR)
	$(CC) $(OBJECTS) $(EXTOBJECTS) $(LIBS) -o $@

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
