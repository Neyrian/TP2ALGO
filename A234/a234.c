#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"
#include "file.h"
#include "pile.h"

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
  switch(a->t){
    case 0:
      feuilles[0]++;
      return;
    case 2:
      noeud2[0]++;
      break;
    case 3:
      noeud3[0]++;
      break;
    case 4:
      noeud4[0]++;
      break;
  }
  if (a->fils != NULL) {
    for (int i = 0; i < 4; i++){
      if (a->fils[i] != NULL){
        AnalyseStructureArbre(a->fils[i], feuilles, noeud2, noeud3, noeud4);
      }
    }
  }
}

Arbre234 noeud_max (Arbre234 a)
{
  if(a == NULL){
    return NULL;
  }

  if(a->t == 0){
    return NULL;
  }
  while (1) {
    switch (a->t) {
      case 0:
        return NULL;
      case 2:
      case 3:
        if (a->fils[2]->t != 0) {
          a = a->fils[2];
        } else {
          return a;
        }
      break;
      case 4:
        if (a->fils[3]->t != 0) {
          a = a->fils[3];
        } else {
          return a;
        }
      break;
    }
  }
}


void Afficher_Cles_Largeur (Arbre234 a)
{
  pfile_t f_act = creer_file();
  pfile_t f_fils = creer_file();
  enfiler(f_act, a);
  Arbre234 tmp;
  do {
    while (!file_vide(f_act)) {
      tmp = defiler(f_act);
      switch (tmp->t) {
        case 0:
          break;
        case 2:
          printf("%d ", tmp->cles[1]);
          enfiler(f_fils, tmp->fils[1]);
          enfiler(f_fils, tmp->fils[2]);
          break;
        case 3:
          printf("%d ", tmp->cles[0]);
          printf("%d ", tmp->cles[1]);
          enfiler(f_fils, tmp->fils[0]);
          enfiler(f_fils, tmp->fils[1]);
          enfiler(f_fils, tmp->fils[2]);
          break;
        case 4:
          printf("%d ", tmp->cles[0]);
          printf("%d ", tmp->cles[1]);
          printf("%d ", tmp->cles[2]);
          enfiler(f_fils, tmp->fils[0]);
          enfiler(f_fils, tmp->fils[1]);
          enfiler(f_fils, tmp->fils[2]);
          enfiler(f_fils, tmp->fils[3]);
          break;
      }
    }
    f_act = f_fils;
    f_fils = creer_file();
  } while (!file_vide(f_act));

  printf("\n");
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
  if(a = null || a->t == 0){
    return;
  }
  ppile_t ATraiter = creer_pile();
  empiler(ATraiter, a);
  ppile_int NbPassage = creer_pile_int();
  empiler_int(NbPassage, 0);
  Arbre234 arbreTmp;
  int tmp;
  while (!pile_vide(ATraiter)) {
    arbreTmp = depiler(ATraiter);
    tmp = depiler_int(NbPassage);
    switch(arbreTmp->t){
      case 2:
        if(tmp == 0){
          empiler(ATraiter, arbreTmp);
          empiler_int(NbPassage, 1);
          empiler(ATraiter, arbreTmp->fils[1]);
          empiler_int(NbPassage, 0);
        } else {
          printf("%d ", arbreTmp->cles[1]);
          empiler(ATraiter, arbreTmp->fils[2]);
          empiler_int(NbPassage, 0);
        }
        break;
      case 3:
        if(tmp == 0){
          empiler(ATraiter, arbreTmp);
          empiler_int(NbPassage, 1);
          empiler(ATraiter, arbreTmp->fils[0]);
          empiler_int(NbPassage, 0);
        } else if(tmp == 0){
          printf("%d ", arbreTmp->cles[1]);
          empiler(ATraiter, arbreTmp);
          empiler_int(NbPassage, 1);
          empiler(ATraiter, arbreTmp->fils[1]);
          empiler_int(NbPassage, 0);
        } else {
          printf("%d ", arbreTmp->cles[1]);
          empiler(ATraiter, arbreTmp->fils[2]);
          empiler_int(NbPassage, 0);
        }
        break;
    }
  }

}


void Detruire_Cle (Arbre234 *a, int cle)
{
  /*
    retirer la cle de l'arbre a
  */

  return ;
}
