#On définit clean comme étant une cible particulière
.PHONY: clean
#OPTIONS
CC = gcc
OPT = -Wall -pedantic -std=c11
SRC = main
EXE = triTas
#PROFILAGE PROG
PROFILE = no
ifeq ($(PROFILE),yes)
	OPT += -pg
endif

#RULES
all: triTas.o fichier.o
	$(CC) $(OPT) -o $(EXE) $(SRC).c $^

#On ajoute les header comme étant des dépéndances des fichiers
triTas.o: triTas.h

fichier.o: fichier.h
#Pour chaque fichier .o, dépendance du .c, compilation
%.o: %.c
	$(CC) $(OPT) -c $< -o $@
#Règle pour nettoyage des objets et du binarie
clean:
	rm -f *.o $(EXE)
