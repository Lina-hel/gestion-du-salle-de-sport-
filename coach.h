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
} Entraineur;
void ajouter_entraineur(Entraineur e);
void modifier_entraineur(char id[], Entraineur nouveau);
void supprimer_entraineur(char id[]);
void afficher_entraineurs();
int rechercher_entraineur(char cle[]);
void statistique();

#endif
