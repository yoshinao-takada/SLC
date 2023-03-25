CC = gcc
INCDIR = ../include
CFLAGS = -c -I$(INCDIR)
OBJDIR = ../o
DEBUG_OBJDIR = $(OBJDIR)/debug
RELEASE_OBJDIR = $(OBJDIR)/release
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/SLC_NumbersUT.o $(DEBUG_OBJDIR)/SLC_NumbersCopyUT.o \
	$(DEBUG_OBJDIR)/SLC_DLinkUT.o $(DEBUG_OBJDIR)/SLC_TestUT.o
RELEASE_OBJECTS = $(RELEASE_OBJDIR)/SLC_NumbersUT.o $(RELEASE_OBJDIR)/SLC_NumbersCopyUT.o \
	$(RELEASE_OBJDIR)/SLC_DLinkUT.o $(RELEASE_OBJDIR)/SLC_TestUT.o

.PHONY	:	debug
debug	:	$(DEBUG_OBJECTS)

$(DEBUG_OBJDIR)/SLC_NumbersUT.o	:	SLC_NumbersUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

$(DEBUG_OBJDIR)/SLC_NumbersCopyUT.o	:	SLC_NumbersCopyUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

$(DEBUG_OBJDIR)/SLC_DLinkUT.o	:	SLC_DLinkUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

$(DEBUG_OBJDIR)/SLC_TestUT.o	:	SLC_TestUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

SLC_NumbersCopyUT.c	:	SLC_NumbersCopyUT.pp.js SLC_NumbersCopyUT.cin
	node $<

.PHONY	:	clean_debug
clean_debug	:
	rm -f $(DEBUG_OBJECTS)
	rm -f SLC_NumbersCopyUT.c