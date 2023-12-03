//
// Created by William on 12/11/2023.
//
#define IgnorerPrecedence 0
#define IgnorerTemps 0

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "structs.h"
#include "ContraintePrecedence.h"
#include "Exclusionalexandre.h"
#include "ContrainteTemps.h"
#include "william.h"

int nbTaches;
poste* postes;
int idMaxPrec;
int ** matricePrec;
float temps;
int main(){
    FILE *tempsExec = fopen("temps_cycle.txt", "r");

    if (tempsExec == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        return 0;
    }
    fscanf(tempsExec,"%f",&temps);
    fclose(tempsExec);
    nbTaches=0;
    tache* taches= NULL;
    taches=wReadFileTimeOperation(&nbTaches);

    //printf("oui ?");
    matricePrec=creerPrec(&idMaxPrec);
    postes= exclusion(taches,nbTaches,temps,matricePrec,idMaxPrec);
    //affichageExclusion();*

    return 0;
}
