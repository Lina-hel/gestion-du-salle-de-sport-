#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include <cairo.h>
#include "support.h"
#include "gestion_cours.h"
#include "coach.h"
#define NB_COLONNES 8
#define NB_C_COLONNES 10

int choix[]={0,0};
int choix_specialite[]={0,0,0,0,0};
char texte[100];
int choix_suppr[2]={0,0};
int choix_niv[]={0,0,0};
int objectif = 0;
int type_cours = 0;
int niveau = 0;
int frequence = 0;
int pref_entraineur = 0;
int mode_notification = 0;
int format_message = 0;
int pref_horaire;
int g_nb_muscu = 0;
int g_nb_danse = 0;
int g_nb_cardio = 0;
int g_nb_natation = 0;
int g_nb_pilates = 0;

enum
{
    ID,
    NOM,
    DUREE,
    DATE,
    HORAIRE,
    CAPACITE,
    FRAIS,
    ID_COACH,
    COLUMNS
};

enum {
    C_ID,
    C_NOM,
    C_PRENOM,
    C_CIN,
    C_EMAIL,
    C_SEXE,
    C_DATE_NAISSANCE,
    C_CENTRE,
    C_SPECIALITE,
    C_COLUMNS
};

enum {
    ID_I,
    NOM_I,
    NIVEAU_I,
    ID_COACH_I,
    DUREE_I,
    DATE_I,
    HORAIRE_I,
    FRAIS_I,
    ICOLUMNS
};


void
on_cb_horaire_cours_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

GtkWidget *combobox;
combobox = lookup_widget(GTK_WIDGET(togglebutton), "combobox");
if (gtk_toggle_button_get_active(togglebutton))
{choix[0]=1;
gtk_widget_set_sensitive(combobox, TRUE);}
else
{choix[0]=0;
gtk_widget_set_sensitive(combobox, FALSE);}

}

void
on_cb_specialte_ajout_cours_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
GtkWidget *rb_muscu;
GtkWidget *rb_danse;
GtkWidget *rb_cardio;
GtkWidget *rb_pilates;
GtkWidget *rb_natation; 


rb_muscu = lookup_widget(GTK_WIDGET(togglebutton), "rb_musculation_coursentraineurajout");
rb_danse = lookup_widget(GTK_WIDGET(togglebutton), "rb_danse_coursentraineur_ajout");
rb_cardio = lookup_widget(GTK_WIDGET(togglebutton), "rb_cardio_coursentraineur_ajout");
rb_pilates = lookup_widget(GTK_WIDGET(togglebutton), "rb_pilates_coursentraineur_ajout");
rb_natation = lookup_widget(GTK_WIDGET(togglebutton), "rb_natation_coursentraineur_ajout");

    if (gtk_toggle_button_get_active(togglebutton)) {
        choix[1] = 1;
        gtk_widget_set_sensitive(rb_muscu, TRUE);
        gtk_widget_set_sensitive(rb_danse, TRUE);
        gtk_widget_set_sensitive(rb_cardio, TRUE);
        gtk_widget_set_sensitive(rb_pilates, TRUE);
        gtk_widget_set_sensitive(rb_natation, TRUE);
    } else {
        choix[1] = 0;
        gtk_widget_set_sensitive(rb_muscu, FALSE);
        gtk_widget_set_sensitive(rb_danse, FALSE);
        gtk_widget_set_sensitive(rb_cardio, FALSE);
        gtk_widget_set_sensitive(rb_pilates, FALSE);
        gtk_widget_set_sensitive(rb_natation, FALSE);
    }

}

void
on_rb_musculation_coursentraineurajout_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[0]=1;}
else
{choix_specialite[0]=0;}

}



void
on_rb_danse_coursentraineur_ajout_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[1]=1;}
else
{choix_specialite[1]=0;}
}




void
on_rb_cardio_coursentraineur_ajout_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[2]=1;}
else
{choix_specialite[2]=0;}
}




void
on_rb_pilates_coursentraineur_ajout_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[4]=1;}
else
{choix_specialite[4]=0;}
}




void
on_rb_natation_coursentraineur_ajout_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[3]=1;}
else
{choix_specialite[3]=0;}

}




void
on_btn_ajouter_cours_admin_clicked     (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

GtkWidget *input1;
GtkWidget *input2;
GtkWidget *input3;
GtkWidget *input4;
GtkWidget *input5;
GtkWidget *input6;
GtkWidget *heure;
GtkWidget *minute;
GtkWidget *combobox_idcours_suppr;
GtkWidget *calendar;
cours c;
input1=lookup_widget(objet_graphique,"entry_id_coursadmin_1");
input2=lookup_widget(objet_graphique,"entry_nom_cours_admin_1");
input3=lookup_widget(objet_graphique,"entry_dure_cours_admin_1");
input4=lookup_widget(objet_graphique,"entry_prix_cours_admin_1");
input5=lookup_widget(objet_graphique,"entry_capacite_cours_admin_1");
input6=lookup_widget(objet_graphique,"entry_id_affectation");
heure=lookup_widget(objet_graphique,"spin_heure_ajout");
minute=lookup_widget(objet_graphique,"spin_minute_ajout");
calendar=lookup_widget(objet_graphique,"calendar_date_cours");
if(strlen(gtk_entry_get_text(GTK_ENTRY(input1)))==0||
strlen(gtk_entry_get_text(GTK_ENTRY(input2)))==0||
strlen(gtk_entry_get_text(GTK_ENTRY(input3)))==0||
strlen(gtk_entry_get_text(GTK_ENTRY(input4)))==0||
strlen(gtk_entry_get_text(GTK_ENTRY(input5)))==0||
strlen(gtk_entry_get_text(GTK_ENTRY(input6)))==0)
{
afficher_erreur("Veuillez remplir tous les champs.");
return;
}
for(int i=0;gtk_entry_get_text(GTK_ENTRY(input3))[i];i++)
if(!g_ascii_isdigit(gtk_entry_get_text(GTK_ENTRY(input3))[i]))
{
afficher_erreur("La durée doit être écrite en minutes (nombre).");
return;
}
int dure=atoi(gtk_entry_get_text(GTK_ENTRY(input3)));
if(dure<=0)
{
afficher_erreur("La durée doit être écrite en minutes.");
return;
}
if(dure>120)
{
afficher_erreur("La durée du cours doit  doivent être un nombre. ne  pas dépasser 120 minutes.");
return;
}
for(int i=0;gtk_entry_get_text(GTK_ENTRY(input4))[i];i++)
if(!g_ascii_isdigit(gtk_entry_get_text(GTK_ENTRY(input4))[i]))
{
afficher_erreur("Les frais doivent être un nombre.");
return;
}
for(int i=0;gtk_entry_get_text(GTK_ENTRY(input5))[i];i++)
if(!g_ascii_isdigit(gtk_entry_get_text(GTK_ENTRY(input5))[i]))
{
afficher_erreur("La capacité doit être un nombre.");
return;
}
strcpy(c.id_c,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(c.nom,gtk_entry_get_text(GTK_ENTRY(input2)));
strcpy(c.dure,gtk_entry_get_text(GTK_ENTRY(input3)));
c.frais=atoi(gtk_entry_get_text(GTK_ENTRY(input4)));
c.capacite=atoi(gtk_entry_get_text(GTK_ENTRY(input5)));
strcpy(c.id_e,gtk_entry_get_text(GTK_ENTRY(input6)));
c.heure=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(heure));
c.minute=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(minute));
int day,month,year;
gtk_calendar_get_date(GTK_CALENDAR(calendar),&year,&month,&day);
sprintf(c.date,"%02d/%02d/%04d",day,month+1,year);
if(ajouter("cours.txt",c))
{
GtkWidget *label=lookup_widget(objet_graphique,"Label_afficher_choix");
gtk_label_set_text(GTK_LABEL(label),"Cours ajouté avec succès !");
}
else
{
afficher_erreur("Erreur : cours non ajouté");
return;
}
FILE *f=fopen("cours.txt","r");
if(f)
{
while(fscanf(f,"%s %s %02d %02d %s %s %f %d %s",c.id_c,c.nom,&c.heure,&c.minute,c.date,c.dure,&c.frais,&c.capacite,c.id_e)!=EOF)
{
combobox_idcours_suppr=lookup_widget(objet_graphique,"combobox_idcours_suppr");
gtk_combo_box_append_text(GTK_COMBO_BOX(combobox_idcours_suppr),c.id_c);
}
fclose(f);
}
gtk_entry_set_text(GTK_ENTRY(input1),"");
gtk_entry_set_text(GTK_ENTRY(input2),"");
gtk_entry_set_text(GTK_ENTRY(input3),"");
gtk_entry_set_text(GTK_ENTRY(input4),"");
gtk_entry_set_text(GTK_ENTRY(input5),"");
gtk_entry_set_text(GTK_ENTRY(input6),"");
gtk_spin_button_set_value(GTK_SPIN_BUTTON(heure),0);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(minute),0);
GDate *date=g_date_new();
g_date_set_time_t(date,time(NULL));
gtk_calendar_select_day(GTK_CALENDAR(calendar),g_date_get_day(date));
gtk_calendar_select_month(GTK_CALENDAR(calendar),g_date_get_month(date)-1,g_date_get_year(date));
g_date_free(date);
}













void afficher_tv_ee(GtkWidget*liste,char *fichier)
{
GtkCellRenderer *renderer; 
GtkTreeViewColumn * column;
GtkTreeIter iter;
GtkListStore *store;
Entraineur e;
store==NULL;


FILE *f;
store=gtk_tree_view_get_model(liste);
if(store== NULL)
{
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", C_ID, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", C_NOM, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text", C_PRENOM, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("cin", renderer, "text", C_CIN, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("email", renderer, "text", C_EMAIL, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text", C_SEXE, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("date_naissance", renderer, "text", C_DATE_NAISSANCE, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("centre", renderer, "text", C_CENTRE, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("specialite", renderer, "text", C_SPECIALITE, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
}

store = gtk_list_store_new(C_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                           G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
f=fopen(fichier,"r");
if(f==NULL)
{
return;
}
else
{
f=fopen(fichier,"a+");
while (fscanf(f, "%s %s %s %s %s %s %s %s %s",e.id, e.nom, e.prenom, e.cin, e.email, e.sexe, e.date_naissance, e.centre, e.specialite) != EOF)
{
gtk_list_store_append (store,&iter);
gtk_list_store_set(store, &iter,
        C_ID, e.id,
        C_NOM, e.nom,
        C_PRENOM, e.prenom,
        C_CIN, e.cin,
        C_EMAIL, e.email,
        C_SEXE, e.sexe,
        C_DATE_NAISSANCE, e.date_naissance,
        C_CENTRE, e.centre,
        C_SPECIALITE, e.specialite,
        -1);
}
fclose(f);
gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
g_object_unref (store);

}
}



void
on_btn_actualiser_entraineur_cours_ajout_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkTreeIter iter;
GtkTreeModel *model;
GtkWidget *tv = lookup_widget(objet_graphique, "tv_coachdispo_cours_ajout");
GtkWidget *cb_horaire = lookup_widget(objet_graphique, "cb_horaire_cours");
GtkWidget *combo_horaire = lookup_widget(objet_graphique, "combobox");
GtkWidget *cb_specialite = lookup_widget(objet_graphique, "cb_specialte_ajout_cours");
GtkWidget *rb_musc = lookup_widget(objet_graphique, "rb_musculation_coursentraineurajout");
GtkWidget *rb_danse = lookup_widget(objet_graphique, "rb_danse_coursentraineur_ajout");
GtkWidget *rb_cardio = lookup_widget(objet_graphique, "rb_cardio_coursentraineur_ajout");
GtkWidget *rb_nat = lookup_widget(objet_graphique, "rb_natation_coursentraineur_ajout");
GtkWidget *rb_pil = lookup_widget(objet_graphique, "rb_pilates_coursentraineur_ajout");
FILE *fin = fopen("coach.txt", "r");
FILE *fout = fopen("coach_temp.txt", "w");
Entraineur e;
int useHoraire = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_horaire));
int useSpec = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_specialite));
if (!useHoraire && !useSpec)
{
fclose(fin);
fclose(fout);
afficher_tv_ee(tv, "coach.txt");
return;
}
int dh=0, dm=0, fh=0, fm=0;
char *texte=NULL;
if (useHoraire)
{
if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(combo_horaire), &iter))
{
model = gtk_combo_box_get_model(GTK_COMBO_BOX(combo_horaire));
gtk_tree_model_get(model, &iter, 0, &texte, -1);
sscanf(texte, "%d:%d-%d:%d", &dh, &dm, &fh, &fm);
}
}
char spec[20] = "";
if (useSpec)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_musc))) strcpy(spec, "Musculation");
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_danse))) strcpy(spec, "Danse");
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_cardio))) strcpy(spec, "Cardio");
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_pil))) strcpy(spec, "Pilates");
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_nat))) strcpy(spec, "Natation");
}
while (fscanf(fin, "%s %s %s %s %s %s %s %s %s",e.id, e.nom, e.prenom, e.cin, e.email,e.sexe, e.date_naissance, e.centre, e.specialite) != EOF)
{
int ok = 1;
if (useSpec && strcmp(spec, e.specialite) != 0)
ok = 0;
if (useHoraire && entraineur_occupe(e.id, dh, dm, fh, fm))
ok = 0;
if (ok)
fprintf(fout, "%s %s %s %s %s %s %s %s %s\n",e.id, e.nom, e.prenom, e.cin, e.email,e.sexe, e.date_naissance, e.centre, e.specialite);
printf("Ligne ajoutée : %s %s\n", e.id, e.nom);
}
fclose(fin);
fclose(fout);
afficher_tv_ee(tv, "coach_temp.txt");
}








void on_tv_recherche_cours_modif_cursor_changed(GtkTreeView *treeview, gpointer user_data)
{
   
}

   


void on_tv_cours_deja_inscrit_cursor_changed(GtkTreeView *treeview, gpointer user_data) {
    
}

void on_tv_cours_deja_inscrit_row_activated(GtkTreeView *treeview,
                                            GtkTreePath *path,
                                            GtkTreeViewColumn *column,
                                            gpointer user_data) {
   
}


void afficher_tv_modif(GtkWidget *liste, char *id_recherche)
{
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
cours c;
char horaire[6];
char capacite_str[10];
char frais_str[10];
store==NULL;

store=gtk_tree_view_get_model(liste);
if (store == NULL)
{
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", ID, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", NOM, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("duree", renderer, "text", DUREE, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("date", renderer, "text", DATE, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("horaire", renderer, "text", HORAIRE, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("capacite", renderer, "text", CAPACITE, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("frais", renderer, "text", FRAIS, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("id_coach", renderer, "text", ID_COACH, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
}

store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                           G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

if (id_recherche != NULL)
{
c = chercher("cours.txt", id_recherche);
if (strcmp(c.id_c, "-1") != 0)
{
sprintf(horaire, "%02d:%02d", c.heure, c.minute);
sprintf(capacite_str, "%d", c.capacite);
sprintf(frais_str, "%.2f", c.frais);

gtk_list_store_append(store, &iter);
gtk_list_store_set(store, &iter,
                   ID, c.id_c,
                   NOM, c.nom,
                   DUREE, c.dure,
                   DATE, c.date,
                   HORAIRE, horaire,
                   CAPACITE, capacite_str,
                   FRAIS, frais_str,
                   ID_COACH, c.id_e,
                   -1);
}
}
else
{
FILE *f = fopen("cours.txt", "r");
if (f != NULL)
{
while (fscanf(f, "%s %s %02d %02d %s %s %f %d %s",c.id_c, c.nom, &c.heure, &c.minute, c.date, c.dure, &c.frais, &c.capacite, c.id_e) != EOF)
{
sprintf(horaire, "%02d:%02d", c.heure, c.minute);
sprintf(capacite_str, "%d", c.capacite);
sprintf(frais_str, "%.2f", c.frais);

gtk_list_store_append(store, &iter);
gtk_list_store_set(store, &iter,
                   ID, c.id_c,
                   NOM, c.nom,
                   DUREE, c.dure,
                   DATE, c.date,
                   HORAIRE, horaire,
                   CAPACITE, capacite_str,
                   FRAIS, frais_str,
                   ID_COACH, c.id_e,
                   -1);
}
fclose(f);
}
}

gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void
on_btn_actualiser_cours_modif_clicked  (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *tv_modif;
GtkWidget *entry_id;
cours c;
tv_modif = lookup_widget(objet_graphique, "tv_recherche_cours_modif");
entry_id = lookup_widget(objet_graphique, "entry_id_cours_modif");
strcpy(c.id_c, gtk_entry_get_text(GTK_ENTRY(entry_id)));

if (c.id_c[0] == '\0')
{
    vider(tv_modif);
    afficher_tv(tv_modif,"cours.txt");
}
else
{
    vider(tv_modif);
    afficher_tv_modif(tv_modif, c.id_c);
}

}


//444444444444444444444444444444444444444444444444444444444444444444444444444444444444




void
on_btn_actualiser_entraineur_cours_modif_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkTreeIter iter;
GtkTreeModel *model;
GtkWidget *tv = lookup_widget(objet_graphique, "tv_recherche_coachcours");
GtkWidget *cb_horaire = lookup_widget(objet_graphique, "cb_recherche_horaire");
GtkWidget *combo_horaire = lookup_widget(objet_graphique, "combobox_horaire_modif_cours");
GtkWidget *cb_specialite = lookup_widget(objet_graphique, "cb_specialte");
GtkWidget *rb_musc = lookup_widget(objet_graphique, "rb_mus");
GtkWidget *rb_danse = lookup_widget(objet_graphique, "rb_dans");
GtkWidget *rb_cardio = lookup_widget(objet_graphique, "rb_car");
GtkWidget *rb_nat = lookup_widget(objet_graphique, "rb_nat");
GtkWidget *rb_pil = lookup_widget(objet_graphique, "rb_pi");
FILE *fin = fopen("coach.txt", "r");
FILE *fout = fopen("coach_temp.txt", "w");
Entraineur e;
int useHoraire = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_horaire));
int useSpec = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_specialite));
if (!useHoraire && !useSpec)
{
fclose(fin);
fclose(fout);
afficher_tv_ee(tv, "coach.txt");
return;
}
int dh=0, dm=0, fh=0, fm=0;
char *texte=NULL;
if (useHoraire)
{
if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(combo_horaire), &iter))
{
model = gtk_combo_box_get_model(GTK_COMBO_BOX(combo_horaire));
gtk_tree_model_get(model, &iter, 0, &texte, -1);
sscanf(texte, "%d:%d-%d:%d", &dh, &dm, &fh, &fm);
}
}
char spec[20] = "";
if (useSpec)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_musc))) strcpy(spec, "Musculation");
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_danse))) strcpy(spec, "Danse");
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_cardio))) strcpy(spec, "Cardio");
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_pil))) strcpy(spec, "Pilates");
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_nat))) strcpy(spec, "natation");
}
while (fscanf(fin, "%s %s %s %s %s %s %s %s %s",e.id, e.nom, e.prenom, e.cin, e.email,e.sexe, e.date_naissance, e.centre, e.specialite) != EOF)
{
int ok = 1;
if (useSpec && strcmp(spec, e.specialite) != 0)
ok = 0;
if (useHoraire && entraineur_occupe(e.id, dh, dm, fh, fm))
ok = 0;
if (ok)
fprintf(fout, "%s %s %s %s %s %s %s %s %s\n",e.id, e.nom, e.prenom, e.cin, e.email,e.sexe, e.date_naissance, e.centre, e.specialite);
printf("Ligne ajoutée : %s %s\n", e.id, e.nom);
}
fclose(fin);
fclose(fout);
afficher_tv_ee(tv, "coach_temp.txt");
}


void
on_btn_retour_admin_modif_cours_clicked
                                        (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *fenetre_actuelle, *fenetre_acceuil;

    
fenetre_actuelle = lookup_widget(objet_graphique, "espace_administrateur");
gtk_widget_destroy(fenetre_actuelle);

    
fenetre_acceuil = create_Acceuil_admin(); 
gtk_widget_show(fenetre_acceuil);
}


void
on_btn_modifier_cours_admin_clicked    (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *input1;
GtkWidget *input2;
GtkWidget *input3;
GtkWidget *input4;
GtkWidget *input5;
GtkWidget *input6;
GtkWidget *output;
GtkWidget *heure;
GtkWidget *minute;
GtkWidget *calendar;
cours nouv;
cours c;
const char *txt;
int dure_int;

input1=lookup_widget(objet_graphique,"entry_id_cours_modif");
txt=gtk_entry_get_text(GTK_ENTRY(input1));
if(strlen(txt)==0){afficher_erreur("Veuillez remplir tous les champs");return;}
strcpy(nouv.id_c,txt);
strcpy(c.id_c,txt);

input2=lookup_widget(objet_graphique,"entry_nom_cours_modif");
txt=gtk_entry_get_text(GTK_ENTRY(input2));
if(strlen(txt)==0){afficher_erreur("Veuillez remplir tous les champs");return;}
strcpy(nouv.nom,txt);

heure=lookup_widget(objet_graphique,"sp_heure");
minute=lookup_widget(objet_graphique,"sp_min");
nouv.heure=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(heure));
nouv.minute=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(minute));

calendar=lookup_widget(objet_graphique,"calendar_date_modif");
int day,month,year;
gtk_calendar_get_date(GTK_CALENDAR(calendar),&year,&month,&day);
sprintf(nouv.date,"%02d/%02d/%04d",day,month+1,year);

input3=lookup_widget(objet_graphique,"entry_dure_cours_modif");
txt=gtk_entry_get_text(GTK_ENTRY(input3));
if(strlen(txt)==0){afficher_erreur("Veuillez remplir tous les champs");return;}
dure_int=atoi(txt);
if(dure_int<=0){afficher_erreur("La durée doit être écrite en minutes");return;}
if(dure_int>120){afficher_erreur("La durée ne doit pas dépasser 120 minutes");return;}
sprintf(nouv.dure,"%d",dure_int);

input4=lookup_widget(objet_graphique,"entry_prix_cours_modif");
txt=gtk_entry_get_text(GTK_ENTRY(input4));
if(strlen(txt)==0){afficher_erreur("Veuillez remplir tous les champs");return;}
if(atoi(txt)<=0){afficher_erreur("Les frais doivent être un nombre");return;}
nouv.frais=atoi(txt);

input5=lookup_widget(objet_graphique,"entry_capacite_cours_modif");
txt=gtk_entry_get_text(GTK_ENTRY(input5));
if(strlen(txt)==0){afficher_erreur("Veuillez remplir tous les champs");return;}
if(atoi(txt)<=0){afficher_erreur("La capacité doit être un nombre");return;}
nouv.capacite=atoi(txt);

input6=lookup_widget(objet_graphique,"id_affectation_modif");
txt=gtk_entry_get_text(GTK_ENTRY(input6));
if(strlen(txt)==0){afficher_erreur("Veuillez remplir tous les champs");return;}
strcpy(nouv.id_e,txt);

if(modifier("cours.txt",c.id_c,nouv))
{
output=lookup_widget(objet_graphique,"label_afficher_choix_1");
gtk_label_set_text(GTK_LABEL(output),"Cours modifié avec succès !");
}
else
{
output=lookup_widget(objet_graphique,"label_afficher_choix_1");
gtk_label_set_text(GTK_LABEL(output),"Erreur:impossible de modifier le cours.");
}

gtk_entry_set_text(GTK_ENTRY(input1),"");
gtk_spin_button_set_value(GTK_SPIN_BUTTON(heure),0);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(minute),0);
gtk_entry_set_text(GTK_ENTRY(input2),"");
gtk_entry_set_text(GTK_ENTRY(input3),"");
gtk_entry_set_text(GTK_ENTRY(input4),"");
gtk_entry_set_text(GTK_ENTRY(input5),"");
gtk_entry_set_text(GTK_ENTRY(input6),"");

GDate *date=g_date_new();
g_date_set_time_t(date,time(NULL));
gtk_calendar_select_day(GTK_CALENDAR(calendar),g_date_get_day(date));
gtk_calendar_select_month(GTK_CALENDAR(calendar),g_date_get_month(date)-1,g_date_get_year(date));
g_date_free(date);
}


void
on_cb_type_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

{
GtkWidget *rb_muscu;
GtkWidget *rb_danse;
GtkWidget *rb_cardio;
GtkWidget *rb_pilates;
GtkWidget *rb_natation; 


rb_muscu = lookup_widget(GTK_WIDGET(togglebutton), "rb_muscl");
rb_danse = lookup_widget(GTK_WIDGET(togglebutton), "rb_ddanse");
rb_cardio = lookup_widget(GTK_WIDGET(togglebutton), "rb_card");
rb_pilates = lookup_widget(GTK_WIDGET(togglebutton), "rb_piilates");
rb_natation = lookup_widget(GTK_WIDGET(togglebutton), "rb_nata");

    if (gtk_toggle_button_get_active(togglebutton)) {
        choix_suppr[0] = 1;
        gtk_widget_set_sensitive(rb_muscu, TRUE);
        gtk_widget_set_sensitive(rb_danse, TRUE);
        gtk_widget_set_sensitive(rb_cardio, TRUE);
        gtk_widget_set_sensitive(rb_pilates, TRUE);
        gtk_widget_set_sensitive(rb_natation, TRUE);
    } else {
        choix_suppr[0] = 0;
        gtk_widget_set_sensitive(rb_muscu, FALSE);
        gtk_widget_set_sensitive(rb_danse, FALSE);
        gtk_widget_set_sensitive(rb_cardio, FALSE);
        gtk_widget_set_sensitive(rb_pilates, FALSE);
        gtk_widget_set_sensitive(rb_natation, FALSE);
    }

}

}


void
on_rb_musculation_supprission_admincours_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[0]=1;}
else
{choix_specialite[0]=0;}
}


void
on_rb_cardio_supprission_admincours_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[2]=1;}
else
{choix_specialite[2]=0;}
}


void
on_rb_danse_supprission_admincours_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[1]=1;}
else
{choix_specialite[1]=0;}
}


void
on_rb_pilate_supprission_admincours_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[4]=1;}
else
{choix_specialite[4]=0;}
}


void
on_rb_natation_supprission_admincours_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[3]=1;}
else
{choix_specialite[3]=0;}
}


void
on_cb_id_coach_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

GtkWidget *combobox;
combobox = lookup_widget(GTK_WIDGET(togglebutton), "combobox_idcours_suppr");
if (gtk_toggle_button_get_active(togglebutton))
{choix[1]=1;
gtk_widget_set_sensitive(combobox, TRUE);}
else
{choix[1]=0;
gtk_widget_set_sensitive(combobox, FALSE);}
}

void vider(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

    if (store == NULL)
    {

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", ID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", NOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("duree", renderer, "text", DUREE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("date", renderer, "text", DATE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("horaire", renderer, "text", HORAIRE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("capacite", renderer, "text", CAPACITE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("frais", renderer, "text", FRAIS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("id_coach", renderer, "text", ID_COACH, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    store = gtk_list_store_new(COLUMNS,
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store); 
}

void afficher_tv(GtkWidget *liste, char *fichier)
{
GtkCellRenderer *renderer;
GtkTreeViewColumn * column;
GtkTreeIter iter;
GtkListStore *store;
cours c;
char horaire[6];
char capacite_str[10];
char frais_str[20];
store==NULL;

FILE *f;
store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" id",renderer,"text",ID,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" nom",renderer,"text",NOM,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" duree",renderer,"text",DUREE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" date",renderer,"text",DATE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" horaire",renderer,"text",HORAIRE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" capacite",renderer,"text",CAPACITE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" frais",renderer,"text",FRAIS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes(" id_coach",renderer,"text",ID_COACH,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
}

store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
f=fopen(fichier,"r");
if(f==NULL)
{
return;
}
else
{
f=fopen(fichier,"a+");
while (fscanf(f, "%s %s %02d %02d %s %s %f %d %s",c.id_c, c.nom, &c.heure, &c.minute, c.date, c.dure, &c.frais, &c.capacite, c.id_e) != EOF)
{
horaire[0] = (c.heure / 10) + '0';
horaire[1] = (c.heure % 10) + '0';
horaire[2] = ':';
horaire[3] = (c.minute / 10) + '0';
horaire[4] = (c.minute % 10) + '0';
horaire[5] = '\0';

sprintf(capacite_str, "%d", c.capacite);
sprintf(frais_str, "%.3f", c.frais);

gtk_list_store_append (store,&iter);
gtk_list_store_set (store,&iter,ID, c.id_c, NOM, c.nom,DUREE,c.dure,DATE,c.date,HORAIRE,horaire,CAPACITE,capacite_str,FRAIS,frais_str,ID_COACH, c.id_e,-1);
}
fclose(f);
gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
g_object_unref (store);

}
}
void
on_btn_supprimer_cours_admin_clicked   (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *input;
GtkWidget *output;
GtkWidget *combobox_idcours_suppr;
cours c;
combobox_idcours_suppr = lookup_widget(objet_graphique, "combobox_idcours_suppr");
input = lookup_widget(objet_graphique, "entry_id_cours_supprission");
output = lookup_widget(objet_graphique,"Label_afficher_choix_suppr");
const char *txt = gtk_entry_get_text(GTK_ENTRY(input));
if(strlen(txt) == 0)
{
afficher_erreur("Il faut remplir tous les champs !");
return;
}
strcpy(c.id_c, txt);
if(supprimer("cours.txt", c.id_c))
{
gtk_label_set_text(GTK_LABEL(output), "Cours supprimé avec succès !");
int index = gtk_combo_box_get_active(GTK_COMBO_BOX(combobox_idcours_suppr));
if(index >= 0)
gtk_combo_box_remove_text(GTK_COMBO_BOX(combobox_idcours_suppr), index);
}
else
{
afficher_erreur("Erreur : impossible de supprimer le cours.");
}
gtk_entry_set_text(GTK_ENTRY(input), "");
}

// iciiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii

void
on_btn_actualier_cours_supprission_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkTreeIter iter;
GtkTreeModel *model;
GtkWidget *tv = lookup_widget(objet_graphique, "tv_cours_recherche");
GtkWidget *cb_type = lookup_widget(objet_graphique, "cb_type");
GtkWidget *combo_id = lookup_widget(objet_graphique, "combobox_idcours_suppr");
GtkWidget *cb_id = lookup_widget(objet_graphique, "cb_id_coach");
GtkWidget *rb_musc = lookup_widget(objet_graphique, "rb_muscl");
GtkWidget *rb_danse = lookup_widget(objet_graphique, "rb_ddanse");
GtkWidget *rb_cardio = lookup_widget(objet_graphique, "rb_card");
GtkWidget *rb_nat = lookup_widget(objet_graphique, "rb_nata");
GtkWidget *rb_pil = lookup_widget(objet_graphique, "rb_piilates");
FILE *fin = fopen("cours.txt", "r");
FILE *fout = fopen("cours_temp.txt", "w");
cours c;
int useid = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_id));
int usetype = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_type));
if (!useid && !usetype)
{
fclose(fin);
fclose(fout);
afficher_tv(tv, "cours.txt");
return;
}
char *texte = NULL;
model = gtk_combo_box_get_model(GTK_COMBO_BOX(combo_id));
if (useid && gtk_combo_box_get_active_iter(GTK_COMBO_BOX(combo_id), &iter))
gtk_tree_model_get(model, &iter, 0, &texte, -1);
char typ[20] = "";
if (usetype)
{
if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_musc))) strcpy(typ, "Musculation");
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_danse))) strcpy(typ, "Danse");
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_cardio))) strcpy(typ, "Cardio");
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_pil))) strcpy(typ, "Pilates");
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_nat))) strcpy(typ, "Natation");
}
while (fscanf(fin, "%s %s %02d %02d %s %s %f %d %s", c.id_c, c.nom, &c.heure, &c.minute, c.date, c.dure, &c.frais, &c.capacite, c.id_e) != EOF)
{
int ok = 1;
if (usetype && strcmp(typ, c.nom) != 0) ok = 0;
if (useid && (!texte || strcmp(texte, c.id_c) != 0)) ok = 0;
if (ok) fprintf(fout, "%s %s %02d %02d %s %s %.2f %d %s\n", c.id_c, c.nom, c.heure, c.minute, c.date, c.dure, c.frais, c.capacite, c.id_e);
}
fclose(fin);
fclose(fout);
if (texte) g_free(texte);
vider(tv);
afficher_tv(tv, "cours_temp.txt");
}

void
on_btn_retour_admin_supp_cours_clicked (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *fenetre_actuelle, *fenetre_acceuil;    
fenetre_actuelle = lookup_widget(objet_graphique, "espace_administrateur");
gtk_widget_destroy(fenetre_actuelle);

    
fenetre_acceuil = create_Acceuil_admin(); 
gtk_widget_show(fenetre_acceuil);
}


void
on_tv_recherche_cours_modif_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar* id_c;
gchar *nom;
gchar *dure;
gchar *date;
gchar *id_e;
gchar *horaire;
gchar *capacite;
gchar *frais;
char capacite_ch[20], frais_ch[20];
cours c; 
int jour, mois, annee,h,m;
GtkWidget *tv_modif;

GtkTreeModel *model =gtk_tree_view_get_model(treeview);
if (gtk_tree_model_get_iter(model, &iter, path))
{
gtk_tree_model_get(model, &iter,
                   0, &id_c,
                   1, &nom,
                   2, &dure,
                   3, &date,
                   4, &id_e,
                   5, &horaire,
                   6, &capacite,
                   7, &frais,
                   -1);
strcpy(c.id_c, id_c);
strcpy(c.nom, nom);
strcpy(c.dure, dure);
strcpy(c.date, date);
strcpy(c.id_e, id_e);


c.capacite = atoi(capacite);


if (sscanf(horaire, "%d:%d", &h, &m) == 2) {
GtkWidget *spin_h = lookup_widget(GTK_WIDGET(user_data), "sp_heure");
GtkWidget *spin_m = lookup_widget(GTK_WIDGET(user_data), "sp_min");
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_h), h);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_m), m);
}

GtkWidget *entry_id = lookup_widget(GTK_WIDGET(treeview), "entry_id_cours_modif");
gtk_entry_set_text(GTK_ENTRY(entry_id), c.id_c);

GtkWidget *entry_nom = lookup_widget(GTK_WIDGET(treeview), "entry_nom_cours_modif");
gtk_entry_set_text(GTK_ENTRY(entry_nom), c.nom);

GtkWidget *entry_d = lookup_widget(GTK_WIDGET(treeview), "entry_dure_cours_modif");
gtk_entry_set_text(GTK_ENTRY(entry_d), c.dure);


GtkWidget *entry_p = lookup_widget(GTK_WIDGET(treeview), "entry_prix_cours_modif");
if (frais != NULL) {
    c.frais = atof(frais);
    sprintf(frais_ch, "%.3f", c.frais);
    gtk_entry_set_text(GTK_ENTRY(entry_p), frais_ch);
}
GtkWidget *entry_c= lookup_widget(GTK_WIDGET(treeview), "entry_capacite_cours_modif");
sprintf(capacite_ch, "%d", c.capacite);
gtk_entry_set_text(GTK_ENTRY(entry_c), capacite_ch);

GtkWidget *entry_e = lookup_widget(GTK_WIDGET(treeview), "id_affectation_modif");
gtk_entry_set_text(GTK_ENTRY(entry_e), c.id_e);

if (sscanf(c.date, "%d/%d/%d", &jour, &mois, &annee) == 3)
{
GtkWidget *calendar = lookup_widget(GTK_WIDGET(treeview), "calendar_date_modif");  
gtk_calendar_select_month(GTK_CALENDAR(calendar), mois - 1, annee);
gtk_calendar_select_day(GTK_CALENDAR(calendar), jour);
}
tv_modif = lookup_widget(GTK_WIDGET(treeview), "tv_recherche_cours_modif");
afficher_tv(tv_modif,"cours.txt");

}
}


void
on_tv_cours_recherche_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar *idc;
cours c;
GtkTreeModel *model =gtk_tree_view_get_model(treeview);
if (gtk_tree_model_get_iter(model,&iter,path))
{
gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0, &idc,-1);
strcpy(c.id_c,idc);
GtkWidget *entry_id = lookup_widget(GTK_WIDGET(treeview), "entry_id_cours_supprission");
gtk_entry_set_text(GTK_ENTRY(entry_id), c.id_c);
}
}


void
on_tv_liste_cours_inscrit_row_activated(GtkTreeView *treeview,
                                        GtkTreePath *path,
                                        GtkTreeViewColumn *column,
                                        gpointer user_data)
{
GtkTreeIter iter;
gchar *idc;
cours c;
GtkTreeModel *model =gtk_tree_view_get_model(treeview);
if (gtk_tree_model_get_iter(model,&iter,path))
{
gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0, &idc,-1);
strcpy(c.id_c,idc);
GtkWidget *entry_id = lookup_widget(GTK_WIDGET(treeview), "Id_cours_membre");
gtk_entry_set_text(GTK_ENTRY(entry_id), c.id_c);
}
}

void on_cb_musculation_membre_inscrit_toggled(GtkToggleButton *togglebutton, gpointer user_data) 
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[0]=1;}
else
{choix_specialite[0]=0;}
}

void
on_cb_cardio_membre_inscrit_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[2]=1;}
else
{choix_specialite[2]=0;}
}


void
on_cb_danse_membre_inscrit_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[1]=1;}
else
{choix_specialite[1]=0;}
}


void
on_cb_natation_membre_inscrit_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[3]=1;}
else
{choix_specialite[3]=0;}
}


void
on_cb_pilates_membre_inscrit_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[4]=1;}
else
{choix_specialite[4]=0;}
}






///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void
on_button_actualiser_inscrit_cours_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{


GtkWidget *tv_cours_inscrit = lookup_widget(objet_graphique, "tv_liste_cours_inscrit");
FILE *fin = fopen("cours.txt", "r");
FILE *fout = fopen("cours_temp.txt", "w");
cours c;
if (!fin || !fout) { if(fin) fclose(fin); if(fout) fclose(fout); return; }

while (fscanf(fin, "%s %s %02d %02d %s %s %f %d %s",
              c.id_c, c.nom, &c.heure, &c.minute,
              c.date, c.dure, &c.frais, &c.capacite, c.id_e) != EOF)
{
int afficher = 0;
int filtre_active = 0;
for (int i = 0; i < 5; i++)
    if (choix_specialite[i] == 1)
        filtre_active = 1;
if (!filtre_active)
afficher = 1;
else
{
    if (strcmp(c.nom, "Musculation") == 0 && choix_specialite[0] == 1) afficher = 1;
    if (strcmp(c.nom, "Danse") == 0 && choix_specialite[1] == 1) afficher = 1;
    if (strcmp(c.nom, "Cardio") == 0 && choix_specialite[2] == 1) afficher = 1;
    if (strcmp(c.nom, "Natation") == 0 && choix_specialite[3] == 1) afficher = 1;
    if (strcmp(c.nom, "Pilates") == 0 && choix_specialite[4] == 1) afficher = 1;
}

if (!afficher)
    continue;

fprintf(fout, "%s %s %02d %02d %s %s %f %d %s\n",
        c.id_c, c.nom, c.heure, c.minute, c.date, c.dure,
        c.frais, c.capacite, c.id_e);
}

fclose(fin);
fclose(fout);
afficher_tv(tv_cours_inscrit, "cours_temp.txt");
}







void
on_rb_niv_debutant_inscrit_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_niv[0]=1;}
else
{choix_niv[0]=0;}
}


void
on_rb_niv_interm_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_niv[1]=1;}
else
{choix_niv[1]=0;}
}


void
on_rb_niv_avance_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_niv[2]=1;}
else
{choix_niv[2]=0;}
}


void
on_btn_inscrire_cours_clicked          (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

GtkWidget *input;
GtkWidget *rb_debutant, *rb_intermediaire, *rb_avance;
cours c;
char niveau[30];
input = lookup_widget(objet_graphique, "Id_cours_membre");
const char *txt = gtk_entry_get_text(GTK_ENTRY(input));
if(strlen(txt) == 0)
{
afficher_erreur("Il faut remplir tous les champs !");
return;
}
strcpy(c.id_c, txt);
rb_debutant = lookup_widget(objet_graphique, "rb_niv_debutant_inscrit");
rb_intermediaire = lookup_widget(objet_graphique, "rb_niv_interm");
rb_avance = lookup_widget(objet_graphique, "rb_niv_avance");
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_debutant)))
strcpy(niveau, "debutant");
else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_intermediaire)))
strcpy(niveau, "intermediaire");
else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_avance)))
strcpy(niveau, "avance");
else
{
afficher_erreur("Il faut remplir tous les champs !");
return;
}
cours cours_trouve = chercher("cours.txt", c.id_c);
if(strcmp(cours_trouve.id_c, "-1") == 0)
{
afficher_erreur("Cours inexistant !");
return;
}
GtkWidget *label = lookup_widget(objet_graphique, "label_afficher_inscri");
if(inscrire_cours("inscriptions.txt", c.id_c, niveau))
gtk_label_set_text(GTK_LABEL(label), "Inscription réussie !");
else
afficher_erreur("Échec de l'inscription");
gtk_entry_set_text(GTK_ENTRY(input), "");

}


void
on_btn_retour_membre_inscrit_clicked   (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *fenetre_actuelle, *fenetre_acceuil;    
fenetre_actuelle = lookup_widget(objet_graphique, "espace_membre");
gtk_widget_destroy(fenetre_actuelle);

    
fenetre_acceuil = create_Acceuil_membre(); 
gtk_widget_show(fenetre_acceuil);
}
void on_cb_recherche_horaire_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
GtkWidget *combobox;
combobox = lookup_widget(GTK_WIDGET(togglebutton), "combobox_horaire_modif_cours");
if (gtk_toggle_button_get_active(togglebutton))
{choix[0]=1;
gtk_widget_set_sensitive(combobox, TRUE);}
else
{choix[0]=0;
gtk_widget_set_sensitive(combobox, FALSE);}
}

void
on_btn_sup_mesinscrit_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}

void vider_inscrit(GtkWidget *liste)
{
 GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;
    GtkTreeIter iter;
store=NULL;

    store=gtk_tree_view_get_model(liste);

    if (store == NULL)
    {
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", ID_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", NOM_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Niveau", renderer, "text", NIVEAU_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Coach", renderer, "text", ID_COACH_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Durée", renderer, "text", DUREE_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", DATE_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Horaire", renderer, "text", HORAIRE_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Frais", renderer, "text", FRAIS_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

}


 store = gtk_list_store_new(ICOLUMNS,
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store); 
}

void afficher_inscrit(GtkWidget *liste)
{
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
cours c;
char id_insc[50],niveau[50];
char horaire[6];
char frais_txt[20];
store=NULL;

store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", ID_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", NOM_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Niveau", renderer, "text", NIVEAU_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Coach", renderer, "text", ID_COACH_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Durée", renderer, "text", DUREE_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", DATE_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Horaire", renderer, "text", HORAIRE_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Frais", renderer, "text", FRAIS_I, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

} 

store=gtk_list_store_new(ICOLUMNS,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING,
G_TYPE_STRING);

FILE *f_insc=fopen("inscriptions.txt","r");
FILE *f_cours=fopen("cours.txt","r");
if(!f_insc||!f_cours)
return;
while(fscanf(f_insc,"%49s %49s",id_insc,niveau)!=EOF)
{
rewind(f_cours);
while(fscanf(f_cours,"%s %s %02d %02d %s %s %f %d %s",c.id_c,c.nom,&c.heure,&c.minute,c.date,c.dure,&c.frais,&c.capacite,c.id_e)!=EOF)
{
if(strcmp(c.id_c,id_insc)==0)
{
sprintf(horaire,"%02d:%02d",c.heure,c.minute);
sprintf(frais_txt,"%.3f",c.frais);
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,
ID_I,c.id_c,
NOM_I,c.nom,
NIVEAU_I,niveau,
ID_COACH_I,c.id_e,
DUREE_I,c.dure,
DATE_I,c.date,
HORAIRE_I,horaire,
FRAIS_I,frais_txt,
-1);
break;
}
}
}
fclose(f_insc);
fclose(f_cours);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}


void
on_btn_actualiser_mesinscritcours_membre_clicked
                                        (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *tv;
tv=lookup_widget(objet_graphique,"tv_cours_deja_inscrit");
vider_inscrit(tv);
afficher_inscrit(tv);
}


void
on_btn_retour_membre_mesinscri_clicked (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_perte_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) objectif = 1;

}


void
on_prise_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) objectif = 2;
}


void
on_detente_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) objectif = 3;
}


void
on_performance_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) objectif = 4;
}


void
on_musculation_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) type_cours = 1;
}


void
on_danse_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) type_cours = 2;
}


void
on_cardio_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) type_cours = 3;
}


void
on_pilates_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) type_cours = 4;
}


void
on_natation_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if(gtk_toggle_button_get_active(togglebutton)) type_cours = 5;
}


void
on_pref_deb_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) niveau = 1;
}


void
on_pref_interm_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) niveau = 2;
}


void
on_pref_avanc_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) niveau = 3;
}


void
on_rb_1fois_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) frequence = 1;
}


void
on_rb_2ou3fois_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) frequence = 2;
}


void
on_rb_plus4fois_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) frequence = 3;
}

void
on_femme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) pref_entraineur = 1;
}


void
on_homme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) pref_entraineur = 2;
}


void
on_peuimporte_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) pref_entraineur = 3;
}


void
on_rb_email_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) mode_notification = 1;
}


void
on_rb_sms_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) mode_notification = 2;
}


void
on_rb_notif_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) mode_notification = 3;
}


void
on_resume_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) format_message = 1;
}


void
on_messagedetail_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) format_message = 2;
}


void
on_btn_enreg_pref_clicked              (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *combobox;
combobox=lookup_widget(objet_graphique,"combobox_pref_horaire");
pref_horaire = gtk_combo_box_get_active(GTK_COMBO_BOX(combobox)); 
if(objectif == 0 || type_cours == 0 || niveau == 0 || frequence == 0 || pref_entraineur == 0 || mode_notification == 0 || format_message == 0 || gtk_combo_box_get_active(GTK_COMBO_BOX(combobox)) < 0)
{
    afficher_erreur("Veuillez remplir tous les champs !");
    return;
}
ajouter_preferences();
sauvegarder_preferences();
GtkWidget *dialog;
dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Préférences enregistrées avec succès !");
gtk_dialog_run(GTK_DIALOG(dialog));
gtk_widget_destroy(dialog);
}


void
on_btn_retour_membre_forpref_clicked   (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

}


void
on_affichage_pref_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    Preference p;

    if (gtk_tree_model_get_iter(model, &iter, path))
    {
        gchar *obj;
        gchar *cours;
        gchar *niv;
        gchar *freq;
        gchar *entraineur;
        gchar *horaire;
        gchar *notif;
        gchar *format;

        gtk_tree_model_get(model, &iter,
                           0, &obj,
                           1, &cours,
                           2, &niv,
                           3, &freq,
                           4, &entraineur,
                           5, &horaire,
                           6, &notif,
                           7, &format,
                           -1);

        strcpy(p.obj, obj);
        strcpy(p.cours, cours);
        strcpy(p.niv, niv);
        strcpy(p.freq, freq);
        strcpy(p.entraineur, entraineur);
        strcpy(p.horaire, horaire);
        strcpy(p.notif, notif);
        strcpy(p.format, format);

        supprimer_preference_fichier("preferences.txt", p.obj);

        gtk_list_store_remove(GTK_LIST_STORE(model), &iter);

        g_free(obj); g_free(cours); g_free(niv); g_free(freq);
        g_free(entraineur); g_free(horaire); g_free(notif); g_free(format);
    }

}


enum {
P_OBJ,
P_COURS,
P_NIV,
P_FREQ,
P_ENTRAINEUR,
P_HORAIRE,
P_NOTIF,
P_FORMAT,
P_COLUMNS
};

void afficher_pref(GtkWidget* liste, char* fichier)
{
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
Preference p;
store = NULL;
store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
if(store == NULL)
{
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Objectif", renderer, "text", P_OBJ, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Cours", renderer, "text", P_COURS, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Niveau", renderer, "text", P_NIV, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Fréquence", renderer, "text", P_FREQ, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Entraîneur", renderer, "text", P_ENTRAINEUR, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Horaire", renderer, "text", P_HORAIRE, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Notification", renderer, "text", P_NOTIF, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("Format", renderer, "text", P_FORMAT, NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
}

store = gtk_list_store_new(P_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

FILE *f = fopen(fichier, "r");
if(f == NULL) return;

char ligne[512];
while(fgets(ligne, sizeof(ligne), f) != NULL)
{
char *token;

token = strtok(ligne, ";");
if(token) strncpy(p.obj, token, sizeof(p.obj)-1); p.obj[sizeof(p.obj)-1] = '\0';

token = strtok(NULL, ";");
if(token) strncpy(p.cours, token, sizeof(p.cours)-1); p.cours[sizeof(p.cours)-1] = '\0';

token = strtok(NULL, ";");
if(token) strncpy(p.niv, token, sizeof(p.niv)-1); p.niv[sizeof(p.niv)-1] = '\0';

token = strtok(NULL, ";");
if(token) strncpy(p.freq, token, sizeof(p.freq)-1); p.freq[sizeof(p.freq)-1] = '\0';

token = strtok(NULL, ";");
if(token) strncpy(p.entraineur, token, sizeof(p.entraineur)-1); p.entraineur[sizeof(p.entraineur)-1] = '\0';

token = strtok(NULL, ";");
if(token) strncpy(p.horaire, token, sizeof(p.horaire)-1); p.horaire[sizeof(p.horaire)-1] = '\0';

token = strtok(NULL, ";");
if(token) strncpy(p.notif, token, sizeof(p.notif)-1); p.notif[sizeof(p.notif)-1] = '\0';

token = strtok(NULL, ";\n");
if(token) strncpy(p.format, token, sizeof(p.format)-1); p.format[sizeof(p.format)-1] = '\0';

gtk_list_store_append(store, &iter);
gtk_list_store_set(store, &iter,
P_OBJ, p.obj,
P_COURS, p.cours,
P_NIV, p.niv,
P_FREQ, p.freq,
P_ENTRAINEUR, p.entraineur,
P_HORAIRE, p.horaire,
P_NOTIF, p.notif,
P_FORMAT, p.format,
-1);
}

fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}

void
on_btn_actualiser_mespref_clicked      (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *treeview;
treeview = lookup_widget(objet_graphique, "affichage_pref");
afficher_pref(treeview, "preference.txt");
}


void on_btn_modifier_mespref_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;
    GtkWidget *tv = lookup_widget(objet_graphique, "affichage_pref");


selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tv));

    if (!gtk_tree_selection_get_selected(selection, &model, &iter))
        return;

    gchar *obj;
    gchar *cours;
    gchar *niv;
    gchar *freq;
    gchar *entraineur;
    gchar *notif;
    gchar *format;
    gchar *horaire_txt;

    gtk_tree_model_get(model, &iter,
                       0, &obj,
                       1, &cours,
                       2, &niv,
                       3, &freq,
                       4, &entraineur,
                       5, &notif,
                       6, &format,
                       7, &horaire_txt,
                       -1);
printf("obj='%s'\n", obj);
    GtkWidget *notebook = lookup_widget(objet_graphique, "notebook10");
    GtkWidget *form_pref = lookup_widget(objet_graphique, "fixed31");
    int page_num = gtk_notebook_page_num(GTK_NOTEBOOK(notebook), form_pref);
    if (page_num != -1)
        gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), page_num);

   
GtkToggleButton *btn_perte      = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"perte"));
GtkToggleButton *btn_prise      = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"prise"));
GtkToggleButton *btn_detente    = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"detente"));
GtkToggleButton *btn_performance= GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"performance"));

gtk_toggle_button_set_active(btn_perte, strcmp(obj,"Perte de poids")==0);
gtk_toggle_button_set_active(btn_prise, strcmp(obj,"Prise de masse")==0);
gtk_toggle_button_set_active(btn_detente, strcmp(obj,"Bien étre/Détente")==0);
gtk_toggle_button_set_active(btn_performance, strcmp(obj,"Performance sportive")==0);


GtkToggleButton *btn_musculation = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"musculation"));
GtkToggleButton *btn_danse       = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"danse"));
GtkToggleButton *btn_cardio      = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"cardio"));
GtkToggleButton *btn_pilates     = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"pilates"));
GtkToggleButton *btn_natation    = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"natation"));

gtk_toggle_button_set_active(btn_musculation, strcmp(cours,"Musculation")==0);
gtk_toggle_button_set_active(btn_danse,       strcmp(cours,"Danse")==0);
gtk_toggle_button_set_active(btn_cardio,      strcmp(cours,"Cardio")==0);
gtk_toggle_button_set_active(btn_pilates,     strcmp(cours,"Pilates")==0);
gtk_toggle_button_set_active(btn_natation,    strcmp(cours,"Natation")==0);


GtkToggleButton *btn_deb   = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"pref_deb"));
GtkToggleButton *btn_interm= GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"pref_interm"));
GtkToggleButton *btn_avanc = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"pref_avanc"));

gtk_toggle_button_set_active(btn_deb,    strcmp(niv,"Débutant")==0);
gtk_toggle_button_set_active(btn_interm, strcmp(niv,"Intérmediaire")==0);
gtk_toggle_button_set_active(btn_avanc,  strcmp(niv,"Avancé")==0);


GtkToggleButton *btn_1fois   = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"rb_1fois"));
GtkToggleButton *btn_2ou3fois= GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"rb_2ou3fois"));
GtkToggleButton *btn_plus4fois=GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"rb_plus4fois"));

gtk_toggle_button_set_active(btn_1fois,    strcmp(freq,"1fois/semaine")==0);
gtk_toggle_button_set_active(btn_2ou3fois, strcmp(freq,"2 ou 3fois/semaie")==0);
gtk_toggle_button_set_active(btn_plus4fois,strcmp(freq,"+4fois/semaine")==0);


GtkToggleButton *btn_femme     = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"femme"));
GtkToggleButton *btn_homme     = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"homme"));
GtkToggleButton *btn_peuimporte=GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"peuimporte"));

gtk_toggle_button_set_active(btn_femme,      strcmp(entraineur,"Femme")==0);
gtk_toggle_button_set_active(btn_homme,      strcmp(entraineur,"Homme")==0);
gtk_toggle_button_set_active(btn_peuimporte, strcmp(entraineur,"Peu Importe")==0);


GtkToggleButton *btn_email = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"rb_email"));
GtkToggleButton *btn_sms   = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"rb_sms"));
GtkToggleButton *btn_notif = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"rb_notif"));

gtk_toggle_button_set_active(btn_email, strcmp(notif,"Email")==0);
gtk_toggle_button_set_active(btn_sms,   strcmp(notif,"Sms")==0);
gtk_toggle_button_set_active(btn_notif, strcmp(notif,"Notification application")==0);


GtkToggleButton *btn_resume       = GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"resume"));
GtkToggleButton *btn_messagedetail=GTK_TOGGLE_BUTTON(lookup_widget(objet_graphique,"messagedetail"));

gtk_toggle_button_set_active(btn_resume,        strcmp(format,"Résumé simple")==0);
gtk_toggle_button_set_active(btn_messagedetail, strcmp(format,"lien vers insccription")==0);


    GtkWidget *cb_horaire = lookup_widget(objet_graphique,"combobox_pref_horaire");
    GtkTreeModel *cb_model = gtk_combo_box_get_model(GTK_COMBO_BOX(cb_horaire));
    GtkTreeIter cb_iter;
    gboolean valid = gtk_tree_model_get_iter_first(cb_model, &cb_iter);
    while (valid)
    {
        gchar *txt;
        gtk_tree_model_get(cb_model, &cb_iter, 0, &txt, -1);
        if (strcmp(txt, horaire_txt) == 0) { gtk_combo_box_set_active_iter(GTK_COMBO_BOX(cb_horaire), &cb_iter); g_free(txt); break; }
        g_free(txt);
        valid = gtk_tree_model_iter_next(cb_model, &cb_iter);
    }

    g_free(obj); g_free(cours); g_free(niv); g_free(freq);
    g_free(entraineur); g_free(notif); g_free(format); g_free(horaire_txt);
}

void
on_btn_supprimer_mespref_clicked       (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
}


void
on_tv_coachdispo_cours_ajout_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar *ide;
Entraineur e;
GtkTreeModel *model =gtk_tree_view_get_model(treeview);
if (gtk_tree_model_get_iter(model,&iter,path))
{
gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0, &ide,-1);
strcpy(e.id,ide);
GtkWidget *entry_id = lookup_widget(GTK_WIDGET(treeview), "entry_id_affectation");
gtk_entry_set_text(GTK_ENTRY(entry_id), e.id);

}
}


void
on_tv_recherche_coachcours_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar *ide;
Entraineur e;
GtkTreeModel *model =gtk_tree_view_get_model(treeview);
if (gtk_tree_model_get_iter(model,&iter,path))
{
gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0, &ide,-1);
strcpy(e.id,ide);
GtkWidget *entry_id = lookup_widget(GTK_WIDGET(treeview), "id_affectation_modif");
gtk_entry_set_text(GTK_ENTRY(entry_id), e.id);
}
}




void
on_rb_musc_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[0]=1;}
else
{choix_specialite[0]=0;}
}


void
on_rb_dans_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[1]=1;}
else
{choix_specialite[1]=0;}
}


void
on_rb_pi_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[4]=1;}
else
{choix_specialite[4]=0;}
}


void
on_rb_nat_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[3]=1;}
else
{choix_specialite[3]=0;}
}


void
on_rb_car_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[2]=1;}
else
{choix_specialite[2]=0;}
}


void
on_rb_muscl_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[0]=1;}
else
{choix_specialite[0]=0;}
}


void
on_rb_piilates_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[4]=1;}
else
{choix_specialite[4]=0;}
}


void
on_rb_nata_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[3]=1;}
else
{choix_specialite[3]=0;}
}


void
on_rb_card_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[2]=1;}
else
{choix_specialite[2]=0;}
}


void
on_rb_ddanse_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix_specialite[1]=1;}
else
{choix_specialite[1]=0;}
}


void
on_cb_specialte_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
{
GtkWidget *rb_muscu;
GtkWidget *rb_danse;
GtkWidget *rb_cardio;
GtkWidget *rb_pilates;
GtkWidget *rb_natation; 


rb_muscu = lookup_widget(GTK_WIDGET(togglebutton), "rb_musc");
rb_danse = lookup_widget(GTK_WIDGET(togglebutton), "rb_dans");
rb_cardio = lookup_widget(GTK_WIDGET(togglebutton), "rb_car");
rb_pilates = lookup_widget(GTK_WIDGET(togglebutton), "rb_pi");
rb_natation = lookup_widget(GTK_WIDGET(togglebutton), "rb_nat");

    if (gtk_toggle_button_get_active(togglebutton)) {
        choix[1] = 1;
        gtk_widget_set_sensitive(rb_muscu, TRUE);
        gtk_widget_set_sensitive(rb_danse, TRUE);
        gtk_widget_set_sensitive(rb_cardio, TRUE);
        gtk_widget_set_sensitive(rb_pilates, TRUE);
        gtk_widget_set_sensitive(rb_natation, TRUE);
    } else {
        choix[1] = 0;
        gtk_widget_set_sensitive(rb_muscu, FALSE);
        gtk_widget_set_sensitive(rb_danse, FALSE);
        gtk_widget_set_sensitive(rb_cardio, FALSE);
        gtk_widget_set_sensitive(rb_pilates, FALSE);
        gtk_widget_set_sensitive(rb_natation, FALSE);
    }

}
}





void
on_button_inscrire_db_clicked          (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *inscri, *fenetre_actuelle;
fenetre_actuelle = lookup_widget(objet_graphique, "Dashboard");
gtk_widget_destroy(fenetre_actuelle);
inscri = create_Inscription();
gtk_widget_show(inscri);
}


void
on_button_connect_db_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *entry_email, *entry_mdp;
const char *email, *mdp;
entry_email = lookup_widget(objet_graphique, "in_mail_db");
entry_mdp   = lookup_widget(objet_graphique, "in_mdp_db");

email = gtk_entry_get_text(GTK_ENTRY(entry_email));
mdp   = gtk_entry_get_text(GTK_ENTRY(entry_mdp));

if (verifier_login("logad.txt", email, mdp))
{
GtkWidget *accueil, *fenetre_actuelle;
fenetre_actuelle = lookup_widget(objet_graphique, "Dashboard");
gtk_widget_destroy(fenetre_actuelle);
accueil = create_Acceuil_admin();
gtk_widget_show(accueil);
}
else if (verifier_login("logcoach.txt", email, mdp))
{
GtkWidget *accueil, *fenetre_actuelle;
fenetre_actuelle = lookup_widget(objet_graphique, "Dashboard");
gtk_widget_destroy(fenetre_actuelle);
accueil = create_Acceuil_entraineur();
gtk_widget_show(accueil);
}
else if (verifier_login("logmembre.txt", email, mdp))
{
GtkWidget *accueil, *fenetre_actuelle;
fenetre_actuelle = lookup_widget(objet_graphique, "Dashboard");
gtk_widget_destroy(fenetre_actuelle);
accueil = create_Acceuil_membre();
gtk_widget_show(accueil);
}
else
{
printf("Email ou mot de passe incorrect !");
}
}


void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_btn_zoom_cm_clicked                 (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

}


gboolean
on_stats_cours_expose_event            (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{

    cairo_t *cr;
    int w, h, margin;
    int maxv;
    double scale, bw;
    double x[5], hbar[5];

    w = widget->allocation.width;
    h = widget->allocation.height;
    margin = 30;

    cr = gdk_cairo_create(widget->window);


    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_rectangle(cr, 0, 0, w, h);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2);
    cairo_move_to(cr, margin, margin);
    cairo_line_to(cr, margin, h - margin);
    cairo_line_to(cr, w - margin, h - margin);
    cairo_stroke(cr);

    maxv = g_nb_muscu;
    if (g_nb_danse > maxv) maxv = g_nb_danse;
    if (g_nb_cardio > maxv) maxv = g_nb_cardio;
    if (g_nb_natation > maxv) maxv = g_nb_natation;
    if (g_nb_pilates > maxv) maxv = g_nb_pilates;
    if (maxv <= 0) maxv = 1;

    scale = (h - 2 * margin - 10) / (double)maxv;

    bw = (w - 2 * margin) / 8.0;
    x[0] = margin + bw * 0.5;
    x[1] = margin + bw * 1.8;
    x[2] = margin + bw * 3.1;
    x[3] = margin + bw * 4.4;
    x[4] = margin + bw * 5.7;

    hbar[0] = g_nb_muscu * scale;
    hbar[1] = g_nb_danse * scale;
    hbar[2] = g_nb_cardio * scale;
    hbar[3] = g_nb_natation * scale;
    hbar[4] = g_nb_pilates * scale;

    double couleurs[5][3] = {
        {0.2, 0.4, 0.9}, 
        {0.9, 0.3, 0.5},
        {0.3, 0.8, 0.3}, 
        {0.9, 0.6, 0.1}, 
        {0.6, 0.2, 0.7}  
    };

    char *labels[5] = {"Musculation", "Danse", "Cardio", "Natation", "Pilates"};
int total = g_nb_muscu + g_nb_danse + g_nb_cardio + g_nb_natation + g_nb_pilates;
double pourcentage[5];

if (total > 0) {
    pourcentage[0] = (g_nb_muscu * 100.0) / total;
    pourcentage[1] = (g_nb_danse * 100.0) / total;
    pourcentage[2] = (g_nb_cardio * 100.0) / total;
    pourcentage[3] = (g_nb_natation * 100.0) / total;
    pourcentage[4] = (g_nb_pilates * 100.0) / total;
} else {
    for(int i=0; i<5; i++) pourcentage[i] = 0;
}


    for(int i = 0; i < 5; i++) {
        cairo_set_source_rgb(cr, couleurs[i][0], couleurs[i][1], couleurs[i][2]);
        cairo_rectangle(cr, x[i], (h - margin) - hbar[i], bw, hbar[i]);
        cairo_fill(cr);

        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 12);
        cairo_move_to(cr, x[i], h - margin + 18);
        cairo_show_text(cr, labels[i]);

	char texte[10];
    sprintf(texte, "%.1f%%", pourcentage[i]);  
    cairo_move_to(cr, x[i], (h - margin) - hbar[i] - 5); 
    cairo_show_text(cr, texte);
    }

    cairo_destroy(cr);
    return FALSE;
}




void
on_btn_stats_cours_clicked             (GtkButton      *button,
                                        gpointer         user_data)
{
GtkWidget *drawing;

    drawing = lookup_widget(GTK_WIDGET(button), "stats_cours");
    if (!drawing) {
        g_print("Widget stats_cours non trouvé !\n");
        return;
    }

    if (!compter_type_cours("cours.txt", &g_nb_muscu, &g_nb_danse, &g_nb_cardio, &g_nb_natation, &g_nb_pilates)) {
        g_print("Erreur : fichier cours.txt introuvable.\n");
        return;
    }

    gtk_widget_queue_draw(drawing);
}


void
on_btn_retour_dash_clicked             (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *accueil, *fenetre_actuelle;
fenetre_actuelle = lookup_widget(objet_graphique, "Inscription");
gtk_widget_destroy(fenetre_actuelle);
accueil = create_Dashboard();
gtk_widget_show(accueil);
}



void
on_btn_valider_dash_clicked            (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *entry_email, *combo, *fenetre;
GtkTreeModel *model;
GtkTreeIter iter;
const char *email;
gchar *heure = NULL;
entry_email = lookup_widget(objet_graphique, "entry_mail_winscr");
combo = lookup_widget(objet_graphique, "combobox_rdv");
email = gtk_entry_get_text(GTK_ENTRY(entry_email));
model = gtk_combo_box_get_model(GTK_COMBO_BOX(combo));
if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(combo), &iter))
gtk_tree_model_get(model, &iter, 0, &heure, -1);
if (strlen(email) == 0 || heure == NULL)
{
afficher_erreur("Veuillez remplir tous les champs");
return;
}
if (nb_rendezvous_pour_heure(heure) >= 2)
{
afficher_erreur("Rendez-vous complet (2 personnes max)");
return;
}
enregistrer_rdv(email, heure);
gtk_entry_set_text(GTK_ENTRY(entry_email), "");
gtk_combo_box_set_active(GTK_COMBO_BOX(combo), -1);

}

void
on_btn_retour__admin_clicked(GtkWidget *objet_graphique,gpointer user_data)
{
GtkWidget *fenetre_actuelle, *fenetre_acceuil;

    
fenetre_actuelle = lookup_widget(objet_graphique, "espace_administrateur");
gtk_widget_destroy(fenetre_actuelle);

    
fenetre_acceuil = create_Acceuil_admin(); 
gtk_widget_show(fenetre_acceuil);
}




