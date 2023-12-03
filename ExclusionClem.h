
#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_EXCLUSIONCLEM_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_EXCLUSIONCLEM_H

typedef struct Workstations {
    int  num; // numero de la station de travail
    int  nbTaches;     // nombres de tâches de la station de travail
    int* taches; // listes des tâches de la station de travail
    int  duree; // duree totale d'execution des taches dans la station de travail
} t_station ;

typedef struct LigneAssemblages {
    int nombreDeStations; // nombre de stations
    t_station* WS; // tableau des WS
} t_ligne;

int** ContrainteExclusions(char* nomFichier,int* ordremat);

int prochaineCouleurDisponibles(int sommet, int nombre_sommets,int* couleurs,int** matrice_adjacence);

void affichageExclusions();

int* listeColl(int *j,int * couleurs,int ignorerCol);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_EXCLUSIONCLEM_H
