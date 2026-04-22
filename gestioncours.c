#include "gestion_cours.h"
#include <string.h> 

void afficher_cours(char *filename)
{
    FILE *f = fopen(filename, "r");
    cours c;
    if (f != NULL)
    {
        while (fscanf(f, "%s %s %s %s %s %s %d %d %d %f\n",
                      c.id_c, c.nom, c.dure, c.date, c.specialite, c.id_e,
                      &c.heure, &c.minute, &c.capacite, &c.frais) != EOF)
        {
            printf("%s %s %s %s %s %s %d %d %d %.2f\n",
                   c.id_c, c.nom, c.dure, c.date, c.specialite, c.id_e,
                   c.heure, c.minute, c.capacite, c.frais);
        }
        fclose(f);
    }
}

int ajouter(char * filename, cours c )
{
    FILE * f=fopen(filename, "a");
    if(f!=NULL)
    {
        fprintf(f,"%s %s %s %s %s %s %d %d %d %.2f\n",
            c.id_c, c.nom, c.dure, c.date, c.specialite, c.id_e, c.heure, c.minute, c.capacite, c.frais);
        fclose(f);
        return 1;
    }
    else return 0;
}

int modifier( char * filename, char *id_c, cours nouv )
{
    int tr=0;
    cours c;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %s %s %s %s %s %d %d %d %f\n",
            c.id_c, c.nom, c.dure, c.date, c.specialite, c.id_e, &c.heure, &c.minute, &c.capacite, &c.frais)!=EOF)
        {
            if(strcmp(c.id_c, id_c)==0)
            {
                fprintf(f2,"%s %s %s %s %s %s %d %d %d %.2f\n",
                    nouv.id_c, nouv.nom, nouv.dure, nouv.date, nouv.specialite, nouv.id_e,
                    nouv.heure, nouv.minute, nouv.capacite, nouv.frais);
                tr=1;
            }
            else
                fprintf(f2,"%s %s %s %s %s %s %d %d %d %.2f\n",
                    c.id_c, c.nom, c.dure, c.date, c.specialite, c.id_e, c.heure, c.minute, c.capacite, c.frais);
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("nouv.txt", filename);
    }
    return tr;
}

int supprimer(char * filename, char *id_c)
{
    int tr=0;
    cours c;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %s %s %s %s %s %d %d %d %f\n",
            c.id_c, c.nom, c.dure, c.date, c.specialite, c.id_e, &c.heure, &c.minute, &c.capacite, &c.frais)!=EOF)
        {
            if(strcmp(c.id_c, id_c)==0){
                tr=1;
		continue;
	}
           
        fprintf(f2,"%s %s %s %s %s %s %d %d %d %.2f\n",c.id_c, c.nom, c.dure, c.date, c.specialite, c.id_e, c.heure, c.minute, c.capacite, c.frais);
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("nouv.txt", filename);
    }
    return tr;
}

cours chercher(char * filename, char *id_c)
{
    cours c;
    int tr=0;
    FILE * f=fopen(filename, "r");
    if(f!=NULL)
    {
        while(tr==0 && fscanf(f,"%s %s %s %s %s %s %d %d %d %f\n",
            c.id_c, c.nom, c.dure, c.date, c.specialite, c.id_e, &c.heure, &c.minute, &c.capacite, &c.frais)!=EOF)
        {
            if(strcmp(c.id_c, id_c)==0)
                tr=1;
        }
        fclose(f);
    }
    
    if(tr==0)
        strcpy(c.id_c,"-1");
    return c;
}

int inscrire_cours(char *filename, char *id_c)
{
    FILE *f = fopen(filename, "a");
    if (f != NULL)
    {
        fprintf(f, "%s\n", id_c);
        fclose(f);
        return 1;
    }
    else
        return 0;
}
