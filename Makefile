.PHONY: clean
CC = gcc
OPT = -Wall -pedantic -std=c11
SRC = main
EXE = triTas

all: triTas.o fichier.o
	$(CC) $(OPT) -o $(EXE) $(SRC).c $^

triTas.o: triTas.h

fichier.o: fichier.h

%.o: %.c
	$(CC) $(OPT) -c $< -o $@

clean:
	rm -f *.o $(EXE)
