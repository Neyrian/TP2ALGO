#ifndef file_h
#define file_h

#include "a234.h"

#define MAX_FILE_SIZE       64

typedef struct {
  int tete ;
  int queue ;
  Arbre234 Tab [MAX_FILE_SIZE] ;
} file_t, *pfile_t ;

pfile_t creer_file () ;

int detruire_file (pfile_t f) ;

int file_vide (pfile_t f) ;

int file_pleine (pfile_t f) ;

Arbre234 defiler (pfile_t f)  ;

int enfiler (pfile_t f, Arbre234 p) ;

  #endif
