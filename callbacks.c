#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "centre.c"

/* ===========================
   VARIABLES GLOBALES
   =========================== */
char TYPE[10] = "Femme";
char SPECIALITES[100] = "";
char PARKING[5] = "Non";
char TYPE_MODIF[10] = "Femme";
char SPECIALITES_MODIF[100] = "";
char PARKING_MODIF[5] = "Non";

char RECH_SPEC_SUPP[100] = "";
char RECH_SPEC_ins[200] = "";

/* ===========================
   FONCTIONS UTILITAIRES
   =========================== */
void ajouter_specialite(const char *spec)
{
    if (!strstr(SPECIALITES, spec))
    {
        strcat(SPECIALITES, spec);
        strcat(SPECIALITES, " ");
    }
}

void supprimer_specialite(const char *spec)
{
    char *p = strstr(SPECIALITES, spec);
    if (p)
        memmove(p, p + strlen(spec) + 1,
                strlen(p + strlen(spec)) + 1);
}

void show_error_dialog(const char *message)
{
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new(
        NULL,
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_ERROR,
        GTK_BUTTONS_OK,
        "%s",
        message
    );

    gtk_window_set_title(GTK_WINDOW(dialog), "Erreur");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}



/* ===========================
   CALLBACKS TREEVIEW / AUTRES
   =========================== */
void on_tv_recherche_cours_modif_cursor_changed(GtkTreeView *treeview, gpointer user_data) {}
void on_tv_recherche_cours_modif_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {}

void on_calendar_date_cours_day_selected(GtkCalendar *calendar, gpointer user_data) {}
void on_calendar_date_cours_month_changed(GtkCalendar *calendar, gpointer user_data) {}
void on_calendar_date_cours_next_year(GtkCalendar *calendar, gpointer user_data) {}
void on_calendar_date_cours_prev_year(GtkCalendar *calendar, gpointer user_data) {}
void on_sp_heure_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data) {}
void on_sp_modifier_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data) {}
void on_cb_horaire_cours_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_cb_specialte_ajout_cours_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_rb_musculation_coursentraineurajout_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_rb_danse_coursentraineur_ajout_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_rb_cardio_coursentraineur_ajout_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_btn_ajouter_cours_admin_clicked(GtkButton *button, gpointer user_data) {}
void on_btn_retour__admin_clicked(GtkButton *button, gpointer user_data) {}
void on_rb_pilates_coursentraineur_ajout_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_rb_natation_coursentraineur_ajout_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_btn_actualiser_entraineur_cours_ajout_clicked(GtkButton *button, gpointer user_data) {}
void on_cb_musculation_membre_inscrit_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_tv_cours_deja_inscrit_cursor_changed(GtkTreeView *treeview, gpointer user_data) {}
void on_tv_cours_deja_inscrit_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {}

/* ===========================
   RADIO BUTTONS – TYPE CENTRE
   =========================== */
void
on_radiobutton_femme_ajouter_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        strcpy(TYPE, "Femme");
}

void
on_radiobutton_homme_ajouter_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        strcpy(TYPE, "Homme");
}

void
on_radiobutton_mixte_ajouter_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        strcpy(TYPE, "Mixte");
}

/* ===========================
   CHECKBUTTONS – SPÉCIALITÉS
   =========================== */
void
on_checkbutton2584_toggled(GtkToggleButton *togglebutton, gpointer user_data) // Cardio
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite("Cardio")
        : supprimer_specialite("Cardio");
}

void
on_checkbutton2585_toggled(GtkToggleButton *togglebutton, gpointer user_data) // Musculation
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite("Musculation")
        : supprimer_specialite("Musculation");
}

void
on_checkbutton2590_toggled(GtkToggleButton *togglebutton, gpointer user_data) // Pilates
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite("Pilates")
        : supprimer_specialite("Pilates");
}

void
on_checkbutton2588_toggled(GtkToggleButton *togglebutton, gpointer user_data) // Natation
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite("Natation")
        : supprimer_specialite("Natation");
}

void
on_checkbutton2589_toggled(GtkToggleButton *togglebutton, gpointer user_data) // Danse
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite("Danse")
        : supprimer_specialite("Danse");
}

/* ===========================
   PARKING OUI / NON
   =========================== */
void
on_checkbutton_oui_ajouter_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        strcpy(PARKING, "Oui");
    else
        strcpy(PARKING, "Non");
}

/* ===========================
   BOUTON AJOUTER CENTRE
   =========================== */

void
on_button_ajouter_ajouter_clicked(GtkButton *button, gpointer user_data)
{
    centre c;
    GtkWidget *dialog;

    GtkWidget *entry_id, *entry_nom, *entry_adresse;
    GtkWidget *combo_horaire, *spin_capacite, *calendar;
    gchar *horaire;

    entry_id = lookup_widget(GTK_WIDGET(button), "entry_id_ajouter");
    entry_nom = lookup_widget(GTK_WIDGET(button), "entry_nom_ajouter");
    entry_adresse = lookup_widget(GTK_WIDGET(button), "entry_adresse_ajouter");
    combo_horaire = lookup_widget(GTK_WIDGET(button), "combobox_add_centre");
    spin_capacite = lookup_widget(GTK_WIDGET(button), "spincapacite_ajouter");
    calendar = lookup_widget(GTK_WIDGET(button), "calendar_date_ajouter");

    strcpy(c.id, gtk_entry_get_text(GTK_ENTRY(entry_id)));
    if (strlen(c.id) == 0)
    {
        show_error_dialog("L'identifiant du centre ne doit pas être vide");
        return;
    }

    if (centre_id_exists(c.id))
    {
        show_error_dialog("Cet identifiant existe déjà");
        return;
    }

    strcpy(c.nom, gtk_entry_get_text(GTK_ENTRY(entry_nom)));
    if (strlen(c.nom) == 0)
    {
        show_error_dialog("Le nom du centre ne doit pas être vide");
        return;
    }

    strcpy(c.adresse, gtk_entry_get_text(GTK_ENTRY(entry_adresse)));
    if (strlen(c.adresse) == 0)
    {
        show_error_dialog("L'adresse du centre ne doit pas être vide");
        return;
    }
    strcpy(c.horaire, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_horaire)));

    if (c.horaire == NULL)
    {
        show_error_dialog("Veuillez sélectionner un horaire");
        return;
    }


    strcpy(c.type, TYPE);
    if (strlen(c.type) == 0)
    {
        show_error_dialog("Veuillez sélectionner le type du centre");
        return;
    }

    strcpy(c.specialites, SPECIALITES);
    if (strlen(c.specialites) == 0)
    {
        show_error_dialog("Veuillez sélectionner au moins une spécialité");
        return;
    }

    strcpy(c.parking, PARKING);

    c.capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_capacite));
    if (c.capacite <= 0)
    {
        show_error_dialog("La capacité doit être supérieure à 0");
        return;
    }

    guint j, m, a;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &a, &m, &j);
    sprintf(c.date_ouverture, "%02d/%02d/%04d", j, m + 1, a);

    ajouter_centre(c);

    dialog = gtk_message_dialog_new(
        NULL,
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_OTHER,
        GTK_BUTTONS_OK,
        "Centre ajouté avec succès ✔"
    );
    gtk_window_set_title(GTK_WINDOW(dialog), "Succès");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(entry_nom), "");
    gtk_entry_set_text(GTK_ENTRY(entry_adresse), "");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_horaire), -1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_capacite), 0);
    gtk_calendar_select_day(GTK_CALENDAR(calendar), 1);

    TYPE[0] = '\0';
    SPECIALITES[0] = '\0';
    strcpy(PARKING, "Non");
}

void
on_btn_actualiser_cours_modif_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *tv;
    GtkWidget *entry_id;
    const char *id_rech;

    tv = lookup_widget(GTK_WIDGET(button), "tv_recherche_centre_modif");
    entry_id = lookup_widget(GTK_WIDGET(button), "entry_id_modifier");

    id_rech = gtk_entry_get_text(GTK_ENTRY(entry_id));

    show_centre(tv, id_rech, "");
}

void
on_select_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *tv;
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;

    GtkWidget *entry_id, *entry_nom, *entry_adresse;
    GtkWidget *combo_horaire, *spin_capacite, *calendar;
    GtkWidget *rb_mixte, *rb_homme, *rb_femme;
    GtkWidget *cb_cardio, *cb_muscu, *cb_fitness, *cb_combat, *cb_pilate;

    gchar *id, *nom, *adresse, *type, *specialites, *horaire, *date;
    gint capacite;

    tv = lookup_widget(GTK_WIDGET(button), "tv_recherche_centre_modif");
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tv));

    if (!gtk_tree_selection_get_selected(selection, &model, &iter))
        return;

    gtk_tree_model_get(
        model, &iter,
        ECenterID, &id,
        ECenterNom, &nom,
        ECenterAdresse, &adresse,
        ECenterType, &type,
        ECenterSpecialites, &specialites,
        ECenterHoraire, &horaire,
        ECenterCapacite, &capacite,
        ECenterDate, &date,
        -1
    );

    entry_id = lookup_widget(GTK_WIDGET(button), "entry_id_modifier");
    entry_nom = lookup_widget(GTK_WIDGET(button), "entry_nom_modifier");
    entry_adresse = lookup_widget(GTK_WIDGET(button), "entry_adresse_modifier");
    combo_horaire = lookup_widget(GTK_WIDGET(button), "combobox_modifier_centre");
    spin_capacite = lookup_widget(GTK_WIDGET(button), "spinbutton_capacite_modifier");
    calendar = lookup_widget(GTK_WIDGET(button), "calendar12");

    rb_mixte = lookup_widget(GTK_WIDGET(button), "radiobutton_mixte_modifier");
    rb_homme = lookup_widget(GTK_WIDGET(button), "radiobutton_homme_modifier");
    rb_femme = lookup_widget(GTK_WIDGET(button), "radiobutton_femme_modifier");

    cb_cardio = lookup_widget(GTK_WIDGET(button), "checkbutton_cardio_modifier");
    cb_muscu = lookup_widget(GTK_WIDGET(button), "checkbutton_musculation_modifier");
    cb_fitness = lookup_widget(GTK_WIDGET(button), "checkbutton_fitness_modifier");
    cb_combat = lookup_widget(GTK_WIDGET(button), "checkbutton_sports_de_combat_modifier");
    cb_pilate = lookup_widget(GTK_WIDGET(button), "checkbutton_pilate_modifier");

    gtk_entry_set_text(GTK_ENTRY(entry_id), id);
    gtk_entry_set_text(GTK_ENTRY(entry_nom), nom);
    gtk_entry_set_text(GTK_ENTRY(entry_adresse), adresse);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_capacite), capacite);

    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_horaire), -1);
    if (strcmp(horaire, "8.00-20.00") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_horaire), 0);
    else if (strcmp(horaire, "6.00-18.00") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_horaire), 1);
    else if (strcmp(horaire, "24h") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_horaire), 2);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb_mixte), strcmp(type, "Mixte") == 0);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb_homme), strcmp(type, "Homme") == 0);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb_femme), strcmp(type, "Femme") == 0);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_cardio), strstr(specialites, "Cardio") != NULL);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_muscu), strstr(specialites, "Musculation") != NULL);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_fitness), strstr(specialites, "Natation") != NULL);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_combat), strstr(specialites, "Danse") != NULL);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_pilate), strstr(specialites, "Pilates") != NULL);

    strcpy(TYPE_MODIF, type);
    strcpy(SPECIALITES_MODIF, specialites);

    guint j, m, a;
    sscanf(date, "%u/%u/%u", &j, &m, &a);
    gtk_calendar_select_month(GTK_CALENDAR(calendar), m - 1, a);
    gtk_calendar_select_day(GTK_CALENDAR(calendar), j);

    g_free(id);
    g_free(nom);
    g_free(adresse);
    g_free(type);
    g_free(specialites);
    g_free(horaire);
    g_free(date);
}

//******************
void ajouter_specialite_modif(const char *spec)
{
    if (!strstr(SPECIALITES_MODIF, spec))
    {
        strcat(SPECIALITES_MODIF, spec);
        strcat(SPECIALITES_MODIF, " ");
    }
}

void supprimer_specialite_modif(const char *spec)
{
    char *p = strstr(SPECIALITES_MODIF, spec);
    if (p)
        memmove(p, p + strlen(spec) + 1,
                strlen(p + strlen(spec)) + 1);
}

void
on_radiobutton_mixte_modifier_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        strcpy(TYPE_MODIF, "Mixte");
}

void
on_radiobutton_homme_modifier_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        strcpy(TYPE_MODIF, "Homme");
}

void
on_radiobutton_femme_modifier_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        strcpy(TYPE_MODIF, "Femme");
}


void
on_checkbutton_cardio_modifier_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite_modif("Cardio")
        : supprimer_specialite_modif("Cardio");
}

void
on_checkbutton_musculation_modifier_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite_modif("Musculation")
        : supprimer_specialite_modif("Musculation");
}

void
on_checkbutton_fitness_modifier_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite_modif("Natation")
        : supprimer_specialite_modif("Natation");
}

void
on_checkbutton_sports_de_combat_modifier_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite_modif("Danse")
        : supprimer_specialite_modif("Danse");
}

void
on_checkbutton_pilate_modifier_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite_modif("Pilates")
        : supprimer_specialite_modif("Pilates");
}

//****************************************************

void
on_button9937_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{


 centre c;
    GtkWidget *dialog,*tv;

    GtkWidget *entry_id, *entry_nom, *entry_adresse;
    GtkWidget *combo_horaire, *spin_capacite, *calendar;
    gchar *horaire;

    entry_id = lookup_widget(GTK_WIDGET(button), "entry_id_modifier");
    entry_nom = lookup_widget(GTK_WIDGET(button), "entry_nom_modifier");
    entry_adresse = lookup_widget(GTK_WIDGET(button), "entry_adresse_modifier");
    combo_horaire = lookup_widget(GTK_WIDGET(button), "combobox_modifier_centre");
    spin_capacite = lookup_widget(GTK_WIDGET(button), "spinbutton_capacite_modifier");
    calendar = lookup_widget(GTK_WIDGET(button), "calendar12");

    strcpy(c.id, gtk_entry_get_text(GTK_ENTRY(entry_id)));
    if (strlen(c.id) == 0)
    {
        show_error_dialog("Sélectionnez un centre à modifier");
        return;
    }

    strcpy(c.nom, gtk_entry_get_text(GTK_ENTRY(entry_nom)));
    if (strlen(c.nom) == 0)
    {
        show_error_dialog("Le nom ne doit pas être vide");
        return;
    }

    strcpy(c.adresse, gtk_entry_get_text(GTK_ENTRY(entry_adresse)));
    if (strlen(c.adresse) == 0)
    {
        show_error_dialog("L'adresse ne doit pas être vide");
        return;
    }

strcpy(c.horaire, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_horaire)));
    if (c.horaire == NULL)
    {
        show_error_dialog("Sélectionnez un horaire");
        return;
    }
  

    strcpy(c.type, TYPE_MODIF);
    if (strlen(c.type) == 0)
    {
        show_error_dialog("Sélectionnez le type");
        return;
    }

    strcpy(c.specialites, SPECIALITES_MODIF);
    if (strlen(c.specialites) == 0)
    {
        show_error_dialog("Sélectionnez au moins une spécialité");
        return;
    }

    c.capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_capacite));
    if (c.capacite <= 0)
    {
        show_error_dialog("Capacité invalide");
        return;
    }

    strcpy(c.parking, PARKING_MODIF);

    guint j, m, a;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &a, &m, &j);
    sprintf(c.date_ouverture, "%02d/%02d/%04d", j, m + 1, a);

    if (!modifier_centre(c))
    {
        show_error_dialog("Centre non trouvé");
        return;
    }

    dialog = gtk_message_dialog_new(
        NULL,
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_OTHER,
        GTK_BUTTONS_OK,
        "Centre modifié avec succès ✔"
    );
    gtk_window_set_title(GTK_WINDOW(dialog), "Succès");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);



  gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(entry_nom), "");
    gtk_entry_set_text(GTK_ENTRY(entry_adresse), "");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_horaire), -1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_capacite), 0);
    gtk_calendar_select_day(GTK_CALENDAR(calendar), 1);

    GtkWidget *rb_mixte = lookup_widget(GTK_WIDGET(button), "radiobutton_mixte_modifier");
    GtkWidget *rb_homme = lookup_widget(GTK_WIDGET(button), "radiobutton_homme_modifier");
    GtkWidget *rb_femme = lookup_widget(GTK_WIDGET(button), "radiobutton_femme_modifier");

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb_mixte), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb_homme), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb_femme), FALSE);

    GtkWidget *cb_cardio = lookup_widget(GTK_WIDGET(button), "checkbutton_cardio_modifier");
    GtkWidget *cb_muscu = lookup_widget(GTK_WIDGET(button), "checkbutton_musculation_modifier");
    GtkWidget *cb_fitness = lookup_widget(GTK_WIDGET(button), "checkbutton_fitness_modifier");
    GtkWidget *cb_combat = lookup_widget(GTK_WIDGET(button), "checkbutton_sports_de_combat_modifier");
    GtkWidget *cb_pilate = lookup_widget(GTK_WIDGET(button), "checkbutton_pilate_modifier");

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_cardio), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_muscu), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_fitness), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_combat), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_pilate), FALSE);

    TYPE_MODIF[0] = "Femme";
    SPECIALITES_MODIF[0] = '\0';
    strcpy(PARKING_MODIF, "Non");


    tv = lookup_widget(GTK_WIDGET(button), "tv_recherche_centre_modif");
    show_centre(tv, "", "");

}

void
on_checkbutton_oui_modifier_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        strcpy(PARKING_MODIF, "Oui");
    else
        strcpy(PARKING_MODIF, "Non");
}




//**********************
void ajouter_spec_rech_supp(const char *spec)
{
    if (!strstr(RECH_SPEC_SUPP, spec))
    {
        strcat(RECH_SPEC_SUPP, spec);
        strcat(RECH_SPEC_SUPP, " ");
    }
}

void supprimer_spec_rech_supp(const char *spec)
{
    char *p = strstr(RECH_SPEC_SUPP, spec);
    if (p)
        memmove(p, p + strlen(spec) + 1,
                strlen(p + strlen(spec)) + 1);
}

void
on_checkbutton2627_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_spec_rech_supp("Musculation")
        : supprimer_spec_rech_supp("Musculation");
}

void
on_checkbutton2630_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_spec_rech_supp("Natation")
        : supprimer_spec_rech_supp("Natation");
}

void
on_checkbutton2631_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_spec_rech_supp("Pilates")
        : supprimer_spec_rech_supp("Pilates");
}

void
on_checkbutton2628_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_spec_rech_supp("Danse")
        : supprimer_spec_rech_supp("Danse");
}

void
on_checkbutton2629_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_spec_rech_supp("Cardio")
        : supprimer_spec_rech_supp("Cardio");
}


//*******************************************************
void
on_button_auctialiser_supprimer_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *tv;
    GtkWidget *entry;
    const char *rech_txt;

    tv = lookup_widget(GTK_WIDGET(button), "treeview1_supprimer");
    entry = lookup_widget(GTK_WIDGET(button), "entry1_chercher_un_centre_supprimer");

    rech_txt = gtk_entry_get_text(GTK_ENTRY(entry));

    show_centre(tv, rech_txt, RECH_SPEC_SUPP);
}


void
on_button_supprimer_supprimer_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *tv;
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;

    gchar *id;
    GtkWidget *dialog;
    GtkWidget *confirm;
    int response;

    tv = lookup_widget(GTK_WIDGET(button), "treeview1_supprimer");
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tv));

    if (!gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        show_error_dialog("Veuillez sélectionner un centre à supprimer");
        return;
    }

    gtk_tree_model_get(model, &iter, ECenterID, &id, -1);

    confirm = gtk_message_dialog_new(
        NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Voulez-vous vraiment supprimer ce centre ?"
    );
    gtk_window_set_title(GTK_WINDOW(confirm), "Confirmation");

    response = gtk_dialog_run(GTK_DIALOG(confirm));
    gtk_widget_destroy(confirm);

    if (response != GTK_RESPONSE_YES)
    {
        g_free(id);
        return;
    }

    if (!delete_centre(id))
    {
        g_free(id);
        show_error_dialog("Erreur lors de la suppression");
        return;
    }

    dialog = gtk_message_dialog_new(
        NULL,
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_OTHER,
        GTK_BUTTONS_OK,
        "Centre supprimé avec succès ✔"
    );
    gtk_window_set_title(GTK_WINDOW(dialog), "Succès");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    g_free(id);

    show_centre(tv, "", "");
}



void
on_showcentrestat_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *da;

    da = lookup_widget(GTK_WIDGET(button), "drawingarea2");
    gtk_widget_queue_draw(da);
}


gboolean
on_drawingarea2_expose_event(GtkWidget *widget,
                             GdkEventExpose *event,
                             gpointer user_data)
{
    cairo_t *cr;
    StatCentre s;

    int values[5];
    const char *labels[5] = {
        "Cardio",
        "Musculation",
        "Danse",
        "Pilates",
        "Natation"
    };

    double colors[5][3] = {
        {0.2, 0.6, 0.9},
        {0.9, 0.3, 0.3},
        {0.3, 0.8, 0.4},
        {0.8, 0.5, 0.2},
        {0.6, 0.4, 0.8}
    };

    cr = gdk_cairo_create(widget->window);

    s = stat_centre();

    values[0] = s.cardio;
    values[1] = s.musculation;
    values[2] = s.danse;
    values[3] = s.pilates;
    values[4] = s.natation;

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    int x = 50;
    int y_base = 300;
    int bar_width = 40;
    int spacing = 30;

    cairo_set_font_size(cr, 12);

    /* ===== DRAW BARS + VALUES ===== */
    for (int i = 0; i < 5; i++)
    {
        int height = values[i] * 30;

        cairo_set_source_rgb(cr, colors[i][0], colors[i][1], colors[i][2]);
        cairo_rectangle(cr, x, y_base - height, bar_width, height);
        cairo_fill(cr);

        /* VALUE ABOVE BAR */
        char txt[10];
        sprintf(txt, "%d", values[i]);
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_move_to(cr, x + 10, y_base - height - 5);
        cairo_show_text(cr, txt);

        /* LABEL */
        cairo_move_to(cr, x, y_base + 15);
        cairo_show_text(cr, labels[i]);

        x += bar_width + spacing;
    }

    /* ===== LEGEND ===== */
    int legend_x = 350;
    int legend_y = 60;

    cairo_set_font_size(cr, 14);
    cairo_move_to(cr, legend_x, legend_y - 20);
    cairo_show_text(cr, "Legend");

    for (int i = 0; i < 5; i++)
    {
        cairo_set_source_rgb(cr, colors[i][0], colors[i][1], colors[i][2]);
        cairo_rectangle(cr, legend_x, legend_y + i * 30, 15, 15);
        cairo_fill(cr);

        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_move_to(cr, legend_x + 25, legend_y + 12 + i * 30);
        cairo_show_text(cr, labels[i]);
    }

    cairo_destroy(cr);
    return FALSE;
}



void
on_rechcentre_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{GtkWidget *tv;
    GtkWidget *entry;
    const char *rech_txt;

    tv = lookup_widget(GTK_WIDGET(button), "treeview_inscri_entraineur");


   

    show_centre(tv,"", RECH_SPEC_ins);

}
void ajouter_specialite_ins(const char *spec)
{
    if (!strstr(RECH_SPEC_ins, spec))
    {
        strcat(RECH_SPEC_ins, spec);
        strcat(RECH_SPEC_ins, " ");
    }
}

void supprimer_specialite_ins(const char *spec)
{
    char tmp[200] = "";
    char buffer[200];

    strcpy(buffer, RECH_SPEC_ins);

    char *token = strtok(buffer, " ");
    while (token)
    {
        if (strcmp(token, spec) != 0)
        {
            strcat(tmp, token);
            strcat(tmp, " ");
        }
        token = strtok(NULL, " ");
    }

    strcpy(RECH_SPEC_ins, tmp);
}

void
on_checkbutton2632_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite_ins("Musculation")
        : supprimer_specialite_ins("Musculation");
}

void
on_checkbutton2633_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite_ins("Natation")
        : supprimer_specialite_ins("Natation");
}

void
on_checkbutton2634_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite_ins("Pilates")
        : supprimer_specialite_ins("Pilates");
}

void
on_checkbutton2635_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite_ins("Danse")
        : supprimer_specialite_ins("Danse");
}

void
on_checkbutton2636_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gtk_toggle_button_get_active(togglebutton)
        ? ajouter_specialite_ins("Cardio")
        : supprimer_specialite_ins("Cardio");
}






void
on_button9964_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *tv, *entry;
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;

    gchar *id_centre, *nom_centre;
    const char *id_entraineur;

    tv = lookup_widget(GTK_WIDGET(button), "treeview_inscri_entraineur");
    entry = lookup_widget(GTK_WIDGET(button), "entry14724");

    id_entraineur = gtk_entry_get_text(GTK_ENTRY(entry));
    if (strlen(id_entraineur) == 0)
    {
        show_error_dialog("Veuillez saisir l'identifiant de l'entraîneur");
        return;
    }

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tv));
    if (!gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        show_error_dialog("Veuillez sélectionner un centre");
        return;
    }

    gtk_tree_model_get(model, &iter,
                       ECenterID, &id_centre,
                       ECenterNom, &nom_centre,
                       -1);

    if (!entraineur_existe(id_entraineur))
    {
        show_error_dialog("Cet entraîneur n'existe pas");
    
        return;
    }

    if (inscription_existe(id_entraineur, id_centre))
    {
        show_error_dialog("Cet entraîneur est déjà inscrit dans ce centre");
        g_free(id_centre);
        g_free(nom_centre);
        return;
    }

    ajouter_inscription(id_entraineur, id_centre, nom_centre);

    GtkWidget *dialog = gtk_message_dialog_new(
        NULL,
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Inscription effectuée avec succès ✔"
    );
    gtk_window_set_title(GTK_WINDOW(dialog), "Succès");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    g_free(id_centre);
    g_free(nom_centre);
}


void
on_button9967_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *entry, *tv;
    const char *id_ent;

    entry = lookup_widget(GTK_WIDGET(button), "entry14755");
    tv = lookup_widget(GTK_WIDGET(button), "treeview19901");

    id_ent = gtk_entry_get_text(GTK_ENTRY(entry));

    show_inscription(tv, id_ent);
}

