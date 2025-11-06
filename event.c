#include "event.h"
#include <string.h>
#include <stdlib.h>

int ajouter_evenement(char *filename, evenement e)
{
    FILE *f = fopen(filename, "a");
    if(f != NULL)
    {
        fprintf(f, "%d %s %s %s %.2f %s %d %s %s\n",
                e.id, e.nom, e.horaire, e.lieu, e.frais,
                e.type, e.nb_inscrits, e.categorie, e.date);
        fclose(f);
        return 1;
    }
    else return 0;
}

int modifier_evenement(char *filename, int id, evenement nouv)
{
    int tr = 0;
    evenement e;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
   
    if(f != NULL && f2 != NULL)
    {
        while(fscanf(f, "%d %99s %9s %19s %f %19s %d %9s %19s",
                    &e.id, e.nom, e.horaire, e.lieu, &e.frais,
                    e.type, &e.nb_inscrits, e.categorie, e.date) != EOF)
        {
            if(e.id == id)
            {
                fprintf(f2, "%d %s %s %s %.2f %s %d %s %s\n",
                        nouv.id, nouv.nom, nouv.horaire, nouv.lieu, nouv.frais,
                        nouv.type, nouv.nb_inscrits, nouv.categorie, nouv.date);
                tr = 1;
            }
            else
            {
                fprintf(f2, "%d %s %s %s %.2f %s %d %s %s\n",
                        e.id, e.nom, e.horaire, e.lieu, e.frais,
                        e.type, e.nb_inscrits, e.categorie, e.date);
            }
        }
        fclose(f);
        fclose(f2);
       
        remove(filename);
        rename("nouv.txt", filename);
    }
    return tr;
}

int supprimer_evenement(char *filename, int id)
{
    int tr = 0;
    evenement e;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
   
    if(f != NULL && f2 != NULL)
    {
        while(fscanf(f, "%d %99s %9s %19s %f %19s %d %9s %19s",
                    &e.id, e.nom, e.horaire, e.lieu, &e.frais,
                    e.type, &e.nb_inscrits, e.categorie, e.date) != EOF)
        {
            if(e.id == id)
                tr = 1;
            else
                fprintf(f2, "%d %s %s %s %.2f %s %d %s %s\n",
                        e.id, e.nom, e.horaire, e.lieu, e.frais,
                        e.type, e.nb_inscrits, e.categorie, e.date);
        }
        fclose(f);
        fclose(f2);
       
        remove(filename);
        rename("nouv.txt", filename);
    }
    return tr;
}

evenement chercher_evenement(char *filename, int id)
{
    evenement e;
    int tr = 0;
    FILE *f = fopen(filename, "r");
   
    // Initialiser la structure avec des valeurs par défaut
    e.id = -1;
    strcpy(e.nom, "");
    strcpy(e.horaire, "");
    strcpy(e.lieu, "");
    e.frais = 0.0;
    strcpy(e.type, "");
    e.nb_inscrits = 0;
    strcpy(e.categorie, "");
    strcpy(e.date, "");
   
    if(f != NULL)
    {
        while(tr == 0 && fscanf(f, "%d %99s %9s %19s %f %19s %d %9s %19s",
                               &e.id, e.nom, e.horaire, e.lieu, &e.frais,
                               e.type, &e.nb_inscrits, e.categorie, e.date) != EOF)
        {
            if(e.id == id)
                tr = 1;
        }
        fclose(f);
    }
   
    if(tr == 0)
        e.id = -1;
       
    return e;
}

int participer_evenement(char *filename, participation p)
{
    FILE *f = fopen(filename, "a");
    if(f != NULL)
    {
        fprintf(f, "%d %s %s %s %s\n",
                p.id_evenement, p.nom_participant,
                p.email, p.telephone, p.date_inscription);
        fclose(f);
        return 1;
    }
    else return 0;
}

