#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "triTas.h"

FILE* OuvrirFichier(char* f){
	FILE *fichier ;

	if ((fichier = fopen(f, "r")) == NULL) {
		fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", f) ;
		exit(EXIT_FAILURE) ;
	}	

	return fichier ;
}

int GetNombreElements(FILE *fichier){
	int c ;
	int nLignes = 0 ;
	int c2 = '\0' ;
 
	while((c=fgetc(fichier)) != EOF){
		if(c == '\n') {
			nLignes++ ;
		}
		c2 = c ;
	}
 
	/* Ici, c2 est égal au caractère juste avant le EOF. */
	if(c2 != '\n'){
		nLignes++ ; /* Dernière ligne non finie */
	}
 
	rewind(fichier) ;
	return nLignes ;
}

int* ConstruireTableau(FILE *fichier,int nbElemts) {

	int* T = (int*)malloc(nbElemts*sizeof(int)) ;

	int a, i ;


	//On enregistre les entiers dans le tableau
	while (fscanf(fichier,"%d", &a ) != EOF){
		T[i] = a ;
		i++ ;
	}

	return T ;
}

void AfficherTableau(int* t,int taille){
	for (int i = 0 ; i < taille ; i++){
		printf("%d ", t[i]) ;
	}
	printf("\n") ;
}

int EnfantGauche(int i){
	if(i == 0) {
		return 1 ;
	}
	else {
		return 2*i ;
	}
}

int EnfantDroite(int i){   
	if(i == 0) {
		return 2 ;
	}
	else {
		return 2*i + 1 ;
	}
}

void Echange(int* a,int* b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
}

void Tamiser_max_rec(int* t,int element,int taille){
	int pos_max ;
	//On récupère les enfants de la racine element
	int gauche = EnfantGauche(element) ;
	int droite = EnfantDroite(element) ;

	//Si la position de l'enfant gauche ne correspond pas à la dernière du tableau, alors element a deux enfants
	//On détermine la plus grande valeur des deux enfants
	if((gauche < taille) && (t[gauche] > t[droite])){
		pos_max = gauche ;
	}
	else {
		pos_max = droite ;
	}
	//Et on compare ce max avec la racine
	if(t[element] > t[pos_max]){
		pos_max = element ;
	}
	//Si le maximum des trois valeurs (racine, enfant gauche, enfant droite) n'est pas la racine
	//On procède à l'échange de la valeur de la racine et du maximum
	//Le maximum devient la nouvelle racine
	if(pos_max != element) {
		Echange(&t[element],&t[pos_max]) ;
		//Puis on fait un appel recursif à la fonction en précisant l'ancienne position du maximum
		Tamiser_max_rec(t, pos_max, taille) ;
	}
	
}

void Tamiser_max(int* t,int element,int taille){
	int k = element ; //Correspond à la position de la racine
	int j = EnfantGauche(k) ; //Correspond à la position de l'enfant gauche de la racine

	//On continue tant que j est inférieur ou égal à la taille du tas
	//En cas d'échange, on va effectuer la même vérification avec les anciens enfants du max calculé
	while(j <= taille) {
		//On determine lequel des enfants (gauche ou droite) de k a la plus grande valeur
		//Uniquement si il y'a deux enfants à comparer (si l'indice de l'enfant gauche n'est pas le dernier élément du tableau)
		if((j<taille) && (t[j] < t[j+1])){
			j++ ;
		}
		// On teste ensuite ce max contre k
		if(t[k] < t[j]){
			//Si le max est plus grand que k, on fait remonter ce max à la position de k (echange)
			Echange(&t[k],&t[j]) ;
			//Et on détermine l'indice de la racine comme étant à la position de son ancien enfant
			k = j ;
			j = EnfantGauche(k) ;
			//Au prochain tour de boucle, on comparera les enfants du max (gauche ou droite) avec la racine à leur nouveau père (ancienne racine)
		}
		else { 
			break ; //On break car il n'y a pas eu d'échange, le tas n'a pas été modifié, il n'y a pas besoin de vérifier les autres valeur
		}
	}
}

void ConstruireTas(int* t,int taille,Pfonction Tamiser){
	//Pour construire le tas, on parcours le tableau d'entier de la moitié jusqu'au début
	//Sur la deuxième moitié du tableau ne sont stockées que les feuilles de l'arbre, qui n'ont donc pas d'enfants
	for(int i = (taille/2); i>=0; i--){
		(*Tamiser)(t,i, taille - 1) ;
	}
}

void TriTas(int* t,int taille,Pfonction Tamiser){
	for(int i = (taille-1); i>=1 ; i--) {
		Echange(&t[0],&t[i]) ; // On échange le premier élément du tableau (soit le max) avec le dernier élément du tableau
		(*Tamiser)(t,0,i-1) ; //On Tamise le tableau sans prendre en compte le dernier élément déjà trié (donc nouveau tableau de taille taille-1)
	}
}