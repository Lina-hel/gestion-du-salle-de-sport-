#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>


void on_butt_ajouter_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_butt_retour_admin_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_rb_homme_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_rb_femme_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_rb_mixte_toggled(GtkToggleButton *togglebutton, gpointer user_data);




void on_butt_actualiser_clicked(GtkWidget *objet_graphique, gpointer user_data);

void on_butt_retour_modif_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_butt_modifier_clicked(GtkWidget *objet_graphique, gpointer user_data);


void on_butt_act_supp_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_cb_detente_supp_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_cb_competition_supp_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_cb_conference_supp_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_butt_retour_supp_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_butt_supp_clicked(GtkWidget *objet_graphique, gpointer user_data);




void
on_calendar_ajout_day_selected         (GtkCalendar     *calendar,
                                        gpointer         user_data);

void
on_calendar_modif_day_selected         (GtkCalendar     *calendar,
                                        gpointer         user_data);

void
on_tv_recherche_if_event_row_activated (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_tv_recherche_evt_supp_row_activated (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview_participer_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_butt_retour_participer_clicked      (GtkWidget *objet_graphique, gpointer user_data);

void
on_butt_inscri_participer_clicked (GtkWidget *objet_graphique, gpointer user_data);

void
on_butt_act_participer_clicked         (GtkWidget *objet_graphique, gpointer user_data);

void
on_treeview_inscri_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_butt_retour_inscri_clicked          (GtkWidget *objet_graphique, gpointer user_data);

void
on_butt_act_inscri_clicked             (GtkWidget *objet_graphique, gpointer user_data);

void
on_cb_conference_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cb_competition_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cb_detente_event_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cb_detente_modif_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);


void
on_cb_competition_modif_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cb_conference_modif_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_homme_modif_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_femme_modif_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_mixte_modif_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);




gboolean
on_entry_calendar_ajout_focus_in_event (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

gboolean
on_entry_calendar_modif_focus_in_event (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);






gboolean
on_drawingarea1_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);



void
on_butt_stat_clicked (GtkWidget *objet_graphique, gpointer user_data);



#endif 
/*
void
on_butt_demander_clicked (GtkWidget *objet_graphique, gpointer user_data);

void
on_butt_inscrire_clicked (GtkWidget *objet_graphique, gpointer user_data);

void
on_butt_participer_clicked (GtkWidget *objet_graphique, gpointer user_data);

void
on_butt_stat_clicked (GtkWidget *objet_graphique, gpointer user_data);*/
