#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a234.h"

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

int nbclef(char *nom_fichier) {
  FILE *f ;
  int cle;
  int nb = 0;
  f = fopen (nom_fichier, "r") ;
  while (fscanf (f, "%d", &cle) != EOF) {
    nb ++;
  }
  fclose (f) ;
  return nb ;
}

int clefmax(char *nom_fichier) {
  FILE *f ;
  int cle;
  int clef_max = -1;
  f = fopen (nom_fichier, "r") ;
  while (fscanf (f, "%d", &cle) != EOF) {
    clef_max = max(cle, clef_max);
  }
  fclose (f) ;
  return clef_max ;
}

int clefmin(char *nom_fichier) {
  FILE *f ;
  int cle;
  f = fopen (nom_fichier, "r") ;
  fscanf (f, "%d", &cle);
  int clef_min = cle;
  while (fscanf (f, "%d", &cle) != EOF) {
    clef_min = min(cle, clef_min);
  }
  fclose (f) ;
  return clef_min;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf (stderr, "il manque le parametre nom de fichier\n") ;
    exit (-1) ;
  }
  printf("Test des fonctions a234.c\n");

  Arbre234 arbre_test = lire_arbre (argv[1]) ;
  printf ("==== Afficher arbre ====\n") ;
  afficher_arbre (arbre_test, 0) ;
  printf("Test de la fonction nombre de clef\nResultat : %d, Resultat attendu : %d \n", NombreCles(arbre_test), nbclef(argv[1]));

  int clef_ask = 0;
  printf("Test de la fonction RechercherCle\n");
  while (clef_ask != -1) {
    printf("Entrez clef rechercher (-1 pour quiter) : ");
    scanf("%d", &clef_ask);
    if (RechercherCle(arbre_test, clef_ask) != NULL) {
      printf("La clef %d est présente\n", clef_ask);
    } else {
      printf("La clef %d n'est pas présente\n", clef_ask);
    }
  }

  printf ("==== Afficher arbre ====\n") ;
  afficher_arbre (arbre_test, 0) ;
  printf("Test de la fonction noeud max\n Noeud max : \n");
  afficher_arbre(noeud_max(arbre_test), 0);
  printf("Test de la fonction clef min\nResultat : %d, Resultat attendu : %d\n", CleMin(arbre_test), clefmin(argv[1]));
  printf("Test de la fonction clef max\nResultat : %d, Resultat attendu : %d\n", CleMax(arbre_test), clefmax(argv[1]));

  printf("Test de la fonction Afficher_Cles_Largeur : \n");
  Afficher_Cles_Largeur (arbre_test);
  printf("Test de la fonction Affihcage_Cles_Triees_Recursive :\n");
  Affichage_Cles_Triees_Recursive (arbre_test);
  printf("Test de la fonction Affihcage_Cles_Triees_NonRecursive :\n");
  Affichage_Cles_Triees_NonRecursive (arbre_test);

  int feuilles = 0;
  int noeud2 = 0;
  int noeud3 = 0;
  int noeud4 = 0;
  AnalyseStructureArbre(arbre_test, &feuilles, &noeud2, &noeud3, &noeud4);
  printf("Test de la fonction AnanlyseStructureArbre\nResultat : nb feuilles = %d, nb 2-noeuds = %d nb 3-noeud = %d nb 4-noeud = %d\n", feuilles, noeud2, noeud3, noeud4);

  printf("Test de la fonction detruire clef");
  clef_ask = 0;
  while (clef_ask != -1) {
    printf ("==== Afficher arbre ====\n") ;
    afficher_arbre (arbre_test, 0) ;
    printf("Entrez clef a supprimer (-1 pour quiter) : ");
    scanf("%d", &clef_ask);
    Detruire_Cle(&arbre_test, clef_ask);
  }

  return 0;
}
