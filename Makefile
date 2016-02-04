CC = gcc
OPT = -Wall -pedantic -std=c11
OBJ = triTas.o
SRC = main
EXE = triTas

all: triTas.o
	$(CC) $(OPT) -o $(EXE) $(SRC).c $(OBJ)

triTas.o: triTas.c triTas.h
	$(CC) $(OPT) -c triTas.c

clean:
	rm -f *.o $(EXE)
