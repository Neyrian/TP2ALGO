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

  for(int i = 0; i < a->t; i++){
    res += NombreCles(a->fils[i]);
  }

  return res;
}

int CleMax (Arbre234 a)
{
  /*
     plus grande cle de l'arbre a
  */

  return 0 ;
}

int CleMin (Arbre234 a)
{
  /*
     Retourne plus petite cle de l'arbre a
  */

  return 0 ;
}

Arbre234 RechercherCle (Arbre234 a, int cle)
{
  if(a == NULL){
    return NULL;
  }

  if(a->t == 0){
    return NULL;
  }

  int i;
  for (i = 0; i<a->t-1;i++) {
    int cle_act = a->cles[i];
    if(cle_act == cle){
      return a;
    }
    if(cle_act < cle){
      return RechercherCle(a->fils[i],cle);
    }
  }
  return RechercherCle(a->fils[i],cle);
}

void AnalyseStructureArbre (Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4)
{
  /*
     calculer le nombre de feuilles, de 2-noeuds, 3-noeuds,et 4-noeuds
  */
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
  /*
     Afficher les cles en ordre croissant
     Cette fonction sera recursive
  */

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
