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
on_rb_sexe_h_ajouter_ent_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_b_ajouter_ajouter_ent_clicked       (GtkButton       *button,
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
on_cal_ajouter_ent_day_selected        (GtkCalendar     *calendar,
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
on_cb_centre_ajouter_ent_changed       (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_b_retour_ajouter_ent_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_b_ajouter_ajouter_ent_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_photo_ajouter_ent_file_set          (GtkFileChooserButton *filechooserbutton,
                                        gpointer         user_data);

void
on_b_act_modifier_ent_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_rb_sexe_h_modifier_ent_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_rb_sexe_f_modifier_ent_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_chb_mus_modifier_ent_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_chb_danse_modifier_ent_clicked      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_chb_nat_modifier_ent_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_chb_pil_modifier_ent_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_chb_car_modifier_ent_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_b_act_supprimer_ent_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_b_enr_modifier_ent_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button10008_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_b_supp_supprimer_ent_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_button10003_clicked                 (GtkButton       *button,
                                        gpointer         user_data);
