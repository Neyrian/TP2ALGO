#include <stdlib.h>
#include "pile.h"

ppile_t creer_pile ()
{
  ppile_t Pile = malloc( sizeof( pile_t ) ) ;
  Pile->sommet = 0;

  return Pile;
}

int detruire_pile (ppile_t p)
{

  if ( p == NULL ) return 0;
  else {
    free( p );
    return 1;
  }
}

int pile_vide (ppile_t p)
{
  return ( p->sommet == 0 );
}

int pile_pleine (ppile_t p)
 {
  return ( p->sommet == MAX_PILE_SIZE );
}

Arbre234 depiler (ppile_t p)
{
  if ( !( pile_vide( p ) ) ){
    p -> sommet--;
    Arbre234 elem = p -> Tab[ p->sommet ];
    return elem;
  }
  else return NULL;
}

int empiler (ppile_t p, Arbre234 pn)
  {
    if ( !( pile_pleine( p ) ) ){

      p -> Tab[ p -> sommet ] = pn;
      p -> sommet++;
      return 1;
    }
    else return 0;
}


ppile_int creer_pile_int ()
{
  ppile_int Pile = malloc( sizeof( pile_int ) ) ;
  Pile->sommet = 0;

  return Pile;
}

int detruire_pile_int (ppile_int p)
{

  if ( p == NULL ) return 0;
  else {
    free( p );
    return 1;
  }
}

int pile_vide_int (ppile_int p)
{
  return ( p->sommet == 0 );
}

int pile_pleine_int (ppile_int p)
 {
  return ( p->sommet == MAX_PILE_SIZE );
}

int depiler_int (ppile_int p)
{
  if ( !( pile_vide_int( p ) ) ){
    p -> sommet--;
    int elem = p -> Tab[ p->sommet ];
    return elem;
  }
  else return 0;
}

int empiler_int (ppile_int p, int pn)
  {
    if ( !( pile_pleine_int( p ) ) ){

      p -> Tab[ p -> sommet ] = pn;
      p -> sommet++;
      return 1;
    }
    else return 0;
}
