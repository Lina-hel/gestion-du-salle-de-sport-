#include <gtk/gtk.h>
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "event.h"
#define EVENT_FILENAME "evenements.txt"
int type[3]={0};
int categorie = 0;



void
on_butt_retour_admin_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
}



void on_butt_ajouter_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
   
 

    GtkWidget *input_id, *input_nom, *input_frais;
    GtkWidget *sb_h, *sb_mn, *sb_nbr;
    GtkWidget *cbox_lieu_ajout;
    GtkWidget *cb_detente_event, *cb_competition, *cb_conference;
    GtkWidget *rb_homme, *rb_femme, *rb_mixte;
    GtkWidget *spec_widget;
    GtkWidget *entry_calendar_ajout = lookup_widget(objet_graphique, "entry_calendar_ajout");
    char *spec_text;

    Evenement e;
    Date d;

    
    input_id    = lookup_widget(objet_graphique, "entry_id_ajout_event");
    input_nom   = lookup_widget(objet_graphique, "entry_nom");
    input_frais = lookup_widget(objet_graphique, "entry_frais");

    sb_h  = lookup_widget(objet_graphique, "sb_h");
    sb_mn = lookup_widget(objet_graphique, "sb_mn");
    sb_nbr = lookup_widget(objet_graphique, "sb_nbr");

    cb_detente_event = lookup_widget(objet_graphique, "cb_detente_event");
    cb_competition   = lookup_widget(objet_graphique, "cb_competition");
    cb_conference    = lookup_widget(objet_graphique, "cb_conference");

    rb_homme = lookup_widget(objet_graphique, "rb_homme");
    rb_femme = lookup_widget(objet_graphique, "rb_femme");
    rb_mixte = lookup_widget(objet_graphique, "rb_mixte");

    spec_widget = lookup_widget(objet_graphique, "cbox_lieu_ajout");

    
    if (!input_id || !input_nom || !input_frais || !sb_h || !sb_mn || !sb_nbr ||
        !spec_widget || !entry_calendar_ajout ||
        strlen(gtk_entry_get_text(GTK_ENTRY(input_id))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(input_nom))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(input_frais))) == 0 ||
        gtk_combo_box_get_active(GTK_COMBO_BOX(spec_widget)) == -1)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Veuillez remplir tous les champs !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    
    e.id = atoi(gtk_entry_get_text(GTK_ENTRY(input_id)));
    if (e.id <= 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " L'ID doit être un entier positif !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    
    d = get_date_from_entry(GTK_ENTRY(entry_calendar_ajout));
    if (d.day == 0 || d.month == 0 || d.year == 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Veuillez choisir une date valide !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }
    e.jour  = d.day;
    e.mois  = d.month;
    e.annee = d.year;

    
    strcpy(e.nom, gtk_entry_get_text(GTK_ENTRY(input_nom)));
    e.frais = atof(gtk_entry_get_text(GTK_ENTRY(input_frais)));
    if (e.frais < 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Le frais ne peut pas être négatif !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    
    e.heure       = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(sb_h));
    e.min         = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(sb_mn));
    e.nb_inscrits = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(sb_nbr));

    
    spec_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(spec_widget));
    if (spec_text)
    {
        strncpy(e.lieu, spec_text, sizeof(e.lieu) - 1);
        e.lieu[sizeof(e.lieu) - 1] = '\0';
        g_free(spec_text);
    }
    else
        e.lieu[0] = '\0';

    
    strcpy(e.type, "");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_detente_event)))
        strcat(e.type, "Détente ");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_competition)))
        strcat(e.type, "Compétition ");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_conference)))
        strcat(e.type, "Conférence ");
    if (strlen(e.type) == 0) 
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Veuillez sélectionner au moins un type d'événement !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_homme)))
        strcpy(e.categorie_participant, "Homme");
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_femme)))
        strcpy(e.categorie_participant, "Femme");
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_mixte)))
        strcpy(e.categorie_participant, "Mixte");
    else
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Veuillez sélectionner une catégorie de participant !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    
    int res = ajouter_evenement(e);
    if (res == 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Impossible d'ouvrir le fichier evenements.txt !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
    }
    else if (res == 2)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Un événement avec cet ID existe déjà !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
    }
    else
    {
        GtkWidget *infoDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            " Événement ajouté avec succès !"
        );
        gtk_dialog_run(GTK_DIALOG(infoDialog));
        gtk_widget_destroy(infoDialog);
    }







 }




void on_rb_homme_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
     if (gtk_toggle_button_get_active(togglebutton))
    {
        categorie = 1;
    }
}

void on_rb_femme_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
     if (gtk_toggle_button_get_active(togglebutton))
    {
        categorie = 2;
    }
}

void on_rb_mixte_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
     if (gtk_toggle_button_get_active(togglebutton))
    {
        categorie = 3;
    }
}




void on_butt_modifier_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
  


    GtkWidget *input_id, *input_nom, *input_frais;
    GtkWidget *sp_heure_modif, *sp_min_event_modif, *sb_nbr_modif;
    GtkWidget *cb_detente_modif, *cb_competition_modif, *cb_conference_modif;
    GtkWidget *rb_homme_modif, *rb_femme_modif, *rb_mixte_modif;
    GtkWidget *entry_calendar_modif = lookup_widget(objet_graphique, "entry_calendar_modif");
    GtkWidget *spec_widget;
    char *spec_text;

    Evenement e_modif;
    Date d;

    
    input_id    = lookup_widget(objet_graphique, "entry_id_event_modif");
    input_nom   = lookup_widget(objet_graphique, "entry_nom_event_modif");
    input_frais = lookup_widget(objet_graphique, "entry_frais_modif");

    sp_heure_modif       = lookup_widget(objet_graphique, "sp_heure_modif");
    sp_min_event_modif   = lookup_widget(objet_graphique, "sp_min_event_modif");
    sb_nbr_modif         = lookup_widget(objet_graphique, "sb_nbr_modif");

    cb_detente_modif     = lookup_widget(objet_graphique, "cb_detente_modif");
    cb_competition_modif = lookup_widget(objet_graphique, "cb_competition_modif");
    cb_conference_modif  = lookup_widget(objet_graphique, "cb_conference_modif");

    rb_homme_modif = lookup_widget(objet_graphique, "rb_homme_modif");
    rb_femme_modif = lookup_widget(objet_graphique, "rb_femme_modif");
    rb_mixte_modif = lookup_widget(objet_graphique, "rb_mixte_modif");

    spec_widget = lookup_widget(objet_graphique, "cbox_lieu_modif");

    if (!input_id || !input_nom || !input_frais || !sp_heure_modif || !sp_min_event_modif || !sb_nbr_modif || !spec_widget || !entry_calendar_modif ||
        strlen(gtk_entry_get_text(GTK_ENTRY(input_id))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(input_nom))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(input_frais))) == 0 ||
        gtk_combo_box_get_active(GTK_COMBO_BOX(spec_widget)) == -1)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Veuillez remplir tous les champs obligatoires !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    
    e_modif.id = atoi(gtk_entry_get_text(GTK_ENTRY(input_id)));
    if (e_modif.id <= 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " L'ID doit être un entier positif !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    
    d = get_date_from_entry(GTK_ENTRY(entry_calendar_modif));
    if (d.day == 0 || d.month == 0 || d.year == 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Veuillez sélectionner une date valide !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }
    e_modif.jour  = d.day;
    e_modif.mois  = d.month;
    e_modif.annee = d.year;

    
    strcpy(e_modif.nom, gtk_entry_get_text(GTK_ENTRY(input_nom)));
    e_modif.frais = atof(gtk_entry_get_text(GTK_ENTRY(input_frais)));
    if (e_modif.frais < 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Les frais doivent être positifs !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    
    e_modif.heure       = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(sp_heure_modif));
    e_modif.min         = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(sp_min_event_modif));
    e_modif.nb_inscrits = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(sb_nbr_modif));

    
    spec_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(spec_widget));
    if (spec_text)
    {
        strncpy(e_modif.lieu, spec_text, sizeof(e_modif.lieu)-1);
        e_modif.lieu[sizeof(e_modif.lieu)-1] = '\0';
        g_free(spec_text);
    }
    else
        e_modif.lieu[0] = '\0';

    
    strcpy(e_modif.type, "");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_detente_modif)))
        strcat(e_modif.type, "Détente ");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_competition_modif)))
        strcat(e_modif.type, "Compétition ");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_conference_modif)))
        strcat(e_modif.type, "Conférence ");
    if (strlen(e_modif.type) == 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Veuillez sélectionner au moins un type d'événement !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_homme_modif)))
        strcpy(e_modif.categorie_participant, "Homme");
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_femme_modif)))
        strcpy(e_modif.categorie_participant, "Femme");
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_mixte_modif)))
        strcpy(e_modif.categorie_participant, "Mixte");
    else
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Veuillez sélectionner une catégorie de participant !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

   
    int res = modifier_evenement(e_modif);
    if (res == 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Impossible d'ouvrir le fichier evenements.txt !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
    }
    else if (res == 1)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Événement ID modifié avec succès !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
    }
    else if (res == 2)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Problème lors de l'écriture dans le fichier !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
    }
    else
    {
        GtkWidget *infoDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            " Aucun ID trouvé!"
        );
        gtk_dialog_run(GTK_DIALOG(infoDialog));
        gtk_widget_destroy(infoDialog);
    }





  
}






void
on_butt_retour_modif_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
}



enum {
    ID,
    NOM,
    DATE,
    HEURE,
    MINUTE,
    LIEU,
    FRAIS,
    TYPE,
    NB_INSCRITS,
    CATEGORIE_PARTICIPANTS,
    COLUMNS
};







void on_butt_actualiser_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *liste;
    GtkWidget *entry_id_recherche;
    const gchar *id_text;
    int id_recherche = 0;  
    
    
    liste = lookup_widget(objet_graphique, "tv_recherche_if_event");
    entry_id_recherche = lookup_widget(objet_graphique, "entry_id_event_modif");
    
    if (!liste) {
        g_warning("Widget tv_recherche_if_event introuvable !");
        return;
    }
    
    if (!entry_id_recherche) {
        g_warning("Widget entry_id_event_modif introuvable !");
        return;
    }
    
    
    vider_treeview(liste);
    
    id_text = gtk_entry_get_text(GTK_ENTRY(entry_id_recherche));
    
    if (id_text == NULL || strlen(id_text) == 0) {
  
        afficher_evenements_treeview(liste);
    } else {
        
        id_recherche = atoi(id_text);
        if (id_recherche > 0) {
            chercher_evenement_treeview(liste, id_recherche);
        } else {
            
            g_warning("ID invalide, affichage de tous les événements");
            afficher_evenements_treeview(liste);
        }
    }

}


void on_tv_recherche_if_event_row_activated(GtkTreeView *treeview,
                                           GtkTreePath *path,
                                           GtkTreeViewColumn *column,
                                           gpointer user_data)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    gchar *id_str, *nom, *date_str, *heure_str, *min_str, *lieu;
    gchar *frais_str, *type, *nb_inscrits_str, *categorie_participant;
    
    
    model = gtk_tree_view_get_model(treeview);
    
    if (model && gtk_tree_model_get_iter(model, &iter, path)) {
        
        gtk_tree_model_get(model, &iter,
                          ID, &id_str,
                          NOM, &nom,
                          DATE, &date_str,
                          HEURE, &heure_str,
                          MINUTE, &min_str,
                          LIEU, &lieu,
                          FRAIS, &frais_str,
                          TYPE, &type,
                          NB_INSCRITS, &nb_inscrits_str,
                          CATEGORIE_PARTICIPANTS, &categorie_participant,
                          -1);
        
        
        GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(treeview));
        GtkWidget *entry_id_event_modif = lookup_widget(window, "entry_id_event_modif");
        GtkWidget *entry_nom_event_modif = lookup_widget(window, "entry_nom_event_modif");
        GtkWidget *sp_heure_modif = lookup_widget(window, "sp_heure_modif");
        GtkWidget *sp_min_event_modif = lookup_widget(window, "sp_min_event_modif");
        GtkWidget *entry_frais_modif = lookup_widget(window, "entry_frais_modif");
        GtkWidget *sb_nbr_modif = lookup_widget(window, "sb_nbr_modif");
        GtkWidget *cbox_lieu_modif = lookup_widget(window, "cbox_lieu_modif");
        
        
        if (entry_id_event_modif) {
            gtk_entry_set_text(GTK_ENTRY(entry_id_event_modif), id_str ? id_str : "");
        }
        
        if (entry_nom_event_modif) {
            gtk_entry_set_text(GTK_ENTRY(entry_nom_event_modif), nom ? nom : "");
        }
        
        if (sp_heure_modif && heure_str) {
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(sp_heure_modif), atoi(heure_str));
        }
        
        if (sp_min_event_modif && min_str) {
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(sp_min_event_modif), atoi(min_str));
        }
        
        if (entry_frais_modif && frais_str) {
            gtk_entry_set_text(GTK_ENTRY(entry_frais_modif), frais_str);
        }
        
        if (sb_nbr_modif && nb_inscrits_str) {
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(sb_nbr_modif), atoi(nb_inscrits_str));
        }
        
        
        if (cbox_lieu_modif && lieu) {
            
            GtkTreeModel *combo_model = gtk_combo_box_get_model(GTK_COMBO_BOX(cbox_lieu_modif));
            GtkTreeIter combo_iter;
            gboolean found = FALSE;
            
            if (gtk_tree_model_get_iter_first(combo_model, &combo_iter)) {
                do {
                    gchar *lieu_combo;
                    gtk_tree_model_get(combo_model, &combo_iter, 0, &lieu_combo, -1);
                    
                    if (lieu_combo && strcmp(lieu_combo, lieu) == 0) {
                        gtk_combo_box_set_active_iter(GTK_COMBO_BOX(cbox_lieu_modif), &combo_iter);
                        found = TRUE;
                    }
                    g_free(lieu_combo);
                    
                    if (found) break;
                } while (gtk_tree_model_iter_next(combo_model, &combo_iter));
            }
            
            
            if (!found) {
                gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(cbox_lieu_modif), lieu);
                gtk_combo_box_set_active(GTK_COMBO_BOX(cbox_lieu_modif), 0);
            }
        }
        
        
        if (type) {
            GtkWidget *cb_detente_modif = lookup_widget(window, "cb_detente_modif");
            GtkWidget *cb_competition_modif = lookup_widget(window, "cb_competition_modif");
            GtkWidget *cb_conference_modif = lookup_widget(window, "cb_conference_modif");
            
            if (cb_detente_modif) {
                gboolean active = (strstr(type, "Détente") != NULL);
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_detente_modif), active);
            }
            
            if (cb_competition_modif) {
                gboolean active = (strstr(type, "Compétition") != NULL);
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_competition_modif), active);
            }
            
            if (cb_conference_modif) {
                gboolean active = (strstr(type, "Conférence") != NULL);
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_conference_modif), active);
            }
        }
        
        
        if (categorie_participant) {
            GtkWidget *rb_homme_modif = lookup_widget(window, "rb_homme_modif");
            GtkWidget *rb_femme_modif = lookup_widget(window, "rb_femme_modif");
            GtkWidget *rb_mixte_modif = lookup_widget(window, "rb_mixte_modif");
            
            if (strcmp(categorie_participant, "Homme") == 0 && rb_homme_modif) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb_homme_modif), TRUE);
            } else if (strcmp(categorie_participant, "Femme") == 0 && rb_femme_modif) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb_femme_modif), TRUE);
            } else if (rb_mixte_modif) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(rb_mixte_modif), TRUE);
            }
        }
        
        
        g_free(id_str);
        g_free(nom);
        g_free(date_str);
        g_free(heure_str);
        g_free(min_str);
        g_free(lieu);
        g_free(frais_str);
        g_free(type);
        g_free(nb_inscrits_str);
        g_free(categorie_participant);
    } else {
        g_warning("Impossible de récupérer la ligne sélectionnée");
    }


}




void on_butt_act_supp_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *liste;
    GtkWidget *entry_id_recherche;
    const gchar *id_text;
    int id_recherche = 0;  
    
    
    
    
    liste = lookup_widget(objet_graphique, "tv_recherche_evt_supp");
    entry_id_recherche = lookup_widget(objet_graphique, "entry_id_evt_supp");
    
    if (!liste) {
        g_warning("Widget tv_recherche_evt_supp introuvable !");
        return;
    }
    
    if (!entry_id_recherche) {
        g_warning("Widget entry_id_evt_supp introuvable !");
        return;
    }
    
    
    vider_treeview(liste);
    
    id_text = gtk_entry_get_text(GTK_ENTRY(entry_id_recherche));
    
    if (id_text == NULL || strlen(id_text) == 0) {
  
        afficher_evenements_treeview(liste);
    } else {
        
        id_recherche = atoi(id_text);
        if (id_recherche > 0) {
            chercher_evenement_treeview(liste, id_recherche);
        } else {
            
            g_warning("ID invalide, affichage de tous les événements");
            afficher_evenements_treeview(liste);
        }
    }

    
    
}



void
on_butt_retour_supp_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
}



void on_butt_supp_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
   

    GtkWidget *input_id_evt_supp, *input_chercher_nom_event;

    int id_evt;

    input_id_evt_supp      = lookup_widget(objet_graphique, "entry_id_evt_supp");
    input_chercher_nom_event = lookup_widget(objet_graphique, "entry_chercher_nom_event");

    
    if (!input_id_evt_supp || strlen(gtk_entry_get_text(GTK_ENTRY(input_id_evt_supp))) == 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Veuillez saisir l'ID de l'événement à supprimer !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    
    id_evt = atoi(gtk_entry_get_text(GTK_ENTRY(input_id_evt_supp)));
    if (id_evt <= 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " L'ID doit être un entier positif !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    
    int res = supprimer_evenement(id_evt);

    if (res == 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Impossible d'ouvrir le fichier evenements.txt !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
    }
    else if (res == 2)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Aucun événement avec cet ID n'a été trouvé !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
    }
    else
    {
        GtkWidget *infoDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            " Événement ID supprimé avec succès !"
        );
        gtk_dialog_run(GTK_DIALOG(infoDialog));
        gtk_widget_destroy(infoDialog);
    }




}




void on_cb_detente_supp_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    type[0] = gtk_toggle_button_get_active(togglebutton);
}

void on_cb_competition_supp_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    type[1] = gtk_toggle_button_get_active(togglebutton);
}

void on_cb_conference_supp_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    type[2] = gtk_toggle_button_get_active(togglebutton);
}







void
on_calendar_ajout_day_selected         (GtkCalendar     *calendar,
                                        gpointer         user_data)
{
    char *date_str;
    GtkWidget *entry_calendar_ajout = lookup_widget(GTK_WIDGET(calendar), "entry_calendar_ajout");
    int year, month, day;

    gtk_calendar_get_date(calendar, &day, &month, &year);

    date_str = g_strdup_printf("%02d-%02d-%04d", year, month + 1, day);

    gtk_entry_set_text(GTK_ENTRY(entry_calendar_ajout), date_str);
    g_free(date_str);
}


void
on_calendar_modif_day_selected         (GtkCalendar     *calendar,
                                        gpointer         user_data)
{
    char *date_str;
    GtkWidget *entry_calendar_modif = lookup_widget(GTK_WIDGET(calendar), "entry_calendar_modif");
    int year, month, day;

    gtk_calendar_get_date(calendar, &day, &month, &year);

    date_str = g_strdup_printf("%02d-%02d-%04d", year, month + 1, day);

    gtk_entry_set_text(GTK_ENTRY(entry_calendar_modif), date_str);
    g_free(date_str);
}



void
on_tv_recherche_evt_supp_row_activated (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

    GtkTreeIter iter;
    GtkTreeModel *model;
    gchar *id_str, *nom;
    gchar *type;
    
    
    model = gtk_tree_view_get_model(treeview);
    
    if (model && gtk_tree_model_get_iter(model, &iter, path)) {
        
        gtk_tree_model_get(model, &iter,
                          ID, &id_str,
                          NOM, &nom,
                      
                          TYPE, &type,
                          
                          -1);
        
        
        GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(treeview));
        GtkWidget *entry_id_evt_supp = lookup_widget(window, "entry_id_evt_supp");
        GtkWidget *entry_chercher_nom_event = lookup_widget(window, "entry_chercher_nom_event");
        
        
        
        if (entry_id_evt_supp) {
            gtk_entry_set_text(GTK_ENTRY(entry_id_evt_supp), id_str ? id_str : "");
        }
        
        if (entry_chercher_nom_event) {
            gtk_entry_set_text(GTK_ENTRY(entry_chercher_nom_event), nom ? nom : "");
        }
        
        
        
        if (type) {
            GtkWidget *cb_detente_supp = lookup_widget(window, "cb_detente_supp");
            GtkWidget *cb_competition_supp = lookup_widget(window, "cb_competition_supp");
            GtkWidget *cb_conference_supp = lookup_widget(window, "cb_conference_supp");
            
            if (cb_detente_supp) {
                gboolean active = (strstr(type, "Détente") != NULL);
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_detente_supp), active);
            }
            
            if (cb_competition_supp) {
                gboolean active = (strstr(type, "Compétition") != NULL);
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_competition_supp), active);
            }
            
            if (cb_conference_supp) {
                gboolean active = (strstr(type, "Conférence") != NULL);
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cb_conference_supp), active);
            }
        }
        
        
       
        
        
        g_free(id_str);
        g_free(nom);
        g_free(type);
    } else {
        g_warning("Impossible de récupérer la ligne sélectionnée");
    }

}


void
on_treeview_participer_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_butt_retour_participer_clicked (GtkWidget *objet_graphique, gpointer user_data)
{

}


void
on_butt_inscri_participer_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
  
    GtkWidget *input_id, *input_id_participant;
    GtkWidget *cb_detente_participer, *cb_competition_participer, *cb_conference_participer;

    int id_evenement, id_participant;
    char categorie[50] = "";

    input_id = lookup_widget(objet_graphique, "entry_id_participer");
    input_id_participant = lookup_widget(objet_graphique, "entry_participant");
    cb_detente_participer = lookup_widget(objet_graphique, "cb_detente_participer");
    cb_competition_participer = lookup_widget(objet_graphique, "cb_competition_participer");
    cb_conference_participer = lookup_widget(objet_graphique, "cb_conference_participer");

    
    if (!input_id || !input_id_participant ||
        strlen(gtk_entry_get_text(GTK_ENTRY(input_id))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(input_id_participant))) == 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Veuillez remplir l'ID de l'événement et l'ID du participant !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    
    id_evenement = atoi(gtk_entry_get_text(GTK_ENTRY(input_id)));
    id_participant = atoi(gtk_entry_get_text(GTK_ENTRY(input_id_participant)));

    if (id_evenement <= 0 || id_participant <= 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Les ID doivent être des entiers positifs !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    
    strcpy(categorie, "");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_detente_participer)))
        strcat(categorie, "Détente ");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_competition_participer)))
        strcat(categorie, "Compétition ");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_conference_participer)))
        strcat(categorie, "Conférence ");

    if (strlen(categorie) == 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Veuillez sélectionner au moins un type de participation !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
        return;
    }

    
    int res = participer_evenement(id_evenement, id_participant, categorie);

    if (res == 0)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Impossible d'ouvrir le fichier evenements.txt !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
    }
    else if (res == 1)
    {
        GtkWidget *errorDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            " Participation à l'événement ID réussie !"
        );
        gtk_dialog_run(GTK_DIALOG(errorDialog));
        gtk_widget_destroy(errorDialog);
    }
    else
    {
        GtkWidget *infoDialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            " Aucun ID trouvé !"
        );
        gtk_dialog_run(GTK_DIALOG(infoDialog));
        gtk_widget_destroy(infoDialog);

    }







}


void
on_butt_act_participer_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *liste;
    GtkWidget *entry_id_recherche;
    const gchar *id_text;
    int id_recherche = 0;  
    
    
    
    liste = lookup_widget(objet_graphique, "treeview_participer");
    entry_id_recherche = lookup_widget(objet_graphique, "entry_id_participer");
    
    if (!liste) {
        g_warning("Widget treeview_participer introuvable !");
        return;
    }
    
    if (!entry_id_recherche) {
        g_warning("Widget entry_id_participer introuvable !");
        return;
    }
    
    
    vider_treeview(liste);
    
    id_text = gtk_entry_get_text(GTK_ENTRY(entry_id_recherche));
    
    if (id_text == NULL || strlen(id_text) == 0) {
  
        afficher_evenements_treeview(liste);
    } else {
        
        id_recherche = atoi(id_text);
        if (id_recherche > 0) {
            chercher_evenement_treeview(liste, id_recherche);
        } else {
            
            g_warning("ID invalide, affichage de tous les événements participés");
            afficher_evenements_treeview(liste);
        }
    }

   
}


void
on_treeview_inscri_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_butt_retour_inscri_clicked (GtkWidget *objet_graphique, gpointer user_data)
{

}


void
on_butt_act_inscri_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *liste;
    liste = lookup_widget(objet_graphique, "treeview_inscri");
    
    
    if (!liste) {
        g_warning("Widget treeview_inscri introuvable !");
        return;
    }
    
    
    vider_treeview(liste);
    
    
  
    afficher_evenements_participes_treeview(liste);

}




void
on_cb_conference_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  type[0] = gtk_toggle_button_get_active(togglebutton);

}


void
on_cb_competition_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  type[1] = gtk_toggle_button_get_active(togglebutton);
}


void
on_cb_detente_event_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  type[2] = gtk_toggle_button_get_active(togglebutton);
}


void
on_cb_detente_modif_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  type[0] = gtk_toggle_button_get_active(togglebutton);
}


void
on_cb_competition_modif_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  type[1] = gtk_toggle_button_get_active(togglebutton);

}

void
on_cb_conference_modif_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  type[2] = gtk_toggle_button_get_active(togglebutton);

}


void
on_rb_homme_modif_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if (gtk_toggle_button_get_active(togglebutton))
    {
        categorie = 1;
    }
}


void
on_rb_femme_modif_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if (gtk_toggle_button_get_active(togglebutton))
    {
        categorie = 2;
    }
}


void
on_rb_mixte_modif_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if (gtk_toggle_button_get_active(togglebutton))
    {
        categorie = 3;
    }
}


gboolean
on_entry_calendar_ajout_focus_in_event (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
  GtkWidget *calendar_ajout = lookup_widget(GTK_WIDGET(widget), "calendar_ajout"); 
  if (calendar_ajout != NULL) 
{ gtk_widget_show(calendar_ajout );
 } 
  return FALSE;

  
}


gboolean
on_entry_calendar_modif_focus_in_event (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
  GtkWidget *calendar_modif = lookup_widget(GTK_WIDGET(widget), "calendar_modif"); 
  if (calendar_modif != NULL) 
{ gtk_widget_show(calendar_modif );
 } 
  return FALSE;
}

int g_ids[100];
int g_counts[100];
int g_n_events = 0;

gboolean
on_drawingarea1_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
      printf("Expose event déclenché\n");
    
    if (g_n_events == 0) {
        printf("Aucune donnée à afficher\n");
        return FALSE;
    }

    
    GdkWindow *window = gtk_widget_get_window(widget);
    if (!window) {
        printf("Pas de fenêtre trouvée\n");
        return FALSE;
    }
    
  
    cairo_t *cr = gdk_cairo_create(window);
    if (!cr) {
        printf("Échec de création du contexte Cairo\n");
        return FALSE;
    }

    
    cairo_rectangle(cr, 
                   event->area.x, event->area.y,
                   event->area.width, event->area.height);
    cairo_clip(cr);

    
    GtkAllocation alloc;
    gtk_widget_get_allocation(widget, &alloc);
    int width = alloc.width;
    int height = alloc.height;
    
    printf("Taille zone dessin: %d x %d\n", width, height);
    printf("Nombre d'événements: %d\n", g_n_events);

    
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);

   
    if (g_n_events <= 0 || width <= 50 || height <= 50) {
        cairo_destroy(cr);
        return FALSE;
    }

    
    int max_count = 1;
    for (int i = 0; i < g_n_events; i++) {
        if (g_counts[i] > max_count) {
            max_count = g_counts[i];
        }
    }
    printf("Maximum trouvé: %d\n", max_count);

    
    int bar_spacing = 10;
    int bar_width = (width - (g_n_events + 1) * bar_spacing) / g_n_events;
    if (bar_width < 20) bar_width = 20; 

   
    for (int i = 0; i < g_n_events; i++) {
       
        double bar_height = 0;
        if (max_count > 0) {
            bar_height = ((double)g_counts[i] / max_count) * (height - 80);
        }
        
        if (bar_height < 2) bar_height = 2;

        
        int x = bar_spacing + i * (bar_width + bar_spacing);
        int y = height - 50 - bar_height;

       
        cairo_set_source_rgb(cr, 0.2, 0.6, 0.8);
        cairo_rectangle(cr, x, y, bar_width, bar_height);
        cairo_fill_preserve(cr);
        
       
        cairo_set_source_rgb(cr, 0.1, 0.3, 0.5);
        cairo_set_line_width(cr, 1);
        cairo_stroke(cr);

       
        char id_str[20];
        sprintf(id_str, "%d", g_ids[i]);
        
      
        cairo_select_font_face(cr, "Sans", 
                              CAIRO_FONT_SLANT_NORMAL, 
                              CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 10);
        cairo_set_source_rgb(cr, 0, 0, 0);
        
        
        cairo_text_extents_t extents;
        cairo_text_extents(cr, id_str, &extents);
        double text_x = x + (bar_width - extents.width) / 2;
        double text_y = height - 30;
        
        cairo_move_to(cr, text_x, text_y);
        cairo_show_text(cr, id_str);

        
        char count_str[20];
        sprintf(count_str, "%d", g_counts[i]);
        
        cairo_text_extents(cr, count_str, &extents);
        text_x = x + (bar_width - extents.width) / 2;
        text_y = y - 5;
        
        cairo_move_to(cr, text_x, text_y);
        cairo_show_text(cr, count_str);
    }

    
    cairo_select_font_face(cr, "Sans", 
                          CAIRO_FONT_SLANT_NORMAL, 
                          CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 14);
    cairo_set_source_rgb(cr, 0, 0, 0);
    
    cairo_move_to(cr, 20, 25);
    cairo_show_text(cr, "Statistiques de participation aux événements");

    cairo_destroy(cr);
    printf("Dessin terminé\n");
  return FALSE;
}




void
on_butt_stat_clicked (GtkWidget *objet_graphique, gpointer user_data)
{

      printf("\n=== BOUTON STATISTIQUES CLIQUÉ ===\n");
    
    
    printf("Vérification des fichiers...\n");
    FILE *test1 = fopen("evenements.txt", "r");
    if (test1) {
        printf("✓ evenements.txt existe\n");
        fclose(test1);
    } else {
        printf("✗ evenements.txt n'existe pas ou inaccessible\n");
    }
    
    FILE *test2 = fopen("participants.txt", "r");
    if (test2) {
        printf("✓ participants.txt existe\n");
        fclose(test2);
    } else {
        printf("✗ participants.txt n'existe pas ou inaccessible\n");
    }
    
    
    g_n_events = calculer_stats(g_ids, g_counts, 100);
    
    printf("\n=== RÉSUMÉ ===\n");
    if (g_n_events == 0) {
        printf("AUCUN ÉVÉNEMENT TROUVÉ!\n");
        printf("Vérifiez que evenements.txt contient des nombres (un par ligne)\n");
        
        
        printf("\nCréation d'un fichier de test evenements.txt...\n");
        FILE *test_file = fopen("evenements.txt", "w");
        if (test_file) {
            fprintf(test_file, "1\n2\n3\n4\n5\n");
            fclose(test_file);
            printf("Fichier evenements.txt créé avec les IDs: 1, 2, 3, 4, 5\n");
            
            
            test_file = fopen("participants.txt", "w");
            if (test_file) {
                fprintf(test_file, "101 1\n");
                fprintf(test_file, "102 1\n");
                fprintf(test_file, "103 2\n");
                fprintf(test_file, "104 2\n");
                fprintf(test_file, "105 2\n");
                fprintf(test_file, "106 3\n");
                fprintf(test_file, "107 3\n");
                fprintf(test_file, "108 4\n");
                fprintf(test_file, "109 5\n");
                fprintf(test_file, "110 5\n");
                fprintf(test_file, "111 5\n");
                fprintf(test_file, "112 5\n");
                fclose(test_file);
                printf("Fichier participants.txt créé avec données de test\n");
                
               
                g_n_events = calculer_stats(g_ids, g_counts, 100);
            }
        }
    }
    
    
    GtkWidget *drawing = lookup_widget(objet_graphique, "drawingarea1");
    
    if (drawing != NULL) {
        
        gtk_widget_queue_draw(drawing);
        printf("\nGraphique mis à jour avec %d événements\n", g_n_events);
    }
}

/*
void
on_butt_demander_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
 GtkWidget *fenetre_actuelle = gtk_widget_get_toplevel(objet_graphique);
    if (GTK_IS_WINDOW(fenetre_actuelle)) {
        gtk_widget_destroy(fenetre_actuelle);
    }
    
    GtkWidget *fenetre_demander = create_Demander_un_entraineur();
    gtk_widget_show(fenetre_demander);
}


void
on_butt_inscrire_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *fenetre_actuelle = gtk_widget_get_toplevel(objet_graphique);
    if (GTK_IS_WINDOW(fenetre_actuelle)) {
        gtk_widget_destroy(fenetre_actuelle);
    }
    
   
    GtkWidget *fenetre_inscrire = create_Sinscrire_a_un_cours_sportif();
    gtk_widget_show(fenetre_inscrire);
}


void
on_butt_participer_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *fenetre_actuelle = gtk_widget_get_toplevel(objet_graphique);
    if (GTK_IS_WINDOW(fenetre_actuelle)) {
        gtk_widget_destroy(fenetre_actuelle);
    }
    
   
    GtkWidget *fenetre_participer = create_Participer_a_un_evenement();
    gtk_widget_show(fenetre_participer);
}


void
on_butt_stat_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget *fenetre_actuelle = gtk_widget_get_toplevel(objet_graphique);
    if (GTK_IS_WINDOW(fenetre_actuelle)) {
        gtk_widget_destroy(fenetre_actuelle);
    }
    
    
    GtkWidget *fenetre_stats = create_Statistiques();
    gtk_widget_show(fenetre_stats);
}
*/

