#include <stdio.h>
#include <stdlib.h>
#include "triTas.h"
#include <time.h>

int main(int argc, char** argv) {
	
	if(argc != 2){
		fprintf(stderr, "Veuillez préciser un nom de fichier en argument\n") ;
		exit(EXIT_FAILURE) ;
	}

	float temps ;
	clock_t t1,t2 ;

	FILE* fichier = OuvrirFichier(argv[1]) ;

	int nbElemts = GetNombreElements(fichier) ; 
	int* Tas = ConstruireTableau(fichier,nbElemts) ;
	
	fclose(fichier) ;
	//Tas utilisé pour l'appel non recursif de la fonction
	int* Tas_non_rec = Tas ;

	printf("%d éléments\n",nbElemts) ;
	AfficherTableau(Tas,nbElemts) ;

	//Partie appel recursif
	t1 = clock();

	ConstruireTas(Tas,nbElemts,Tamiser_max_rec) ;
	AfficherTableau(Tas,nbElemts) ;
	TriTas(Tas,nbElemts,Tamiser_max_rec) ;

	t2 = clock();

	AfficherTableau(Tas,nbElemts) ;

	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("temps = %f\n", temps);

	//Partie appel non recursif
	t1 = clock();

	ConstruireTas(Tas_non_rec,nbElemts,Tamiser_max) ;
	AfficherTableau(Tas_non_rec,nbElemts) ;
	TriTas(Tas_non_rec,nbElemts,Tamiser_max) ;

	t2 = clock();

	AfficherTableau(Tas_non_rec,nbElemts) ;

	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("temps = %f\n", temps);


	return EXIT_SUCCESS;
}

