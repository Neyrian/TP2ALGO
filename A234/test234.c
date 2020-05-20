#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a234.h"


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

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf (stderr, "il manque le parametre nom de fichier\n") ;
    exit (-1) ;
  }
  printf("Test des fonctions a234.c\n");

  Arbre234 arbre_test = lire_arbre (argv[1]) ;
  printf ("==== Afficher arbre ====\n") ;
  afficher_arbre (arbre_test, 0) ;
  printf("Test de la fonction nombre de clef\nResultat : %d, Resultat attentu : %d ", NombreCles(arbre_test), nbclef(argv[1]));
  return 0;
}
