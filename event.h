#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED
#include <gtk/gtk.h>

typedef struct {
char nom[30];
int prix_de_billet;
int jour;
char mois[30];
int annee;
int heure;
char lieu[30];
char organisateur[30];
char le challenge_de_mois_est[30]
}Event;

void ajouter_event(Event e);
void supprimer_event(char nom);
void modifier_event(Event e);
void rechercher_event(char nom);

