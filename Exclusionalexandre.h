//
// Created by super on 26/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_EXCLUSIONALEXANDRE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_EXCLUSIONALEXANDRE_H
void influence(t_graphe* ptgraphe );


typedef struct Workstation {
    int  num; // numero de la station de travail
    int  nbTaches;     // nombres de tâches de la station de travail
    int* taches; // listes des tâches de la station de travail
    int  duree; // duree totale d'execution des taches dans la station de travail
} t_station ;

typedef struct LigneAssemblage {
    int nombreDeStations; // nombre de stations
    t_station* WS; // tableau des WS
} t_ligne;

int** ContrainteExclusion(char* nomFichier,int* ordremat);

int prochaineCouleurDisponible(int sommet, int nombre_sommets,int* couleurs,int** matrice_adjacence);

void affichageExclusion();
#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_EXCLUSIONALEXANDRE_H
