#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <stdio.h>

typedef struct {
    int id;
    char nom[100];
    char horaire[10];
    char lieu[20];
    float frais;
    char type[20];
    int nb_inscrits;
    char categorie[10];
    char date[20];
} evenement;

typedef struct {
    int id_evenement;
    char nom_participant[100];
    char email[100];
    char telephone[20];
    char date_inscription[20];
} participation;

// Fonction pour ajouter un événement
int ajouter_evenement(char *filename, evenement e);

// Fonction pour participer à un événement
int participer_evenement(char *filename, participation p);

#endif // EVENT_H_INCLUDED
