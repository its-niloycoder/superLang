# i extreactd and modularize things from flaten source structer
# i think i can make a built in mudlues archive


BUILD = ../build
CFLAGS = -w -g -I../includes

STANDARD_OBJ= bltinmodule.o mathmodule.o moduleobject.o  posixmodule.o regexpmodule.o regexp.o sysmodule.o timemodule.o

all: $(STANDARD_OBJ)
$(STANDARD_OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $*.c -o $(BUILD)/$*.o

# Build "glmodule.c", the GL interface.
# See important note at "GL Option" above.
# You may have to set and export PYTHONPATH for this to work.
# Ignore the messages emitted by the cgen script as long as its exit
# status is zero.
# Also ignore the warnings emitted while compiling glmodule.c; it works.

glmodule.c:	cstubs cgen
		python cgen <cstubs >@glmodule.c
		mv @glmodule.c glmodule.c