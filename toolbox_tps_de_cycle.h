
#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_TOOLBOX_TPS_DE_CYCLE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_TOOLBOX_TPS_DE_CYCLE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct Tache{
    int id;
    int marque;
    int col;
    int degreeEntree;
    float temps;
    int nbPredecesseur;
    int nbSuccesseurs;
    int *tListeTachePrecedente;
    bool estSansSuccesseur;
}sTache;

typedef struct parametre{
    int cNombreOperations;
    int cNombreTacheAvecSucesseur;
}sParametre;

typedef struct{
    int id; //chaque sPoste suit le suivant: une opération b dépedant de a pourra se trouver dans la station n si a est effectué par la station m<n
    int* taches;
    float tpsTot;//temps cumulé des opérations étant effectuées dans  cette station
    int cNombreTaches;
}sPoste;

//Prototype des programmes

//Lecture du fichier
sTache* ReadFileTimeOperations(float* prTempsDeCycle,sParametre * prParametreListe);
void ReadFilePrecedentOperations(sTache *prListeTache,sParametre* prParametre);


//Repartition uniquement selon le temps
sPoste* RepartitionStationTemps(sTache* prTabTache,float prTempsDeCycle,sParametre* prParametre);

//Temps et précedence
sPoste* RepartitionStationTempsSansTris(sTache* prTabTache, float prTempsDeCycle, sParametre *prParametre);

//Precedence
sTache* TriTopologiques(sTache* prListeTache, sParametre *prParametre,float prTempsDeCycle);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_TOOLBOX_TPS_DE_CYCLE_H
