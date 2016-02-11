#ifndef __TRITAS__
#define __TRITAS__
//Définition du pointeur de fonction pour Tamiser_max et Tamiser_max_rec
typedef void (*Pfonction)(int*,int,int);

//En-tête des fonctions
int* ConstruireTableau(FILE *,int) ;
void AfficherTableau(int*,int) ;
int EnfantGauche(int) ;
int EnfantDroite(int) ;
void Echange(int*,int*) ;
void Tamiser_max_rec(int*,int,int) ;
void Tamiser_max(int*,int,int) ;
void ConstruireTas(int*,int,Pfonction) ;
void TriTas(int*,int,Pfonction) ;

#endif
