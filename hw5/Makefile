#######################################################################
# Homework Assignment 5, for EECS 22, Fall 2017
#
# Author: Tim Schmidt
# Date: 11/09/2017
#
# Makefile: Makefile for HW 5 
#
#######################################################################

CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -Wall

OBJS = ImageList.o FileIO.o Image.o Movie.o MovieLab.o DIPs.o
DEBUGOBJS =  ImageList.o FileIO.o Image.o Movie.o MovieLabTest.o DIPs.o
DEPS = Image.h FileIO.h DIPs.h ImageList.h Movie.h Constants.h

DESIGN = MovieLab MovieLabTest out.yuv

all: MovieLab MovieLabTest

test: MovieLabTest

######################### Generate object files #######################
# Target for MovieLab.o
MovieLab.o: MovieLab.c $(DEPS)
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o

MovieLabTest.o: MovieLab.c $(DEPS)
	$(CC) $(CFLAGS) MovieLab.c $(DEBUG) -o MovieLabTest.o


# Target for FileIO.o 
FileIO.o: FileIO.c $(DEPS)
	$(CC) $(CFLAGS) FileIO.c  -o FileIO.o

# Target for DIPs.o
DIPs.o: DIPs.c DIPs.h $(DEPS)
	$(CC) $(CFLAGS) DIPs.c   -o DIPs.o -lm

# Target for Image.o
Image.o: Image.c $(DEPS)
	$(CC) $(CFLAGS) Image.c  -o Image.o 

# Target for ImageList.o
ImageList.o: ImageList.c $(DEPS)
	$(CC) $(CFLAGS) ImageList.c  -o ImageList.o

# Target for Movie.o
Movie.o: Movie.c $(DEPS)
	$(CC) $(CFLAGS) Movie.c  -o Movie.o

######################### Generate the executable #####################
# Target for MovieLab
MovieLab: $(OBJS) $(DEPS)
	$(CC) $(LFLAGS) -ansi -std=c99 $(OBJS) -o MovieLab -lm

MovieLabTest: $(DEBUGOBJS) $(DEPS)
        $(CC) $(LFLAGS) -ansi -std=c99 $(OBJS) $(DEBUG) -o MovieLabTest -lm

###############################  others  ##############################
# Target for clean-up
clean:
	rm -f *.o *.jpg $(DESIGN)  
