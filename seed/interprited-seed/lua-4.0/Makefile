LUA= .
include $(LUA)/config

all:
	mkdir lib bin
	cd src/lua; $(MAKE) $@

clean:
	rm -r lib bin
	cd src; $(MAKE) $@
	cd src/lib; $(MAKE) $@
	cd src/lua; $(MAKE) $@