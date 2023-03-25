CC = gcc
INCDIR = ../include
CFLAGS = -c -I$(INCDIR)
OBJDIR = ../o
DEBUG_OBJDIR = $(OBJDIR)/debug
RELEASE_OBJDIR = $(OBJDIR)/release
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/SLC_MiniBLAS.o $(DEBUG_OBJDIR)/SLC_MiniLA.o \
	$(DEBUG_OBJDIR)/SLC_Geometry.o

.PHONY	:	debug
debug	:	$(DEBUG_OBJECTS)

$(DEBUG_OBJDIR)/SLC_MiniBLAS.o	:	SLC_MiniBLAS.c $(INCDIR)/SLC/SLC_MiniBLAS.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

$(DEBUG_OBJDIR)/SLC_MiniLA.o	:	SLC_MiniLA.c $(INCDIR)/SLC/SLC_MiniLA.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

$(DEBUG_OBJDIR)/SLC_Geometry.o	:	SLC_Geometry.c $(INCDIR)/SLC/SLC_Geometry.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

SLC_MiniBLAS.c	:	SLC_MiniBLAS.pp.js SLC_MiniBLAS.cin
	node $<

$(INCDIR)/SLC/SLC_MiniBLAS.h	:	SLC_MiniBLAS.pp.js SLC_MiniBLAS.hin
	node $<

SLC_MiniLA.c	:	SLC_MiniLA.pp.js SLC_MiniLA.cin
	node $<

$(INCDIR)/SLC/SLC_MiniLA.h	:	SLC_MiniLA.pp.js SLC_MiniLA.hin
	node $<

SLC_Geometry.c	:	SLC_Geometry.pp.js SLC_Geometry.cin
	node $<

$(INCDIR)/SLC/SLC_Geometry.h	:	SLC_Geometry.pp.js SLC_Geometry.hin
	node $<


.PHONY	:	clean_debug
clean_debug	:
	rm -f $(DEBUG_OBJECTS)
	rm -f $(INCDIR)/SLC/SLC_Mini*.h $(INCDIR)/SLC/SLC_Geometry.h
	rm -f SLC_Mini*.c SLC_Geometry.c