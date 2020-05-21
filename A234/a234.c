#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"

#define max(a,b) ((a)>(b)?(a):(b))


int hauteur (Arbre234 a)
{
  int h0, h1, h2, h3 ;

  if (a == NULL)
    return 0 ;

  if (a->t == 0)
    return 0 ;

  h0 = hauteur (a->fils [0]) ;
  h1 = hauteur (a->fils [1]) ;
  h2 = hauteur (a->fils [2]) ;
  h3 = hauteur (a->fils [3]) ;

  return 1 + max (max (h0,h1),max (h2,h3)) ;
}

int NombreCles (Arbre234 a)
{
  if(a == NULL){
    return 0;
  }

  if(a->t == 0){
    return 0;
  }

  int res = a->t - 1;

  for(int i = 0; i < 4; i++){
    res += NombreCles(a->fils[i]);
  }

  return res;
}

int CleMax (Arbre234 a)
{
  if ((a == NULL) || (a->t == 0)){
    return 0;
  }
  switch(a->t){
    case 2:
    case 3:
      if (a->fils[2]->t == 0) {
        return a->cles[1];
      }
      return CleMax(a->fils[2]);
    case 4:
      if (a->fils[3]->t == 0) {
          return a->cles[2];
      }
      return CleMax(a->fils[3]);
  }
  return 0;
}

int CleMin (Arbre234 a)
{
  if ((a == NULL) || (a->t == 0)){
    return 0;
  }
  switch(a->t){
    case 2:
      if (a->fils[1]->t == 0) {
          return a->cles[1];
      }
      return CleMin(a->fils[1]);
    case 3:
    case 4:
      if (a->fils[0]->t == 0) {
          return a->cles[0];
      }
      return CleMin(a->fils[0]);
  }
  return 0;
}

Arbre234 RechercherCle (Arbre234 a, int cle)
{
  if(a == NULL){
    return NULL;
  }

  int i;

  switch(a->t){
    case 0:
      return NULL;
    case 2:
      if(cle == a->cles[1]){
        return a;
      }
      if(cle < a->cles[1]){
        return RechercherCle(a->fils[1], cle);
      }
      return RechercherCle(a->fils[2], cle);
    default:
      for (i = 0; i<a->t-1;i++) {
        int cle_act = a->cles[i];
        if(cle_act == cle){
          return a;
        }
        if(cle_act > cle){
          return RechercherCle(a->fils[i], cle);
        }
      }
      return RechercherCle(a->fils[i], cle);
  }
}

void AnalyseStructureArbre (Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4)
{
  if (a == NULL){
    return;
  }
}

Arbre234 noeud_max (Arbre234 a)
{
  /*
    Retourne le noeud avec la somme maximale des cles internes
  */

  return NULL ;
}


void Afficher_Cles_Largeur (Arbre234 a)
{
  /*
    Afficher le cles de l'arbre a avec
    un parcours en largeur
  */

  return ;
}

void Affichage_Cles_Triees_Recursive (Arbre234 a)
{
  if(a == NULL){
    return;
  }

  switch (a->t){
    case 0:
      return;
    case 2:
      Affichage_Cles_Triees_Recursive(a->fils[1]);
      printf("%d\n", a->cles[1]);
      Affichage_Cles_Triees_Recursive(a->fils[2]);
      return;
    case 3:
      Affichage_Cles_Triees_Recursive(a->fils[0]);
      printf("%d\n", a->cles[0]);
      Affichage_Cles_Triees_Recursive(a->fils[1]);
      printf("%d\n", a->cles[1]);
      Affichage_Cles_Triees_Recursive(a->fils[2]);
      return;
    case 4:
      Affichage_Cles_Triees_Recursive(a->fils[0]);
      printf("%d\n", a->cles[0]);
      Affichage_Cles_Triees_Recursive(a->fils[1]);
      printf("%d\n", a->cles[1]);
      Affichage_Cles_Triees_Recursive(a->fils[2]);
      printf("%d\n", a->cles[2]);
      Affichage_Cles_Triees_Recursive(a->fils[3]);
      return;
  }
  return;
}

void Affichage_Cles_Triees_NonRecursive (Arbre234 a)
{
    /*
     Afficher les cles en ordre croissant
     Cette fonction ne sera pas recursive
     Utiliser une pile
  */

}


void Detruire_Cle (Arbre234 *a, int cle)
{
  /*
    retirer la cle de l'arbre a
  */

  return ;
}
