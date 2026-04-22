#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"

int ajouter_evenement(Evenement e) {
	FILE *f = fopen("evenements.txt", "a");
 
	if (f == NULL)
{   	printf("impossible d'ouvrir le fichier evenements.txt");
    	return 0;
}

	fprintf(f, "%d %s %d %d %d %d %d %s %s %.2f %d %s\n",
        	e.id, e.nom, e.jour, e.mois, e.annee,
        	e.heure, e.min, e.lieu, e.type, e.frais,
        	e.nb_inscrits, e.categorie_participant);

	fclose(f);
	return 1;
}


 

int modifier_evenement(Evenement e_modif) {
    FILE *f = fopen("evenements.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");
    Evenement e;
    int trouve = 0;

    if (f == NULL || tmp == NULL) {
        printf("Erreur ouverture fichier.\n");
        return 0;
    }

    while (fscanf(f, "%d %s %d %d %d %d %d %s %s %f %d %s",
              	&e.id, e.nom, &e.jour, &e.mois, &e.annee,
              	&e.heure, &e.min, e.lieu, e.type, &e.frais,
              	&e.nb_inscrits, e.categorie_participant) == 12) 
    {
        if (e.id == e_modif.id) {
            fprintf(tmp, "%d %s %d %d %d %d %d %s %s %.2f %d %s\n",
                    e_modif.id, e_modif.nom,
                    e_modif.jour, e_modif.mois, e_modif.annee,
                    e_modif.heure, e_modif.min,
                    e_modif.lieu, e_modif.type,
                    e_modif.frais, e_modif.nb_inscrits,
                    e_modif.categorie_participant);
            trouve = 1;
        }
        else {
            fprintf(tmp, "%d %s %d %d %d %d %d %s %s %.2f %d %s\n",
                    e.id, e.nom,
                    e.jour, e.mois, e.annee,
                    e.heure, e.min,
                    e.lieu, e.type,
                    e.frais, e.nb_inscrits,
                    e.categorie_participant);
        }
    }

    fclose(f);
    fclose(tmp);
    remove("evenements.txt");
    rename("temp.txt", "evenements.txt");
    return trouve;
}



void chercher_evenment(char *filename,int id)
{
Evenement e;
int tr = 0;
FILE *f = fopen(filename, "r");
if (f != NULL)
{
while (tr == 0 && fscanf(f, "%d %s %d %d %d %d %d %s %s %f %d %s",
              	&e.id, e.nom, &e.jour, &e.mois, &e.annee,
              	&e.heure, &e.min, e.lieu, e.type, &e.frais,
              	&e.nb_inscrits, e.categorie_participant) != EOF)
{
if (e.id==id) 
tr = 1;
}
fclose(f);
}
if (tr == 0)
e.id=-1;

}





int supprimer_evenement(int id) {
	FILE *f = fopen("evenements.txt", "r");
	FILE *tmp = fopen("temp.txt", "w");
	Evenement e;
	int trouve = 0;

	if (f == NULL || tmp == NULL) {
    	printf("Erreur ouverture fichier.\n");
    	return 0;
	}

	while (fscanf(f, "%d %s %d %d %d %d %d %s %s %f %d %s",
              	&e.id, e.nom, &e.jour, &e.mois, &e.annee,
              	&e.heure, &e.min, e.lieu, e.type, &e.frais,
              	&e.nb_inscrits, e.categorie_participant) == 12) {

    	if (e.id == id)
        	trouve = 1;
    	else
        	fprintf(tmp, "%d %s %d %d %d %d %d %s %s %.2f %d %s\n",
                	e.id, e.nom, e.jour, e.mois, e.annee,
                	e.heure, e.min, e.lieu, e.type,
                	e.frais, e.nb_inscrits, e.categorie_participant);
	}

	fclose(f);
	fclose(tmp);
	remove("evenements.txt");
	rename("temp.txt", "evenements.txt");

	if (trouve)
    	printf("Événement supprimé avec succès.\n");
	else
    	printf("Aucun événement trouvé avec cet ID.\n");

	return trouve;
}





int participer_evenement(int id_evenement, int id_participant, char categorie[]) {
	FILE *f = fopen("evenements.txt", "r");
	FILE *temp = fopen("temp.txt", "w");
	FILE *p = fopen("participants.txt", "a");
	Evenement e;
	int trouve = 0;

	if (f == NULL || temp == NULL || p == NULL) {
    	printf("Erreur d'ouverture fichier.\n");
    	return 0;
	}

	while (fscanf(f, "%d %s %d %d %d %d %d %s %s %f %d %s",
              	&e.id, e.nom, &e.jour, &e.mois, &e.annee,
              	&e.heure, &e.min, e.lieu, e.type, &e.frais,
              	&e.nb_inscrits, e.categorie_participant) == 12) {

    	if (e.id == id_evenement) {
        	trouve = 1;
        	e.nb_inscrits++;
        	fprintf(p, "%d %d %s\n", id_evenement, id_participant, categorie);
    	}
    	fprintf(temp, "%d %s %d %d %d %d %d %s %s %.2f %d %s\n",
            	e.id, e.nom, e.jour, e.mois, e.annee,
            	e.heure, e.min, e.lieu, e.type,
            	e.frais, e.nb_inscrits, e.categorie_participant);
	}

	fclose(f);
	fclose(temp);
	fclose(p);
	remove("evenements.txt");
	rename("temp.txt", "evenements.txt");

	if (trouve)
    	printf("Participant %d ajouté à l'événement %d dans la catégorie %s.\n",
           	id_participant, id_evenement, categorie);
	else
    	printf("Événement introuvable.\n");

	return trouve;
}


enum {
    R_ID,
    R_NOM,
    R_DATE,
    R_HEURE,
    R_MINUTE,
    R_LIEU,
    R_FRAIS,
    R_TYPE,
    R_NB_INSCRITS,
    R_CATEGORIE_PARTICIPANTS,
    R_COLUMNS
};

void vider_treeview(GtkWidget *treeview)
{
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    
    if (model != NULL) {
        if (GTK_IS_LIST_STORE(model)) {
            gtk_list_store_clear(GTK_LIST_STORE(model));
        }
    }
}

void afficher_evenements_treeview(GtkWidget *liste)
{
    GtkTreeView *treeview = GTK_TREE_VIEW(liste);
    GtkTreeView *tv = GTK_TREE_VIEW(treeview);
    GtkTreeIter iter;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    treeview = GTK_TREE_VIEW(liste);
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));

    
    FILE *f;
    Evenement e;
    char heure_str[50], frais_str[50],min_str[50],id_str[50],inscrit_str[50],date[50];
    
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    
    if (store == NULL) {
 renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" id",renderer,"text",R_ID,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" nom",renderer,"text",R_NOM,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" date",renderer,"text",R_DATE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" heure",renderer,"text",R_HEURE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" minute",renderer,"text",R_MINUTE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" lieu",renderer,"text",R_LIEU,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" type",renderer,"text",R_TYPE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" frais",renderer,"text",R_FRAIS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" nb_inscrits",renderer,"text",R_NB_INSCRITS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" categorie_participants",renderer,"text",R_CATEGORIE_PARTICIPANTS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

}      

store = gtk_list_store_new(
    R_COLUMNS,
    G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
    G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

f=fopen("evenements.txt","r");
if(f==NULL)
{
return;
}
else
{
f=fopen("evenements.txt","a+");
while (fscanf(f, "%d %s %d %d %d %d %d %s %s %f %d %s",&e.id, e.nom, &e.jour, &e.mois,&e.annee,&e.heure, &e.min, e.lieu, e.type,&e.frais,&e.nb_inscrits,e.categorie_participant) != EOF)
{
char horaire[6];
horaire[0] = (e.heure / 10) + '0';
horaire[1] = (e.heure % 10) + '0';
horaire[2] = ':';
horaire[3] = (e.min / 10) + '0';
horaire[4] = (e.min % 10) + '0';
horaire[5] = '\0';

sprintf(id_str, "%d", e.id);
sprintf(heure_str, "%d", e.heure);
sprintf(min_str, "%d", e.min);
sprintf(inscrit_str, "%d", e.nb_inscrits);
sprintf(frais_str, "%.3f", e.frais);
sprintf(date, "%02d/%02d/%04d", e.jour,e.mois,e.annee);

gtk_list_store_append(store, &iter);
gtk_list_store_set(store, &iter,
    R_ID, id_str,
    R_NOM, e.nom,
    R_DATE, date,
    R_HEURE, heure_str,
    R_MINUTE, min_str,
    R_LIEU, e.lieu,
    R_FRAIS, frais_str,
    R_TYPE, e.type,
    R_NB_INSCRITS, inscrit_str,
    R_CATEGORIE_PARTICIPANTS, e.categorie_participant,
    -1
);
}
fclose(f);
gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
g_object_unref (store);

}
}

enum {
    PARTICIPANTS_ID,
    PARTICIPANTS_ID_PARTICIPANT,
    PARTICIPANTS_TYPE,
    PARTICIPANTS_COLUMNS
};

void afficher_evenements_participes_treeview(GtkWidget *liste)
{
    GtkTreeIter iter;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;
    FILE *f;
    Evenement e;
    char id_str[20], id_participant_str[20];

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

    if (store == NULL)
    {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(
            "ID", renderer, "text", PARTICIPANTS_ID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(
            "ID Participant", renderer, "text", PARTICIPANTS_ID_PARTICIPANT, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(
            "Type", renderer, "text", PARTICIPANTS_TYPE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    store = gtk_list_store_new(
        PARTICIPANTS_COLUMNS,
        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    f = fopen("participants.txt", "r");
    if (f == NULL)
    {
        g_warning("Impossible d’ouvrir participants.txt");
        return;
    }

    while (fscanf(f, "%d %d %29s",
                  &e.id,
                  &e.id_participant,
                  e.type) != EOF)
    {
        sprintf(id_str, "%d", e.id);
        sprintf(id_participant_str, "%d", e.id_participant);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            PARTICIPANTS_ID, id_str,
            PARTICIPANTS_ID_PARTICIPANT, id_participant_str,
            PARTICIPANTS_TYPE, e.type,
            -1);
    }

    fclose(f);
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}




void chercher_evenement_treeview(GtkWidget *liste, int id_recherche)
{

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    FILE *f;
    Evenement e;
    char heure_str[50], frais_str[50], min_str[50], id_str[50], inscrit_str[50], date[50];
    int trouve = 0;
    
    if (!liste || !GTK_IS_TREE_VIEW(liste)) {
        g_warning("TreeView invalide !");
        return;
    }
    
    store = gtk_list_store_new(
        R_COLUMNS,
        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING
    );
    

    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(liste)) == 0) {
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", R_ID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", R_NOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", R_DATE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Heure", renderer, "text", R_HEURE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Minute", renderer, "text", R_MINUTE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Lieu", renderer, "text", R_LIEU, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", R_TYPE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Frais", renderer, "text", R_FRAIS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nb inscrits", renderer, "text", R_NB_INSCRITS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Catégorie", renderer, "text", R_CATEGORIE_PARTICIPANTS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }
    
    f = fopen("evenements.txt", "r");
    if (f == NULL) {
        g_warning("Impossible d'ouvrir le fichier evenements.txt !");
        g_object_unref(store);
        return;
    }
    
   
    while (fscanf(f, "%d %s %d %d %d %d %d %s %s %f %d %s",
                  &e.id, e.nom, &e.jour, &e.mois, &e.annee,
                  &e.heure, &e.min, e.lieu, e.type, &e.frais,
                  &e.nb_inscrits, e.categorie_participant) == 12) {
        
        
        if (id_recherche > 0) {
            if (e.id == id_recherche) {
                trouve = 1;
                
                sprintf(id_str, "%d", e.id);
                sprintf(heure_str, "%d", e.heure);
                sprintf(min_str, "%d", e.min);
                sprintf(inscrit_str, "%d", e.nb_inscrits);
                sprintf(frais_str, "%.3f", e.frais);
                sprintf(date, "%02d/%02d/%04d", e.jour, e.mois, e.annee);
                
                
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                    R_ID, id_str,
                    R_NOM, e.nom,
                    R_DATE, date,
                    R_HEURE, heure_str,
                    R_MINUTE, min_str,
                    R_LIEU, e.lieu,
                    R_FRAIS, frais_str,
                    R_TYPE, e.type,
                    R_NB_INSCRITS, inscrit_str,
                    R_CATEGORIE_PARTICIPANTS, e.categorie_participant,
                    -1
                );
                break;  
            }
        } else {
            
            trouve = 1;
            sprintf(id_str, "%d", e.id);
            sprintf(heure_str, "%d", e.heure);
            sprintf(min_str, "%d", e.min);
            sprintf(inscrit_str, "%d", e.nb_inscrits);
            sprintf(frais_str, "%.3f", e.frais);
            sprintf(date, "%02d/%02d/%04d", e.jour, e.mois, e.annee);
            
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                R_ID, id_str,
                R_NOM, e.nom,
                R_DATE, date,
                R_HEURE, heure_str,
                R_MINUTE, min_str,
                R_LIEU, e.lieu,
                R_FRAIS, frais_str,
                R_TYPE, e.type,
                R_NB_INSCRITS, inscrit_str,
                R_CATEGORIE_PARTICIPANTS, e.categorie_participant,
                -1
            );
        }
    }
    
    fclose(f);
    
    if (!trouve && id_recherche > 0) {
        g_warning("Aucun événement trouvé avec l'ID %d", id_recherche);
    }
    
    
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);




}



Date get_date_from_entry(GtkEntry *entry) {
    Date date; 
    const char *date_str = gtk_entry_get_text(entry);
    
    if (date_str == NULL || strlen(date_str) == 0) {
        return date;
    }
 
    if (sscanf(date_str, "%d-%d-%d", &date.day, &date.month, &date.year) == 3) {
        return date;
    }
}




int calculer_nb_participants(int event_id) {
    
 
 printf("\n🔍 Recherche participants pour événement ID: %d\n", event_id);
    
    FILE *f = fopen("participants.txt", "r");
    if (!f) {
        printf("❌ ERREUR: Fichier participants.txt introuvable\n");
        return 0;
    }

    int count = 0;
    char ligne[256];
    int ligne_num = 1;
    
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        ligne[strcspn(ligne, "\n")] = 0;
        
        if (strlen(ligne) == 0) continue;
        
        int id_event, id_participant;  // NOTE: ORDRE INVERSE !
        char type[50] = "";
        
        // Lire: ID_événement ID_participant Type
        int resultat = sscanf(ligne, "%d %d %49s", &id_event, &id_participant, type);
        
        if (resultat >= 2) {
            printf("  Ligne %d: Événement %d <- Participant %d", 
                   ligne_num, id_event, id_participant);
            if (resultat == 3) printf(" (Type: %s)", type);
            printf("\n");
            
            if (id_event == event_id) {
                count++;
                printf("    ✅ CORRESPONDANCE! Total: %d\n", count);
            }
        }
        
        ligne_num++;
    }

    fclose(f);
    
    printf("  📊 Total pour événement %d: %d participants\n", event_id, count);
    return count;





}


int calculer_stats(int ids[], int counts[], int max) {
    printf("\n LECTURE DU FICHIER evenements.txt\n");
    
    FILE *f = fopen("evenements.txt", "r");
    if (!f) {
        printf(" ERREUR: Fichier evenements.txt introuvable\n");
        return 0;
    }

    int n = 0;
    char ligne[256];
    int ligne_num = 1;
    
    while (n < max && fgets(ligne, sizeof(ligne), f) != NULL) {
        
        ligne[strcspn(ligne, "\n")] = 0;
        
        if (strlen(ligne) == 0) continue;
        
        printf("\n--- Ligne %d: %s\n", ligne_num, ligne);
        
        
        int id_lu;
        if (sscanf(ligne, "%d", &id_lu) == 1) {
            ids[n] = id_lu;
            counts[n] = calculer_nb_participants(id_lu);
            
            printf("\n Événement %d: ID = %d, Participants = %d\n", 
                   n+1, ids[n], counts[n]);
            
            n++;
        } else {
            printf("  Ligne ignorée (pas d'ID numérique trouvé)\n");
        }
        
        ligne_num++;
    }

    fclose(f);
    
    if (n == 0) {
        printf("\n AUCUN événement valide trouvé!\n");
    } else {
        printf("\n Total événements valides lus: %d\n", n);
    }
    
    return n;
}















































