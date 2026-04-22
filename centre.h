#ifndef CENTRE_H_INCLUDED
#define CENTRE_H_INCLUDED

#include <gtk/gtk.h>


typedef struct
{
    char id[20];
    char nom[50];
    char adresse[100];
    char type[10];          
    char specialites[100];  
    char horaire[50];
    char parking[50];            
    int capacite;
    char date_ouverture[20];

} centre;
typedef struct
{
    int cardio;
    int musculation;
    int danse;
    int pilates;
    int natation;
} StatCentre;


void ajouter_centre(centre c);

#endif

