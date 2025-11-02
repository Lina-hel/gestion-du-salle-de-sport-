#ifndef MEMBRE_H_INCLUDED
#define MEMBRE_H_INCLUDED
#include <gtk/gtk.h>


typedef struct {
 int id;
 char nom[30];
 char prenom[30];
 char email[30];
 int jour;
 int mois;
 int annee;
 char sexe[30];
 char ville[30];
 int abonnement;
 char type_de_sport[30];

 }gestion_membre;
void ajouter_un_membre(gestion_membre gm);
void supprimer_event(char nom);
void modifier_un_membre(gestion_membre gm);
void rechercher_un_membre(char nom);
