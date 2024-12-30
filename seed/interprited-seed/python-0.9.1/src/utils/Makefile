
# For "Pure" BSD Systems
# ======================
#
# "Pure" BSD systems (as opposed to enhanced BSD derivatives like SunOS)
# often miss certain standard library functions.  Source for
# these is provided, you just have to turn it on.  This may work for
# other systems as well, where these things are needed.

# If your system does not have a strerror() function in the library,
# uncomment the following two lines to use one I wrote.  (Actually, this
# is missing in most systems I have encountered, so it is turned on
# in the Makefile.  Turn it off if your system doesn't have sys_errlist.)

# STRERROR_SRC=  strerror.c
# STRERROR_OBJ=  strerror.o

# If your BSD system does not have a fmod() function in the library,
# uncomment the following two lines to use one I wrote.

#FMOD_SRC=  fmod.c
#FMOD_OBJ=  fmod.o

# If your BSD system does not have a strtol() function in the library,
# uncomment the following two lines to use one I wrote.

#STRTOL_SRC=  strtol.c
#STRTOL_OBJ=  strtol.o

# If your BSD system does not have a getcwd() function in the library,
# but it does have a getwd() function, uncomment the following two lines
# to use one I wrote.  (If you don't have getwd() either, turn on the
# NO_GETWD #define in getcwd.c.)

#GETCWD_SRC=  getcwd.c
#GETCWD_OBJ=  getcwd.o

# If your signal() function believes signal handlers return int,
# uncomment the following line.

#SIGTYPEDEF=	-DSIGTYPE=int


# BSD Time Option
# ===============
#
# This option does not add a new module but adds two functions to
# an existing module.
#
# It implements time.millisleep() and time.millitimer()
# using the BSD system calls select() and gettimeofday().
#
# Uncomment the following line to select this option.

#BSDTIMEDEF=	-DBSD_TIME


# GNU Readline Option
# ===================
#
# If you have the sources of the GNU Readline library you can have
# full interactive command line editing and history in Python.
# The GNU Readline library is distributed with the BASH shell
# (I only know of version 1.05).  You must build the GNU Readline
# library and the alloca routine it needs in their own source
# directories (which are subdirectories of the basg source directory),
# and plant a pointer to the BASH source directory in this Makefile.
#
# Uncomment and edit the following block to use the GNU Readline option.
# - Edit the definition of BASHDIR to point to the bash source tree.
# You may have to fix the definition of LIBTERMCAP; leave the LIBALLOCA
# definition commented if alloca() is in your C library.

#BASHDIR=	../../bash-1.05
#LIBREADLINE=	$(BASHDIR)/readline/libreadline.a
#LIBALLOCA=	$(BASHDIR)/alloc-files/alloca.o
#LIBTERMCAP=	-ltermcap
#RL_USE =	-DUSE_READLINE
#RL_LIBS=	$(LIBREADLINE) $(LIBALLOCA) $(LIBTERMCAP)
#RL_LIBDEPS=	$(LIBREADLINE) $(LIBALLOCA)


# STDWIN Option
# =============
#
# If you have the sources of STDWIN (by the same author) you can
# configure Python to incorporate the built-in module 'stdwin'.
# This requires a fairly recent version of STDWIN (dated late 1990).
#
# Uncomment and edit the following block to use the STDWIN option.
# - Edit the STDWINDIR defition to reflect the top of the STDWIN source
#   tree.
# - Edit the ARCH definition to reflect your system's architecture
#   (usually the program 'arch' or 'machine' returns this).
# You may have to edit the LIBX11 defition to reflect the location of
# the X11 runtime library if it is non-standard.

#STDWINDIR=	../../stdwin
#ARCH=		sgi
#LIBSTDWIN=	$(STDWINDIR)/Build/$(ARCH)/x11/lib/lib.a
#LIBX11 =	-lX11
#STDW_INCL=	-I$(STDWINDIR)/H
#STDW_USE=	-DUSE_STDWIN
#STDW_LIBS=	$(LIBSTDWIN) $(LIBX11)
#STDW_LIBDEPS=	$(LIBSTDWIN)
#STDW_SRC=	stdwinmodule.c
#STDW_OBJ=	stdwinmodule.o


# Amoeba Option
# =============
#
# If you have the Amoeba 4.0 distribution (Beta or otherwise) you can
# configure Python to incorporate the built-in module 'amoeba'.
# (Python can also be built for native Amoeba, but it requires more
# work and thought.  Contact the author.)
#
# Uncomment and edit the following block to use the Amoeba option.
# - Edit the AMOEBADIR defition to reflect the top of the Amoeba source
#   tree.
# - Edit the AM_CONF definition to reflect the machine/operating system
#   configuration needed by Amoeba (this is the name of a subdirectory
#   of $(AMOEBADIR)/conf/unix, e.g., vax.ultrix).

#AMOEBADIR=	/usr/amoeba
#AM_CONF=	mipseb.irix
#LIBAMUNIX=	$(AMOEBADIR)/conf/unix/$(AM_CONF)/lib/amunix/libamunix.a
#AM_INCL=	-I$(AMOEBADIR)/src/h
#AM_USE =	-DUSE_AMOEBA
#AM_LIBDEPS=	$(LIBAMUNIX)
#AM_LIBS=	$(LIBAMUNIX)
#AM_SRC =	amoebamodule.c sc_interpr.c sc_errors.c
#AM_OBJ =	amoebamodule.o sc_interpr.o sc_errors.o


# Silicon Graphics IRIS Options
# =============================
#
# The following three options are only relevant if you are using a
# Silicon Graphics IRIS machine.  These have been tested with IRIX 3.3.1
# on a 4D/25.


# GL Option
# =========
#
# This option incorporates the built-in module 'gl', which provides a
# complete interface to the Silicon Graphics GL library.  It adds
# about 70K to the Python text size and about 260K to the unstripped
# binary size.
#
# NOTE WHEN BUILDING FOR THE FIRST TIME:
# There is a circular dependency in the build process: you need to have
# a working Python interpreter before you can build a Python interpreter
# that incorporates the 'gl' module -- the source file 'glmodule.c' is
# not distributed (it's about 140K!) and a Python script is used to
# create it. Thus, you first have to build python without the the GL
# and Panel options, then edit the Makefile to turn them (or at least GL)
# on and rebuild. You may also have to set PYTHONPATH to point to
# the place where the module library is for the generation script to
# work.
#
# Uncomment the following block to use the GL option.

#GL_USE =	-DUSE_GL
#GL_LIBDEPS=
#GL_LIBS=	-lgl_s
#GL_SRC =	glmodule.c cgensupport.c
#GL_OBJ =	glmodule.o cgensupport.o


# Panel Option
# ============
#
# If you have source to the NASA Ames Panel Library, you can configure
# Python to incorporate the built-in module 'pnl', which is used byu
# the standard module 'panel' to provide an interface to most features
# of the Panel Library.  This option requires that you also turn on the
# GL option.  It adds about 100K to the Python text size and about 160K
# to the unstripped binary size. This requires Panel Library version 9.7
# (for lower versions you may have to remove some functionality -- send
# me the patches if you bothered to do this).
#
# Uncomment and edit the following block to use the Panel option.
# - Edit the PANELDIR definition to point to the top-level directory
#   of the Panel distribution tree.

#PANELDIR=	/usr/people/guido/src/pl
#PANELLIBDIR=	$(PANELDIR)/library
#LIBPANEL=	$(PANELLIBDIR)/lib/libpanel.a
#PANEL_USE=	-DUSE_PANEL
#PANEL_INCL=	-I$(PANELLIBDIR)/include
#PANEL_LIBDEPS=	$(LIBPANEL)
#PANEL_LIBS=	$(LIBPANEL)
#PANEL_SRC=	panelmodule.c
#PANEL_OBJ=	panelmodule.o


# Audio Option
# ============
#
# This option lets you play with /dev/audio on the IRIS 4D/25.
# It incorporates the built-in module 'audio'.
# Warning: using the asynchronous I/O facilities of this module can
# create a second 'thread', which looks in the listings of 'ps' like a
# forked child.  However, it shares its address space with the parent.
#
# Uncomment the following block to use the Audio option.

#AUDIO_USE=	-DUSE_AUDIO
#AUDIO_SRC=	audiomodule.c asa.c
#AUDIO_OBJ=	audiomodule.o asa.o

# Generated Sources
# =================
#
# Some source files are (or may be) generated.
# The rules for doing so are given here.