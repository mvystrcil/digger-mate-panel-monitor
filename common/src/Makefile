LIBS = -lpthread

HEADERS = mutex.h
OBJECTS = $(OBJDIR)/mutex.o

.PHONY: $(OBJDIR) staging clean

all: $(OBJDIR) $(OBJECTS)

$(OBJDIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(TARGET): $(OBJECTS) $(BINDIR)
	$(CC) $(OBJECTS) $(LIBS) -o $@

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
