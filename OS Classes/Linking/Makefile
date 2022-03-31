CC=gcc
CFLAGS1=-Wall -Werror -Wextra
CFLAGS2=-Wall -fPIC

SRC=src
LIB=lib
OUT=out/exe
DLIB=dLib

slibr:	
	cd $(LIB)/ && \
	$(CC) $(CFLAGS1) -c *.c && \
	ar rs lib.a *.o

# -shared flag generates a shared object which, at the moment to be compiled with another object file, it could be linked to form an executable file. -Wl,options passes options to linker: in this case, -soname, to indicate the binary api compatibility of the library (0, by default). -o flag saves the output library in a file with a given name — libcalc.so.
dlibr:
	cd $(DLIB)/ && \
	$(CC) $(CFLAGS2) -c *.c  && \
	$(CC) $(CFLAGS) -fPIC -shared -o libprinter.so printer.c -lc
# $(CC) -shared -Wl,-soname,libprinter.so -o libprinter.so *.o

build:
	cp -v $(LIB)/lib.a $(SRC)/
	cp -v $(DLIB)/libprinter.so $(SRC)/
	sudo cp -v $(DLIB)/libprinter.so /usr/lib # installing the shared library
	sudo ldconfig
#mkdir -p out
	cd src && \
	$(CC) $(CFLAGS1) -c main.c && \
	$(CC) $(CFLAGS1) -o runner main.o lib.a -L. -lprinter

run:
	./src/runner

all:
	make slibr
	make dlibr
	make build
	make run

clean:
	rm */*.o */*.a src/libprinter.so src/runner dlib/*.so
	ls /usr/lib/ | grep libprinter
	sudo rm /usr/lib/libprinter.so