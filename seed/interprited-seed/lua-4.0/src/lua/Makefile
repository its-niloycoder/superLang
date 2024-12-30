# makefile for Lua interpreter

LUA= ../..

include $(LUA)/config

EXTRA_DEFS= $(POSIX)

OBJS= nlang.o
SRCS= nlang.c

T= $(BIN)/nlang

all: $T

$T: $(OBJS) $(LIB)/liblua.a $(LIB)/liblualib.a
	$(CC) -o $@ $(OBJS) -L$(LIB) -llua -llualib $(EXTRA_LIBS)

$(LIB)/liblua.a:
	cd ..; $(MAKE)

$(LIB)/liblualib.a:
	cd ../lib; $(MAKE)

clean:
	rm -f $(OBJS) $T