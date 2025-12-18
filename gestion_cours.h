
#ifndef UI_GESTION_COURS_H
#define UI_GESTION_COURS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int objectif;
extern int type_cours;
extern int niveau;
extern int frequence;
extern int pref_entraineur;
extern int mode_notification;
extern int format_message;
extern int pref_horaire;

typedef struct {

char id_c[32];
char nom[64];
char dure[30];
char date[30];
char id_e[30];
int heure;
int minute;
int capacite;
float frais;
}cours;

typedef struct {
char obj[20];
char cours[20];
char niv[20];
char freq[20];
char entraineur[20];
char horaire[20];
char notif[20];
char format[20];
} Preference;
int supprimer_preference_fichier(char *filename,char *obj_pref);
void afficher_erreur(const char *msg);
void ajouter_preferences();
void sauvegarder_preferences();

int compter_type_cours(char fichier[100], int *nb_muscu, int *nb_danse, int *nb_cardio, int *nb_natation, int *nb_pilates);
int entraineur_occupe(char *id_entraineur, int debut_h, int debut_m, int fin_h, int fin_m);
void Specialite(int choix_specialite[], char texte[]);
void enregistrer_rdv(const char *email, const char *heure);
int rendezvous_occupe(const char *heure);
int nb_rendezvous_pour_heure(const char *heure);
void Resultat(int choix[], char texte[]);
void Res_suppr(int choix_suppr[],char texte[]);
void choix_niveau(int choix_niv[],char texte[]);
void afficher_cours(char *filename);
int ajouter(char *filename,cours c); 
int modifier(char *filename, char*id_c, cours nouv);
int supprimer(char *filename, char*id_c);
cours chercher(char *filename, char*id_c);
int inscrire_cours(char *filename, char *id_c, char*niveau);
int verifier_login(const char *fichier, const char *email, const char *mdp);
#endif





