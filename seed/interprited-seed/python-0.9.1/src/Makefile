# You don't have to rebuild all objects when you turn on options;
# all dependencies
# are concentrated in the file "config.c" which is rebuilt whenever
# the Makefile changes.  (Except if you turn on the GNU Readline option
# you may have to toss out the tokenizer.o object.)


# Operating System Defines (ALWAYS READ THIS)
# ===========================================

# Uncomment the following line if you are using a System V derivative.
# This must be used, for instance, on an SGI IRIS.  Don't use it for
# SunOS.  (This is only needed by posixmodule.c...)

#SYSVDEF=	-DSYSV



# If your system doesn't have symbolic links, uncomment the following
# line.

#NOSYMLINKDEF=	-DNO_LSTAT


# Installation Options
# ====================

# You may want to change DEFPYTHONPATH to reflect where you install the
# Python module library. The default contains "../lib" so running
# the interpreter from the source/build directory as distributed will
# find the library (admittedly a hack).

DEFPYTHONPATH= .:/usr/local/lib/python:../lib


# Further porting hints
# =====================
#
# If you don't have the header file <string.h>, but you do have
# <strings.h>, create a file "string.h" in this directory which contains
# the single line "#include <strings.h>", and add "-I." to CFLAGS.
# If you don't have the functions strchr and strrchr, add definitions
# "-Dstrchr=index -Dstrrchr=rindex" to CFLAGS.  (NB: CFLAGS is not
# defined in this Makefile.)

CFLAGS = -w -g -I./includes

# Configurable Options
# ====================
#
# Python can be configured to interface to various system libraries that
# are not available on all systems.  It is also possible to configure
# the input module to use the GNU Readline library for interactive
# input.  For each configuration choice you must uncomment the relevant
# section of the Makefile below.  Note: you may also have to change a
# pathname and/or an architecture identifier that is hardcoded in the
# Makefile.
#
# Read the comments to determine if you can use the option.  (You can
# always leave all options off and build a minimal portable version of
# Python.)

# Main Targets
# ============

all: python

SUBDIRS = core parser grammer stubCode modules objects 
submodules:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done

python:	clean libpython.a pythonmain.o config.o Makefile
		$(CC) $(CFLAGS) pythonmain.o config.o  build/libpython.a -lm -o python
# NB: the ordering of items in LIBS is significant!

libpython.a: submodules
	$(MAKE) -C build



# Utility Targets
# ===============

clean::
		-rm -f *.o python
		$(MAKE) clean -C build


## regular source build
pythonmain.o:
	$(CC) $(CFLAGS) -c $*.c -o $*.o

## auto configered source build
# Mafefile is added because makefile is also a source file and it get change
# and for rebuild things makefile is added in dependency list
config.o: config.c Makefile 
		$(CC) -c $(CFLAGS) '-DPYTHONPATH="$(DEFPYTHONPATH)"' $*.c

# genarated source build ; this like like featching data and genarat source accoding to data


# The dependencies for graminit.[ch] are not turned on in the
# distributed Makefile because the files themselves are distributed.
# Turn them on if you want to hack the grammar.

#graminit.c graminit.h:	Grammar python_gen
#		python_gen Grammar