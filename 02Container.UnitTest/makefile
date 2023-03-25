CC = gcc
INCDIR = ../include
CFLAGS = -c -I$(INCDIR)
OBJDIR = ../o
DEBUG_OBJDIR = $(OBJDIR)/debug
RELEASE_OBJDIR = $(OBJDIR)/release
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/SLC_ArrayUT.o $(DEBUG_OBJDIR)/SLC_RingBufferUT.o
RELEASE_OBJECTS = $(RELEASE_OBJDIR)/SLC_ArrayUT.o $(RELEASE_OBJDIR)/SLC_RingBufferUT.o

.PHONY	:	debug
debug	:	$(DEBUG_OBJECTS)

$(DEBUG_OBJDIR)/SLC_ArrayUT.o	:	SLC_ArrayUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

$(DEBUG_OBJDIR)/SLC_RingBufferUT.o	:	SLC_RingBufferUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

SLC_RingBufferUT.c	:	SLC_RingBufferUT.pp.js SLC_RingBufferUT.cin SLC_RingBufferUTfoot.cin
	node $<

.PHONY	:	clean_debug
clean_debug	:
	rm -f $(DEBUG_OBJECTS)
	rm -f SLC_RingBufferUT.c