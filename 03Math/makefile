CC = gcc
INCDIR = ../include
CFLAGS = -c -I$(INCDIR)
OBJDIR = ../o
DEBUG_OBJDIR = $(OBJDIR)/debug
RELEASE_OBJDIR = $(OBJDIR)/release
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/SLC_MiniBLAS.o $(DEBUG_OBJDIR)/SLC_MiniLA.o \
	$(DEBUG_OBJDIR)/SLC_Geometry.o $(DEBUG_OBJDIR)/SLC_NLSLGN.o \
	$(DEBUG_OBJDIR)/SLC_Shapes.o $(DEBUG_OBJDIR)/SLC_Polyline.o

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

$(DEBUG_OBJDIR)/SLC_NLSLGN.o	:	SLC_NLSLGN.c $(INCDIR)/SLC/SLC_NLSLGN.h $(INCDIR)/SLC/SLC_NLSL.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

$(DEBUG_OBJDIR)/SLC_Shapes.o	:	SLC_Shapes.c $(INCDIR)/SLC/SLC_Shapes.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(CFLAGS) -g -o $@ $<

$(DEBUG_OBJDIR)/SLC_Polyline.o	:	SLC_Polyline.c $(INCDIR)/SLC/SLC_Polyline.h
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

SLC_NLSLGN.c	:	SLC_NLSLGN.pp.js SLC_NLSLGN.cin
	node $<

$(INCDIR)/SLC/SLC_NLSLGN.h	:	SLC_NLSLGN.pp.js SLC_NLSLGN.hin
	node $<

$(INCDIR)/SLC/SLC_NLSL.h	:	SLC_NLSL.pp.js SLC_NLSL.hin
	node $<

SLC_Polyline.c	:	SLC_Polyline.pp.js SLC_Polyline.cin
	node $<
	
$(INCDIR)/SLC/SLC_Polyline.h	:	SLC_Polyline.pp.js SLC_Polyline.hin
	node $<

.PHONY	:	clean_debug
clean_debug	:
	rm -f $(DEBUG_OBJECTS)
	rm -f $(INCDIR)/SLC/SLC_Mini*.h $(INCDIR)/SLC/SLC_Geometry.h
	rm -f SLC_Mini*.c SLC_Geometry.c