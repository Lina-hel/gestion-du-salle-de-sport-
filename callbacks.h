#include <gtk/gtk.h>


void
on_tv_recherche_cours_modif_cursor_changed
                                        (GtkTreeView     *treeview,
                                        gpointer         user_data);

void
on_tv_recherche_cours_modif_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_btn_actualiser_cours_modif_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_calendar_date_cours_day_selected    (GtkCalendar     *calendar,
                                        gpointer         user_data);

void
on_calendar_date_cours_month_changed   (GtkCalendar     *calendar,
                                        gpointer         user_data);

void
on_calendar_date_cours_next_year       (GtkCalendar     *calendar,
                                        gpointer         user_data);

void
on_calendar_date_cours_prev_year       (GtkCalendar     *calendar,
                                        gpointer         user_data);

void
on_sp_heure_change_value               (GtkSpinButton   *spinbutton,
                                        GtkScrollType    scroll,
                                        gpointer         user_data);

void
on_sp_modifier_change_value            (GtkSpinButton   *spinbutton,
                                        GtkScrollType    scroll,
                                        gpointer         user_data);

void
on_cb_horaire_cours_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cb_specialte_ajout_cours_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_musculation_coursentraineurajout_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_danse_coursentraineur_ajout_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_cardio_coursentraineur_ajout_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_btn_ajouter_cours_admin_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour__admin_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_rb_pilates_coursentraineur_ajout_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_natation_coursentraineur_ajout_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_btn_actualiser_entraineur_cours_ajout_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_cb_musculation_membre_inscrit_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_tv_cours_deja_inscrit_cursor_changed
                                        (GtkTreeView     *treeview,
                                        gpointer         user_data);

void
on_tv_cours_deja_inscrit_row_activated (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_radiobutton_femme_ajouter_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_homme_ajouter_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_mixte_ajouter_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2584_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2585_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2590_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2588_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2589_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton_oui_ajouter_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_ajouter_ajouter_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_select_clicked                      (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobutton_mixte_modifier_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_homme_modifier_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_femme_modifier_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button9937_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton_cardio_modifier_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton_musculation_modifier_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton_fitness_modifier_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton_sports_de_combat_modifier_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton_pilate_modifier_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton_oui_modifier_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2627_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2630_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2631_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2628_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2629_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_auctialiser_supprimer_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_supprimer_supprimer_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_showcentrestat_clicked              (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_drawingarea2_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_rechcentre_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button9964_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton2636_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2635_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2633_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2634_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2632_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button9967_clicked                  (GtkButton       *button,
                                        gpointer         user_data);
