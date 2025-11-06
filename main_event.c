#include <stdio.h>
#include <string.h>
#include "event.h"

int main()
{
    printf("=== TEST DES FONCTIONS DISPONIBLES ===\n\n");

   
    printf("1. TEST AJOUT D'EVENEMENTS:\n");
    printf("----------------------------\n");
   
    evenement e1 = {1, "Conference_Tech", "14:00", "Salle_A",
                   50.0, "Conference", 0, "Pro", "15/12/2024"};
   
    evenement e2 = {2, "Workshop_IA", "10:00", "Salle_B",
                   75.0, "Atelier", 0, "Educatif", "20/12/2024"};
   
    evenement e3;

    int x = ajouter_evenement("evenements.txt", e1);
    if(x == 1)
        printf("✓ Événement 1 ajouté: %s (ID: %d)\n", e1.nom, e1.id);
    else
        printf("✗ Échec ajout événement 1\n");
   
    x = ajouter_evenement("evenements.txt", e2);
    if(x == 1)
        printf("✓ Événement 2 ajouté: %s (ID: %d)\n", e2.nom, e2.id);
    else
        printf("✗ Échec ajout événement 2\n");

    
    printf("\n2. TEST RECHERCHE D'EVENEMENT:\n");
    printf("-------------------------------\n");
   
    e3 = chercher_evenement("evenements.txt", 1);
    if(e3.id != -1)
        printf("✓ Événement trouvé: %s (Lieu: %s, Date: %s)\n", e3.nom, e3.lieu, e3.date);
    else
        printf("✗ Événement introuvable\n");

    
    printf("\n3. TEST MODIFICATION D'EVENEMENT:\n");
    printf("----------------------------------\n");
   
    evenement e_modif = {1, "Conference_Tech_Modifiee", "15:00", "Salle_Principale",
                       60.0, "Conference", 50, "Pro", "16/12/2024"};
   
    x = modifier_evenement("evenements.txt", 1, e_modif);
    if(x == 1)
        printf("✓ Événement ID 1 modifié avec succès\n");
    else
        printf("✗ Échec modification d'événement\n");

    
    e3 = chercher_evenement("evenements.txt", 1);
    if(e3.id != -1)
        printf("✓ Événement modifié trouvé: %s (Nouveau lieu: %s)\n", e3.nom, e3.lieu);
    else
        printf("✗ Événement modifié introuvable\n");

    
    printf("\n4. TEST PARTICIPATION A UN EVENEMENT:\n");
    printf("-------------------------------------\n");
   
    participation p1 = {1, "Jean_Dupont", "jean.dupont@email.com", "0123456789", "10/12/2024"};
    participation p2 = {1, "Marie_Martin", "marie.martin@email.com", "0987654321", "10/12/2024"};

    x = participer_evenement("participations.txt", p1);
    if(x == 1)
        printf("✓ Participation 1 ajoutée: %s pour événement %d\n", p1.nom_participant, p1.id_evenement);
    else
        printf("✗ Échec ajout participation 1\n");
   
    x = participer_evenement("participations.txt", p2);
    if(x == 1)
        printf("✓ Participation 2 ajoutée: %s pour événement %d\n", p2.nom_participant, p2.id_evenement);
    else
        printf("✗ Échec ajout participation 2\n");

    
    printf("\n5. TEST SUPPRESSION D'EVENEMENT:\n");
    printf("---------------------------------\n");
   
    x = supprimer_evenement("evenements.txt", 1);
    if(x == 1)
        printf("✓ Suppression d'événement ID 1 avec succès\n");
    else
        printf("✗ Échec suppression événement\n");

    
    e3 = chercher_evenement("evenements.txt", 1);
    if(e3.id == -1)
        printf("✓ Vérification: événement supprimé avec succès\n");
    else
        printf("✗ Erreur: événement toujours présent\n");

    
    printf("\n6. VERIFICATION FINALE:\n");
    printf("------------------------\n");
   
    e3 = chercher_evenement("evenements.txt", 2);
    if(e3.id != -1)
        printf("✓ Événement 2 toujours présent: %s\n", e3.nom);
    else
        printf("✗ Événement 2 introuvable (ne devrait pas être supprimé)\n");

    printf("\n=== TOUS LES TESTS TERMINES ===\n");
    printf("Vérifiez les fichiers 'evenements.txt' et 'participations.txt' pour voir les résultats.\n");

    return 0;
}
	

