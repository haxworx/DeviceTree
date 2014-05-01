include_dir=/usr/local/include/ofapi

LIBNAME = libofapi.so
SONAME = $(LIBNAME).0
SOVERSION = $(SONAME).0.0

default:
	gcc -g -Wall -D_REENTRANT -DPIC -fpic -Wl,-soname -Wl,$(SONAME) lib/*.c -shared -o $(SOVERSION)

install:
	cp $(SOVERSION) /usr/local/lib
	ln -s /usr/local/lib/$(SOVERSION) /usr/local/lib/$(SONAME)
	ln -s /usr/local/lib/$(SOVERSION) /usr/local/lib/$(LIBNAME)
	test -d "$(include_dir)" || mkdir "$(include_dir)"
	cp lib/*.h $(include_dir)

all:
	make default
	make install
	make examples

examples:
	make -C example/

clean:
	make -C example/ clean 
	rm -f libofapi.so.*
