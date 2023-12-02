//
// Created by Willyson on 25/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_TOOLBOXWILLIAM_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_TOOLBOXWILLIAM_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct{
    int id;
    int col;
    float temps;
}sTache;

typedef struct{
    int id; //chaque sPoste suit le suivant: une opération b dépedant de a pourra se trouver dans la station n si a est effectué par la station m<n
    int* taches;
    float tpsTot;//temps cumulé des opérations étant effectuées dans  cette station
}sPoste;

//Prototype des programmes
sTache* wReadFileTimeOperation(float* prTempsDeCycle);
sPoste* wRepartitionStationTemps(sTache* prTabTache,float prTempsDeCycle);
sTache * wReadFileTimeOperation(float* prTempsDeCycle);
#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_TOOLBOXWILLIAM_H
