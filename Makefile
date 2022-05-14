#
# Created by gmakemake (Ubuntu Jul 25 2014) on Sat May  7 00:34:06 2022
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

CFLAGS =	-std=c99 -ggdb -Wall -Wextra -Werror -ggdb -pedantic
CLIBFLAGS =	-lm

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	QueueADT.c coordinates.c maze.c mopsolver.c solver.c
PS_FILES =	
S_FILES =	
H_FILES =	QueueADT.h coordinates.h maze.h solver.h structs.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	QueueADT.o coordinates.o maze.o solver.o 

#
# Main targets
#

all:	mopsolver 

mopsolver:	mopsolver.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mopsolver mopsolver.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

QueueADT.o:	QueueADT.h structs.h
coordinates.o:	QueueADT.h coordinates.h maze.h structs.h
maze.o:	maze.h structs.h
mopsolver.o:	QueueADT.h coordinates.h maze.h solver.h structs.h
solver.o:	QueueADT.h coordinates.h maze.h solver.h structs.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) mopsolver.o core

realclean:        clean
	-/bin/rm -f mopsolver 
