//
// Created by super on 03/12/2023.
//

#include <stdio.h>
#include "Exclusionalexandre.h"

#include <stdlib.h>

//////////////////////////////////////LECTURE DE LA PRECEDENCE ////////////////////////////////////////////////////////
int** lecturePrecedence(int* ordremat){
    FILE* fp= fopen("precedences.txt","r");
    if(!fp){
        printf("Probleme d ouverture du fichier\n");
    }
    int ordre=0,nb1,nb2;
    while(fscanf(fp,"%d %d\n",&nb1,&nb2)==2){ //Recherche du nombre de Taches Maximums et donc de l'ordre du graphe qu'on va créer
        //printf("op1 op2 : %d %d \n",nb1,nb2);
        if(nb2>ordre) {
            ordre = nb2;
        }
        if(nb1>ordre) {
            ordre = nb1;
        }
    }
    *ordremat=ordre+1;

    ///Création d'une matrice d'adjacence selon l'ordre trouvé
    int** matrice;

    // Allocation dynamique pour les lignes
    matrice = (int**) malloc((ordre+1) * sizeof(int*));

    if (matrice == NULL) {
        printf("Erreur d'allocation pour les lignes de la matrice.\n");
        exit(EXIT_FAILURE);
    }

    // Allocation dynamique pour les colonnes de chaque ligne
    for (int i = 0; i < ordre+1; i++) {
        matrice[i] = (int*) calloc(ordre+1, sizeof(int));

        if (matrice[i] == NULL) {
            printf("Erreur d'allocation pour les colonnes de la matrice.\n");
            exit(EXIT_FAILURE);
        }
    }

    ///On rembobine le fichier au début pour remplir la matrice d'adjacence en fonction des contraintes d'exclusion
    rewind(fp);
    while(fscanf(fp,"%d %d\n",&nb1,&nb2)==2){
        matrice[nb1][nb2]=1;
        //printf("op1 op2 : %d %d \n",nb1,nb2);
    }
    return matrice;
}


/////////////////////////////////////////////////////////////////////////////CONTRAINTE DE PRECEDENCE ET D'EXCLUSION
struct Probleme {
    int** grapheExclusion;
    int** graphePrecedence;
    int nbTaches;
    int* stations;
    int* tacheAssignee;
};

// Fonction pour calculer le degré d'une tâche dans le graphe de précédence
int calculerDegre(struct Probleme* probleme, int tache) {
    int degre = 0;
    for (int i = 1; i <= probleme->nbTaches; i++) {
        if (probleme->graphePrecedence[i][tache]) {
            degre++;
        }
    }
    //printf("Tache : %d Degree : %d\n", tache,degre);
    return degre;
}

// Fonction pour trouver la tâche avec le degré minimal non assignée
int trouverTacheAvecMinDegre(struct Probleme* probleme, int* degre) {
    int minDegre = probleme->nbTaches + 1;
    int tacheSelectionnee = -1;

    for (int tache = 1; tache <= probleme->nbTaches; tache++) {
        if (probleme->tacheAssignee[tache] == 0) {
            *degre = calculerDegre(probleme, tache);
            if (*degre < minDegre) {
                minDegre = *degre;
                tacheSelectionnee = tache;
            }
        }
    }
    return tacheSelectionnee;
}

// Fonction pour vérifier si une tâche peut être ajoutée à une station donnée
int estTacheValide(struct Probleme* probleme, int tache, int tachec) {
    if (probleme->grapheExclusion[tache][tachec] == 0) {
        return 1;
    }
    else return 0;
}

// Fonction principale pour générer les stations
void genererStations(struct Probleme* probleme) {
    int nbstation=1,curseurstat=1;
    int tache;
    int degre;
    tache= trouverTacheAvecMinDegre(probleme,&degre);
    if(tache==-1){
        printf("Pas de taches trouvees\n");
        return;
    }
    probleme->tacheAssignee[tache]=1;
    do{
       tache= trouverTacheAvecMinDegre(probleme,&degre);
       if (tache!=-1){
           for(int i=1; i<=probleme->nbTaches;i++){
              if(probleme->tacheAssignee[i]>0){
                  if(estTacheValide(probleme,tache,i)){
                      probleme->tacheAssignee[tache]=probleme->tacheAssignee[i];
                      break;
                  }
              }
           }
           if(probleme->tacheAssignee[tache]==0){
               nbstation++;
               probleme->tacheAssignee[tache]=nbstation;
           }
       }
    }while(tache!=-1);

}

int precedenceEtExclusion() {
    struct Probleme monProbleme;
    int nbTacheexclu,nbTacheprece;

    // Allocation dynamique des tableaux
    monProbleme.grapheExclusion  = ContrainteExclusion("exclusions.txt",&nbTacheexclu);
    monProbleme.graphePrecedence = lecturePrecedence(&nbTacheprece);
    ///RECHERCHE
    if(nbTacheexclu>=nbTacheprece){
        monProbleme.nbTaches=nbTacheexclu-1;
    }
    else{
        monProbleme.nbTaches=nbTacheprece-1;
    }
    printf("[DEBUG]: nbTaches = %d\n", monProbleme.nbTaches);

    monProbleme.stations = malloc((monProbleme.nbTaches + 1) * sizeof(int));
    monProbleme.tacheAssignee = malloc((monProbleme.nbTaches + 1) * sizeof(int));
    for (int i = 1; i <= monProbleme.nbTaches; i++) {
        monProbleme.tacheAssignee[i] = 0; // Initialisation à zéro
        monProbleme.stations[i]=0; //Initialisation à 0
    }
    printf("[DEBUG]: tacheAssignee init a 0 \n");

    printf("[DEBUG]: %d %d \n",nbTacheprece,nbTacheexclu);


    // Initialisation des graphes d'exclusion et de précédence à partir de l'entrée utilisateur ou d'un fichier
    // ...

    // Générer les stations en utilisant l'heuristique de degré minimal
    genererStations(&monProbleme);
    // Afficher la configuration des stations
    printf("Configuration de stations :\n ");
    for (int i = 1; i <= monProbleme.nbTaches; i++) {
        printf("Tache: %d station -> %d\n",i,monProbleme.tacheAssignee[i]);
    }
    printf("\n");

    // Libérer la mémoire allouée
    for (int i = 1; i <= monProbleme.nbTaches; i++) {
        free(monProbleme.grapheExclusion[i]);
        free(monProbleme.graphePrecedence[i]);
    }
    free(monProbleme.grapheExclusion);
    free(monProbleme.graphePrecedence);
    free(monProbleme.stations);
    free(monProbleme.tacheAssignee);

    return 0;
}
int main(){
    precedenceEtExclusion();
}