#ifndef GESTION_MEMBRE_H
#define GESTION_MEMBRE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>


typedef struct {
  char id[30] ;
  char nom[30];
  char prenom[30];
  char email[50];
  char date [30];
  char ville[30];
  char abonnement[30];
  char type_de_sport[30];
  char sexe[10];        
  char type_abonnement[30];
  char mot_de_passe[30];
} gestion_membre;


typedef struct {
  char sport[30];
  int jour;
  int mois;
  int heure;         
  int duree_seance;  
} reserver_un_coach;

void generer_id_membre_PM(char *filename, char *new_id);
int ajouter_un_membre( char *filename ,  gestion_membre gm);
int modifier_un_membre(  char *filename , char id[30] , gestion_membre nouv);
int supprimer_un_membre( char *filename , char id[30]);
gestion_membre rechercher_un_membre( char *filename , char id[30]);
void afficher_un_membre(char *filename);
int reserver_un_coach_file( reserver_un_coach r);
void afficher_gestion_membres_treeview(GtkWidget *liste , char *filename);
void vider_gestion_membres(GtkWidget *liste);

#endif 

