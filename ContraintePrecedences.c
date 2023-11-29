#include <stdlib.h>
#include <stdio.h>

int** MatriceAdjacence(int nb_operations){
    int** matrice=(int**) malloc(nb_operations*sizeof (int*));
    for (int i = 0; i < nb_operations; i++) {
        matrice[i]=(int*) calloc(nb_operations, sizeof (int));
    }
    return matrice;
}

void libereMatrice(int** matrice, int nb_op){
    for (int i = 0; i < nb_op; i++) {
        free(matrice[i]);
    }
    free(matrice);
}

void remplirMatrice(const char* nomfichier,int** matrice){
    FILE* fichier= fopen(nomfichier,"r");
    if(fichier == NULL){
        printf("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    int source, final;

    while (fscanf(fichier, "%d %d", &source, &final)==2){
        matrice[source-1][final-1]=1;
    }
    fclose(fichier);
}

int main(){
    const char* nomfichier ="precedences.txt";
    FILE* fichier= fopen(nomfichier,"r");
    if(fichier == NULL){
        printf("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int nb_operations =0;
    int source, final;

    while (fscanf(fichier,"%d %d", &source, &final)==2){
        if(source > nb_operations){
            nb_operations=source;
        }
        if(final > nb_operations){
            nb_operations=final;
        }
    }
    fclose(fichier);

    int** matriceAdjacence= MatriceAdjacence(nb_operations);

    remplirMatrice(nomfichier,matriceAdjacence);

    for (int i = 0; i < nb_operations; i++) {
        for (int j = 0; j < nb_operations; j++) {
            printf("%d ", matriceAdjacence[i][j]);
        }
        printf("\n");
    }
    libereMatrice(matriceAdjacence,nb_operations);
    return 0;
}
