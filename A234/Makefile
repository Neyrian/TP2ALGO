all: test234

OPTIONS_COMPIL=-Wall -g -c

a234: a234.o lire_affichage.o ajout_cle.o
	gcc -o a234 a234.o lire_affichage.o ajout_cle.o

a234.o: a234.c a234.h
	gcc $(OPTIONS_COMPIL) a234.c

test234: test234.o lire_affichage.o ajout_cle.o a234.o
	gcc -o test234 test234.o a234.o lire_affichage.o ajout_cle.o

test234.o: test234.c
	gcc $(OPTIONS_COMPIL) test234.c

lire_affichage.o: lire_affichage.c a234.h
	gcc $(OPTIONS_COMPIL) lire_affichage.c

ajout_cle.o : ajout_cle.c a234.h
	gcc $(OPTIONS_COMPIL) ajout_cle.c

clean:
	rm -rf test234 *.o *~
