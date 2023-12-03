#define ignorerPrecedence 0
#define ignorerTemps 1
#define ignorerCouleur 0

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "ContraintePrecedences.h"
#include "ContrainteTemps.h"
#include "william.h"
#include "Exclusion_et_Exclusion_TempsDeCycles.h"


int Les3(){
    int nbTaches;
    poste* postes;
    int idMaxPrec;
    int ** matricePrec;
    int temps;
    FILE *tempsExec = fopen("temps_cycle.txt", "r");

    if (tempsExec == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        return 0;
    }
    fscanf(tempsExec,"%d",&temps);
    fclose(tempsExec);
    nbTaches=0;
    tache* taches= NULL;
    taches=ReadFileTimeOperation(&nbTaches);

    //printf("oui ?");
    matricePrec=creerPrec(&idMaxPrec);
    postes= exclusion(taches,nbTaches,temps,matricePrec,idMaxPrec,ignorerCouleur,ignorerTemps,ignorerPrecedence);
    //affichageExclusion();*

    return 0;
}
