prog:gestioncours.o main_cours.o
	gcc gestioncours.o main_cours.o -o prog -g
main_cours.o:main_cours.c
	gcc -c main_cours.c -g
gestioncours.o:gestioncours.c
	gcc -c gestioncours.c -g
