#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
typedef struct tab{
  float tab[140][10];
  int pos[140][10];
} Tpos;
typedef struct mini{
  int * tmini;
  int * ind;
} Mini;
typedef struct serial{
  float val;
  int num;
} Serial;

Tpos distance(FILE*,FILE*);//Fait la distance euclidienne entre tout les termes
Tpos tri_tab(Tpos);//Tri le tableau de manière croissante
int * remplirtab_class(FILE*,int);//Convertit les fichiers label en tableau
void affichetab(Tpos);//Affiche le tableau (optionnel)
int max3(int,int,int);//Fonction aiguillage
void k_ppv(int,Tpos,int*,int*,FILE*);//Algorithme k_ppv
