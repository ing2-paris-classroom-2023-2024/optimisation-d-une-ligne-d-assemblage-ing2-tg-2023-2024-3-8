
#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_TOOLBOX_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_TOOLBOX_H


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

sTache* wReadFileTimeOperation();
sPoste* wRepartitionStationTempsCol(sTache* tabTache, int col, float Tc, int* nbSsStations);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_TOOLBOX_H
