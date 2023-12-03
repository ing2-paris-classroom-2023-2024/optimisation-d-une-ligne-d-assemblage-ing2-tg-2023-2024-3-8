#include "ToolBoxWilliam.h"


int getId(int index,sTache *prListeTache) {
    return prListeTache[index].id;
}

// Renvoie l'index d'une tâche à partir de son ID
int getIndex(int id,sTache * prListeTaches,int prNombreTaches) {
    for(int i=0; i < prNombreTaches; i++) {
        if(prListeTaches[i].id == id) {
            return i;
        }
    }
    return -1; // id non trouvé
}
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Fonction de comparaison pour qsort
int comparerDegres(const void* t1, const void* t2) {
    sTache* temp1 = (sTache*) t1;
    sTache* temp2 = (sTache*) t2;

    // Comparer d'abord les degrés d'entrée
    if (temp1->degreeEntree != temp2->degreeEntree) {
        return (temp1->degreeEntree - temp2->degreeEntree);
    }
    // En cas d'égalité, comparer le nombre de successeurs
    return (temp2->nbSuccesseurs - temp1->nbSuccesseurs);
}
int wCalculerDegreeEntree(sTache *prTache, sTache *prlisteTache, int nbTaches) {
    int degre = 0;
    prTache->marque = 1; // Marquer la tâche comme visitée

    for (int i = 0; i < prTache->nbPredecesseur; i++) {
        int vIdPrec = prTache->tListeTachePrecedente[i];
        int indexPrec = getIndex(vIdPrec, prlisteTache, nbTaches);
        sTache* sPrec = &prlisteTache[indexPrec];

        if (sPrec->marque == 1) {
            printf("Cycle detecte sur tache %d\n", prTache->id);
            exit(EXIT_FAILURE);
        }

        if (sPrec->degreeEntree == -1) {
            int deg_prec = wCalculerDegreeEntree(sPrec, prlisteTache, nbTaches);
            degre = max(degre, deg_prec + 1);
        } else {
            degre = max(degre, sPrec->degreeEntree + 1);
        }
    }

    prTache->marque = 0; // Désactiver la marque
    prTache->degreeEntree = degre;
    return degre;
}

sTache* wTriTopologique(sTache* prListeTache, sParametre *prParametre) {
    // Initialiser les degrés d'entrée et les marques
    for (int i = 0; i < prParametre->cNombreOperations; i++) {
        prListeTache[i].degreeEntree = -1;
        prListeTache[i].marque = 0;
        prListeTache[i].nbSuccesseurs = 0; // Initialisez le compteur de successeurs
    }

    // Calculer les degrés d'entrée et les successeurs pour chaque tâche
    for (int i = 0; i < prParametre->cNombreOperations; i++) {
        if (prListeTache[i].degreeEntree == -1) {
            prListeTache[i].degreeEntree = wCalculerDegreeEntree(&prListeTache[i], prListeTache, prParametre->cNombreOperations);
        }
        for (int j = 0; j < prListeTache[i].nbPredecesseur; j++) {
            int predId = prListeTache[i].tListeTachePrecedente[j];
            int indexPred = getIndex(predId, prListeTache, prParametre->cNombreOperations);
            prListeTache[indexPred].nbSuccesseurs++;
        }
    }

    // Tri Topologique Classique
    qsort(&prListeTache[0], prParametre->cNombreOperations, sizeof(sTache), comparerDegres);

    // Identifier les tâches avec et sans successeurs
    sTache* avecSuccesseurs = malloc(prParametre->cNombreOperations * sizeof(sTache));
    sTache* sansSuccesseurs = malloc(prParametre->cNombreOperations * sizeof(sTache));
    int countAvec = 0, countSans = 0;

    for (int i = 0; i < prParametre->cNombreOperations; i++) {
        if (prListeTache[i].nbSuccesseurs > 0) {
            avecSuccesseurs[countAvec++] = prListeTache[i];
        } else {
            sansSuccesseurs[countSans++] = prListeTache[i];
        }
    }

    // Fusionner les listes dans l'ordre souhaité
    memcpy(prListeTache, avecSuccesseurs, countAvec * sizeof(sTache));
    memcpy(prListeTache + countAvec, sansSuccesseurs, countSans * sizeof(sTache));

    // Libérer la mémoire allouée pour les listes temporaires
    free(avecSuccesseurs);
    free(sansSuccesseurs);

    // Affichage des tâches triées
    printf("Ordre des tâches:\n");
    for (int i = 0; i < prParametre->cNombreOperations; i++) {
        int id = getId(i, prListeTache);
        printf("Tache %d (degre %d)\n", id, prListeTache[i].degreeEntree);
    }

    return prListeTache;
}

