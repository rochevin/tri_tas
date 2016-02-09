#include <stdio.h>
#include <stdlib.h>
#include "triTas.h"

//Fonction qui va allouer la mémoire nécessaire pour créer un tableau contenant l'ensemble des entiers présents dans le fichier
//Et remplir le tableau avec les entiers
int* ConstruireTableau(FILE *fichier,int nbElemts) {

	//Allocation de mémoire dynamique
	int* T = (int*)malloc(nbElemts*sizeof(int)) ;

	//Déclaration des variables
	int a, i = 0 ;


	//On enregistre les entiers dans le tableau tant qu'on est pas arrivé à la fin du fichier
	while (fscanf(fichier,"%d", &a ) != EOF){
		T[i] = a ;
		i++ ;
	}
	//Et on renvoit le tableau
	return T ;
}

//Fonction d'affichage du tableau, utilisé lorsque l'option -o n'est pas précisée
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
	int tmp=*a; //On déclare un entier égal à l'entier pointé par a
	*a=*b; //On remplace la valeur du pointeur a par la valeur pointée par b
	*b=tmp; //Puis on remplace la valeur pointée par b par tmp
}

//RECURSIF
//Fonction principale du tri par tas utilisé (Tas max, soit entier le plus grand comme racine)
//	- pour la construction initiale du tas (ConstruireTas)
//	- pour le tri dans l'ordre croissant (TriTas) 
void Tamiser_max_rec(int* t,int racine,int taille){
	int pos_max ; //On déclare un entier qui va contenir le maximum
	//On récupère les enfants de la racine
	int gauche = EnfantGauche(racine) ;
	int droite = EnfantDroite(racine) ;

	//Si la position de l'enfant gauche ne correspond pas à la dernière du tableau, alors racine a deux enfants
	//On détermine la plus grande valeur entre la racine et l'enfant gauche
	if((gauche <= taille) && (t[gauche] > t[racine])){
		pos_max = gauche ;
	}
	else {
		pos_max = racine ;
	}
	//Puis la plus grande valeur entre l'enfant droite et le maximum (soit gauche soit racine)
	if((droite <= taille) && (t[droite] > t[pos_max])){
		pos_max = droite ;
	}
	//Si le maximum des trois valeurs (racine, enfant gauche, enfant droite) n'est pas la racine
	//On procède à l'échange de la valeur de la racine et du maximum
	//Le maximum devient la nouvelle racine
	if(pos_max != racine) {
		Echange(&t[racine],&t[pos_max]) ;
		//Puis on fait un appel recursif à la fonction en précisant l'ancienne position du maximum
		Tamiser_max_rec(t, pos_max, taille) ;
	}
}


//ITERATIF
//Fonction principale du tri par tas utilisé (Tas max, soit entier le plus grand comme racine)
//	- pour la construction initiale du tas (ConstruireTas)
//	- pour le tri dans l'ordre croissant (TriTas) 
void Tamiser_max(int* t,int racine,int taille){
	int pos_max ; //On définit un variable qui contiendra la valeur de l'enfant (gauche au début de la boucle)

	//On continue tant que l'enfant gauche de la racine est inférieur ou égal à la taille du tas
	//En cas d'échange entre un enfant et la racine, on va effectuer la même vérification avec les anciens enfants du premier et le second
	while(EnfantGauche(racine) <= taille) {
		pos_max = EnfantGauche(racine) ; //On déclare la position max comme étant l'enfant gauche
		//On determine lequel des enfants (gauche ou droite) de racine a la plus grande valeur
		//Uniquement si il y'a deux enfants à comparer (si l'indice de l'enfant gauche n'est pas le dernier élément du tableau)
		if((pos_max<taille) && (t[pos_max] < t[pos_max+1])){
			pos_max++ ;
		}
		// On teste ensuite ce max contre racine
		if(t[racine] < t[pos_max]){
			//Si le max est plus grand que racine, on fait remonter ce max à la position de racine (echange)
			Echange(&t[racine],&t[pos_max]) ;
			//Et on détermine l'indice de la racine comme étant à la position de son ancien enfant
			racine = pos_max ;
			//Au prochain tour de boucle, on comparera les enfants du max (gauche ou droite) avec la racine à leur nouveau père (ancienne racine)
		}
		else { 
			break ; //On break car il n'y a pas eu d'échange, le tas n'a pas été modifié, il n'y a pas besoin de vérifier les noeuds inférieurs
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
//On recommence jusqu'à arriver au deuxième indice de l'arbre (la première valeur étant déjà forcement triée)
void TriTas(int* t,int taille,Pfonction Tamiser){
	for(int i = (taille-1); i>0 ; i--) {
		Echange(&t[0],&t[i]) ; // On échange le premier élément du tableau (soit le max) avec le dernier élément du tableau
		(*Tamiser)(t,0,i-1) ; //On Tamise le tableau sans prendre en compte le dernier élément déjà trié (donc nouveau tableau de taille taille-1)
	}
}
