#ifndef COACH_H
#define COACH_H


typedef struct {
    char id[20];
    char nom[20];
    char prenom[20];
    char cin[20];
    char email[100];
    char sexe[10];
    char date_naissance[20];
    char centre[50];
    char specialite[20];
} entraineur;
void ajouter_entraineur(entraineur e);
void modifier_entraineur(char id[], entraineur nouveau);
void supprimer_entraineur(char id[]);
void afficher_entraineurs();
int rechercher_entraineur(const char *cle, entraineur *e);
void statistique();
int s_inscrire_cours_ent(char *filename, char *id_c, char *niveau);

#endif
