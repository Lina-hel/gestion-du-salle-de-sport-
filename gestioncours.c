#include "gestion_cours.h"
#include <string.h> 
#include <stdio.h>
#define MAX_PREF 100
#include <gtk/gtk.h>


Preference preferences[MAX_PREF];
int nb_preferences = 0;

char objectifs[][20] = {"", "Perte de poids", "Prise de masse", "Bien étre/Detente", "Performance sportive"};
char types_cours[][20] = {"", "Musculation", "Danse", "Cardio", "Pilates", "Natation"};
char niveaux[][20] = {"", "Débutant", "Intermédiaire", "Avancé"};
char frequences[][20] = {"", "1 fois/semaine", "2-3 fois/semaine", "+4 fois/semaine"};
char prefs_entraineur[][20] = {"", "Femme", "Homme", "Peu importe"};
char modes_notification[][20] = {"", "Email", "SMS", "Application"};
char formats_message[][20] = {"", "Résumé simple", "lien vers inscription"};
char horaires[][20] = { "Matin: 08:00-12:00", "Après midi: 12:00-18:00", "Nuit: 18:00-21:00"};


int supprimer_preference_fichier(char *filename,char *obj_pref)
{
    int tr=0;
    Preference p;
    FILE *f=fopen(filename,"r");
    FILE *f2=fopen("nouv.txt","w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %s %s %s %s %s %s %s",p.obj,p.cours,p.niv,p.freq,p.entraineur,p.horaire,p.notif,p.format)!=EOF)
        {
            if(strcmp(p.obj,obj_pref)==0){tr=1;continue;}
            fprintf(f2,"%s %s %s %s %s %s %s %s\n",p.obj,p.cours,p.niv,p.freq,p.entraineur,p.horaire,p.notif,p.format);
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("nouv.txt",filename);
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
if(nb_preferences >= MAX_PREF) {
printf("Tableau plein !\n");
return;
}
strcpy(p.obj, objectifs[objectif]);
strcpy(p.cours, types_cours[type_cours]);
strcpy(p.niv, niveaux[niveau]);
strcpy(p.freq, frequences[frequence]);
strcpy(p.entraineur, prefs_entraineur[pref_entraineur]);
strcpy(p.notif, modes_notification[mode_notification]);
strcpy(p.format, formats_message[format_message]);
 strcpy(p.horaire, horaires[pref_horaire]);
preferences[nb_preferences++] = p;
printf("Préférences ajoutées !\n");
}

void sauvegarder_preferences() {
 FILE *f = fopen("preference.txt", "a");
    if(f == NULL) {
        printf("Erreur ouverture fichier !\n");
        return;
    }
 for(int i=0; i<nb_preferences; i++) {
        Preference p = preferences[i];
        
        fprintf(f, "%s;%s;%s;%s;%s;%s;%s;%s\n",
                p.obj, p.cours, p.niv, p.freq,
                p.entraineur, p.notif, p.format, p.horaire);
    }

    fclose(f);
    printf("Préférences sauvegardées dans preference.txt\n");
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

    while (fscanf(f, "%s %s", e, m) != EOF)
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
