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
  if (a == NULL || a->t == 0){
    return;
  }
  switch(a->t){
    case 2:
      (*noeud2)++;
      break;
    case 3:
      (*noeud3)++;
      break;
    case 4:
      (*noeud4)++;
      break;
  }
  if (a->fils != NULL && a->fils[1]->t == 0) {
    (*feuilles) += a->t;
    return;
  }

  if (a->fils != NULL) {
    for (int i = 0; i < 4; i++){
        AnalyseStructureArbre(a->fils[i], feuilles, noeud2, noeud3, noeud4);
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
  if(a == NULL || a->t == 0){
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
        } else if(tmp == 1){
          printf("%d ", arbreTmp->cles[0]);
          empiler(ATraiter, arbreTmp);
          empiler_int(NbPassage, 2);
          empiler(ATraiter, arbreTmp->fils[1]);
          empiler_int(NbPassage, 0);
        } else {
          printf("%d ", arbreTmp->cles[1]);
          empiler(ATraiter, arbreTmp->fils[2]);
          empiler_int(NbPassage, 0);
        }
        break;
      case 4:
        if(tmp == 0){
          empiler(ATraiter, arbreTmp);
          empiler_int(NbPassage, 1);
          empiler(ATraiter, arbreTmp->fils[0]);
          empiler_int(NbPassage, 0);
        } else if(tmp == 1){
          printf("%d ", arbreTmp->cles[0]);
          empiler(ATraiter, arbreTmp);
          empiler_int(NbPassage, 2);
          empiler(ATraiter, arbreTmp->fils[1]);
          empiler_int(NbPassage, 0);
        } else if(tmp == 2){
          printf("%d ", arbreTmp->cles[1]);
          empiler(ATraiter, arbreTmp);
          empiler_int(NbPassage, 3);
          empiler(ATraiter, arbreTmp->fils[2]);
          empiler_int(NbPassage, 0);
        } else {
          printf("%d ", arbreTmp->cles[2]);
          empiler(ATraiter, arbreTmp->fils[3]);
          empiler_int(NbPassage, 0);
        }
        break;
      default:
        break;
    }
  }
  printf("\n");

}


void Retirer_Cle(Arbre234 a, int cle){
  switch(a->t){
    case 3:
      for(int i = 0; i<2; i++){
        if(a->cles[i] == cle){
          a->cles[i] = a->cles[i+1];
          cle = a->cles[i];
        }
      }
      a->cles[2] = a->cles[1];
      a->cles[1] = a->cles[0];
      a->t = 2;
      return;
    case 4:
      for(int i = 0; i<3; i++){
        if(a->cles[i] == cle){
          a->cles[i] = a->cles[i+1];
          cle = a->cles[i];
        }
      }
      a->t = 3;
      return;
  }
}

Arbre234 Rechercher_Voisin(Arbre234 a, Arbre234 parent){
  switch(parent->t){
    case 2:
      if(parent->fils[1] == a){
        return parent->fils[2];
      } else {
        return parent->fils[1];
      }
    case 3:
      for(int i = 0; i<2; i++){
        if(parent->fils[i] == a){
          return parent->fils[i+1];
        }
      }
      return parent->fils[1];
    case 4:
      for(int i = 0; i<3; i++){
        if(parent->fils[i] == a){
          return parent->fils[i+1];
        }
      }
      return parent->fils[2];
  }
  return NULL;
}

void Detruire_Cle_Noeud_Feuille(Arbre234 a, Arbre234 parent, int cle){
  Arbre234 Voisin;
  int tmp;
  int tmp_voisin;
  int tmp_parent;
  switch(a->t){
    case 2:
      Voisin = Rechercher_Voisin(a, parent);
      switch(parent->t){
        case 2:
         if(Voisin->cles[0] > a->cles[1]){
            tmp = Voisin->cles[0];
            Retirer_Cle(Voisin, tmp);
            tmp_parent = parent->cles[1];
            parent->cles[1] = tmp;
            a->cles[1] = tmp_parent;
          } else {
            tmp = Voisin->cles[Voisin->t-2];
            Retirer_Cle(Voisin, tmp);
            tmp_parent = parent->cles[1];
            parent->cles[1] = tmp;
            a->cles[1] = tmp_parent;
          }
          return;
        case 3:
          switch(Voisin->t){
            case 2:
              if (parent->fils[0] == a || parent->fils[0] == Voisin){
                tmp = parent->cles[0];
                parent->t = 2;
              } else {
                tmp = parent->cles[1];
                parent->cles[1] = parent->cles[0];
                parent->t = 2;
              }
              if(a->cles[1]<tmp){
                Voisin->cles[0] = tmp;
                Voisin->t = 3;
              } else {
                Voisin->cles[0] = Voisin->cles[1];
                Voisin->cles[1] = tmp;
                Voisin->t = 3;
              }
              return;
            case 3:
              for(int i = 0; i<3; i++){
                if (parent->fils[i] == a || parent->fils[i] == Voisin){
                  tmp = parent->cles[i];
                  if (a->cles[1] < tmp){
                    tmp_voisin = Voisin->cles[0];
                    Voisin->t = 2;
                  } else {
                    tmp_voisin = Voisin->cles[1];
                    Voisin->cles[1] = Voisin->cles[0];
                    Voisin->t = 2;
                  }
                  parent->cles[i] = tmp_voisin;
                  a->cles[1] = tmp;
                  return;
                }
              }
              return;
            case 4:
              for(int i = 0; i<3; i++){
                if (parent->fils[i] == a || parent->fils[i] == Voisin){
                  tmp = parent->cles[i];
                  if (a->cles[1] < tmp){
                    tmp_voisin = Voisin->cles[0];
                    Voisin->cles[0] = Voisin->cles[1];
                    Voisin->cles[1] = Voisin->cles[2];
                    Voisin->t = 3;
                  } else {
                    tmp_voisin = Voisin->cles[2];
                    Voisin->t = 3;
                  }
                  parent->cles[i] = tmp_voisin;
                  a->cles[1] = tmp;
                  return;
                }
              }
            }
          case 4:
            switch(Voisin->t){
              case 2:
                if (parent->fils[0] == a || parent->fils[0] == Voisin){
                  tmp = parent->cles[0];
                  parent->cles[0] = parent->cles[1];
                  parent->cles[1] = parent->cles[2];
                  parent->t = 3;
                } else if (parent->fils[1] == a || parent->fils[1] == Voisin){
                  tmp = parent->cles[1];
                  parent->cles[1] = parent->cles[2];
                  parent->t = 3;
                } else {
                  tmp = parent->cles[2];
                  parent->t = 3;
                }
                  if(a->cles[1]<tmp){
                    Voisin->cles[0] = tmp;
                    Voisin->t = 3;
                  } else {
                    Voisin->cles[0] = Voisin->cles[1];
                    Voisin->cles[1] = tmp;
                    Voisin->t = 3;
                  }
                return;
              case 3:
                for(int i = 0; i<3; i++){
                  if (parent->fils[i] == a || parent->fils[i] == Voisin){
                    tmp = parent->cles[i];
                    if (a->cles[1] < tmp){
                      tmp_voisin = Voisin->cles[0];
                      Voisin->t = 2;
                    } else {
                      tmp_voisin = Voisin->cles[1];
                      Voisin->cles[1] = Voisin->cles[0];
                      Voisin->t = 2;
                    }
                    parent->cles[i] = tmp_voisin;
                    a->cles[1] = tmp;
                    return;
                  }
                }
                return;
              case 4:
                for(int i = 0; i<3; i++){
                  if (parent->fils[i] == a || parent->fils[i] == Voisin){
                    tmp = parent->cles[i];
                    if (a->cles[1] < tmp){
                      tmp_voisin = Voisin->cles[0];
                      Voisin->cles[0] = Voisin->cles[1];
                      Voisin->cles[1] = Voisin->cles[2];
                      Voisin->t = 3;
                    } else {
                      tmp_voisin = Voisin->cles[2];
                      Voisin->t = 3;
                    }
                    parent->cles[i] = tmp_voisin;
                    a->cles[1] = tmp;
                    return;
                  }
                }
              }
      }
    case 3:
    case 4:
      Retirer_Cle(a, cle);
      return;
  }
}

void Detruire_Cle_Noeud_Pas_Feuille(Arbre234 a, int cle){
  int newVal;
  int indice_fils;
  switch (a->t) {
    case 2:
      newVal = CleMin(a->fils[2]);
      a->cles[1] = newVal;
      Detruire_Cle(&(a->fils[2]), newVal);
      return;
    case 3:
      if (a->cles[0] == cle) {
        indice_fils = 1;
      } else {
        indice_fils = 2;
      }
      newVal = CleMin(a->fils[indice_fils]);
      a->cles[indice_fils - 1] = newVal;
      Detruire_Cle(&(a->fils[indice_fils]), newVal);
      return;
    case 4:
      if (a->cles[0] == cle) {
        indice_fils = 1;
      } else if (a->cles[1] == cle){
        indice_fils = 2;
      } else {
        indice_fils = 3;
      }
      newVal = CleMin(a->fils[indice_fils]);
      a->cles[indice_fils - 1] = newVal;
      Detruire_Cle(&(a->fils[indice_fils]), newVal);
      return;
  }
  return;
}

void Detruire_Cle_Rec (Arbre234 a, Arbre234 parent, int cle){
    if(a == NULL){
      return;
    }
    int i;
    switch(a->t){
      case 0:
        return;
      case 2:
        if(cle == a->cles[1]){
          if (a->fils[1]->t == 0){
            Detruire_Cle_Noeud_Feuille(a, parent, cle);
          } else {
            Detruire_Cle_Noeud_Pas_Feuille(a, cle);
          }
          return;
        }
        if(cle < a->cles[1]){
          Detruire_Cle_Rec(a->fils[1], a, cle);
          return;
        } else {
          Detruire_Cle_Rec(a->fils[2], a, cle);
          return;
        }
      case 3:
        for (i = 0; i<a->t-1;i++) {
          int cle_act = a->cles[i];
          if(cle_act == cle){
            if (a->fils[1]->t == 0){
              Detruire_Cle_Noeud_Feuille(a, parent, cle);
            } else {
              Detruire_Cle_Noeud_Pas_Feuille(a, cle);
            }
            return;
          }
          if(cle_act > cle){
            Detruire_Cle_Rec(a->fils[i], a, cle);
            return;
          }
        }
        Detruire_Cle_Rec(a->fils[2], a, cle);
        return;
      case 4:
        for (i = 0; i<a->t-1;i++) {
          int cle_act = a->cles[i];
          if(cle_act == cle){
            if (a->fils[1]->t == 0){
              Detruire_Cle_Noeud_Feuille(a, parent, cle);
            } else {
                Detruire_Cle_Noeud_Pas_Feuille(a, cle);
            }
            return;
          }
          if(cle_act > cle){
            Detruire_Cle_Rec(a->fils[i], a, cle);
            return;
          }
        }
        Detruire_Cle_Rec(a->fils[3], a, cle);
        return;
    }
  return ;
}

void fusion2noeud(Arbre234 a) {
  a->cles[0] = a->fils[1]->cles[1];
  a->cles[2] = a->fils[2]->cles[1];
  Arbre234 tmp;
  tmp = a->fils[1];
  a->fils[0] = tmp->fils[1];
  a->fils[1] = tmp->fils[2];
  tmp = a->fils[2];
  a->fils[2] = tmp->fils[1];
  a->fils[3] = tmp->fils[2];
  a->t = 4;
}

void Equilibrage(Arbre234 a, Arbre234 racine) {
  int newVal;
  Arbre234 newArbre;
  Arbre234 newArbre2;
  switch (a->t) {
    case 2:
      if (a->fils[1]->t != 0) {
        if (a->fils[1]->t == 2 && a->fils[2]->t == 2) {
          fusion2noeud(a);
          Equilibrage(racine, racine);
          return;
        } else if (hauteur(a->fils[1]) == hauteur(a->fils[2])) {
          Equilibrage(a->fils[1], racine);
          Equilibrage(a->fils[2], racine);
        } else {
          if (hauteur(a->fils[1]) < hauteur(a->fils[2])) {
            newVal = CleMin(a->fils[2]);
            newArbre = NULL;
            ajouter_cle(&newArbre, a->fils[1]->cles[0], 0,NULL);
            ajouter_cle(&newArbre, a->fils[1]->cles[1], 0, NULL);
            a->fils[1]->cles[1] = a->fils[1]->cles[2];
            a->fils[1]->fils[1] = newArbre;
            newArbre2 = NULL;
            ajouter_cle(&newArbre2, a->cles[1], 0, NULL);
            a->fils[1]->fils[2] = newArbre2;
            a->cles[1] = newVal;
            a->fils[1]->t = 2;
            Detruire_Cle(&(a->fils[2]), newVal);
          } else {
            newVal = CleMax(a->fils[1]);
            newArbre = NULL;
            ajouter_cle(&newArbre, a->cles[1], 0,NULL);
            ajouter_cle(&newArbre, a->fils[2]->cles[0], 0,NULL);
            a->fils[2]->fils[1] = newArbre;
            newArbre2 = NULL;
            ajouter_cle(&newArbre2, a->fils[2]->cles[2], 0,NULL);
            a->fils[2]->fils[2] = newArbre2;
            a->cles[1] = newVal;
            a->fils[2]->t = 2;
            Detruire_Cle(&(a->fils[1]), newVal);
          }
        }
      }
      return;
    case 3:
      if (a->fils[1]->t != 0) {
        if ((hauteur(a->fils[1]) == hauteur(a->fils[2])) && (hauteur(a->fils[0]) == hauteur(a->fils[2]))) {
          Equilibrage(a->fils[0], racine);
          Equilibrage(a->fils[1], racine);
          Equilibrage(a->fils[2], racine);
        } else {
          for (int i = 0; i < 2; i ++) {
            if (hauteur(a->fils[i]) < hauteur(a->fils[i+1])) {
              newVal = CleMin(a->fils[i+1]);
              newArbre = NULL;
              ajouter_cle(&newArbre, a->fils[i]->cles[0],0, NULL);
              ajouter_cle(&newArbre, a->fils[i]->cles[1], 0,NULL);
              a->fils[i]->cles[1] = a->fils[i]->cles[2];
              a->fils[i]->fils[1] = newArbre;
              newArbre2 = NULL;
              ajouter_cle(&newArbre2, a->cles[0], 0,NULL);
              a->fils[i]->fils[2] = newArbre2;
              a->cles[0] = newVal;
              a->fils[i]->t = 2;
              Detruire_Cle(&(a->fils[i+1]), newVal);
              return;
            }
          }
          newVal = CleMax(a->fils[1]);
          newArbre = NULL;
          ajouter_cle(&newArbre, a->cles[1], 0,NULL);
          a->fils[2]->fils[1] = newArbre;
          newArbre2 = NULL;
          ajouter_cle(&newArbre2, a->fils[2]->cles[1], 0,NULL);
          ajouter_cle(&newArbre2, a->fils[2]->cles[2], 0,NULL);
          a->fils[2]->fils[2] = newArbre2;
          a->cles[1] = newVal;
          a->fils[2]->t = 2;
          Detruire_Cle(&(a->fils[1]), newVal);
        }
      }
      return;
    case 4:
      if (a->fils[1]->t != 0) {
        if ((hauteur(a->fils[1]) == hauteur(a->fils[2])) && (hauteur(a->fils[0]) == hauteur(a->fils[2])) && (hauteur(a->fils[0]) == hauteur(a->fils[3]))) {
          Equilibrage(a->fils[0], racine);
          Equilibrage(a->fils[1], racine);
          Equilibrage(a->fils[2], racine);
          Equilibrage(a->fils[3], racine);
        } else {
          for (int i = 0; i < 3; i ++) {
            if (hauteur(a->fils[i]) < hauteur(a->fils[i+1])) {
              newVal = CleMin(a->fils[i+1]);
              newArbre = NULL;
              ajouter_cle(&newArbre, a->fils[i]->cles[0], 0,NULL);
              ajouter_cle(&newArbre, a->fils[i]->cles[1], 0,NULL);
              a->fils[i]->cles[1] = a->fils[i]->cles[2];
              a->fils[i]->fils[1] = newArbre;
              newArbre2 = NULL;
              ajouter_cle(&newArbre2, a->cles[0], 0,NULL);
              a->fils[i]->fils[2] = newArbre2;
              a->cles[0] = newVal;
              a->fils[i]->t = 2;
              Detruire_Cle(&(a->fils[i+1]), newVal);
              return;
            }
          }
          newVal = CleMax(a->fils[2]);
          newArbre = NULL;
          ajouter_cle(&newArbre, a->cles[1], 0,NULL);
          a->fils[3]->fils[1] = newArbre;
          newArbre2 = NULL;
          ajouter_cle(&newArbre2, a->fils[3]->cles[1], 0,NULL);
          ajouter_cle(&newArbre2, a->fils[3]->cles[2], 0,NULL);
          a->fils[3]->fils[2] = newArbre2;
          a->cles[1] = newVal;
          a->fils[3]->t = 2;
          Detruire_Cle(&(a->fils[2]), newVal);
        }
      }
      return;
  }

}
void Detruire_Cle (Arbre234 *a, int cle)
{
  switch((*a)->t){
    case 0:
      return;
    case 2:
      if ((*a)->cles[1]<cle){
        Detruire_Cle_Rec ((*a)->fils[2], (*a), cle);
      } else if ((*a)->cles[1] > cle){
        Detruire_Cle_Rec ((*a)->fils[1], (*a), cle);
      } else {
        Detruire_Cle_Rec ((*a), (*a), cle);
      }
      Equilibrage((*a), (*a));
      return;
    case 3:
      for(int i = 0; i<2; i++){
        if ((*a)->cles[i] > cle){
          Detruire_Cle_Rec ((*a)->fils[i], (*a), cle);
          Equilibrage((*a), (*a));
          return;
        } else if ((*a)->cles[i] == cle) {
          Detruire_Cle_Rec ((*a), (*a), cle);
          Equilibrage((*a), (*a));
          return;
        }
      }
      Detruire_Cle_Rec((*a)->fils[2], (*a), cle);
      Equilibrage((*a), (*a));
      return;
    case 4:
      for(int i = 0; i<3; i++){
        if((*a)->cles[i] > cle){
          Detruire_Cle_Rec ((*a)->fils[i], (*a), cle);
          Equilibrage((*a), (*a));
          return;
        }else if ((*a)->cles[i] == cle) {
          Detruire_Cle_Rec ((*a), (*a), cle);
          Equilibrage((*a), (*a));
          return;
        }
      }
      Detruire_Cle_Rec((*a)->fils[3], (*a), cle);
      Equilibrage((*a), (*a));
      return;
  }
  return ;
}
