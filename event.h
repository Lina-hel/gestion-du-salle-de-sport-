#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED
#include <gtk/gtk.h>
typedef struct {
    int id;
    char nom[100];
    char type[20];  
    char date[20];
    char heure[10];
    char lieu[50];
    float frais;
    int nb_inscrits;
    int capacite_max;
    char categorie[10];  
} evenement;

typedef struct {
    int id_evenement;
    char nom_participant[100];
    char email[100];
    char telephone[20];
    char date_inscription[20];
} participation;

//Fonctions pour evenement
int ajouter_evenement(char *, evenement);
int modifier_evenement(char *, int, evenement);
int supprimer_evenement(char *, int);
evenement chercher_evenement(char *, int);


// Fonctions pour participation
int participer_evenement(char *filename, participation p);


#endif


