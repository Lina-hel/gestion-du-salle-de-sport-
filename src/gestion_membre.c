#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <curl/curl.h>
#include <stdio.h>
#include "gestion_membre.h" 
#include "coach.h"
#include "gestion_cours.h"

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    size_t buffer_size = size * nmemb;

    if(upload_ctx->data[upload_ctx->bytes_read] == '\0')
        return 0; // fin de données

    size_t len = strlen(upload_ctx->data + upload_ctx->bytes_read);
    if(len > buffer_size)
        len = buffer_size;

    memcpy(ptr, upload_ctx->data + upload_ctx->bytes_read, len);
    upload_ctx->bytes_read += len;
    return len;
}
void envoyer_email_bienvenue(const char *destinataire, const char *mot_de_passe) {
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;

    char message[1024];
    snprintf(message, sizeof(message),
        "Bonjour,\n"
        "Votre compte de l'application de salle de sport Pure Motion a été créé.\n\n"
        "Email : %s\n"
        "Mot de passe : %s\n\n"
        "Veuillez  changer le mot de passe lors de votre première connexion.\n",
        destinataire, mot_de_passe);

    char data[2048];
    snprintf(data, sizeof(data),
        "To: %s\r\n"
        "From: <AhHelali123@gmail.com>\r\n"
        "Subject: Bienvenue à la salle de sport\r\n"
        "\r\n"
        "%s\r\n",
        destinataire, message);

    struct upload_status upload_ctx = { data, 0 };

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, "ad.lin.stra.min@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "qetn bnkk jgpu cotj");

        // SMTP sécurisé TLS
        curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com:465");
        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<ad.lin.stra.min@gmail.com>");
        recipients = curl_slist_append(recipients, destinataire);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        // Callback pour envoyer le contenu
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        // pour debug si besoin
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "Erreur envoi email: %s\n", curl_easy_strerror(res));

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}


 void generer_mot_de_passe(char *mdp, int length)
{
    const char *chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "abcdefghijklmnopqrstuvwxyz"
                        "0123456789";
    int i;
    srand(time(NULL));
    for (i = 0; i < length; i++)
    {
        mdp[i] = chars[rand() % (strlen(chars))];
    }
    mdp[length] = '\0';
}
 

  void generer_id_membre_PM(const char *filename, char *new_id)
{
    FILE *f = fopen(filename, "r");
    char line[512];
    char id_str[58];
    int max = 0;
    int num;

    if (!f) {
        sprintf(new_id, "PM%03d", 1);
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

    sprintf(new_id, "PM%03d", max + 1);
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
   
   
        fprintf(f, "%s %s %s %s %s %s %s %s %s %s\n",
                gm.id,
                gm.nom,
                gm.prenom,
                gm.email,
                gm.date,
                gm.ville,
                gm.abonnement,
                gm.type_de_sport,
                gm.sexe,
                gm.type_abonnement);
        fclose(f);

        return 1; 
}
	
    else 
	
	return 0;
} 




int modifier_un_membre(char *filename, char id[30], gestion_membre nouv)
{
    gestion_membre gm;
    FILE *f = fopen(filename, "r");
    FILE *aux = fopen("aux.txt", "w");
    int trouve = 0;

    if (f == NULL || aux == NULL)
        return 0;

    FILE *flog = fopen("logmembre.txt", "r");
    FILE *flog_aux = fopen("logmembre_aux.txt", "w");
    if (!flog || !flog_aux) {
        if (flog) fclose(flog);
        if (flog_aux) fclose(flog_aux);
    }

    while (fscanf(f, "%s %s %s %s %s %s %s %s %s %s\n",
                  gm.id, gm.nom, gm.prenom, gm.email,
                  gm.date,
                  gm.ville, gm.abonnement, gm.type_de_sport, gm.sexe, gm.type_abonnement) != EOF)
    {
        if (strcmp(gm.id, id) == 0)
        {

            fprintf(aux, "%s %s %s %s %s %s %s %s %s %s\n",
                    gm.id, nouv.nom, nouv.prenom, nouv.email,
                    nouv.date,
                    nouv.ville, nouv.abonnement, nouv.type_de_sport, nouv.sexe, nouv.type_abonnement);

            trouve = 1;

            if (flog && flog_aux) {
                char email[100], mdp[50];
                while (fscanf(flog, "%s %s\n", email, mdp) != EOF) {
                    if (strcmp(email, gm.email) == 0)
                        fprintf(flog_aux, "%s %s\n", nouv.email, mdp);
                    else
                        fprintf(flog_aux, "%s %s\n", email, mdp);
                }
            }
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

    if (flog) fclose(flog);
    if (flog_aux) {
        fclose(flog_aux);
        remove("logmembre.txt");
        rename("logmembre_aux.txt", "logmembre.txt");
    }

    remove(filename);
    rename("aux.txt", filename);

    return trouve;
}
int supprimer_un_membre(char *filename, char id[30])
{
    gestion_membre gm;
    FILE *f = fopen(filename, "r");
    FILE *aux = fopen("aux.txt", "w");
    int trouve = 0;

    if (f == NULL || aux == NULL)
        return 0;

    while (fscanf(f, "%s %s %s %s %s %s %s %s %s %s",
                   gm.id, gm.nom, gm.prenom, gm.email,
                   gm.date, gm.ville, gm.abonnement,
                   gm.type_de_sport, gm.sexe, gm.type_abonnement) != EOF)
    {
        if (strcmp(gm.id, id) != 0)
        {
            fprintf(aux, "%s %s %s %s %s %s %s %s %s %s\n",
                    gm.id, gm.nom, gm.prenom, gm.email,
                    gm.date, gm.ville, gm.abonnement,
                    gm.type_de_sport, gm.sexe, gm.type_abonnement);
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
 printf("\nLISTE DES MEMBRES\n");

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
        fprintf(f, "%s %d %d %d %d %s %s %s\n",
                r.sport,
                r.jour,
                r.mois,
                r.heure,
                r.duree_seance,
                r.id_entraineur,
                r.nom,
                r.prenom);
        fclose(f);
        return 1;
    }
    return 0; 
}
int entraineur_occupe_date(char *id_entraineur, int jour, int mois, int heure, int duree)
{
     int intervalle_debut = heure * 60;
    int intervalle_fin   = intervalle_debut + duree;

    FILE *f;
    
    // ===== Vérification dans cours.txt =====
    f = fopen("cours.txt", "r");
    if (f)
    {
        cours c;
        while(fscanf(f, "%s %s %s %s %s %d %d %d %f",
                     c.id_c, c.nom, c.dure, c.date, c.id_e,
                     &c.heure, &c.minute, &c.capacite, &c.frais) != EOF)
        {
            int cours_j, cours_m;
            sscanf(c.date,"%d/%d/%*d",&cours_j,&cours_m);

            if(strcmp(c.id_e, id_entraineur) == 0 && cours_j==jour && cours_m==mois)
            {
                int cours_debut = c.heure*60 + c.minute;
                int cours_fin   = cours_debut + atoi(c.dure);

                if(cours_fin > intervalle_debut && cours_debut < intervalle_fin)
                {
                    fclose(f);
                    return 1; // occupé
                }
            }
        }
        fclose(f);
    }

    // ===== Vérification dans reserver_coach.txt =====
    f = fopen("reserver_coach.txt","r");
    if(f)
    {
        reserver_un_coach r;
        while(fscanf(f,"%s %d %d %d %d %s %s %s",
                     r.sport,&r.jour,&r.mois,&r.heure,&r.duree_seance,
                     r.id_entraineur,r.nom,r.prenom) != EOF)
        {
            if(strcmp(r.id_entraineur,id_entraineur)==0 &&
               r.jour==jour && r.mois==mois)
            {
                int res_debut = r.heure*60; 
                int res_fin   = res_debut + r.duree_seance;

                if(res_fin > intervalle_debut && res_debut < intervalle_fin)
                {
                    fclose(f);
                    return 1;
                }
            }
        }
        fclose(f);
    }

    return 0;
}

