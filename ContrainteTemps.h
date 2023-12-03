//
// Created by clementt on 23/11/23.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_CONTRAINTETEMPS_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_CONTRAINTETEMPS_H


poste* ajouterPoste(poste* poste1,int taille){
    poste* poste2= malloc(sizeof(poste*));
    poste1->suivant=poste2;
    poste2->taches= malloc(taille*sizeof(tache));
    poste2->nbTache=0;
    poste2->tpsTot=0;
    poste2->suivant=NULL;
    return poste2;
}



poste* exclusion(tache* taches,int nbTaches,int T0,int** MatricePrec,int idMaxPrec){
    int nbCol=0;

    int idmax=0;
    for (int i = 0; i < nbTaches; ++i) {
        if(taches[i].id>idmax) idmax=taches[i].id;
    }

    int couleurs[idmax];
    listeCol(&nbCol, couleurs);
    tache** tachesCol=malloc(nbCol*(sizeof(tache**)));
    int* repartCol= malloc(nbCol*(sizeof(int*)));//allocation de la liste pour chaque couleur
    for (int i = 0; i < nbCol; ++i) {
        tachesCol[i]= malloc(nbTaches*sizeof(tache));
    }
    for (int i = 0; i < nbCol; ++i){//initialisation de repartCol
        repartCol[i]=0;
    }

    for (int i = 0; i < nbTaches; ++i) {//on met chaque tâche dans la liste qui correspond à sa couleur&
        taches[i].col=couleurs[taches[i].id];

        tachesCol[taches[i].col][repartCol[taches[i].col]]=taches[i];
        repartCol[taches[i].col]++;
    }
    tache temp;
    for (int i = 0; i < nbCol; ++i) {//Tri pour avoir, dans chaque couleur, les tâches triées par ordre de temps
        for (int j = 0; j < repartCol[i]-1; ++j) {
            for (int k = 0; k < repartCol[i]-j-1; ++k) {
                if(tachesCol[i][k].temps<tachesCol[i][k+1].temps){
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
    int indicapost=0;//compte les postes passés (utile pour le débuggage)

    /*for (int i = 0; i < idMaxPrec; ++i) {
        for (int j = 0; j < idMaxPrec; ++j) {
            if (MatricePrec[i][j] == -1) printf("- ");
            else printf("A%d",MatricePrec[i][j]);
        }
        printf("\n");
    }*/
    while (nbTachesEnreg<nbTaches){
        postes->col=colorSelec;
        for (int i = 0; i < repartCol[colorSelec]; ++i) {
            if(tachesCol[colorSelec][i].temps==0){
                nbTachesEnreg++;
                tachesCol[colorSelec][i].temps=-1;
            }
            else if((tachesCol[colorSelec][i].temps<=(T0-postes->tpsTot) || IgnorerTemps) && tachesCol[colorSelec][i].temps>0){
                //printf("%d\n",tachesCol[colorSelec][i].id);
                if(IgnorerPrecedence ||precedence(base,tachesCol[colorSelec][i].id,idMaxPrec,MatricePrec)){
                    printf("Tache: %d | Couleur : %d | Temps: %f\n", tachesCol[colorSelec][i].id,tachesCol[colorSelec][i].col, tachesCol[colorSelec][i].temps);
                    //printf("acceptee dans le poste %d\n", indicapost);
                    postes->taches[postes->nbTache]=tachesCol[colorSelec][i].id;
                    nbTachesEnreg++;
                    postes->nbTache++;
                    postes->tpsTot+=tachesCol[colorSelec][i].temps;
                    tachesCol[colorSelec][i].temps=-1;
                    i=-1;//on réinitialise au cas où une contrainte de précédence est libérée
                }
            }
            else if(tachesCol[colorSelec][i].temps>T0 && !(IgnorerTemps)){
                printf("ERREUR: UNE TACHE EST PLUS LONGUE QUE LE TEMPS DE CYCLE: ELLE NE SERA PAS COMPTABILISEE\n");
                nbTachesEnreg++;
                tachesCol[colorSelec][i].temps=-1;
            }
        }
        /*colorSelec=(colorSelec+1)%nbCol;on passe à la couleur suivante (le % signifie modulo)
        Le plus pertinent ici serait tout de même de trouver un moyen de choisir à chaque fois quelle couleur il vaut mieux utiliser*/
        colorSelec= determinerCouleur(base,idMaxPrec,MatricePrec,tachesCol,repartCol,nbCol);
        //printf("passage a la couleur %d\n",colorSelec);

        if(!(postes->tpsTot==0)){
            printf("Temps total du poste: %f/%d (couleur:%d)\n",postes->tpsTot,T0,postes->col);
            indicapost++;
        }
        if(nbTachesEnreg<nbTaches ){
            if(postes->tpsTot==0){
                postes->col=colorSelec;
            }
            else {
                postes = ajouterPoste(postes, repartCol[colorSelec]);
                printf("\nfin de boucle: passage au poste %d\n", indicapost);
            }
        }
        //postes= ajouterPoste(postes,repartCol[colorSelec]);
    }
    for (int i = 0; i < nbCol; ++i) {
        free(tachesCol[i]);
    }
    free(tachesCol);
    free(repartCol);
    for (int i = 0; i < idMaxPrec; ++i) {
        free(MatricePrec[i]);
    }
    free(MatricePrec);
    return base;
}





#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_CONTRAINTETEMPS_H