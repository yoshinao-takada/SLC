CC = gcc
INCDIR = ../include
CFLAGS = -c -I$(INCDIR)
OBJDIR = ../o
DEBUG_OBJDIR = $(OBJDIR)/debug
RELEASE_OBJDIR = $(OBJDIR)/release
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/SLC_Numbers.o $(DEBUG_OBJDIR)/SLC_NumbersCopy.o \
	$(DEBUG_OBJDIR)/SLC_DLink.o

.PHONY	:	debug
debug	:	$(DEBUG_OBJECTS)

$(DEBUG_OBJDIR)/SLC_Numbers.o	:	SLC_Numbers.c $(INCDIR)/SLC/SLC_Numbers.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(DEBUG_OBJDIR)/SLC_NumbersCopy.o	:	SLC_NumbersCopy.c $(INCDIR)/SLC/SLC_NumbersCopy.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

SLC_NumbersCopy.c	:	SLC_NumbersCopy.pp.js SLC_NumbersCopy.cin
	node $<

$(INCDIR)/SLC/SLC_NumbersCopy.h	:	SLC_NumbersCopy.pp.js SLC_NumbersCopy.hin
	node $<

$(DEBUG_OBJDIR)/SLC_DLink.o	:	SLC_DLink.c $(INCDIR)/SLC/SLC_DLink.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY	:	clean_debug
clean_debug	:
	rm -f $(DEBUG_OBJECTS)
	rm -f $(INCDIR)/SLC/SLC_NumbersCopy.h

