
#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_STRUCTURES_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_STRUCTURES_H

typedef struct t_poste{
    int* taches;
    float tpsTot;//temps cumulé des opérations étant effectuées dans  cette station
    int col;//couleur des taches qui y sont (cf algo exclusion)
    int nbTache;
    struct t_poste* suivant;
}poste;

typedef struct{
    int id;
    int col;
    float temps;
}tache;

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_STRUCTURES_H
