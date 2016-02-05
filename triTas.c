#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "triTas.h"

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

//Fonction qui va allouer la mémoire nécessaire pour créer un tableau contenant l'ensemble des entiers présents dans le fichier
int* ConstruireTableau(FILE *fichier,int nbElemts) {

	//Allocation de mémoire dynamique
	int* T = (int*)malloc(nbElemts*sizeof(int)) ;

	//Déclaration des variables
	int a, i ;


	//On enregistre les entiers dans le tableau
	while (fscanf(fichier,"%d", &a ) != EOF){
		T[i] = a ;
		i++ ;
	}
	//Et on renvoit le tableau
	return T ;
}

//Fonction d'affichage du tableau (pour debogage)
void AfficherTableau(int* t,int taille){
	for (int i = 0 ; i < taille ; i++){
		printf("%d ", t[i]) ;
	}
	printf("\n") ;
}

//Fonction qui va récupérer l'indice de l'enfant gauche de la racine en position i
int EnfantGauche(int i){
	//Si i correspond à la première position du tableau, on renvoit la deuxième position
	if(i == 0) {
		return 1 ;
	}
	//Sinon on renvoit le double de l'indice de la racine i
	else {
		return 2*i ;
	}
}
//Fonction qui va récupérer l'indice de l'enfant droite de la racine en position i
int EnfantDroite(int i){   
	//Si i correspond à la première position du tableau, on renvoit la troisième position
	if(i == 0) {
		return 2 ;
	}
	//Sinon on renvoit le double de l'indice de la racine i +1
	else {
		return 2*i + 1 ;
	}
}

//Fonction qui va échanger l'adresse memoire d'un entier a avec l'adresse d'un entier b
void Echange(int* a,int* b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
}

//RECURSIF
//Fonction principale du tri par tas utilisé (Tas max, soit entier le plus grand comme racine)
//	- pour la construction initiale du tas (ConstruireTas)
//	- pour le tri dans l'ordre croissant (TriTas) 
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

//NON RECURSIF
//Fonction principale du tri par tas utilisé (Tas max, soit entier le plus grand comme racine)
//	- pour la construction initiale du tas (ConstruireTas)
//	- pour le tri dans l'ordre croissant (TriTas) 
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

//Fonction qui va appeler la fonction Tamiser pour construire le Tas initiale
//Soit correspondant à un arbre binaire complet partiellement ordonné, avec le maximum comme racine
//On fait remonter chaque élément à sa bonne place
//Ou chaque enfant est plus petit que son parent
void ConstruireTas(int* t,int taille,Pfonction Tamiser){
	//Pour construire le tas, on parcours le tableau d'entier de la moitié jusqu'au début
	//Sur la deuxième moitié du tableau ne sont stockées que les feuilles de l'arbre, qui n'ont donc pas d'enfants
	for(int i = (taille/2); i>=0; i--){
		(*Tamiser)(t,i, taille - 1) ;
	}
}

//Fonction de tri dans l'ordre croissant du Tas
//Appelle la fonction Tamiser
//On fait descendre la racine au maximum de l'arbre, via echange, puis on reconstruit l'arbre avec la nouvelle racine
//On recommence jusqu'à arriver au deuxième indice de l'arbre
void TriTas(int* t,int taille,Pfonction Tamiser){
	for(int i = (taille-1); i>=1 ; i--) {
		Echange(&t[0],&t[i]) ; // On échange le premier élément du tableau (soit le max) avec le dernier élément du tableau
		(*Tamiser)(t,0,i-1) ; //On Tamise le tableau sans prendre en compte le dernier élément déjà trié (donc nouveau tableau de taille taille-1)
	}
}