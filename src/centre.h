#ifndef CENTRE_H_INCLUDED
#define CENTRE_H_INCLUDED

#include <gtk/gtk.h>


typedef struct
{
    char id[20];
    char nom[50];
    char adresse[100];
    char type[10];          
    char specialites[100];  
    char horaire[50];
    char parking[50];            
    int capacite;
    char date_ouverture[20];

} centre;
typedef struct
{
    int cardio;
    int musculation;
    int danse;
    int pilates;
    int natation;
} StatCentre;



int centre_id_exists(const char *id);

int match_specialite(const char *centre_specs, const char *rech_specs);

void ajouter_centre(centre c);

int modifier_centre(centre nouv);

int delete_centre(const char *old_id);

void show_centre(GtkWidget *fr, const char *rech_id_nom, const char *rech_specialite);

StatCentre stat_centre(void);

int entraineur_existe(const char *id);

int inscription_existe(const char *id_entraineur, const char *id_centre);

void ajouter_inscription(const char *id_entraineur,
                         const char *id_centre,
                         const char *nom_centre);

void show_inscription(GtkWidget *tv, const char *id_entraineur);

#endif

