ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif
all: main.o dirinfo.o
	gcc -o program main.o dirinfo.o
main.o: main.c dirinfo.h
	gcc -c main.c dirinfo.h
dirinfo.o: dirinfo.c dirinfo.h
	gcc -c dirinfo.c dirinfo.h
run:
	./program
clean:
	rm program *.o