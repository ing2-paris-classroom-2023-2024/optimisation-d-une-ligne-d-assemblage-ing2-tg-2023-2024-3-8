//
// Created by clementt on 02/12/23.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_CONTRAINTEPRECEDENCE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_CONTRAINTEPRECEDENCE_H

int** creerPrec(int* idMaxPrec){
    FILE *precedences = fopen("precedences.txt", "r");

    if (precedences == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        return NULL;
    }
    
    int nombre1,nombre2,idMax=0;
    while (fscanf(precedences, "%d %d", &nombre1, &nombre2) == 2){
        if(idMax<nombre2) { idMax =nombre2 ; }
    }
    idMax++;
    *idMaxPrec = idMax;
    rewind(precedences);
    
    int** matPrec= malloc(idMax*sizeof(int*));
    for (int i = 0; i < idMax; ++i) {
        matPrec[i]= malloc(idMax*sizeof(int));
        for (int j = 0; j < idMax; ++j) {
            matPrec[i][j]=-1;
        }
    }

    while (fscanf(precedences, "%d %d", &nombre1, &nombre2) == 2){
        matPrec[nombre2][nombre1]=1;
    }
    /*for (int i = 0; i < idMax; ++i) {
        for (int j = 0; j < idMax; ++j) {
            if(matPrec[i][j]==-1) printf("-");
            else printf("0");
        }
        printf("\n");
    }*/
    return matPrec;
}

int rechercheTache(poste* posteR,int cible){
    //printf("exploration poste\n");
    for (int i = 0; i < posteR->nbTache; ++i) {
        //printf("%d ",posteR->taches[i]);
        if(posteR->taches[i]==cible) return (1);
    }
    if(posteR->suivant!=NULL) return (rechercheTache(posteR->suivant,cible));
    else return 0;
}

int precedence(poste* base,int sommet,int idMax,int** matricePrec){
    for (int i = 0; i < idMax; ++i) {
        if(matricePrec[sommet][i]!=(-1)){
            //printf("Sommet %d: verification de la precedence %d\n",sommet,i);
            if(rechercheTache(base,i)==0) return 0;
            //printf("validee\n");
        }
    }
    return 1;
}
































#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_CONTRAINTEPRECEDENCE_H
