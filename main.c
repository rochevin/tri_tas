#include <stdio.h>
#include <stdlib.h>
#include "triTas.h"
#include <time.h>

int main(int argc, char** argv) {
	
	//Si on a pas au moins le nom du programme, un nom de fichier en argument et un nom de fichier de sortie, on quitte le programme
	if(argc < 3){
		fprintf(stderr, "Veuillez préciser un nom de fichier en argument\n") ;
		exit(EXIT_FAILURE) ;
	}

	//Partie qui va servir à calculer le temps d'execution des fonctions
	float temps ;
	clock_t t1,t2 ;

	//On ouvre le fichier portant le nom donné en argument
	FILE* fichier = OuvrirFichier(argv[1]) ;

	//On détermine son nombre d'éléments
	int nbElemts = GetNombreElements(fichier) ;
	//Puis on construit le tableau à partir des entiers contenus dans le fichier 
	int* Tas = ConstruireTableau(fichier,nbElemts) ;
	//On ferme le fichier
	fclose(fichier) ;

	//Puisqu'on modifie directement le tableau, on le duplique pour l'appel non recursif
	//Tas utilisé pour l'appel non recursif de la fonction
	int* Tas_non_rec = Tas ;

	//On affiche le nombre d'élements, puis le tableau
	printf("%d éléments\n",nbElemts) ;
	//AfficherTableau(Tas,nbElemts) ;

	//Partie appel recursif
	t1 = clock();

	ConstruireTas(Tas,nbElemts,Tamiser_max_rec) ;
	//AfficherTableau(Tas,nbElemts) ;
	TriTas(Tas,nbElemts,Tamiser_max_rec) ;

	t2 = clock();

	//AfficherTableau(Tas,nbElemts) ;
	EcrireFichier(argv[2],Tas,nbElemts) ;

	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("temps = %f\n", temps);

	//On libère l'espace mémoire alloué pour le Tas trié puisqu'il ne sert plus
	free(Tas) ;

	//Partie appel non recursif
	t1 = clock();

	ConstruireTas(Tas_non_rec,nbElemts,Tamiser_max) ;
	//AfficherTableau(Tas_non_rec,nbElemts) ;
	TriTas(Tas_non_rec,nbElemts,Tamiser_max) ;

	t2 = clock();

	//AfficherTableau(Tas_non_rec,nbElemts) ;

	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("temps = %f\n", temps);


	return EXIT_SUCCESS;
}

