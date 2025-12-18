#include <stdio.h>
#include <string.h>
#include "centre.h"


enum
{
    ECenterID,
    ECenterNom,
    ECenterAdresse,
    ECenterType,
    ECenterSpecialites,
    ECenterHoraire,
    ECenterParking,
    ECenterCapacite,
    ECenterDate,
    COLUMNS_CENTER
};




int centre_id_exists(const char *id)
{
    FILE *f = fopen("centres.txt", "r");
    char line[512], fid[50];

    if (f == NULL)
        return 0;

    while (fgets(line, sizeof(line), f))
    {
        sscanf(line, "%49[^;]", fid);
        if (strcmp(fid, id) == 0)
        {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}




int match_specialite(const char *centre_specs, const char *rech_specs)
{
    char tmp[200];
    char *token;

    if (rech_specs == NULL || strlen(rech_specs) == 0)
        return 0;

    strcpy(tmp, rech_specs);
    token = strtok(tmp, " ");

    while (token != NULL)
    {
        if (strstr(centre_specs, token) != NULL)
            return 1;

        token = strtok(NULL, " ");
    }

    return 0;
}

/* Ajouter centre dans un fichier */
void ajouter_centre(centre c)
{
    FILE *f = fopen("centres.txt", "a");
    if (f != NULL)
    {
        fprintf(f, "%s;%s;%s;%s;%s;%s;%s;%d;%s\n",
                c.id,
                c.nom,
                c.adresse,
                c.type,
                c.specialites,
                c.horaire,
                c.parking,
                c.capacite,
                c.date_ouverture);

        fclose(f);
    }
}







int modifier_centre(centre nouv)
{
    FILE *f, *tmp;
    centre c;
    int found = 0;
    char line[512];

    f = fopen("centres.txt", "r");
    tmp = fopen("centres_tmp.txt", "w");

    if (f == NULL || tmp == NULL)
        return 0;

    while (fgets(line, sizeof(line), f))
    {
        sscanf(line,
               "%49[^;];%49[^;];%99[^;];%19[^;];%99[^;];%49[^;];%9[^;];%d;%19[^\n]",
               c.id,
               c.nom,
               c.adresse,
               c.type,
               c.specialites,
               c.horaire,
               c.parking,
               &c.capacite,
               c.date_ouverture);

        if (strcmp(c.id, nouv.id) == 0)
        {
            fprintf(tmp, "%s;%s;%s;%s;%s;%s;%s;%d;%s\n",
                    nouv.id,
                    nouv.nom,
                    nouv.adresse,
                    nouv.type,
                    nouv.specialites,
                    nouv.horaire,
                    nouv.parking,
                    nouv.capacite,
                    nouv.date_ouverture);
            found = 1;
        }
        else
        {
            fputs(line, tmp);
        }
    }

    fclose(f);
    fclose(tmp);

    remove("centres.txt");
    rename("centres_tmp.txt", "centres.txt");

    return found;
}

int delete_centre(const char *old_id)
{
    FILE *f, *tmp;
    centre c;
    char line[512];
    int deleted = 0;

    f = fopen("centres.txt", "r");
    tmp = fopen("centres_tmp.txt", "w");

    if (f == NULL || tmp == NULL)
        return 0;

    while (fgets(line, sizeof(line), f))
    {
        sscanf(line,
               "%49[^;];%49[^;];%99[^;];%19[^;];%99[^;];%49[^;];%9[^;];%d;%19[^\n]",
               c.id,
               c.nom,
               c.adresse,
               c.type,
               c.specialites,
               c.horaire,
               c.parking,
               &c.capacite,
               c.date_ouverture);

        if (strcmp(c.id, old_id) == 0)
        {
            deleted = 1;
        }
        else
        {
            fputs(line, tmp);
        }
    }

    fclose(f);
    fclose(tmp);

    if (!deleted)
    {
        remove("centres_tmp.txt");
        return 0;
    }

    remove("centres.txt");
    rename("centres_tmp.txt", "centres.txt");

    return 1;
}




void show_centre(GtkWidget *fr, const char *rech_id_nom, const char *rech_specialite)
{
    centre c;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    FILE *f;

    store = gtk_list_store_new(
        COLUMNS_CENTER,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_INT,
        G_TYPE_STRING
    );

    if (store == NULL)
        return;

    if (gtk_tree_view_get_model(GTK_TREE_VIEW(fr)) == NULL)
    {
        renderer = gtk_cell_renderer_text_new();

        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", ECenterID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", ECenterNom, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        column = gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text", ECenterAdresse, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", ECenterType, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        column = gtk_tree_view_column_new_with_attributes("Spécialités", renderer, "text", ECenterSpecialites, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        column = gtk_tree_view_column_new_with_attributes("Horaire", renderer, "text", ECenterHoraire, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        column = gtk_tree_view_column_new_with_attributes("Parking", renderer, "text", ECenterParking, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        column = gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", ECenterCapacite, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);

        column = gtk_tree_view_column_new_with_attributes("Date ouverture", renderer, "text", ECenterDate, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(fr), column);
    }

    f = fopen("centres.txt", "r");
    if (f == NULL)
        return;

    while (fscanf(
               f,
               "%49[^;];%49[^;];%99[^;];%19[^;];%99[^;];%49[^;];%9[^;];%d;%19[^\n]\n",
               c.id,
               c.nom,
               c.adresse,
               c.type,
               c.specialites,
               c.horaire,
               c.parking,
               &c.capacite,
               c.date_ouverture) != EOF)
    {
       int match = 0;

	if ((rech_id_nom == NULL || strlen(rech_id_nom) == 0) &&
	    (rech_specialite == NULL || strlen(rech_specialite) == 0))
	{
	    match = 1;
	}
	else
	{
	    if (rech_id_nom != NULL && strlen(rech_id_nom) > 0)
	    {
		if (strstr(c.id, rech_id_nom) != NULL ||
		    strstr(c.nom, rech_id_nom) != NULL)
		    match = 1;
	    }

	    if (rech_specialite != NULL && strlen(rech_specialite) > 0)
	    {
		if (match_specialite(c.specialites, rech_specialite))
		    match = 1;
	    }
	}

        if (match)
        {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(
                store, &iter,
                ECenterID, c.id,
                ECenterNom, c.nom,
                ECenterAdresse, c.adresse,
                ECenterType, c.type,
                ECenterSpecialites, c.specialites,
                ECenterHoraire, c.horaire,
                ECenterParking, c.parking,
                ECenterCapacite, c.capacite,
                ECenterDate, c.date_ouverture,
                -1);
        }
    }

    gtk_tree_view_set_model(GTK_TREE_VIEW(fr), GTK_TREE_MODEL(store));
    g_object_unref(store);
    fclose(f);
}






StatCentre stat_centre(void)
{
    StatCentre s = {0, 0, 0, 0, 0};
    FILE *f;
    centre c;

    f = fopen("centres.txt", "r");
    if (f == NULL)
        return s;

    while (fscanf(f,
                  "%49[^;];%49[^;];%99[^;];%19[^;];%99[^;];%49[^;];%9[^;];%d;%19[^\n]\n",
                  c.id,
                  c.nom,
                  c.adresse,
                  c.type,
                  c.specialites,
                  c.horaire,
                  c.parking,
                  &c.capacite,
                  c.date_ouverture) != EOF)
    {
        if (strstr(c.specialites, "Cardio")) s.cardio++;
        if (strstr(c.specialites, "Musculation")) s.musculation++;
        if (strstr(c.specialites, "Danse")) s.danse++;
        if (strstr(c.specialites, "Pilates")) s.pilates++;
        if (strstr(c.specialites, "Natation")) s.natation++;
    }

    fclose(f);
    return s;
}




int entraineur_existe(const char *id)
{
    FILE *f;
    Entraineur e;

    f = fopen("entraineur.txt", "r");


    while (fscanf(f,
        "%19[^;];%19[^;];%19[^;];%19[^;];%99[^;];%9[^;];%19[^;];%49[^;];%19[^\n]\n",
        e.id, e.nom, e.prenom, e.cin, e.email, e.sexe,
        e.date_naissance, e.centre, e.specialite) != EOF)
    {
        if (strcmp(e.id, id) == 0)
        {
            fclose(f);
            return 1;

        }
    }
    fclose(f);
    return 0;
}





int inscription_existe(const char *id_entraineur, const char *id_centre)
{
    FILE *f;
    char id_e[20], id_c[20], nom_c[50];

    f = fopen("inscriptions.txt", "r");
    if (!f) return 0;

    while (fscanf(f, "%19[^;];%19[^;];%49[^\n]\n",
                   id_e, id_c, nom_c) != EOF)
    {
        if (strcmp(id_e, id_entraineur) == 0 &&
            strcmp(id_c, id_centre) == 0)
        {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}




void ajouter_inscription(const char *id_entraineur,
                         const char *id_centre,
                         const char *nom_centre)
{
    FILE *f = fopen("inscriptions.txt", "a");
    if (!f) return;

    fprintf(f, "%s;%s;%s\n",
            id_entraineur,
            id_centre,
            nom_centre);

    fclose(f);
}


enum
{
    EInsIdEnt,
    EInsIdCentre,
    EInsNomCentre,
    NBR_COL_INS
};



void show_inscription(GtkWidget *tv, const char *id_entraineur)
{
    GtkListStore *store;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    FILE *f;

    char id_e[20], id_c[20], nom_c[50];

    store = gtk_list_store_new(
        NBR_COL_INS,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_STRING
    );

    if (gtk_tree_view_get_model(GTK_TREE_VIEW(tv)) == NULL)
    {
        renderer = gtk_cell_renderer_text_new();

        column = gtk_tree_view_column_new_with_attributes(
            "ID Entraîneur", renderer, "text", EInsIdEnt, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(tv), column);

        column = gtk_tree_view_column_new_with_attributes(
            "ID Centre", renderer, "text", EInsIdCentre, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(tv), column);

        column = gtk_tree_view_column_new_with_attributes(
            "Nom Centre", renderer, "text", EInsNomCentre, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(tv), column);
    }

    f = fopen("inscriptions.txt", "r");
    if (!f) return;

    while (fscanf(f, "%19[^;];%19[^;];%49[^\n]\n",
                  id_e, id_c, nom_c) != EOF)
    {
        if (
            strcmp(id_e, id_entraineur) == 0)
        {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               EInsIdEnt, id_e,
                               EInsIdCentre, id_c,
                               EInsNomCentre, nom_c,
                               -1);
        }
    }

    fclose(f);
    gtk_tree_view_set_model(GTK_TREE_VIEW(tv), GTK_TREE_MODEL(store));
    g_object_unref(store);
}











