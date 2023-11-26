//
// Created by clementt on 23/11/23.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_CONTRAINTETEMPS_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_CONTRAINTETEMPS_H


typedef struct t_poste{
    int* taches;
    int tpsTot;//temps cumulé des opérations étant effectuées dans  cette station
    int col;//couleur des taches qui y sont (cf algo exclusion)
    int nbTache;
    struct t_poste* suivant;
}poste;

typedef struct{
    int id;
    int col;
    int temps;
}tache;

int contraintePrecRespecte(){}//je définis rien pour l'instant, cette fonction dépoendra de la manière dont sont gérées les précédences.

poste* ajouterPoste(poste* poste1,int taille){
    poste* poste2= malloc(sizeof(poste*));
    poste1->suivant=poste2;
    poste2->taches= malloc(taille*sizeof(tache));
    poste2->nbTache=0;
    poste2->tpsTot=0;
    poste2->suivant=NULL;
    return poste2;
}

poste* exclusion(int nbCol,tache* taches,int nbTaches,int T0){
    tache** tachesCol=malloc(nbCol*(sizeof(tache*)));
    int* repartCol= malloc(nbCol*(sizeof(int)));
    for (int i = 0; i < nbCol; ++i) {
        tachesCol[i]= malloc(nbTaches*sizeof(tache));
    }
    for (int i = 0; i < nbCol; ++i){
        repartCol[i]=0;
    }
    for (int i = 0; i < nbTaches; ++i) {//on met chaque tâche dans la liste qui correspond à sa couleur&
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
    int nbTachesEnreg=0;
    int colorSelec=0;//faudra le faire commencer en fonction de l'instruction l'instruction, penser éventuellement à trier les couleurs
    poste* postes= malloc(sizeof(poste*));
    postes= ajouterPoste(postes,repartCol[colorSelec]);
    poste* base=postes;
    while (nbTachesEnreg<nbTaches){
        for (int i = 0; i < repartCol[colorSelec]; ++i) {
            if(tachesCol[colorSelec][i].temps==0){
                nbTachesEnreg++;
                tachesCol[colorSelec][i].temps=-1;
            }
            else if(tachesCol[colorSelec][i].temps<(T0-postes->tpsTot) && tachesCol[colorSelec][i].temps>0){
                if(/*precedence*/1){
                    postes->taches[postes->nbTache]=tachesCol[colorSelec][i].id;
                    postes->nbTache++;
                    tachesCol[colorSelec][i].temps=-1;
                }
            }
        }
        colorSelec=(colorSelec+1)%nbCol;/*on passe à la couleur suivante (le % signifie modulo)
        Le plus pertinent ici serait tout de même de trouver un moyen de choisir à chaque fois quelle couleur il vaut mieux utiliser*/
        postes= ajouterPoste(postes,repartCol[colorSelec]);
    }
    for (int i = 0; i < nbCol; ++i) {
        free(tachesCol[i]);
    }
    free(tachesCol);
    free(repartCol);
    return base;
}





#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_CONTRAINTETEMPS_H
