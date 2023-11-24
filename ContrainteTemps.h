//
// Created by clementt on 23/11/23.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_CONTRAINTETEMPS_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_CONTRAINTETEMPS_H


typedef struct{
    int id; //chaque poste suit le suivant: une opération b dépedant de a pourra se trouver dans la station n si a est effectué par la station m<n
    int* taches;
    int tpsTot;//temps cumulé des opérations étant effectuées dans  cette station
    int col;//couleur des taches qui y sont (cf algo exclusion)
}poste;

typedef struct{
    int id;
    int col;
    int temps;
}tache;

int contraintePrecRespecte(){}//je définis rien pour l'instant, cette fonction dépoendra de la manière dont sont gérées les précédences.

void exclusion(int nbCol,tache* taches,int nbTaches,int T0){
    tache** tachesCol=malloc(nbCol*(sizeof(tache*)));
    int* repartCol= malloc(nbCol*(sizeof(int)));
    for (int i = 0; i < nbCol; ++i) {
        tachesCol[i]= malloc(nbTaches*sizeof(tache));
    }
    for (int i = 0; i < nbCol; ++i){
        repartCol[i]=0;
    }
    for (int i = 0; i < nbTaches; ++i) {
        tachesCol[taches[i].col][repartCol[taches[i].col]]=taches[i];
        repartCol[taches[i].col]++;
    }
    tache temp;
    for (int i = 0; i < nbCol; ++i) {//Tri à bulles pour avoir, dans chaque couleur, les tâches triées par ordre de temps
        for (int j = 0; j < repartCol[i]-1; ++j) {
            for (int k = 0; k < repartCol[i]-j-1; ++k) {
                if(tachesCol[i][k].temps>tachesCol[i][k+1].temps){
                    temp= tachesCol[i][k+1];
                    tachesCol[i][k+1]=tachesCol[i][k];
                    tachesCol[i][k]=temp;
                }
            }
        }
    }

}
#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_CONTRAINTETEMPS_H
