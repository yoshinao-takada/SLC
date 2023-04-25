CC = gcc
INCDIR = ../include
CFLAGS = -c -I$(INCDIR)
OBJDIR = ../o
DEBUG_OBJDIR = $(OBJDIR)/debug
RELEASE_OBJDIR = $(OBJDIR)/release
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/SLC_Log.o $(DEBUG_OBJDIR)/SLC_pixmap.o \
	$(DEBUG_OBJDIR)/SLC_PNG.o

.PHONY	:	debug
debug	:	$(DEBUG_OBJECTS)

$(DEBUG_OBJDIR)/SLC_Log.o	:	SLC_Log.c $(INCDIR)/SLC/SLC_Log.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

$(INCDIR)/SLC/SLC_Log.h	:	SLC_Log.pp.js SLC_Log.hin SLC_LogHead.hin
	node $<

$(DEBUG_OBJDIR)/SLC_pixmap.o	:	SLC_pixmap.c $(INCDIR)/SLC/SLC_pixmap.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

$(DEBUG_OBJDIR)/SLC_PNG.o	:	SLC_PNG.c $(INCDIR)/SLC/SLC_PNG.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

.PHONY	:	clean_debug
clean_debug	:
	rm -f $(DEBUG_OBJECTS)
	rm -f $(INCDIR)/SLC/SLC_Log.h