#include <stdio.h>
#include <string.h>
#include "coach.h"
#include <curl/curl.h>
#include <stdlib.h>   
struct upload_status {
    const char *data;
    size_t bytes_read;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    size_t buffer_size = size * nmemb;

    const char *data = upload_ctx->data + upload_ctx->bytes_read;
    size_t len = strlen(data);
    if(len > buffer_size)
        len = buffer_size;

    if(len == 0)
        return 0;

    memcpy(ptr, data, len);
    upload_ctx->bytes_read += len;

    return len;
}



void envoyer_email_modification(const char *destinataire, const char *mot_de_passe) {
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;

    char message[1024];
    snprintf(message, sizeof(message),
        "Bonjour,\n"
        "Votre compte de l'application de salle de sport Pure Motion a été modifié.\n\n"
        "Email : %s\n"
        "Mot de passe : %s\n\n"
        "Veuillez changer le mot de passe lors de votre prochaine connexion.\n",
        destinataire, mot_de_passe);

    char data[2048];
    snprintf(data, sizeof(data),
        "To: %s\r\n"
        "From: <AhHelali123@gmail.com>\r\n"
        "Subject: Modification de votre compte Pure Motion\r\n"
        "\r\n"
        "%s\r\n",
        destinataire, message);

    struct upload_status upload_ctx;
upload_ctx.data = data;
upload_ctx.bytes_read = 0;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, "ad.lin.stra.min@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "qetn bnkk jgpu cotj");

        curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com:465");
        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<ad.lin.stra.min@gmail.com>");
        recipients = curl_slist_append(recipients, destinataire);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "Erreur envoi email: %s\n", curl_easy_strerror(res));

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}


void generer_id_entraineur(const char *filename, char *new_id)
{
    FILE *f = fopen(filename, "r");
    char line[512];
    char id_str[58];
    int max = 0;
    int num;

    if (!f) {
        sprintf(new_id, "ENT%03d", 1);
        return;
    }

    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "%9[^;];", id_str) == 1) { // on lit jusqu'au ';'
            if (strncmp(id_str, "ENT", 3) == 0) {
                num = atoi(id_str + 3);
                if (num > max)
                    max = num;
            }
        }
    }

    fclose(f);

    sprintf(new_id, "ENT%03d", max + 1);
}

void ajouter_entraineur(Entraineur e)
{
    FILE *f = fopen("coach.txt", "a");
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
    FILE *f = fopen("coach.txt", "r");
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


    remove("coach.txt");
    rename("f1.txt", "coach.txt");

    if (trouve)
        printf("entraineur %s modifié\n", id);
    else
        printf(" entraineur non trouve %s.\n", id);
}
void supprimer_entraineur(char id[])
{
    FILE *f = fopen("coach.txt", "r");
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


    remove("coach.txt");
    rename("f1.txt", "coach.txt");

    if (trouve)
        printf("entraineur %s supprime \n", id);
    else
        printf("entraineur %s non trouve \n", id);
}
void afficher_entraineurs()
{
    FILE *f = fopen("coach.txt", "r");
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
    FILE *f = fopen("coach.txt", "r");
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

int rechercher_entraineur( const char *cle)
{
    FILE *f = fopen("coach.txt", "r");
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
int inscrire_cours_complet(const char *fichier_cours, const char *fichier_insc, 
                           const char *id_cours)
{
    FILE *f_cours = fopen(fichier_cours, "r");
    if (!f_cours)
    {
        printf("Erreur : impossible d'ouvrir %s\n", fichier_cours);
        return 0;
    }

    FILE *f_insc = fopen(fichier_insc, "a");
    if (!f_insc)
    {
        printf("Erreur : impossible d'ouvrir %s\n", fichier_insc);
        fclose(f_cours);
        return 0;
    }

    char line[256];
    int trouve = 0;

    while (fgets(line, sizeof(line), f_cours))
    {
        char cours_id[20];
        sscanf(line, "%19s", cours_id);

        if (strcmp(cours_id, id_cours) == 0)
        {
            // Ajouter la ligne complète du cours dans inscrient.txt, sans email
            fprintf(f_insc, "%s", line);
            trouve = 1;
            break;
        }
    }

    fclose(f_cours);
    fclose(f_insc);

    if (!trouve)
    {
        printf("Cours %s introuvable dans %s\n", id_cours, fichier_cours);
        return 0;
    }

    return 1;
}

