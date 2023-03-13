CC = gcc
INCDIR = ../include
CFLAGS = -c -I$(INCDIR)
OBJDIR = ../o
DEBUG_OBJDIR = $(OBJDIR)/debug
RELEASE_OBJDIR = $(OBJDIR)/release
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/SLC_Array.o $(DEBUG_OBJDIR)/SLC_RingBuffer.o
RELEASE_OBJECTS = $(RELEASE_OBJDIR)/SLC_Array.o $(RELEASE_OBJDIR)/SLC_RingBuffer.o

.PHONY	:	debug
debug	:	$(DEBUG_OBJECTS)

$(DEBUG_OBJDIR)/SLC_Array.o	:	SLC_Array.c $(INCDIR)/SLC/SLC_Array.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(DEBUG_OBJDIR)/SLC_RingBuffer.o	:	SLC_RingBuffer.c $(INCDIR)/SLC/SLC_RingBuffer.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

SLC_RingBuffer.c	:	SLC_RingBuffer.pp.js SLC_RingBuffer.ci*
	node $<

$(INCDIR)/SLC/SLC_RingBuffer.h	:	SLC_RingBuffer.pp.js SLC_RingBuffer.hi*
	node $<

.PHONY	:	clean_debug
clean_debug	:
	rm -f $(DEBUG_OBJECTS)
	rm -f $(INCDIR)/SLC/SLC_RingBuffer.h
