#ifndef __TRITAS__
#define __TRITAS__
typedef void (*Pfonction)(int*,int,int);

int* ConstruireTableau(FILE *,int) ;
void AfficherTableau(int*,int) ;
int EnfantGauche(int) ;
int EnfantDroite(int) ;
void Echange(int*,int*) ;
void Tamiser_max_rec(int*,int,int) ;
void Tamiser_max_rec_2(int*,int,int) ;
void Tamiser_max(int*,int,int) ;
void ConstruireTas(int*,int,Pfonction) ;
void TriTas(int*,int,Pfonction) ;

#endif
