CC = gcc
INCDIR = ../include
CFLAGS = -c -I$(INCDIR)
OBJDIR = ../o
DEBUG_OBJDIR = $(OBJDIR)/debug
RELEASE_OBJDIR = $(OBJDIR)/release
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/SLC_MiniBLASUT.o $(DEBUG_OBJDIR)/SLC_MiniLAUT.o \
	 $(DEBUG_OBJDIR)/SLC_GeometryUT.o $(DEBUG_OBJDIR)/SLC_NLSLGNUT.o \
	 $(DEBUG_OBJDIR)/SLC_CameraUT.o
RELEASE_OBJECTS = $(RELEASE_OBJDIR)/SLC_MiniBLASUT.o $(RELEASE_OBJDIR)/SLC_MiniLAUT.o \
	 $(RELEASE_OBJDIR)/SLC_GeometryUT.o $(RELEASE_OBJDIR)/SLC_NLSLGNUT.o \
	 $(RELEASE_OBJDIR)/SLC_CameraUT.o

.PHONY	:	debug
debug	:	$(DEBUG_OBJECTS)

$(DEBUG_OBJDIR)/SLC_MiniBLASUT.o	:	SLC_MiniBLASUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

$(DEBUG_OBJDIR)/SLC_MiniLAUT.o	:	SLC_MiniLAUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

$(DEBUG_OBJDIR)/SLC_GeometryUT.o	:	SLC_GeometryUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

$(DEBUG_OBJDIR)/SLC_NLSLGNUT.o	:	SLC_NLSLGNUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

$(DEBUG_OBJDIR)/SLC_CameraUT.o	:	SLC_CameraUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

SLC_MiniBLASUT.c	:	SLC_MiniBLASUT.pp.js SLC_MiniBLASUT.cin SLC_MiniBLASUTfoot.cin
	node $<

SLC_MiniLAUT.c	:	SLC_MiniLAUT.pp.js SLC_MiniLAUT.cin SLC_MiniLAUTfoot.cin
	node $<

SLC_GeometryUT.c	:	SLC_GeometryUT.pp.js SLC_GeometryUT.cin SLC_GeometryUTfoot.cin
	node $<

SLC_NLSLGNUT.c	:	SLC_NLSLGNUT.pp.js SLC_NLSLGNUT.cin SLC_NLSLGNUTfoot.cin
	node $<

SLC_CameraUT.c	:	SLC_CameraUT.pp.js SLC_CameraUT.cin SLC_CameraUTfoot.cin
	node $<

.PHONY	:	clean_debug
clean_debug	:
	rm -f $(DEBUG_OBJECTS)
	rm -f SLC_*.c