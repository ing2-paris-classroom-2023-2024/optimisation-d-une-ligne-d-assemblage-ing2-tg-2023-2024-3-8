//
// Created by super on 26/11/2023.
//

#include "stdio.h"
#include "stdlib.h"

#include "Exclusionalexandre.h"

/* Lire le temps de cycle */
//float lireTemps_cycle();


/************************************************************************************/
// Algorithme qui lit le fichier de contrainte d'exclusions et crée un graphe associé
/************************************************************************************/
// retourne la matrice d'adjacence - convention indice 0 non utilisé
// retourne l'ordre du graphe dans ordremat (nombre de sommets + 1, car il y a le 0 "mort")

int** ContrainteExclusion(char* nomFichier,int* ordremat){
    FILE* fp= fopen(nomFichier,"r");
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
#ifdef DEBUG
    printf("[DEBUG]:ordre: %d\n",ordre);
#endif

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
        matrice[nb2][nb1]=1;
        //printf("op1 op2 : %d %d \n",nb1,nb2);
    }

    int j,k;
    matrice[0][0]= *ordremat;

    ///debug matrice
#ifdef DEBUG
    printf("[DEBUG]:\n");
    for(j=0;j<ordre+1;j++){
        for(k=0;k<ordre+1;k++){
            printf("%d ",matrice[j][k]);
        }
        printf("\n");
    }
#endif

    fclose(fp);

    return matrice;
}


////   COLORATION DU GRAPHE POUR TROUVER LE NOMBRE DE STATIONS DE TRAVAIL

// Fonction pour trouver la prochaine couleur disponible pour un sommet
int prochaineCouleurDisponible(int sommet, int nombre_sommets,int* couleurs,int** exclusion_adj) {
    int couleur_disponible = 0;

    // Parcourir les sommets adjacents et vérifier leurs couleurs
    for (int i = 0; i < nombre_sommets; ++i) {
        if (exclusion_adj[sommet][i] && couleurs[i] != -1) {
            if (couleurs[i] == couleur_disponible) {
                // Cette couleur est déjà utilisée par un voisin, essayer la suivante
                couleur_disponible++;
                i = -1;  // Redémarrer la boucle pour revérifier avec la nouvelle couleur
            }
        }
    }

    return couleur_disponible;
}

// Algorithme de tri à bulle
void triBulle(int degres[], int sommets_ord[], int nombre_sommets) {
    for (int i = 0; i < nombre_sommets - 1; ++i) {
        for (int j = 0; j < nombre_sommets - i - 1; ++j) {
            if (degres[sommets_ord[j]] < degres[sommets_ord[j + 1]]) {
                // Échanger les positions
                int temp = sommets_ord[j];
                sommets_ord[j] = sommets_ord[j + 1];
                sommets_ord[j + 1] = temp;
            }
        }
    }
}

/*******************************************************************************/
// Algorithme de coloration de Welsh-Powell
// Retourne la liste couleurs qui donne une couleur pour chaque sommet de 1 à N
// l'indice 0 ne sert à rien
//******************************************************************************
void welshPowell(int** exclusion_adj, int nombre_sommets,int* couleurs,int ordre) {
    int degres[ordre];
    int sommets_ord[ordre];

    // Calculer les degrés des sommets
    for (int i = 0; i < nombre_sommets; ++i) {
        degres[i] = 0;
        couleurs[i] = -1;

        for (int j = 0; j < nombre_sommets; ++j) {
            degres[i] += exclusion_adj[i][j];
        }

        sommets_ord[i] = i;  // Initialiser la liste des sommets
    }

    // Trier les sommets par degré décroissant (tri à bulle)
    triBulle(degres, sommets_ord, nombre_sommets);

    // Attribution des couleurs
    for (int i = 0; i < nombre_sommets; ++i) {
        int sommet = sommets_ord[i];
        if (couleurs[sommet] == -1) {
            couleurs[sommet] = 0;  // Utiliser la couleur 0 pour le premier sommet non coloré

            // Colorer les sommets non adjacents
            for (int j = 0; j < nombre_sommets; ++j) {
                if (!exclusion_adj[sommet][j] && couleurs[j] == -1) {
                    couleurs[j] = prochaineCouleurDisponible(j, nombre_sommets,couleurs,exclusion_adj);
                }
            }
        }
    }

}

///DETERMINATION DES STATIONS & AFFICHAGE


/******************************************************************************************************/
// Fonction qui retourne le tableau des couleurs pour chaque indice de tâches existante ou non   // 0 n'existe pas systématiquement
// prend en entree la liste des tâches, et les colorie en sorite
// prend en entree un pointeur sur le nombreDeWS et le complète en sortie
// prend en entree un pointeur sur une matrice d'exclusion et la complète en sorite
// rend également le nombreDeWS

int* traiteExclusion(sTache* tListeTache, int*  nombreDeWS, int** exclusion_adj) {
    int ordremat;
    char nom_fichier[] = "exclusions.txt";
    int* couleur;

    // Lit les contraintes d'exclusion et stocke dans la matrice d'adjacence
    exclusion_adj = ContrainteExclusion(nom_fichier,&ordremat);

    couleur = (int*) malloc(ordremat*sizeof(int));
    welshPowell(exclusion_adj,ordremat,couleur,ordremat);

    ////Recherche du nombre de couleurs et donc du nombre de stations
    int i,j,k,l;
    j =couleur[0];
    for(i=0;i<ordremat;i++){
        if(j<couleur[i]){
            j=couleur[i];
        }
    }
    j++;
    *nombreDeWS = j;

    /// Met à jour la liste des tâches avec la bonne couleur
    for(int i=1; i< tListeTache[0].id +1; i++){
        tListeTache[i].col = couleur[tListeTache[i].id];
        // debug
#ifdef DEBUG
        printf("[DEBUG]:tache[id=%d, col=%d, temps=%f] \n", tListeTache[i].id, tListeTache[i].col, tListeTache[i].temps );
#endif

    }
    return couleur;
}


void affichageExclusion() {
    int ordremat;
    int** exclusion_adj;
    char nom_fichier[] = "exclusions.txt";
    int  nombreDeWS;

    sTache *tListeTache;
    tListeTache = wReadFileTimeOperation();

    //    lit les tâches pour savoir celles qui existent
    //    printf("Lecture des temps d'operation ok; Nombre d'operations a realiser : %d\n",tListeTache[0].id);
    //    printf("Saisissez le nom du fichier : \n");
    //    scanf("%s",nom_fichier);

    // Lit les contraintes d'exclusion et stocke dans la matrice d'adjacence
    exclusion_adj = ContrainteExclusion(nom_fichier,&ordremat);

    int couleur[ordremat];
    welshPowell(exclusion_adj,ordremat,couleur,ordremat);

    ////Recherche du nombre de couleurs et donc du nombre de stations
    int i,j,k,l;
    j=couleur[0];
    for(i=0;i<ordremat;i++){
        if(j<couleur[i]){
            j=couleur[i];
        }
    }
    j++;
    nombreDeWS = j;

    /// Met à jour la liste des tâches avec la bonne couleur
    for(int i=1; i< tListeTache[0].id +1; i++){
        tListeTache[i].col = couleur[tListeTache[i].id];
        // debug
#ifdef DEBUG
        printf("[DEBUG]:tache[id=%d, col=%d, temps=%f] \n", tListeTache[i].id, tListeTache[i].col, tListeTache[i].temps );
#endif
    }

    /*printf("%d",j);
    ///Affichage liste de couleur
    for(i=0;i<ordremat;i++){
        printf("Couleur de %d : %d ",i,couleur[i]);
    }*/

    ///Creation de la solution
    t_ligne LigneAssemblage;
    LigneAssemblage.nombreDeStations = nombreDeWS;
    LigneAssemblage.WS= (t_station*) malloc(nombreDeWS*sizeof(t_station));
    for(i=0;i<j;i++){
        LigneAssemblage.WS[i].num=i;
        LigneAssemblage.WS[i].duree=0;
        LigneAssemblage.WS[i].nbTaches=0;
        for(k=1;k<ordremat;k++){
            if(couleur[k]==i){
                LigneAssemblage.WS[i].nbTaches++;
            }
        }
        LigneAssemblage.WS[i].taches= (int*)malloc((LigneAssemblage.WS[i].nbTaches)*sizeof(int));
        l=0;
        for(k=1;k<ordremat;k++){
            if(couleur[k]==i){
                LigneAssemblage.WS[i].taches[l]=k;
                l++;
            }
        }
    }
    ///////////////////AFFICHAGE DE LA SOLUTION
    printf("Le nombre de stations est : %d - nota: pas de prise en compte du temps d'execution.. il peut y avoir des taches qui n'existeront pas\n",nombreDeWS);
    for(i=0;i<nombreDeWS; i++){
        printf("Station [%d] : ",i);
        for(k=0;k<LigneAssemblage.WS[i].nbTaches;k++){
            printf("%d ",LigneAssemblage.WS[i].taches[k]);
        }
        printf("\n");
    }
}


void affichageExclusionBis() {
    int ordremat;
    int** exclusion_adj;
    char nom_fichier[] = "exclusions.txt";
    int* couleur;
    int  nombreDeWS;
    int l,k;


    sTache *tListeTache;
    tListeTache = wReadFileTimeOperation();
    couleur = traiteExclusion(tListeTache, &nombreDeWS, exclusion_adj);

    //    lit les tâches pour savoir celles qui existent
#ifdef DEBUG
    printf("[DEBUG]:Lecture des temps d'operation ok; Nombre d'operations a realiser : %d\n",tListeTache[0].id);
#endif

    /// Met à jour la liste des tâches avec la bonne couleur
    for(int i=1; i< tListeTache[0].id +1; i++){
        tListeTache[i].col = couleur[tListeTache[i].id];
        // debug
#ifdef DEBUG
        printf("[DEBUG]:tache[id=%d, col=%d, temps=%f] \n", tListeTache[i].id, tListeTache[i].col, tListeTache[i].temps );
#endif
    }
}

float lireTemps_cycle(){
    FILE *fichier = fopen("temps_cycle.txt", "r");
    float Tc;

    // Vérifier si le fichier a pu être ouvert
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    if (fscanf(fichier, "%f", &Tc) == 1){
        fclose(fichier);
        return Tc;
    } else
        exit(EXIT_FAILURE);
}


/***********************************************************************/
/*                                           */

int exclusionEtTempsCycle(){
    int ordremat;
    int** exclusion_adj;
    int* couleur;
    int  nombreDeWS;
    int i,j,l,k;
    int Tc = lireTemps_cycle();
    sPoste** listePostesExcl;

    // debug
#ifdef DEBUG
    printf("[DEBUG]:Tc = %f \n", Tc);
#endif

    sTache *tListeTache;
    tListeTache = wReadFileTimeOperation();
    couleur = traiteExclusion(tListeTache, &nombreDeWS, exclusion_adj);

    //    lit les tâches pour savoir celles qui existent
#ifdef DEBUG
    printf("[DEBUG]:Lecture des temps d'operation ok; Nombre d'operations a realiser : %d\n",tListeTache[0].id);
#endif

    /// Met à jour la liste des tâches avec la bonne couleur
    for(int i=1; i< tListeTache[0].id +1; i++){
        tListeTache[i].col = couleur[tListeTache[i].id];
        // debug
#ifdef DEBUG
        printf("[DEBUG]:tache[id=%d, col=%d, temps=%.2f] \n", tListeTache[i].id, tListeTache[i].col, tListeTache[i].temps );
#endif
    }

    // Crée une liste de stations de travail tenant compte de l'exclusion
    listePostesExcl = (sPoste**) malloc(nombreDeWS*sizeof(sPoste*));
    
    int nbSsStat;
    int nbStationInFine = 0;
    // Traite chacune des workstations en contrainte de temps
    for(i=0; i<nombreDeWS; i++){
        listePostesExcl[i] = wRepartitionStationTempsCol(tListeTache, i, Tc, &nbSsStat);
        nbStationInFine += nbSsStat;
    }
    // Traite chacune des workstations en contrainte de temps
    //printf("NbSSsation : %d\n",nbStationInFine);

    return nbStationInFine;
}


/***********************************************************/
int main(){

    printf("---------- Contraintes d'exclusion uniquement -----------------------\n");
    affichageExclusion();

    printf("\n\n---------- Contraintes d'exclusion et temps de cycle max ------------\n");
    int nbInFine = exclusionEtTempsCycle();
    printf("\nNombre de stations final : %d",nbInFine);

}
