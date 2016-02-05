#include <stdio.h>
#include <stdlib.h>



//Fonction d'ouverture d'un fichier f en mode lecture
FILE* OuvrirFichier(char* f){
	FILE *fichier ;

	//Ouverture du fichier
	if ((fichier = fopen(f, "r")) == NULL) {
		//si fopen renvoit NULL, CaD que le fichier n'a pas été ouvert, on ferme le programme
		fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", f) ;
		exit(EXIT_FAILURE) ;
	}	

	//On renvoit le pointeur vers le fichier
	return fichier ;
}

//Fonction d'écriture dans un fichier f, d'un tableau t de taille taille
void EcrireFichier(char* f,int* t,int taille){
	FILE *fichier ;

	//Ouverture du fichier en mode écriture
	if ((fichier = fopen(f, "w")) == NULL) {
		//si fopen renvoit NULL, CaD que le fichier n'a pas été ouvert, on ferme le programme
		fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", f) ;
		exit(EXIT_FAILURE) ;
	}
	//On écrit chaque élément du tableau dans le fichier suivit d'un saut de ligne
	for (int i = 0 ; i < taille ; i++){
		fprintf(fichier,"%d\n",t[i]) ;
	}
	//fermeture du fichier
	fclose(fichier) ;
}

//Fonction qui va calculer le nombre d'éléments dans un fichier
//En comptant le nombre de saut de ligne
int GetNombreElements(FILE *fichier){
	int c ;
	int nLignes = 0 ;
	int c2 = '\0' ;

	//Tant qu'on est pas arrivé au caractère fin de fichier
	//On enregistre un seul caractère dans la variable c
	while((c=fgetc(fichier)) != EOF){
		if(c == '\n') {
			//Dans le cas ou ce caractère est un saut de ligne, on ajoute +1 au compteur
			nLignes++ ;
		}
		//On enregistre le caractère dans une variable à chaque fois
		//On aura donc à la fin du fichier le dernier caractère
		c2 = c ;
	}
 
	//Si ce caractère n'est pas un saut de ligne
	//On rajoute +1 au ocmpteur
	if(c2 != '\n'){
		nLignes++ ;
	}

	//On remet le pointeur au début du fichier
	rewind(fichier) ;
	//Et on renvoit le nombre de lignes
	return nLignes ;
}