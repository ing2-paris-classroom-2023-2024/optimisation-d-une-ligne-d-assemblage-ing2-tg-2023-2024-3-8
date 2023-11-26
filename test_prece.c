#include <stdlib.h>
#include <stdio.h>


#define MAX_OP 100

typedef struct {
    int id;
    int*taches;
    int tpsTot;
    int col;
} poste;

typedef struct {
    int id;
    int col;
    int temps;
} tache;

typedef struct {
    int nombre_operation;
    int matrice_adj[MAX_OP][MAX_OP];
} GraphePrecedences;

GraphePrecedences Graphe(int nb_op){
    GraphePrecedences  graphe;
    graphe.nombre_operation = nb_op;
    for (int i = 0; i < nb_op; ++i) {
        for (int j = 0; j < nb_op; ++j) {
            graphe.matrice_adj[i][j]=0;
        }
    }
    return graphe;
}

void ajoutContraintePrece(GraphePrecedences* graphe, int op_prece, int op_suiv){
    graphe->matrice_adj[op_prece-1][op_suiv-1]=1;
}

void  affiche(GraphePrecedences* graphe){
    for (int i = 0; i < graphe->nombre_operation; ++i) {
        for (int j = 0; j < graphe->nombre_operation; ++j) {
            printf("%d", graphe->matrice_adj[i][j]);
        }
        printf("/n");
    }
}

int main(){
    FILE *fichier = fopen("precedences.txt","r");
    if (fichier == NULL){
        fprintf(stderr, "Erreur lors de l'ouverture");
        return 1;
    }
    int nombre_op;
    fscanf(fichier,"%d",&nombre_op);
    GraphePrecedences graphe = Graphe(nombre_op);
    rewind(fichier);

    char ligne[100];
    fgets(ligne,sizeof(ligne), fichier);
    int op_precedente, op_suivante;
    while (fscanf(fichier,"%d %d", &op_precedente, &op_suivante) == 2 ){
        ajoutContraintePrece(&graphe, op_precedente,op_suivante);
    }
    fclose(fichier);
    affiche(&graphe);
    return 0;
}
