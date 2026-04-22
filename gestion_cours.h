
#ifndef UI_GESTION_COURS_H
#define UI_GESTION_COURS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {

char id_c[32];
char nom[64];
char dure[30];
char date[30];
char specialite[30];
char id_e[30];
int heure;
int minute;
int capacite;
float frais;


}cours;


void afficher_cours(char *filename);
int ajouter(char *filename,cours c); 
int modifier(char *filename, char*id_c, cours nouv);
int supprimer(char *filename, char*id_c);
cours chercher(char *filename, char*id_c);
int inscrire_cours(char *filename, char *id_c);

#endif





