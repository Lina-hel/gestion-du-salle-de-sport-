
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gestion_cours.h"

int main() {
    int choix=-1;
    cours c1, c2, c3;
    int x;
    char id_recherche[30];
    char id_c[30];

    do {
        printf("MENU DE GESTION DES COURS\n");
        printf("1. Afficher les cours\n");
        printf("2. Ajouter un cours\n");
        printf("3. Modifier un cours\n");
        printf("4. Supprimer un cours\n");
        printf("5. Chercher un cours\n");
        printf("6. Inscrire à un cours\n");
        printf("0. Quitter\n");
        printf("Saisissez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
        case 1:
            afficher_cours("cours.txt");
            break;

        case 2:
            printf(" Ajouter un cours\n");
            printf("ID du cours : ");
            scanf("%s", c1.id_c);
            printf("Nom du cours : ");
            scanf("%s", c1.nom);
            printf("Durée : ");
            scanf("%s", c1.dure);
            printf("Date (jj/mm/aaaa) : ");
            scanf("%s", c1.date);
            printf("Spécialité : ");
            scanf("%s", c1.specialite);
            printf("ID de l'entraineur : ");
            scanf("%s", c1.id_e);
            printf("Heure : ");
            scanf("%d", &c1.heure);
            printf("Minute : ");
            scanf("%d", &c1.minute);
            printf("Capacité : ");
            scanf("%d", &c1.capacite);
            printf("Frais : ");
            scanf("%f", &c1.frais);

            x = ajouter("cours.txt", c1);
            if (x == 1)
                printf("Ajout du cours avec succès.\n");
            else
                printf("Échec d'ajout.\n");
            break;

        case 3:
            printf(" Modifier un cours \n");
            printf("Entrez l'ID du cours à modifier : ");
            scanf("%s", id_recherche);
	    strcpy(c2.id_c,id_recherche);

            printf("Nouveau nom : ");
            scanf("%s", c2.nom);
            printf("Nouvelle durée : ");
            scanf("%s", c2.dure);
            printf("Nouvelle date : ");
            scanf("%s", c2.date);
            printf("Nouvelle spécialité : ");
            scanf("%s", c2.specialite);
            printf("Nouvel ID d'entraineur : ");
            scanf("%s", c2.id_e);
            printf("Nouvelle heure : ");
            scanf("%d", &c2.heure);
            printf("Nouvelle minute : ");
            scanf("%d", &c2.minute);
            printf("Nouvelle capacité : ");
            scanf("%d", &c2.capacite);
            printf("Nouveaux frais : ");
            scanf("%f", &c2.frais);

            x = modifier("cours.txt", id_recherche, c2);
            if (x == 1)
                printf("Modification réussie.\n");
            else
                printf("Échec de la modification.\n");
            break;

        case 4:
            printf(" Supprimer un cours \n");
            printf("Entrez l'ID du cours à supprimer : ");
            scanf("%s", id_recherche);
            x = supprimer("cours.txt", id_recherche);
            if (x == 1)
                printf("Suppression réussie.\n");
            else
                printf("Échec de la suppression.\n");
            break;

        case 5:
            printf(" Chercher un cours \n");
            printf("Entrez l'ID du cours à chercher : ");
            scanf("%s", id_recherche);
            c3 = chercher("cours.txt", id_recherche);
            if (strcmp(c3.id_c, "-1") == 0)
                printf("Cours introuvable.\n");
            else
                printf("Cours trouvé : %s (%s)\n", c3.nom, c3.id_c);
            break;

        case 6:
    	    printf("Donnez l'identifiant du cours à inscrire : ");
            scanf("%s", id_c);
            cours c_found = chercher("cours.txt", id_c);
            if (strcmp(c_found.id_c, "-1") == 0) {
            	printf(" Cours introuvable !\n");
            }
	    else {
            if (inscrire_cours("inscriptions.txt", id_c))
            	printf("Inscription réussie pour le cours %s ✅\n", id_c);
            else
           	 printf("Erreur lors de l'inscription \n");
   	    }
   	    break;
        case 0:
            printf("Fermeture du programme...\n");
            break;

        default:
            printf("Choix invalide, veuillez réessayer.\n");
        }

    } while (choix != 0);

    return 0;
}

