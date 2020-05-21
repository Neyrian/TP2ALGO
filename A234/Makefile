all: test234

OPTIONS_COMPIL=-Wall -g -c

a234: a234.o lire_affichage.o ajout_cle.o file.o pile.o
	gcc -o a234 a234.o lire_affichage.o ajout_cle.o file.o pile.o

a234.o: a234.c a234.h
	gcc $(OPTIONS_COMPIL) a234.c

test234: test234.o lire_affichage.o ajout_cle.o a234.o file.o pile.o
	gcc -o test234 test234.o a234.o lire_affichage.o ajout_cle.o file.o pile.o

test234.o: test234.c
	gcc $(OPTIONS_COMPIL) test234.c

lire_affichage.o: lire_affichage.c a234.h
	gcc $(OPTIONS_COMPIL) lire_affichage.c

ajout_cle.o : ajout_cle.c a234.h
	gcc $(OPTIONS_COMPIL) ajout_cle.c

file.o: file.h file.c
	gcc $(OPTIONS_COMPIL) file.c

pile.o: pile.h pile.c
	gcc $(OPTIONS_COMPIL) pile.c

clean:
	rm -rf test234 *.o *~
