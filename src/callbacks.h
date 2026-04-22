#include <gtk/gtk.h>





void
on_zoomc_clicked                       (GtkWidget       *objet_graphiue,
                                        gpointer         user_data);

void
on_cb_horaire_cours_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

gboolean
on_sbb_horaire_dispo_ajout_popdown     (GtkComboBox     *combobox,
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
on_rb_pilates_coursentraineur_ajout_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);


void
on_rb_natation_coursentraineur_ajout_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);



void
on_btn_ajouter_cours_admin_clicked     (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_btn_retour__admin_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data);





void
on_btn_actualiser_entraineur_cours_ajout_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void on_tv_recherche_cours_modif_cursor_changed(GtkTreeView *treeview, gpointer user_data);
void on_cb_musculation_membre_inscrit_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_tv_cours_deja_inscrit_cursor_changed(GtkTreeView *treeview, gpointer user_data);
void on_tv_cours_deja_inscrit_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);

void afficher_tv_modif(GtkWidget *liste, char *id_recherche);

void
on_btn_actualiser_cours_modif_clicked  (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_cb_recherche_horaire_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);



void
on_btn_actualiser_entraineur_cours_modif_clicked
                                        (GtkWidget      *objet_graphique,
                                        gpointer         user_data);

void
on_btn_retour_admin_modif_cours_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_btn_modifier_cours_admin_clicked    (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_cb_type_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_musculation_supprission_admincours_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_cardio_supprission_admincours_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_danse_supprission_admincours_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_pilate_supprission_admincours_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_natation_supprission_admincours_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cb_id_coach_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void vider(GtkWidget *liste);
void afficher_tv(GtkWidget *liste, char*fichier);

void
on_btn_actualier_cours_supprission_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_btn_supprimer_cours_admin_clicked   (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_btn_retour_admin_supp_cours_clicked (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_tv_recherche_cours_modif_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_tv_cours_recherche_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_tv_liste_cours_inscrit_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_cb_cardio_membre_inscrit_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cb_danse_membre_inscrit_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cb_natation_membre_inscrit_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cb_pilates_membre_inscrit_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_actualiser_inscrit_cours_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_rb_niv_debutant_inscrit_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_niv_interm_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_niv_avance_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_btn_inscrire_cours_clicked          (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_btn_retour_membre_inscrit_clicked   (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_btn_sup_mesinscrit_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_actualiser_mesinscritcours_membre_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_btn_retour_membre_mesinscri_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_perte_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_prise_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_detente_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_performance_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_musculation_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_danse_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cardio_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_pilates_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_natation_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_pref_deb_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_pref_interm_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_pref_avanc_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_1fois_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_2ou3fois_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_plus4fois_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);


void
on_rb_email_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_sms_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_notif_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_resume_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_messagedetail_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_btn_enreg_pref_clicked              (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_btn_retour_membre_forpref_clicked   (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_affichage_pref_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_btn_actualiser_mespref_clicked      (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_btn_modifier_mespref_clicked        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_btn_supprimer_mespref_clicked       (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_tv_coachdispo_cours_ajout_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_tv_recherche_coachcours_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_rb_musc_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_dans_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_pi_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_nat_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_car_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_muscl_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_piilates_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_nata_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_card_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_ddanse_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void vider_inscrit(GtkWidget *liste);

void
on_cb_specialte_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_femme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_homme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_peuimporte_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_inscrire_db_clicked          (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_button_connect_db_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_btn_zoom_cm_clicked                 (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

gboolean
on_stats_cours_expose_event            (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_btn_stats_cours_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_dash_clicked             (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_btn_valider_dash_clicked            (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

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
on_rb_pilates_coursentraineur_ajout_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_natation_coursentraineur_ajout_toggled
                                        (GtkToggleButton *togglebutton,
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


void
on_button_retour_supprimer_centre_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_btn_retour_centre_modif_clicked     (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_button_retour_ajoiuter_clicked      (GtkWidget       *objet_graphique,
                                        gpointer         user_data);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
on_drawingarea3_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);



void
on_butt_stat_clicked (GtkWidget *objet_graphique, gpointer user_data);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void
on_az_btn_ajouter_clicked (GtkWidget  *objet_graphique ,
       gpointer user_data);

void
on_az_btn_retour_clicked  (GtkWidget  *objet_graphique ,
 gpointer  user_data);

void
on_az_btn_modifier_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_az_bouton_rechercher_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_az_btn_actualiser_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_az_retour1_clicked (GtkButton *button, GtkWidget  *objet_graphique ,
                                        gpointer  user_data);

void
on_az_btn_supprimer_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_az_bouton_rechercher1_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_az_btn_actualiser_sup_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_az_retour2_clicked                  (GtkButton       *button, GtkWidget  *objet_graphique ,
                                        gpointer         user_data);

void
on_azsexe0_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_azsexe1_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_treeview_membre_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview_sup_membre_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_az_afficher_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_azpremium_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_azchersexe0_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_azchersexe1_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cher_identifiant_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cher_sexe_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_azspup_typeab_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_azbasique_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_azspecifique_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_btn_centre_admin_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_cours_admin_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_coach_admin_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_equip_admin_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_event_admin_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_statistiques_admin_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_membre_admin_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_decon_admin_clicked          (GtkButton       *button,
                                        gpointer         user_data);




void
on_btn_nscrire_cours_coach_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_inscrire_centre_coach_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_dec_entr_clicked                    (GtkWidget       *objet_graphiue,
                                        gpointer         user_data);

void
on_dec_mem_clicked                     (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_btn_demnade_coach_membre_clicked    (GtkButton       *button,
                                        gpointer         user_data);


void
on_btn_particip_event_membre_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_inscri_cours_membre_clicked     (GtkWidget      *objet_graphique,
                                        gpointer         user_data);



void
on_rb_sexe_h_ajouter_ent_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_sexe_f_ajouter_ent_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_chb_mus_ajouter_ent_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_chb_danse_ajouter_ent_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_chb_nat_ajouter_ent_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_chb_pil_ajouter_ent_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_chb_car_ajouter_ent_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_b_ajouter_ajouter_ent_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_b_retour_ajouter_ent_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton_show_password_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_show_ps_ad_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_show_ps_ent_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_show_ps_mem_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_modif_main_ad_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_modif_mdp_ad_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_modif_mail_ent_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_modif_mdp_mem_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_modif_mail_mem_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_modif_mdp_ent_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_z_mem_clicked                       (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_z_centr_clicked                     (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_z_coacou_clicked                    (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_z_ent_clicked                       (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_z_event_clicked                     (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_btn_recherchecentre_modif_clicked(GtkButton *button, gpointer user_data);


void
on_treeview_ent_modif_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_b_act_modifier_ent_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_b_enr_modifier_ent_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button10008_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_ent_adm_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_statis_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_button9996_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button9997_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_cour_coach_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_mesinscri_coach_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_centre_insc_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_ret_ins_centre_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview19908_row_activated         (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);


void
on_b_act_insc_ent_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_b_sinscrire_insc_ent_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_b_act_mins_ent_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_ch90_toggled                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_ch45_toggled                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_sport_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_act_mesdem_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_reserve_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_but_act_dem_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_butt_question_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_butt_question3_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_contact_mem_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_contact_ent_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_butt_question2_clicked              (GtkButton       *button,
                                        gpointer         user_data);
