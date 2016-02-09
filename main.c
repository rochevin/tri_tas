#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include "triTas.h"
#include "fichier.h"

//Fonction qui affiche la bonne utilisation du programme
void prog_usage(char* progname){
	fprintf(stderr, "Usage: %s [-r (recursive usage)] [-i input file name (non optional)] [-o output file name (optional)]\n", progname) ;
	exit(EXIT_FAILURE) ;
}

//Fonction principale
int main(int argc, char** argv) {
	
	//Definition des variables pour getopt
	int option ;
	char *input_file = NULL, *output_file = NULL , *type = "itérative" ;
	Pfonction Tamiser = Tamiser_max ; //Définit un pointeur de fonction pour le choix recursif ou non, par défaut 
	//Parsing de getopt
	while ((option = getopt(argc , argv, "i:o:rh")) != -1){
    	switch (option) {
			case 'i':
				input_file = optarg ; //On récupère le nom du fichier qui contient la liste d'entiers
				break ;
			case 'o':
				output_file = optarg ; //On récupère le nom du fichier de sortie
				break ;
			case 'r':
				type = "récursive" ;
				Tamiser = Tamiser_max_rec ; //dans le cas ou l'utilisateur selectionne -r, on utilise la fonction recursive
				break ;
			case 'h':
				prog_usage(argv[0]) ; //On print l'utilisation du programme dans le cas ou l'utilisateur utilise la commande h
				break ;
			case '?':
				prog_usage(argv[0]) ; //On print l'utilisation du programme dans le cas ou un argument inconnu est utilisé
				break ;
    	}
	}

	//On print l'utilisation du programme si input_file vaut NULL
	if(input_file == NULL){
		prog_usage(argv[0]) ;
	}

	//Sinon on peut lancer le programme
	//On affiche le type de la fonction de tri utilisée : itérative ou récursive
	fprintf(stderr, "MESSAGE : Utilisation %s du programme\n",type) ;

	//Partie qui va servir à calculer le temps d'execution des fonctions
	float temps ;
	clock_t t1,t2 ;

	//On ouvre le fichier portant le nom donné en argument
	FILE* fichier = OuvrirFichier(input_file) ;

	//On détermine son nombre d'éléments
	int nbElemts = GetNombreElements(fichier) ;

	//Puis on construit le tableau à partir des entiers contenus dans le fichier 
	int* Tas = ConstruireTableau(fichier,nbElemts) ;

	//On ferme le fichier
	fclose(fichier) ;

	//On affiche le nombre d'élements, puis le tableau
	fprintf(stderr, "MESSAGE : %d éléments à traiter\n",nbElemts) ;



	t1 = clock(); //Capture le temps avant l'éxecution du programme

	ConstruireTas(Tas,nbElemts,Tamiser) ; //Construction du tas initial (max) à partir du tableau (Équivalent fonction insertion)

	TriTas(Tas,nbElemts,Tamiser) ; //Tri à partir du Tas max

	t2 = clock(); //Capture le temps après l'éxecution du programme

	//Affichage du temps d'éxecution du programme
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	fprintf(stderr, "MESSAGE : Temps d'éxecution = %f secondes\n", temps);

	//Ecriture du fichier de sortie
	if(output_file == NULL) {
		fprintf(stderr, "MESSAGE : Affichage du tri sur sortie standard\n") ;
		AfficherTableau(Tas,nbElemts) ;
	}
	else {
		EcrireFichier(output_file,Tas,nbElemts) ;
		fprintf(stderr, "MESSAGE : Tri enregistré dans \"%s\"\n",output_file) ;
	}

	free(Tas) ; //Libération de l'espace mémoire (optionnel)

	return EXIT_SUCCESS;
}

