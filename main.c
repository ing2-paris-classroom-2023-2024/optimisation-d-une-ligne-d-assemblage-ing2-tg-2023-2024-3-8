//
// Created by William on 12/11/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "ContrainteTemps.h"
#include "william.h"
int nbTaches;
poste* postes;
int main(){
    nbTaches=0;
    printf("chelou\n");
    tache* taches= NULL;
    taches=wReadFileTimeOperation(&nbTaches);
    /*printf("c'est pas la faute du voisin de gauche");*/
    postes= exclusion(1,taches,nbTaches,1);
    return 0;
}
