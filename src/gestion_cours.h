
#ifndef UI_GESTION_COURS_H
#define UI_GESTION_COURS_H
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#ifndef GLOBALS_H
#define GLOBALS_H
extern char id_entraineur_connecte[20];
extern char email_entraineur_connecte[100];
extern char membre_connecte[100];
extern int objectif;
extern int type_cours;
extern int niveau;
extern int frequence;
extern int pref_entraineur;
extern int mode_notification;
extern int format_message;
extern int pref_horaire;
#endif



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
char obj[40];
char cours[20];
char niv[20];
char freq[40];
char entraineur[20];
char horaire[40];
char format[200];
} Preference;

typedef struct {
    const char *data;
    size_t bytes_read;
} upload_status;

void recuperer_id_entraineur_par_email(const char* email, char* id_ent);
void afficher_page_inscription(GtkNotebook *notebook, gint index_page);
void trim(char *str);
void envoyer_email_a_tous_les_membres_compatibles(const char* nom_cours, int heure, const char* id_entraineur, const char* date);
void envoyer_email_membre(const char* email_dest, const char* sujet, const char* corps);
void generer_email(const char* nom_cours, const char* horaire, const char* date, const char* format, char* message);
int preference_compatible(const char* cours_ajoute, int heure, const char* id_entraineur);
const char* get_plage_horaire(int heure);
void get_sexe_entraineur(const char* id, char* sexe);

void generer_id_cours(char *filename, char *new_id);
void modifier_email(const char *fichier,
                    const char *ancien_email,
                    const char *nouvel_email);
void modifier_mdp(const char *fichier,
                  const char *email_user,
                  const char *nouveau_mdp);
int chercher_utilisateur(const char *fichier, const char *email, const char *mdp);
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
void generer_email_modifier(const char* nom_cours, const char* horaire, const char* date, const char* format, char* message);
void notifier_membres_compatibles(const char* nom_cours, int heure, const char* id_entraineur, const char* date);
time_t date_to_time(const char *date_str);
int cours_est_confirme(const char *fichier_insc, const char *id_cours);
void nettoyer_cours(const char *fichier_cours, const char *fichier_insc);
void open_mail_client();
void show_phone_number();
const char* chatbot_membre_reponse(const char *msg);
const char* chatbot_admin_reponse(const char *msg);
const char* chatbot_entraineur_reponse(const char *msg);

#endif





