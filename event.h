#ifndef EVENT_H
#define EVENT_H
#define EVENT_FILENAME "evenements.txt"
#include <gtk/gtk.h>

typedef struct {
	int id;
        int id_participant;
	char nom[50];
	int jour;
	int mois;
	int annee;
	int heure;
	int min;
	char lieu[50];
	char type[30];
	float frais;
	int nb_inscrits;
	char categorie_participant[30];
} Evenement;


typedef struct
{
    int day ;
    int month ;
    int year;
}Date;

typedef struct {
    int id_event;
    char nom_event[50];
    int nb_participants;
} StatEvent;




int ajouter_evenement(Evenement e);
int modifier_evenement(Evenement e_modif);
int supprimer_evenement(int id);
void chercher(char *filename,int id);
int calculer_stats(int ids[], int counts[], int max);
int calculer_nb_participants(int event_id);
void afficher_evenements_treeview(GtkWidget *liste);
void afficher_evenements_participes_treeview(GtkWidget *liste);
void vider_treeview(GtkWidget *treeview);
void chercher_evenement_treeview(GtkWidget *liste, int id_recherche);
int participer_evenement(int id_evenement, int id_participant, char categorie[]);
Date get_date_from_entry(GtkEntry *entry);
#endif





