#include <stdio.h>
#include <string.h>
#include "coach.h"

void ajouter_entraineur(Entraineur e)
{
    FILE *f = fopen("entraineurs.txt", "a");
    if (f == NULL)
    {
        printf("impossible d’ouvrir le fichier\n");
        return;
    }

    fprintf(f, "%s %s %s %s %s %s %s %s %s\n",
            e.id,
            e.nom,
            e.prenom,
            e.cin,
            e.email,
            e.sexe,
            e.date_naissance,
            e.centre,
            e.specialite);

    fclose(f);
    printf("entraineur ajoute \n");
}
void modifier_entraineur(char id[], Entraineur nouveau)
{
    FILE *f = fopen("entraineurs.txt", "r");
    FILE *f1 = fopen("f1.txt", "w");
    int trouve = 0;
    Entraineur e;

    if (f == NULL || f1 == NULL)
    {
        printf("impossible d’ouvrir le fichier.\n");
        return;
    }

    while (fscanf(f, "%s %s %s %s %s %s %s %s %s",
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
        printf(" entraineur non trouve %s.\n", id);
}
void supprimer_entraineur(char id[])
{
    FILE *f = fopen("entraineurs.txt", "r");
    FILE *f1 = fopen("f1.txt", "w");
    int trouve = 0;
    Entraineur e;

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
        printf("entraineur %s supprime \n", id);
    else
        printf("entraineur %s non trouve \n", id);
}
void afficher_entraineurs()
{
    FILE *f = fopen("entraineurs.txt", "r");
    Entraineur e;

    if (f == NULL)
    {
        printf("impossible d’ouvrir le fichier\n");
        return;
    }

    printf("Liste des entraîneurs enregistrés \n");
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
    Entraineur e;
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
        if (strcmp(e.sexe, "Homme") == 0)
            nb_h++;
        else if (strcmp(e.sexe, "Femme") == 0)
            nb_f++;
        if (strstr(e.specialite, "musculation") != NULL)
            nb_mus++;
        if (strstr(e.specialite, "danse") != NULL)
            nb_danse++;
        if (strstr(e.specialite, "natation") != NULL)
            nb_nat++;
        if (strstr(e.specialite, "pilates") != NULL)
            nb_pil++;
        if (strstr(e.specialite, "cardio") != NULL)
            nb_car++;
    }
    fclose(f);
    printf("statistiques des entraineurs:\n");
    printf("hommes: %d", nb_h);
    printf("femmes: %d", nb_f);
    printf("total: %d", nb_h + nb_f);
    printf("specialite\n");
    printf("musculation : %d", nb_mus);
    printf("danse: %d", nb_danse);
    printf("natation: %d", nb_nat);
    printf("pilates: %d", nb_pil);
    printf("cardio: %d", nb_car);
}

int rechercher_entraineur(char cle[])
{
    FILE *f = fopen("entraineurs.txt", "r");
    Entraineur e;
    int trouve = 0;

    if (f == NULL)
    {
        printf("impossible d’ouvrir le fichier\n");
        return 0;
    }

    while (fscanf(f, "%s %s %s %s %s %s %s %s %[^\n]",
                  e.id, e.nom, e.prenom, e.cin, e.email,
                  e.sexe, e.date_naissance, e.centre, e.specialite) != EOF)
    {
        if (strcmp(e.id, cle) == 0)
        {
            printf("entraineur trouve ");
            printf("ID           : %s\n", e.id);
            printf("Nom          : %s\n", e.nom);
            printf("Prénom       : %s\n", e.prenom);
            printf("CIN          : %s\n", e.cin);
            printf("Email        : %s\n", e.email);
            printf("Sexe         : %s\n", e.sexe);
            printf("Date Naiss.  : %s\n", e.date_naissance);
            printf("Centre       : %s\n", e.centre);
            printf("Spécialité   : %s\n", e.specialite);
            trouve = 1;
            break;
        }
    }

    fclose(f);

    if (!trouve)
        printf("entraineur non trouve pour : %s\n", cle);

    return trouve;
}

//liaison

