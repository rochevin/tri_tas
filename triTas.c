#include <stdio.h>
#include <stdlib.h>
#include "triTas.h"

//Fonction qui va allouer la mémoire nécessaire pour créer un tableau contenant l'ensemble des entiers présents dans le fichier
int* ConstruireTableau(FILE *fichier,int nbElemts) {

	//Allocation de mémoire dynamique
	int* T = (int*)malloc(nbElemts*sizeof(int)) ;

	//Déclaration des variables
	int a, i = 0 ;


	//On enregistre les entiers dans le tableau
	while (fscanf(fichier,"%d", &a ) != EOF){
		T[i] = a ;
		i++ ;
	}
	//Et on renvoit le tableau
	return T ;
}

//Fonction d'affichage du tableau
void AfficherTableau(int* t,int taille){
	for (int i = 0 ; i < taille ; i++){
		printf("%d\n", t[i]) ;
	}
}

//Fonction qui va récupérer l'indice de l'enfant gauche de la racine en position i
int EnfantGauche(int i){
	return 2*i+1 ;
}
//Fonction qui va récupérer l'indice de l'enfant droite de la racine en position i
int EnfantDroite(int i){   
	return 2*i+2 ;
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
	//On détermine la plus grande valeur entre la racine et l'enfant gauche
	if((gauche <= taille) && (t[gauche] > t[element])){
		pos_max = gauche ;
	}
	else {
		pos_max = element ;
	}
	//Puis la plus grande valeur entre l'enfant droite et le maximum (soit gauche soit racine)
	if((droite <= taille) && (t[droite] > t[pos_max])){
		pos_max = droite ;
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


//ITERATIF
//Fonction principale du tri par tas utilisé (Tas max, soit entier le plus grand comme racine)
//	- pour la construction initiale du tas (ConstruireTas)
//	- pour le tri dans l'ordre croissant (TriTas) 
void Tamiser_max(int* t,int element,int taille){
	int racine = element ; //Correspond à la position de la racine
	int enfant ; //On définit un variable qui contiendra la valeur de l'enfant (gauche au début de la boucle)

	//On continue tant que l'enfant droite est inférieur ou égal à la taille du tas
	//Soit on continue tant que l'index maximum possible à chaque itération ne dépasse pas l'index max du tas
	//En cas d'échange, on va effectuer la même vérification avec les anciens enfants du max calculé
	while(2*racine+1 <= taille) {
		enfant = EnfantGauche(racine) ;
		//On determine lequel des enfants (gauche ou droite) de racine a la plus grande valeur
		//Uniquement si il y'a deux enfants à comparer (si l'indice de l'enfant gauche n'est pas le dernier élément du tableau)
		if((enfant<taille) && (t[enfant] < t[enfant+1])){
			enfant++ ;
		}
		// On teste ensuite ce max contre racine
		if(t[racine] < t[enfant]){
			//Si le max est plus grand que racine, on fait remonter ce max à la position de racine (echange)
			Echange(&t[racine],&t[enfant]) ;
			//Et on détermine l'indice de la racine comme étant à la position de son ancien enfant
			racine = enfant ;
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
	for(int i = (taille-1)/2; i>=0; i--){
		(*Tamiser)(t,i, taille-1) ;
	}
}

//Fonction de tri dans l'ordre croissant du Tas
//Appelle la fonction Tamiser
//On fait descendre la racine au maximum de l'arbre, via echange, puis on reconstruit l'arbre avec la nouvelle racine
//On recommence jusqu'à arriver au deuxième indice de l'arbre
void TriTas(int* t,int taille,Pfonction Tamiser){
	for(int i = (taille-1); i>0 ; i--) {
		Echange(&t[0],&t[i]) ; // On échange le premier élément du tableau (soit le max) avec le dernier élément du tableau
		(*Tamiser)(t,0,i-1) ; //On Tamise le tableau sans prendre en compte le dernier élément déjà trié (donc nouveau tableau de taille taille-1)
	}
}
