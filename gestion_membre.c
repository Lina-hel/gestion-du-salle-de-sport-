#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_membre.h" 




  

void generer_id_membre_PM(char *filename, char *new_id)
{
    FILE *f = fopen(filename, "r");
    char line[512];
    char id_str[58];
    int max = 0;
    int num;

    if (!f) {
        strcpy(new_id, "PM1");
        return;
    }

    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "%9[^|]|", id_str) == 1) {
            if (strncmp(id_str, "PM", 2) == 0) {
                num = atoi(id_str + 2);   
                if (num > max)
                    max = num;
            }
        }
    }

    fclose(f);
    sprintf(new_id, "PM%d", max + 1);
}


int login_membre(char *filename, const char *email, const char *mdp, gestion_membre *out)
{
    FILE *f = fopen(filename, "r");
    gestion_membre m;

    if (!f) return 0;

    while (fscanf(f, "%s %s %s %s %s %s %s %s %s %s %s\n",
                  m.id,
                  m.nom,
                  m.prenom,
                  m.email,
                  m.date,
                  m.ville,
                  m.abonnement,
                  m.type_de_sport,
                  m.sexe,
                  m.type_abonnement,
                  m.mot_de_passe) != EOF)
    {
        if (strcmp(m.email, email) == 0 &&
            strcmp(m.mot_de_passe, mdp) == 0)
        {
            if (out)
                *out = m;   /* copier toutes les infos */
            fclose(f);
            return 1;       /* LOGIN OK */
        }
    }

    fclose(f);
    return 0;   /* email ou mdp incorrect */
}



int ajouter_un_membre( char *filename ,  gestion_membre gm)
{
    FILE *f = fopen(filename, "a");

    if (f != NULL) {
   
   
        fprintf(f, "%s %s %s %s %s %s %s %s %s %s %s\n",
                gm.id,
                gm.nom,
                gm.prenom,
                gm.email,
                gm.date,
                gm.ville,
                gm.abonnement,
                gm.type_de_sport,
                gm.sexe,
                gm.type_abonnement,
                gm.mot_de_passe);
        fclose(f);

        return 1; 
}
	
    else 
	
	return 0;
} 





int modifier_un_membre(  char *filename , char id[30] ,  gestion_membre nouv)
{
    gestion_membre gm;
    FILE *f = fopen(filename , "r");
    FILE *aux = fopen("aux.txt", "w"); 
    int trouve = 0;

    if (f == NULL || aux == NULL)

         return 0;
    
        while (fscanf(f, "%s %s %s %s %s %s %s %s %s %s\n",
                      gm.id, gm.nom, gm.prenom, gm.email,
                      gm.date,
                      gm.ville, gm.abonnement, gm.type_de_sport, gm.sexe, gm.type_abonnement) != EOF)
        {
            if (gm.id == id)
            {
                fprintf(aux , "%s %s %s %s %s %s %s %s %s %s\n",
                        gm.id, nouv.nom, nouv.prenom, nouv.email,
                        nouv.date,
                        nouv.ville, nouv.abonnement, nouv.type_de_sport, nouv.sexe, nouv.type_abonnement);
                trouve = 1;
            }
            else
            {
                fprintf(aux, "%s %s %s %s %s %s %s %s %s %s\n",
                        gm.id, gm.nom, gm.prenom, gm.email,
                        gm.date,
                        gm.ville, gm.abonnement, gm.type_de_sport, gm.sexe, gm.type_abonnement);
            }
        }
    
    fclose(f);
    fclose(aux);
    remove(filename);
    rename("aux.txt", filename);
    return trouve;
}

int supprimer_un_membre( char *filename , char id[30]) {
    
    gestion_membre gm;
    FILE *f = fopen(filename, "r");
    FILE *aux = fopen("aux.txt", "w");
    int trouve = 0 ; 

if (f == NULL || aux == NULL)
   return 0 ;

        while (fscanf(f, "%s %s %s %s %s %s %s %s %s %s\n",
                           gm.id, gm.nom, gm.prenom, gm.email,
                           gm.date,
                           gm.ville, gm.abonnement, gm.type_de_sport, 
                           gm.sexe, gm.type_abonnement) != EOF) {

            if (gm.id != id) {

    fprintf(aux, "%s %s %s %s %s %s %s %s %s %s\n",
                        gm.id, gm.nom, gm.prenom, gm.email,
                        gm.date,
                        gm.ville, gm.abonnement, gm.type_de_sport, gm.sexe, gm.type_abonnement);
            }
            else
            {
                trouve = 1;
            }
        }
    
     fclose(f);
    fclose(aux);
    remove(filename);
    rename("aux.txt", filename);

    return trouve;
}

gestion_membre rechercher_un_membre( char *filename , char id[30] )
{   
     gestion_membre gm;
     gestion_membre vide = {-1};  
  
    FILE *f = fopen(filename, "r");
      if (f == NULL)
        return vide;
    

    while (fscanf(f,"%s %s %s %s %s %s %s %s %s %s\n",
            gm.id,
            gm.nom,
            gm.prenom,
            gm.email,
            gm.date,
            gm.ville,
            gm.abonnement,
            gm.type_de_sport,
            gm.sexe,
            gm.type_abonnement
        ) != EOF)  
        {
              if (gm.id == id) {
            fclose(f);
            return gm;
        }
    }

    fclose(f);
    return vide;
}
  

void afficher_un_membre(char *filename) {
    gestion_membre gm;
    FILE *f = fopen(filename, "r");
    
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier!\n");
        return;
    }
 printf("\n=== LISTE DES MEMBRES ===\n");

    while (fscanf(f,"%s %s %s %s %s %s %s %s %s %s\n",
            gm.id,
            gm.nom,
            gm.prenom,
            gm.email,
            gm.date,
            gm.ville,
            gm.abonnement,
            gm.type_de_sport,
            gm.sexe,
            gm.type_abonnement
        ) != EOF)  
        {
        printf("ID: %s\n", gm.id);
        printf("Nom: %s\n", gm.nom);
        printf("Prenom: %s\n", gm.prenom);
        printf("Email: %s\n", gm.email);
        printf("Date de naissance: %s\n", gm.date);
        printf("Ville: %s\n", gm.ville);
        printf("Abonnement: %s\n", gm.abonnement);
        printf("type de sport: %s\n", gm.type_de_sport);
        printf("Sexe: %s\n", gm.sexe);
        printf("Type abonnement: %s\n", gm.type_abonnement);       
        printf("---------------------------\n");
}
   fclose(f);


}
        

int reserver_un_coach_file(reserver_un_coach r)
{
    FILE *f = fopen("reserver_coach.txt", "a");
    if (f != NULL)
    {
        fprintf(f, "%s | %d | %d | %d | %d", r.sport, r.jour, r.mois, r.heure, r.duree_seance);
        fclose(f);
        return 1;
    }
    return 0;
}
