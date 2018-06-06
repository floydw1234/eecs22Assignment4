
#Makefile: PhotoLab

all: PhotoLab PhotoLabTest

test: PhotoLabTest
	./PhotoLabTest

clean:
	rm -f *.o
	rm -f PhotoLab
	rm -f PhotoLabTest

libFilter.a: DIPs.o Advanced.o
	ar rc libFilter.a DIPs.o Advanced.o
	ranlib libFilter.a


PhotoLabTest: PhotoLabTest.o Advanced.o DIPs.o FileIO.o
	gcc -Wall -ansi -g -std=c99 PhotoLabTest.o -lfilter -L.  FileIO.o -o PhotoLabTest

PhotoLab: PhotoLab.o FileIO.o libFilter.a
    gcc -Wall -ansi -std=c99 PhotoLab.o -lfilter -L.  FileIO.o -o PhotoLab



FileIO.o: FileIO.c FileIO.h Constants.h
    gcc -Wall -ansi -std=c99 -c FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
    gcc -Wall -ansi -std=c99 -c DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h Constants.h
    gcc -Wall -ansi -std=c99 -c Advanced.c -o Advanced.o

PhotoLab.o: PhotoLab.c Advanced.h FileIO.h DIPs.h Constants.h
	gcc -Wall -g  -ansi -std=c99 -c PhotoLab.c -o PhotoLab.o

PhotoLabTest.o: PhotoLab.c Advanced.h FileIO.h DIPs.h Constants.h
	gcc PhotoLab.c -g -Wall -ansi -std=c99 -c -D DEBUG -o PhotoLabTest.o
