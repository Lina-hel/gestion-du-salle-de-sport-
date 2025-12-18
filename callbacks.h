#include <gtk/gtk.h>






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
void on_btn_retour__admin_clicked(GtkWidget *objet_graphique,gpointer user_data);
void afficher_pref(GtkWidget* liste, char* fichier);


