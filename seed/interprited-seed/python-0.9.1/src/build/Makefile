# Choose one of the following two lines depending on whether your system
# requires the use of 'ranlib' after creating a library, or not.

#RANLIB =	true	# For System V
RANLIB =	ranlib	# For BSD

LIBOBJECTS= $(wildcard *.o)


LIB = pythonlib.a


libpython.a:	$(LIBOBJECTS)
		-rm -f @libpython.a
		ar cr @libpython.a $(LIBOBJECTS)
		$(RANLIB) @libpython.a
		mv @libpython.a libpython.a

clean:
	-rm *.o *.a