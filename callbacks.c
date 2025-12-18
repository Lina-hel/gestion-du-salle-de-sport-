#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "coach.h"

entraineur ent;
enum
{
COL_ID,
COL_NOM,
COL_PRENOM,
COL_CIN,
COL_SEXE,
COL_DATE,
COL_CENTRE,
N_COLS
};



GtkWidget *treeview_modifier_ent;
GtkWidget *entry_recherche_id_ent; 


void creer_colonnes_treeview_entraineur(GtkWidget *treeview)
{
GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
GtkTreeViewColumn *column;


column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", COL_ID, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);


column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", COL_NOM, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);


column = gtk_tree_view_column_new_with_attributes("Prenom", renderer, "text", COL_PRENOM, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);


column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", COL_CIN, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);


column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", COL_SEXE, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);


column = gtk_tree_view_column_new_with_attributes("Naissance", renderer, "text", COL_DATE, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);


column = gtk_tree_view_column_new_with_attributes("Centre", renderer, "text", COL_CENTRE, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
}



void afficher_treeview_entraineur(GtkWidget *treeview)
{
GtkListStore *store;


store = gtk_list_store_new(N_COLS,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING);


afficher_entraineurs(store);


gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
g_object_unref(store);
}

void afficher_treeview_recherche_entraineur(GtkWidget *treeview, const char *id)
{
GtkListStore *store;
GtkTreeIter iter;
entraineur e;


store = gtk_list_store_new(N_COLS,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING);


if (rechercher_entraineur(id, &e))
{
gtk_list_store_append(store, &iter);
gtk_list_store_set(store, &iter,
COL_ID, e.id,
COL_NOM, e.nom,
COL_PRENOM, e.prenom,
COL_CIN, e.cin,
COL_SEXE, e.sexe,
COL_DATE, e.date_naissance,
COL_CENTRE, e.centre,
-1);
}


gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
g_object_unref(store);
}

char id [10];
GtkWidget *treeview_modifier_ent;
GtkWidget *entry_recherche_id_ent;



void
on_tv_recherche_cours_modif_cursor_changed
                                        (GtkTreeView     *treeview,
                                        gpointer         user_data)
{


}


void
on_tv_recherche_cours_modif_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_btn_actualiser_cours_modif_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_rb_sexe_h_ajouter_ent_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if (gtk_toggle_button_get_active(togglebutton))
        strcpy(ent.sexe, "Homme");

}




void
on_cb_musculation_membre_inscrit_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_tv_cours_deja_inscrit_cursor_changed
                                        (GtkTreeView     *treeview,
                                        gpointer         user_data)
{

}


void
on_tv_cours_deja_inscrit_row_activated (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_cal_ajouter_ent_day_selected        (GtkCalendar     *calendar,
                                        gpointer         user_data)
{ guint day, month, year;
    gtk_calendar_get_date(calendar, &year, &month, &day);

    sprintf(ent.date_naissance, "%02d/%02d/%04d",
            day, month + 1, year);

}


void
on_chb_mus_ajouter_ent_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if (gtk_toggle_button_get_active(togglebutton))
        strcpy(ent.specialite, "Musculation");
}


void
on_chb_danse_ajouter_ent_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if (gtk_toggle_button_get_active(togglebutton))
        strcpy(ent.specialite, "Danse");
}


void
on_chb_nat_ajouter_ent_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{  if (gtk_toggle_button_get_active(togglebutton))
        strcpy(ent.specialite, "Natation");
}


void
on_chb_pil_ajouter_ent_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{ if (gtk_toggle_button_get_active(togglebutton))
        strcpy(ent.specialite, "Pilates");
}


void
on_chb_car_ajouter_ent_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{  if (gtk_toggle_button_get_active(togglebutton))
        strcpy(ent.specialite, "Cardio");
}


void
on_cb_centre_ajouter_ent_changed       (GtkComboBox     *combobox,
                                        gpointer         user_data)
{  gchar *centre;

    centre = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combobox));

    if (centre != NULL)
    {
        g_print("Centre sélectionné : %s\n", centre);
        g_free(centre);
    }

}


void
on_b_retour_ajouter_ent_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{ GtkWidget *window;

    window = GTK_WIDGET(user_data);
    gtk_widget_destroy(window);

}


void on_b_ajouter_ajouter_ent_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{ 
   GtkBuilder *builder = GTK_BUILDER(user_data);

    strcpy(ent.id,
        gtk_entry_get_text(GTK_ENTRY(
            gtk_builder_get_object(builder, "entry_id_modifier_ent"))));

    strcpy(ent.nom,
        gtk_entry_get_text(GTK_ENTRY(
            gtk_builder_get_object(builder, "entry_nom_modifier_ent"))));

    strcpy(ent.prenom,
        gtk_entry_get_text(GTK_ENTRY(
            gtk_builder_get_object(builder, "entry_prenom_modifier_ent"))));
    strcpy(ent.email,
        gtk_entry_get_text(GTK_ENTRY(
            gtk_builder_get_object(builder, "entry_email_modifier_ent"))));

    ajouter_entraineur(ent);



    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               " Entraîneur ajoutee avec succès ");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

}


void
on_photo_ajouter_ent_file_set          (GtkFileChooserButton *filechooserbutton,
                                        gpointer         user_data)
{

}


void
on_b_act_modifier_ent_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{ const char *id_recherche;


id_recherche = gtk_entry_get_text(GTK_ENTRY(entry_recherche_id_ent));


if (strlen(id_recherche) == 0)
{

afficher_treeview_entraineur(treeview_modifier_ent);
}
else
{
afficher_treeview_recherche_entraineur(treeview_modifier_ent, id_recherche);
}

}


void
on_rb_sexe_h_modifier_ent_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{ if (gtk_toggle_button_get_active(togglebutton))
        strcpy(ent.sexe, "Homme");

}


void
on_rb_sexe_f_modifier_ent_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if (gtk_toggle_button_get_active(togglebutton))
        strcpy(ent.sexe, "Femme");

}


void
on_chb_mus_modifier_ent_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{  if (gtk_toggle_button_get_active(togglebutton))
        strcat(ent.specialite, "Musculation");

   
}


void
on_chb_danse_modifier_ent_clicked      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{ if (gtk_toggle_button_get_active(togglebutton))
        strcat(ent.specialite, "Danse");

}


void
on_chb_nat_modifier_ent_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{    if (gtk_toggle_button_get_active(togglebutton))
        strcpy(ent.specialite, "Natation");

}


void
on_chb_pil_modifier_ent_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{if (gtk_toggle_button_get_active(togglebutton))
        strcpy(ent.specialite, "Pilates");

}


void
on_chb_car_modifier_ent_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{    if (gtk_toggle_button_get_active(togglebutton))
        strcpy(ent.specialite, "Cardio");

}


void
on_b_act_supprimer_ent_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_b_enr_modifier_ent_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{GtkBuilder *builder = GTK_BUILDER(user_data);

    strcpy(ent.id,
        gtk_entry_get_text(GTK_ENTRY(
            gtk_builder_get_object(builder, "entry_id_modifier_ent"))));

    strcpy(ent.nom,
        gtk_entry_get_text(GTK_ENTRY(
            gtk_builder_get_object(builder, "entry_nom_modifier_ent"))));

    strcpy(ent.prenom,
        gtk_entry_get_text(GTK_ENTRY(
            gtk_builder_get_object(builder, "entry_prenom_modifier_ent"))));
    strcpy(ent.email,
        gtk_entry_get_text(GTK_ENTRY(
            gtk_builder_get_object(builder, "entry_email_modifier_ent"))));

    modifier_entraineur(id,ent);

   
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               " Entraîneur modifie avec succès");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);




}


void
on_button10008_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{GtkWidget *window;

    window = GTK_WIDGET(user_data);
    gtk_widget_destroy(window);

}


void
on_b_supp_supprimer_ent_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{ GtkBuilder *builder = GTK_BUILDER(user_data);

    GtkWidget *entry_id;
    GtkWidget *entry_raison;
    GtkWidget *entry_rapport;
    GtkWidget *window;

    char id[20];

    entry_id = GTK_WIDGET(gtk_builder_get_object(builder, "entry_id_supprimer_ent"));
    entry_raison = GTK_WIDGET(gtk_builder_get_object(builder, "entry_raison_supprimer_ent"));
    entry_rapport = GTK_WIDGET(gtk_builder_get_object(builder, "entry_rapport_supprimer_ent"));
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_supprimer_ent"));

    strcpy(id, gtk_entry_get_text(GTK_ENTRY(entry_id)));

    supprimer_entraineur(id);

    GtkWidget *dialog;

    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_MODAL,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "Suppression avec succès");

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

}


void
on_button10003_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{GtkWidget *window;

    window = GTK_WIDGET(user_data);
    gtk_widget_destroy(window);

}

