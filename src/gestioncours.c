#include "gestion_cours.h"
#include "coach.h"
#include <curl/curl.h>
#include <string.h> 
#include <stdio.h>
#define MAX_PREF 100
#include <gtk/gtk.h>
#include <time.h>

char membre_connecte[100] = "";
char email_entraineur_connecte[100] = "";
char id_entraineur_connecte[20] = "";

Preference preferences[MAX_PREF];
int nb_preferences = 0;


char objectifs[][40] = {"", "Perte de poids", "Prise de masse", "Bien etre/Detente", "Performance sportive"};
char types_cours[][20] = {"", "Musculation", "Danse", "Cardio", "Pilates", "Natation"};
char niveaux[][20] = {"", "Debutant", "Intermediaire", "Avance"};
char frequences[][40] = {"", "1 fois/semaine", "2-3 fois/semaine", "+4 fois/semaine"};
char prefs_entraineur[][20] = {"", "Femme", "Homme", "Peu importe"};
char formats_message[][200] = {"", "Resume simple", "lien vers inscription"};
char horaires[][200] = { "Matin: 08:00-12:00", "Apres midi: 12:00-18:00", "Nuit: 18:00-21:00"};

void recuperer_id_entraineur_par_email(const char* email, char* id_ent)
{
    FILE *f = fopen("coach.txt", "r");
    if (!f) {
        id_ent[0] = '\0';
        return;
    }

    Entraineur e;
    char ligne[512];

    while (fgets(ligne, sizeof(ligne), f)) {

        int n = sscanf(ligne,
            "%19s %19s %19s %19s %99s %9s %19s %49s %19s",
            e.id,
            e.nom,
            e.prenom,
            e.cin,
            e.email,
            e.sexe,
            e.date_naissance,
            e.centre,
            e.specialite
        );

        if (n != 9) continue;  // ✅ 9 champs EXACTEMENT

        if (strcmp(e.email, email) == 0) {
            strcpy(id_ent, e.id);
            fclose(f);
            return;
        }
    }

    id_ent[0] = '\0';
    fclose(f);
}













void afficher_page_inscription(GtkNotebook *notebook, gint index_page) {
    if (!notebook) return;
    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), index_page);
}


static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {
    upload_status *upload_ctx = (upload_status *)userp;
    size_t buffer_size = size * nmemb;

    if (upload_ctx->bytes_read >= strlen(upload_ctx->data))
        return 0;

    size_t len = strlen(upload_ctx->data + upload_ctx->bytes_read);
    if (len > buffer_size)
        len = buffer_size;

    memcpy(ptr, upload_ctx->data + upload_ctx->bytes_read, len);
    upload_ctx->bytes_read += len;
    return len;
}
void trim(char *str) {
    if (!str) return;
    // Espaces au début
    char *p = str;
    while (*p && isspace((unsigned char)*p)) p++;
    if (p != str) memmove(str, p, strlen(p) + 1);

    // Espaces à la fin
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) str[--len] = '\0';
}

void notifier_membres_compatibles(const char* nom_cours, int heure, const char* id_entraineur, const char* date) {
    FILE *f = fopen("envoieemail.txt", "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir envoieemail.txt\n");
        return;
    }

    char ligne[512];
    char email[100], obj[50], cours[50], niv[50], freq[50], pref_sexe[20], horaire_pref[50], format[200];
    char sexe_entraineur[20];
    get_sexe_entraineur(id_entraineur, sexe_entraineur);

    const char* plage_cours = get_plage_horaire(heure);

    while(fgets(ligne, sizeof(ligne), f)) {

        int n = sscanf(ligne, "%99[^;];%49[^;];%49[^;];%49[^;];%49[^;];%19[^;];%49[^;];%199[^\n]",
                       email, obj, cours, niv, freq, pref_sexe, horaire_pref, format);
        if (n != 8) continue;

        trim(email); trim(cours); trim(pref_sexe); trim(horaire_pref); trim(format);


        if (strcmp(nom_cours, cours) != 0) continue;


        if ((strcmp(pref_sexe, "Homme") == 0 && strcmp(sexe_entraineur, "Homme") != 0) ||
            (strcmp(pref_sexe, "Femme") == 0 && strcmp(sexe_entraineur, "Femme") != 0))
            continue;


        char horaire_simple[20];
        sscanf(horaire_pref, "%19[^:]", horaire_simple);
        if (strcmp(plage_cours, horaire_simple) != 0) continue;


        char message[512];
        generer_email_modifier(nom_cours, plage_cours, date, format, message);

        envoyer_email_membre(email, "Nouveau cours disponible", message);
        printf("Email envoyé à %s pour le cours %s\n", email, nom_cours);
    }

    fclose(f);
}


void envoyer_email_a_tous_les_membres_compatibles(const char* nom_cours, int heure, const char* id_entraineur, const char* date) {
    FILE *f = fopen("envoieemail.txt","r");
    if (!f) return;

    char ligne[512], email[100], obj[50], cours[50], niv[50], freq[50], sexe[20], horaire[50], format[200];

    const char* plage_cours = get_plage_horaire(heure);

    while(fgets(ligne,sizeof(ligne),f)) {
        int n = sscanf(ligne, "%99[^;];%49[^;];%49[^;];%49[^;];%49[^;];%19[^;];%49[^;];%199[^\n]",
                       email, obj, cours, niv, freq, sexe, horaire, format);
        if (n != 8) continue;

        trim(email); trim(format);

        if (strcmp(cours, nom_cours) != 0) continue;
        char horaire_simple[20]; sscanf(horaire, "%19[^:]", horaire_simple);
        if (strcmp(plage_cours, horaire_simple) != 0) continue;

        // envoyer mail
        char message[512];
        generer_email(nom_cours, plage_cours, date, format, message);
        envoyer_email_membre(email, "Nouveau cours disponible", message);
    }

    fclose(f);
}

void generer_email_modifier(const char* nom_cours, const char* horaire, const char* date, const char* format, char* message)
{
    if (strcmp(format, "Resume simple") == 0)
        sprintf(message,
                "Cours compatible avec vos préferences a été modifié!\nCours: %s\nHoraire: %s\nDate: %s\nInscrivez-vous rapidement !",
                nom_cours, horaire, date);
    else
        sprintf(message,
                "Courscompatible avec vos préferences a été modifié\nCours: %s\nHoraire: %s\nDate: %s\nInscrivez-vous ici : mymotion://inscription",
                nom_cours, horaire, date);
}

void generer_email(const char* nom_cours, const char* horaire, const char* date, const char* format, char* message)
{
    if (strcmp(format, "Resume simple") == 0)
        sprintf(message,
                "Nouveau cours compatible a vos préférences disponible !\nCours: %s\nHoraire: %s\nDate: %s\nInscrivez-vous rapidement !",
                nom_cours, horaire, date);
    else
        sprintf(message,
                "Nouveau cours compatible a vos préférences disponible !\nCours: %s\nHoraire: %s\nDate: %s\nInscrivez-vous ici : mymotion://inscription",
                nom_cours, horaire, date);
}

void envoyer_email_membre(const char* email_dest, const char* sujet, const char* corps) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *recipients = NULL;
    upload_status upload_ctx;

    char data[2048];
    snprintf(data, sizeof(data),
        "To: %s\r\n"
        "From: <ad.lin.stra.min@gmail.com>\r\n"
        "Subject: %s\r\n"
        "\r\n"
        "%s\r\n",
        email_dest, sujet, corps);

    upload_ctx.data = data;
    upload_ctx.bytes_read = 0;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, "ad.lin.stra.min@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "qetn bnkk jgpu cotj"); 
        curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com:465");
        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<ad.lin.stra.min@gmail.com>");

        recipients = curl_slist_append(recipients, email_dest);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "Erreur envoi email: %s\n", curl_easy_strerror(res));

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}



const char* get_plage_horaire(int heure)
{
    if (heure >= 8 && heure < 12) return "Matin";
    else if (heure >= 12 && heure < 18) return "Apres midi";
    else if (heure >= 18 && heure < 22) return "Nuit";
    else return "Autre";
}

void get_sexe_entraineur(const char* id, char* sexe) {
    FILE *f = fopen("coach.txt", "r");
    if (!f) {
        strcpy(sexe, "");
        return;
    }

    char line[512];
    char id_f[50], nom[50], prenom[50], cin[50], email[100], sexe_f[20], date_naissance[20], centre[50], specialite[50];

    while(fgets(line, sizeof(line), f)) {
        sscanf(line, "%49s %49s %49s %49s %99s %19s %19s %49s %49s",
               id_f, nom, prenom, cin, email, sexe_f, date_naissance, centre, specialite);

        if(strcmp(id_f, id) == 0) {
            strcpy(sexe, sexe_f); // maintenant sexe correct
            fclose(f);
            return;
        }
    }

    strcpy(sexe, "");
    fclose(f);
}


int preference_compatible(const char* cours_ajoute, int heure, const char* id_entraineur)
{
    FILE *f = fopen("envoieemail.txt", "r");
    if (!f) return 0;

    char ligne[512];
    char email_f[100], obj[50], cours[50], niv[50], freq[50], pref_sexe[20], horaire_pref[50], format[200];
    char sexe_entraineur[10];
    get_sexe_entraineur(id_entraineur, sexe_entraineur);

    const char* plage_cours = get_plage_horaire(heure);

    while(fgets(ligne, sizeof(ligne), f)) {
        int n = sscanf(ligne, "%99[^;];%49[^;];%49[^;];%49[^;];%49[^;];%19[^;];%49[^;];%199[^\n]",
                       email_f, obj, cours, niv, freq, pref_sexe, horaire_pref, format);
        if(n != 8) continue;

        if(strcmp(cours_ajoute, cours) != 0) continue;
        if(strcmp(email_f, membre_connecte) != 0) continue;

        if(strcmp(pref_sexe, "Homme") == 0 && strcmp(sexe_entraineur, "Homme") != 0) continue;
        if(strcmp(pref_sexe, "Femme") == 0 && strcmp(sexe_entraineur, "Femme") != 0) continue;

        char horaire_pref_simple[20];
        sscanf(horaire_pref, "%19[^:]", horaire_pref_simple);
        if(strcmp(plage_cours, horaire_pref_simple) != 0) continue;

        fclose(f);
        return 1;
    }

    fclose(f);
    return 0;
}





void generer_id_cours(char *filename, char *new_id)
{
FILE *f = fopen(filename, "r");
    char line[512];
    int max = 0;
    int num;

    if (!f)
    {
        sprintf(new_id, "CS001");
        return;
    }

    while (fgets(line, sizeof(line), f))
    {
        char *p = strstr(line, "CS");
        if (p)
        {
            num = atoi(p + 2);
            if (num > max)
                max = num;
        }
    }

    fclose(f);

    sprintf(new_id, "CS%03d", max + 1);
}

void modifier_email(const char *fichier,
                    const char *ancien_email,
                    const char *nouvel_email)
{
    FILE *f = fopen(fichier, "r");
    FILE *tmp = fopen("temp_modif.txt", "w");

    char email[50], mdp[50];

    if (!f || !tmp) return;

    while (fscanf(f, "%s %s", email, mdp) != EOF)
    {
        if (strcmp(email, ancien_email) == 0)
            fprintf(tmp, "%s %s\n", nouvel_email, mdp);
        else
            fprintf(tmp, "%s %s\n", email, mdp);
    }

    fclose(f);
    fclose(tmp);

    remove(fichier);
    rename("temp_modif.txt", fichier);
}

void modifier_mdp(const char *fichier,
                  const char *email_user,
                  const char *nouveau_mdp)
{
    FILE *f = fopen(fichier, "r");
    FILE *tmp = fopen("temp_modi.txt", "w");

    char email[50], mdp[50];

    if (!f || !tmp) return;

    while (fscanf(f, "%s %s", email, mdp) != EOF)
    {
        if (strcmp(email, email_user) == 0)
            fprintf(tmp, "%s %s\n", email, nouveau_mdp);
        else
            fprintf(tmp, "%s %s\n", email, mdp);
    }

    fclose(f);
    fclose(tmp);

    remove(fichier);
    rename("temp_modi.txt", fichier);
}



int chercher_utilisateur(const char *fichier, const char *email, const char *mdp)
{
    FILE *f = fopen(fichier, "r");
    char e[100], m[100];

    if (!f) return 0;

    while (fscanf(f, "%s %s", e, m) != EOF)
    {
        if (strcmp(e, email) == 0 && strcmp(m, mdp) == 0)
        {
            fclose(f);
            return 1; // trouvé
        }
    }

    fclose(f);
    return 0; // pas trouvé
}

int supprimer_preference_fichier(char *filename, char *obj_pref)
{
    int tr = 0;
    Preference p;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if(f != NULL && f2 != NULL)
    {
        char ligne[512];
        while(fgets(ligne, sizeof(ligne), f))
        {
            char *token = strtok(ligne, ";");
            if(token) strncpy(p.obj, token, sizeof(p.obj)-1); p.obj[sizeof(p.obj)-1]='\0';

            token = strtok(NULL, ";");
            if(token) strncpy(p.cours, token, sizeof(p.cours)-1); p.cours[sizeof(p.cours)-1]='\0';

            token = strtok(NULL, ";");
            if(token) strncpy(p.niv, token, sizeof(p.niv)-1); p.niv[sizeof(p.niv)-1]='\0';

            token = strtok(NULL, ";");
            if(token) strncpy(p.freq, token, sizeof(p.freq)-1); p.freq[sizeof(p.freq)-1]='\0';

            token = strtok(NULL, ";");
            if(token) strncpy(p.entraineur, token, sizeof(p.entraineur)-1); p.entraineur[sizeof(p.entraineur)-1]='\0';

            token = strtok(NULL, ";");
            if(token) strncpy(p.horaire, token, sizeof(p.horaire)-1); p.horaire[sizeof(p.horaire)-1]='\0';

            token = strtok(NULL, ";\n");
            if(token) strncpy(p.format, token, sizeof(p.format)-1); p.format[sizeof(p.format)-1]='\0';

            if(strcmp(p.obj, obj_pref) != 0)
            {
                fprintf(f2, "%s;%s;%s;%s;%s;%s;%s\n",
                        p.obj, p.cours, p.niv, p.freq,
                        p.entraineur, p.horaire, p.format);
            }
            else tr = 1;
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("nouv.txt", filename);
    }
    return tr;
}




void afficher_erreur(const char *msg)
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s", msg);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}





void ajouter_preferences() {
    Preference p;
    strcpy(p.obj, objectifs[objectif]);
    strcpy(p.cours, types_cours[type_cours]);
    strcpy(p.niv, niveaux[niveau]);
    strcpy(p.freq, frequences[frequence]);
    strcpy(p.entraineur, prefs_entraineur[pref_entraineur]);
    strcpy(p.format, formats_message[format_message]);
    strcpy(p.horaire, horaires[pref_horaire]);

    for(int i = 0; i < nb_preferences; i++) {
        Preference tmp = preferences[i];
        if(strcmp(tmp.obj, p.obj) == 0 &&
           strcmp(tmp.cours, p.cours) == 0 &&
           strcmp(tmp.niv, p.niv) == 0 &&
           strcmp(tmp.freq, p.freq) == 0 &&
           strcmp(tmp.entraineur, p.entraineur) == 0 &&
           strcmp(tmp.horaire, p.horaire) == 0 &&
           strcmp(tmp.format, p.format) == 0) {
            printf("Cette preference existe deja !\n");
            return;
        }
    }

    if(nb_preferences < MAX_PREF) {
        preferences[nb_preferences++] = p;
        printf("Preference ajoutee !\n");
    } else {
        printf("Tableau de preferences plein !\n");
    }
}

void sauvegarder_preferences() {
    FILE *fpref = fopen("preference.txt", "a");
    FILE *fmail = fopen("envoieemail.txt", "a");

    if (!fpref || !fmail) {
        printf("Erreur ouverture fichier !\n");
        if (fpref) fclose(fpref);
        if (fmail) fclose(fmail);
        return;
    }

    for (int i = 0; i < nb_preferences; i++) {
        Preference p = preferences[i];

        /* preference.txt : FORMAT ORIGINAL */
        fprintf(fpref, "%s;%s;%s;%s;%s;%s;%s\n",
                p.obj,
                p.cours,
                p.niv,
                p.freq,
                p.entraineur,
                p.horaire,
                p.format);

        /* envoieemail.txt : AVEC EMAIL */
        fprintf(fmail, "%s;%s;%s;%s;%s;%s;%s;%s\n",
                membre_connecte,
                p.obj,
                p.cours,
                p.niv,
                p.freq,
                p.entraineur,
                p.horaire,
                p.format);
    }

    fclose(fpref);
    fclose(fmail);

    nb_preferences = 0;
    printf("Préférences sauvegardées correctement\n");
}

void enregistrer_rdv(const char *email, const char *heure)
{
FILE *f = fopen("rendezvous.txt", "a");
if (f)
{
fprintf(f, "%s %s\n", email, heure);
fclose(f);
}
}


int compter_type_cours(char fichier[100], int *nb_muscu, int *nb_danse, int *nb_cardio, int *nb_natation, int *nb_pilates)
{
    FILE *f;
    char ligne[512];

    *nb_muscu = 0;
    *nb_danse = 0;
    *nb_cardio = 0;
    *nb_natation = 0;
    *nb_pilates = 0;

    f = fopen(fichier, "r");
    if (f == NULL)
        return 0;

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        if (strstr(ligne, "Musculation") != NULL) (*nb_muscu)++;
        else if (strstr(ligne, "Danse") != NULL) (*nb_danse)++;
        else if (strstr(ligne, "Cardio") != NULL) (*nb_cardio)++;
        else if (strstr(ligne, "Natation") != NULL) (*nb_natation)++;
        else if (strstr(ligne, "Pilates") != NULL) (*nb_pilates)++;
    }

    fclose(f);
    return 1;
}





int entraineur_occupe(char *id_entraineur, int debut_h, int debut_m, int fin_h, int fin_m)
{
FILE *f = fopen("cours.txt", "r");
if (f == NULL) return 0;
cours c;
int intervalle_debut = debut_h * 60 + debut_m;
int intervalle_fin   = fin_h * 60 + fin_m;
while (fscanf(f, "%s %s %02d %02d %s %s %f %d %s",c.id_c, c.nom, &c.heure, &c.minute, c.date, c.dure, &c.frais, &c.capacite, c.id_e) != EOF)
{
if (strcmp(c.id_e, id_entraineur) == 0)
{
int cours_debut = c.heure * 60 + c.minute;
int duree_i = atoi(c.dure);
int cours_fin   = cours_debut + duree_i;
printf("Comparaison: %s -> intervalle_cours: %d-%d, intervalle_demande: %d-%d\n",
           c.id_e, cours_debut, cours_fin, intervalle_debut, intervalle_fin);
if (cours_fin > intervalle_debut && cours_debut < intervalle_fin)
{
fclose(f);
return 1; 
}
}
}
fclose(f);
return 0;
}


void Specialite(int choix_specialite[], char texte[])
{
    strcpy(texte, "Spécialité choisie :");
    if (choix_specialite[0] == 1)
        strcat(texte, " Musculation");
    if (choix_specialite[1] == 1)
        strcat(texte, " Danse");
    if (choix_specialite[2] == 1)
        strcat(texte, " Cardio");
    if (choix_specialite[3] == 1)
        strcat(texte, " Natation");
    if (choix_specialite[4] == 1)
        strcat(texte, " Pilates");
}


void Resultat(int choix[],char texte[])
{
	strcpy(texte,"Voulez-vous filtrer la recherche par:");
	if(choix[0]==1)
	strcat(texte,"Horaire");
	if(choix[1]==1)
	strcat (texte," Specialité");
}

void Res_suppr(int choix_suppr[],char texte[])
{
	strcpy(texte,"Voulez-vous filtrer la recherche par:");
	if(choix_suppr[0]==1)
	strcat(texte,"Type");
	if(choix_suppr[1]==1)
	strcat (texte,"idcours");
}

void choix_niveau(int choix_niv[],char texte[])
{
	strcpy(texte,"Vous_etes quel niveau?");
	if(choix_niv[0]==1)
	strcat(texte,"Débutant");
	if(choix_niv[1]==1)
	strcat (texte,"Intermediaire");
	if(choix_niv[2]==1)
	strcat (texte,"Avancé");
}

int rendezvous_occupe(const char *heure)
{
FILE *f;
char email[100], h[20];
f = fopen("rendezvous.txt", "r");
if (f == NULL)
return 0; 
while (fscanf(f, "%s %s", email, h) != EOF)
{
if (strcmp(h, heure) == 0)
{
fclose(f);
return 1; 
}
}
fclose(f);
return 0; 
}
int nb_rendezvous_pour_heure(const char *heure)
{
    FILE *f;
    char email[100], h[20];
    int count = 0;

    f = fopen("rendezvous.txt", "r");
    if (f == NULL)
        return 0;

    while (fscanf(f, "%s %s", email, h) != EOF)
    {
        if (strcmp(h, heure) == 0)
            count++;
    }

    fclose(f);
    return count;
}


void afficher_cours(char *filename)
{
    FILE *f = fopen(filename, "r");
    cours c;
    if (f != NULL)
    {
       while (fscanf(f, "%s %s %02d %02d %s %s %f %d %s",c.id_c, c.nom, &c.heure, &c.minute, c.date, c.dure, &c.frais, &c.capacite, c.id_e) != EOF)
        {
            printf("%s %s %02d %02d %s %s %f %d %s\n",c.id_c, c.nom, c.heure, c.minute, c.date, c.dure, c.frais, c.capacite, c.id_e);
        }
        fclose(f);
    }
}

int ajouter(char * filename, cours c )
{
    FILE * f=fopen(filename, "a");
    if(f!=NULL)
    {
        fprintf(f,"%s %s %02d %02d %s %s %f %d %s\n",c.id_c, c.nom, c.heure, c.minute, c.date, c.dure, c.frais, c.capacite, c.id_e);
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
        while (fscanf(f, "%s %s %02d %02d %s %s %f %d %s",c.id_c, c.nom, &c.heure, &c.minute, c.date, c.dure, &c.frais, &c.capacite, c.id_e) != EOF)
        {
            if(strcmp(c.id_c, id_c)==0)
            {
                fprintf(f2,"%s %s %02d %02d %s %s %.2f %d %s\n",nouv.id_c, nouv.nom, nouv.heure, nouv.minute, nouv.date, nouv.dure, nouv.frais, nouv.capacite, nouv.id_e);
                tr=1;
            }
            else
                fprintf(f2,"%s %s %02d %02d %s %s %f %d %s\n",c.id_c, c.nom, c.heure, c.minute, c.date, c.dure, c.frais, c.capacite, c.id_e);
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
	while (fscanf(f, "%s %s %02d %02d %s %s %f %d %s",c.id_c, c.nom, &c.heure, &c.minute, c.date, c.dure, &c.frais, &c.capacite, c.id_e) != EOF)
        {
            if(strcmp(c.id_c, id_c)==0){
                tr=1;
		continue;
	}
           
	fprintf(f2,"%s %s %02d %02d %s %s %f %d %s\n",c.id_c, c.nom, c.heure, c.minute, c.date, c.dure, c.frais, c.capacite, c.id_e);
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("nouv.txt", filename);
    }
    return tr;
}

cours chercher(char *filename,char *id_c)
{
cours c;
int tr = 0;
FILE *f = fopen(filename, "r");
if (f != NULL)
{
while (tr == 0 && fscanf(f, "%s %s %02d %02d %s %s %f %d %s",c.id_c, c.nom, &c.heure, &c.minute, c.date, c.dure, &c.frais, &c.capacite, c.id_e) != EOF)
{
if (strcmp(c.id_c, id_c) == 0)
tr = 1;
}
fclose(f);
}
if (tr == 0)
strcpy(c.id_c, "-1");
return c;
}


int inscrire_cours(char *filename, char *id_c, char *niveau)
{
    FILE *f = fopen(filename, "a");
    if (f != NULL)
    {
        fprintf(f, "%s %s\n", id_c,niveau); 
        fclose(f);
        return 1;
    }
    else
        return 0;
}

int verifier_login(const char *fichier, const char *email, const char *mdp)
{
    FILE *f = fopen(fichier, "r");
    char e[50], m[50];

    if (!f) return 0;

    while (fscanf(f, "%49s %49s", e, m) == 2)
    {
        if (strcmp(e, email) == 0 && strcmp(m, mdp) == 0)
        {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

time_t date_to_time(const char *date_str) {
    int j, m, a;
    sscanf(date_str, "%d/%d/%d", &j, &m, &a);
    struct tm tm_date = {0};
    tm_date.tm_mday = j;
    tm_date.tm_mon = m - 1;
    tm_date.tm_year = a - 1900;
    tm_date.tm_hour = 0;
    tm_date.tm_min = 0;
    tm_date.tm_sec = 0;
    return mktime(&tm_date);
}
int cours_est_confirme(const char *fichier_insc, const char *id_cours) {
    FILE *f = fopen(fichier_insc, "r");
    if (!f) return 0;

    char line[256], cours_id[20];
    while (fgets(line, sizeof(line), f)) {
        sscanf(line, "%19s", cours_id);
        if (strcmp(cours_id, id_cours) == 0) {
            fclose(f);
            return 1; // trouvé => confirmé
        }
    }
    fclose(f);
    return 0; // pas trouvé => non confirmé
}

void nettoyer_cours(const char *fichier_cours, const char *fichier_insc) {
    FILE *f = fopen(fichier_cours, "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir %s\n", fichier_cours);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        fclose(f);
        printf("Erreur : impossible de créer le fichier temporaire\n");
        return;
    }

    char line[256], date_str[15], id_cours[20];
    time_t now = time(NULL);

    while (fgets(line, sizeof(line), f)) {
        sscanf(line, "%19s %*s %*d %*d %14s", id_cours, date_str);

        time_t t_cours = date_to_time(date_str);
        double diff = difftime(t_cours, now) / (60*60*24); // différence en jours

        int confirme = cours_est_confirme(fichier_insc, id_cours);

        if (diff >= 0 && (confirme || diff > 2)) {
            // garder le cours
            fprintf(temp, "%s", line);
        }
        // sinon : cours dépassé ou non confirmé à moins de 2 jours => supprimer
    }

    fclose(f);
    fclose(temp);

    remove(fichier_cours);
    rename("temp.txt", fichier_cours);
}

void open_mail_client() {
    system("ad.lin.stra.min@gmail.com");
}

void show_phone_number() {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Appelez-nous au : +216 XX XXX XXX");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


const char* chatbot_admin_reponse(const char *msg)
{
    static char buffer[256];
    strcpy(buffer, msg);
    to_lower(buffer);

    if (strstr(buffer, "comment_ajouter_un_evenement?"))
    return "Pour ajouter un événement, l’administrateur saisit les informations et valide l’ajout. L’événement devient visible.";

if (strstr(buffer, "comment_modifier_un_evenement?"))
    return "Pour modifier un événement, l’administrateur met à jour les informations et enregistre les changements.";

if (strstr(buffer, "comment_supprimer_un_evenement?"))
    return "Pour supprimer un événement, l’administrateur sélectionne l’événement et confirme la suppression.";





if (strstr(buffer, "comment_ajouter_un_centre?"))
    return "Pour ajouter un centre sportif, l’administrateur saisit les informations du centre et valide l’ajout.";

if (strstr(buffer, "comment_modifier_un_centre?"))
    return "Pour modifier un centre sportif, l’administrateur met à jour les informations et enregistre les changements.";

if (strstr(buffer, "comment_supprimer_un_centre?"))
    return "Pour supprimer un centre sportif, l’administrateur sélectionne le centre et confirme la suppression.";





if (strstr(buffer, "comment_ajouter_un_membre?"))
    return "Pour ajouter un membre, l’administrateur ouvre la gestion des membres, saisit les informations nécessaires, valide l’ajout. Le système génère automatiquement l’identifiant, le login et le mot de passe, puis envoie un email.";

if (strstr(buffer, "comment_modifier_un_membre?"))
    return "Pour modifier un membre, l’administrateur sélectionne le membre, met à jour ses informations et enregistre les changements. Un email de notification est envoyé.";

if (strstr(buffer, "comment_supprimer_un_membre?"))
    return "Pour supprimer un membre, l’administrateur sélectionne le membre et confirme la suppression. Le compte est définitivement supprimé.";




if (strstr(buffer, "comment_ajouter_un_entraineur?"))
    return "Pour ajouter un entraîneur, l’administrateur saisit ses informations. Le système génère automatiquement les accès et envoie un email.";

if (strstr(buffer, "comment_modifier_un_entraineur?"))
    return "Pour modifier un entraîneur, l’administrateur met à jour les informations et enregistre les changements. Un email est envoyé.";

if (strstr(buffer, "comment_supprimer_un_entraineur?"))
    return "Pour supprimer un entraîneur, l’administrateur sélectionne l’entraîneur et confirme la suppression du compte.";

    
if (strstr(buffer, "quand_les_emails_sont_envoyes?"))
    return "Un email est envoyé lors de l’ajout ou de la modification d’un membre ou d’un entraîneur.";


return "Je n’ai pas compris ";

}



void to_lower(char *s)
{
     int i;
    for (i = 0; s[i]; i++)
        s[i] = tolower((unsigned char)s[i]);
}




const char* chatbot_membre_reponse(const char *msg)
{
    static char buffer[256];
    strcpy(buffer, msg);
    to_lower(buffer);

   if (strstr(buffer, "comment_demander_un_entraineur?"))
    return "Le membre accède à son espace personnel, fait une demande d’entraîneur et sélectionne le type d’entraînement souhaité.";


if (strstr(buffer, "comment_s'inscrire_a_un_cours?"))
    return "Le membre consulte la liste des cours disponibles, sélectionne le cours souhaité et confirme son inscription.";

if (strstr(buffer, "que_se_passe_apres_l'inscription_a_un_cours?"))
    return "Après l’inscription, le membre est ajouté à la liste des participants et peut consulter les détails du cours.";



if (strstr(buffer, "comment_enregistrer_mes_preferences_de_cours?"))
    return "Le membre remplit le formulaire de préférences et enregistre ses choix.";

if (strstr(buffer, "que_se_passe_apres_l'enregistrement_de_mes_preferences?"))
    return "Le système analyse les nouveaux cours et envoie un email si un cours compatible devient disponible.";


if (strstr(buffer, "comment_participer_a_un_evenement?"))
    return "Le membre consulte les événements disponibles, sélectionne l’événement souhaité et confirme sa participation.";

if (strstr(buffer, "vais_je_recevoir_une_confirmation_pour_un_evenement?"))
    return "Oui, une confirmation est envoyée après l’inscription à un événement.";



if (strstr(buffer, "quand_vais_je_recevoir_des_emails?"))
    return "Le membre reçoit des emails lors de l’inscription à un cours, à un événement ou lorsqu’un cours compatible est disponible.";

    return "Je n’ai pas compris ";



}
const char* chatbot_entraineur_reponse(const char *msg)
{
    static char buffer[256];
    strcpy(buffer, msg);
    to_lower(buffer);

    if (strstr(buffer, "comment_un_entraineur_peut_s'inscrire_a_un_cours?"))
    return "L’entraîneur consulte la liste des cours et s’inscrit au cours souhaité depuis son espace personnel.";

if (strstr(buffer, "que_se_passe_apres_l'inscription_a_un_cours_entraineur?"))
    return "Après l’inscription, l’entraîneur est associé au cours et peut consulter ses informations.";


if (strstr(buffer, "comment_un_entraineur_peut_s'inscrire_a_un_centre?"))
    return "L’entraîneur sélectionne le centre souhaité. La demande est traitée par l’administration.";

if (strstr(buffer, "que_se_passe_apres_l'inscription_a_un_centre?"))
    return "L’administration traite la demande et l’entraîneur reçoit une notification.";


if (strstr(buffer, "vais_je_recevoir_un_email_apres_une_inscription?"))
    return "Oui, un email est envoyé automatiquement après chaque inscription à un cours ou à un centre.";



    return "Je n’ai pas compris ";



}



