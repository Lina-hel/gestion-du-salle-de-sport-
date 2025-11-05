#include <stdio.h>
#include <string.h>
#include "evenement.h"

int main()
{
    // Test des fonctions evenement
    evenement e1 = {1, "Conference Tech", "Conference sur les nouvelles technologies",
                   "15/12/2024", "14:00", 100, 100, 50.0};
    evenement e2 = {2, "Workshop IA", "Atelier pratique sur l'intelligence artificielle",
                   "20/12/2024", "10:00", 50, 50, 75.0};
  
   
    int x = ajouter_evenement("evenements.txt", e1);
    if(x == 1)
        printf("\nAjout d'evenement avec succes");
    else
        printf("\nEchec ajout");
   
    x = ajouter_evenement("evenements.txt", e2);
    if(x == 1)
        printf("\nAjout du deuxieme evenement avec succes");
    else
        printf("\nEchec ajout du deuxieme evenement");
   
    // Modification
    evenement e_modif = {1, "Conference Tech Modifiee", "Conference mise a jour",
                        "16/12/2024", "15:00", 120, 120, 60.0};
    x = modifier_evenement("evenements.txt", 1, e_modif);
    if(x == 1)
        printf("\nModification d'evenement avec succes");
    else
        printf("\nEchec Modification");
   
    // Recherche
    e2 = chercher_evenement("evenements.txt", 2);
    if(e3.id != -1)
        printf("\nEvenement trouve: %s", e2.nom);
    else
        printf("\nEvenement introuvable");
   
    
   
    // Suppression evenement
    x = supprimer_evenement("evenements.txt", 1);
    if(x == 1)
        printf("\nSuppression d'evenement avec succes");
    else
        printf("\nEchec Suppression evenement");
   
    return 0;
   // participation
	participer_evenement("evenements.txt, participation p1)
	if(x == 1)
        printf("\n vous avez participer à un evenement.");
    else
        printf("\nEchec de participation.");

}
