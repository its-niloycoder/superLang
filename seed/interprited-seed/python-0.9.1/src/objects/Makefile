BUILD = ../build
CFLAGS = -w -g -I../includes

STANDARD_OBJ=  classobject.o dictobject.o fileobject.o floatobject.o frameobject.o funcobject.o intobject.o listobject.o methodobject.o   stringobject.o tupleobject.o typeobject.o

all: $(STANDARD_OBJ)
$(STANDARD_OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $*.c -o $(BUILD)/$*.o

# xxobject.c is a boiler plate code for new object type