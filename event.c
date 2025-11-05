#include "evenement.h"
#include <string.h>
#include <stdlib.h>

// Fonctions pour evenement
int ajouter_evenement(char *filename, evenement e)
{
    FILE *f = fopen(filename, "a");
    if(f != NULL)
    {
        fprintf(f, "%d %s %s %s %s %s %.2f %d %d %s\n",
                e.id, e.nom, e.type, e.date, e.heure, e.lieu,
                e.frais, e.nb_inscrits, e.capacite_max, e.categorie);
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
        while(fscanf(f, "%d %s %s %s %s %s %f %d %d %s\n",
                    &e.id, e.nom, e.type, e.date, e.heure, e.lieu,
                    &e.frais, &e.nb_inscrits, &e.capacite_max, e.categorie) != EOF)
        {
            if(e.id == id)
            {
                fprintf(f2, "%d %s %s %s %s %s %.2f %d %d %s\n",
                        nouv.id, nouv.nom, nouv.type, nouv.date, nouv.heure, nouv.lieu,
                        nouv.frais, nouv.nb_inscrits, nouv.capacite_max, nouv.categorie);
                tr = 1;
            }
            else
                fprintf(f2, "%d %s %s %s %s %s %.2f %d %d %s\n",
                        e.id, e.nom, e.type, e.date, e.heure, e.lieu,
                        e.frais, e.nb_inscrits, e.capacite_max, e.categorie);
        }
    }
    if(f) fclose(f);
    if(f2) fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
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
        while(fscanf(f, "%d %s %s %s %s %s %f %d %d %s\n",
                    &e.id, e.nom, e.type, e.date, e.heure, e.lieu,
                    &e.frais, &e.nb_inscrits, &e.capacite_max, e.categorie) != EOF)
        {
            if(e.id == id)
                tr = 1;
            else
                fprintf(f2, "%d %s %s %s %s %s %.2f %d %d %s\n",
                        e.id, e.nom, e.type, e.date, e.heure, e.lieu,
                        e.frais, e.nb_inscrits, e.capacite_max, e.categorie);
        }
    }
    if(f) fclose(f);
    if(f2) fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}

evenement chercher_evenement(char *filename, int id)
{
    evenement e;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if(f != NULL)
    {
        while(tr == 0 && fscanf(f, "%d %s %s %s %s %s %f %d %d %s\n",
                               &e.id, e.nom, e.type, e.date, e.heure, e.lieu,
                               &e.frais, &e.nb_inscrits, &e.capacite_max, e.categorie) != EOF)
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
        fprintf(f, "%d %s %s %s %s %s\n", 
                p.id_evenement, p.type_evenement, p.nom_participant,
                p.email, p.telephone , p.date_inscription);
        fclose(f);
        return 1;
     }
      else return 0;
}









