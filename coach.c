#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coach.h"
void ajouter_entraineur(entraineur e)
{
    FILE *f = fopen("entraineurs.txt", "a");
    if (f == NULL)
    {
        printf("impossible d’ouvrir le fichier\n");
        return;
    }

    fprintf(f, "%s %s %s %s %s %s %s %s %s\n",
            e.id, e.nom, e.prenom, e.cin, e.email,
            e.sexe, e.date_naissance, e.centre, e.specialite);

    fclose(f);
    printf("entraineur ajouté\n");
}

void modifier_entraineur(char id[], entraineur nouveau)
{
    FILE *f = fopen("entraineurs.txt", "r");
    FILE *f1 = fopen("f1.txt", "w");
    int trouve = 0;
    entraineur e;

    if (f == NULL || f1 == NULL)
    {
        printf("impossible d’ouvrir le fichier.\n");
        return;
    }

    while (fscanf(f, "%s %s %s %s %s %s %s %s %[^\n]",
                  e.id, e.nom, e.prenom, e.cin, e.email,
                  e.sexe, e.date_naissance, e.centre, e.specialite) != EOF)
    {
        if (strcmp(e.id, id) == 0)
        {
            fprintf(f1, "%s %s %s %s %s %s %s %s %s\n",
                    nouveau.id, nouveau.nom, nouveau.prenom, nouveau.cin,
                    nouveau.email, nouveau.sexe, nouveau.date_naissance,
                    nouveau.centre, nouveau.specialite);
            trouve = 1;
        }
        else
        {
            fprintf(f1, "%s %s %s %s %s %s %s %s %s\n",
                    e.id, e.nom, e.prenom, e.cin, e.email,
                    e.sexe, e.date_naissance, e.centre, e.specialite);
        }
    }

    fclose(f);
    fclose(f1);

    remove("entraineurs.txt");
    rename("f1.txt", "entraineurs.txt");

    if (trouve)
        printf("entraineur %s modifié\n", id);
    else
        printf("entraineur %s non trouvé\n", id);
}

void supprimer_entraineur(char id[])
{
    FILE *f = fopen("entraineurs.txt", "r");
    FILE *f1 = fopen("f1.txt", "w");
    int trouve = 0;
    entraineur e;

    if (f == NULL || f1 == NULL)
    {
        printf("impossible d’ouvrir le fichier\n");
        return;
    }

    while (fscanf(f, "%s %s %s %s %s %s %s %s %[^\n]",
                  e.id, e.nom, e.prenom, e.cin, e.email,
                  e.sexe, e.date_naissance, e.centre, e.specialite) != EOF)
    {
        if (strcmp(e.id, id) != 0)
        {
            fprintf(f1, "%s %s %s %s %s %s %s %s %s\n",
                    e.id, e.nom, e.prenom, e.cin, e.email,
                    e.sexe, e.date_naissance, e.centre, e.specialite);
        }
        else
        {
            trouve = 1;
        }
    }

    fclose(f);
    fclose(f1);

    remove("entraineurs.txt");
    rename("f1.txt", "entraineurs.txt");

    if (trouve)
        printf("entraineur %s supprimé\n", id);
    else
        printf("entraineur %s non trouvé\n", id);
}

void afficher_entraineurs()
{
    FILE *f = fopen("entraineurs.txt", "r");
    entraineur e;

    if (f == NULL)
    {
        printf("impossible d’ouvrir le fichier\n");
        return;
    }

    printf("Liste des entraineurs enregistrés:\n");
    printf("%s %s %s %s %s %s %s %s %s\n",
           "ID", "Nom", "Prenom", "CIN", "Email", "Sexe",
           "DateNaiss", "Centre", "Specialite");

    while (fscanf(f, "%s %s %s %s %s %s %s %s %[^\n]",
                  e.id, e.nom, e.prenom, e.cin, e.email,
                  e.sexe, e.date_naissance, e.centre, e.specialite) != EOF)
    {
        printf("%s %s %s %s %s %s %s %s %s\n",
               e.id, e.nom, e.prenom, e.cin, e.email,
               e.sexe, e.date_naissance, e.centre, e.specialite);
    }

    fclose(f);
}

void statistique()
{
    FILE *f = fopen("entraineurs.txt", "r");
    entraineur e;
    int nb_h = 0, nb_f = 0;
    int nb_mus = 0, nb_danse = 0, nb_nat = 0, nb_pil = 0, nb_car = 0;

    if (f == NULL)
    {
        printf("impossible d’ouvrir le fichier\n");
        return;
    }

    while (fscanf(f, "%s %s %s %s %s %s %s %s %[^\n]",
                  e.id, e.nom, e.prenom, e.cin, e.email,
                  e.sexe, e.date_naissance, e.centre, e.specialite) != EOF)
    {
        if (strcmp(e.sexe, "Homme") == 0) nb_h++;
        else if (strcmp(e.sexe, "Femme") == 0) nb_f++;

        if (strstr(e.specialite, "musculation")) nb_mus++;
        if (strstr(e.specialite, "danse"))       nb_danse++;
        if (strstr(e.specialite, "natation"))    nb_nat++;
        if (strstr(e.specialite, "pilates"))     nb_pil++;
        if (strstr(e.specialite, "cardio"))      nb_car++;
    }

    fclose(f);

    printf("statistiques des entraineurs:\n");
    printf("hommes: %d\n", nb_h);
    printf("femmes: %d\n", nb_f);
    printf("total: %d\n", nb_h + nb_f);
    printf("\nspecialites:\n");
    printf("musculation: %d\n", nb_mus);
    printf("danse: %d\n", nb_danse);
    printf("natation: %d\n", nb_nat);
    printf("pilates: %d\n", nb_pil);
    printf("cardio: %d\n", nb_car);
}

int rechercher_entraineur(const char *cle, entraineur *e)
{
    FILE *f = fopen("entraineurs.txt", "r");

    if (f == NULL)
        return 0;

    while (fscanf(f, "%s %s %s %s %s %s %s %s %[^\n]",
                  e->id,
                  e->nom,
                  e->prenom,
                  e->cin,
                  e->email,
                  e->sexe,
                  e->date_naissance,
                  e->centre,
                  e->specialite) != EOF)
    {
        if (strcmp(e->id, cle) == 0)
        {
            fclose(f);
            return 1;   // trouvé
        }
    }

    fclose(f);
    return 0;           // non trouvé
}
int s_inscrire_cours_ent(char *filename, char *id_c, char *niveau)
{
    FILE *f = fopen(filename, "a");

    if (f == NULL)
    {
        printf("erreur\n");
        return 0;
    }

    fprintf(f, "%s %s\n", id_c, niveau);
    fclose(f);

    printf("inscription au cours sportif avec succes\n");
    return 1;
}


