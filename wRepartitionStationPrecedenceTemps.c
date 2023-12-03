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
    //https://koor.fr/C/cstdlib/qsort.wp
    sTache* temp1 = (sTache*) t1;
    sTache* temp2 = (sTache*) t2;
    return (temp1->degreeEntree - temp2->degreeEntree);
}

int wCalculerDegreeEntree(sTache *prTache, sTache *prlisteTache, int nbTaches) {
    int degre = 0;
    prTache->marque = 1; // Marquer la tâche comme visitée

    for (int i = 0; i < prTache->nbPredecesseur; i++) {
        int vIdPrec = prTache->tListeTachePrecedente[i];
        int indexPrec = getIndex(vIdPrec,prlisteTache,nbTaches);
        sTache* sPrec = &prlisteTache[indexPrec];

        if (sPrec->marque == 1) {
            // Cycle détecté
            printf("Cycle detecte sur tache %d\n", prTache->id);
            exit(EXIT_FAILURE);
        }

        if (sPrec->degreeEntree == -1) {
            // Récursion si non visitée
            int deg_prec = wCalculerDegreeEntree(sPrec, prlisteTache, nbTaches);
            degre = max(degre, deg_prec + 1);
        } else {
            // Sinon, incrémenter le degré
            degre = max(degre, sPrec->degreeEntree + 1);
        }
    }

    prTache->marque = 0; // Désactiver la marque
    prTache->degreeEntree = degre;
    return degre;
}

sTache* wTriTopologique(sTache* prListeTache, sParametre *prParametre) {
    //https://perso.ens-lyon.fr/frederic.vivien/Enseignement/Algo-2001-2002/Corrige-TD09.pdf
    //https://ressources.unisciel.fr/algoprog/s51gpcours/emodules/gp03mexerc1/res/gp03exerc1-enonce-cpp-xxx.pdf

    for (int i = 0; i < prParametre->cNombreOperations; i++) {
        prListeTache[i].degreeEntree = -1;
        prListeTache[i].marque = 0;
    }
    for (int i = 0; i < prParametre->cNombreOperations; i++) {
        if (prListeTache[i].degreeEntree == -1) {
            prListeTache[i].degreeEntree = wCalculerDegreeEntree(&prListeTache[i], prListeTache, prParametre->cNombreOperations);
        }
    }
    // Tri par degré croissant
    qsort(&prListeTache[0], prParametre->cNombreOperations, sizeof(sTache), comparerDegres);

    // Affichage des tâches triées
    for (int i = 0; i < prParametre->cNombreOperations; i++) {
        int id = getId(i,prListeTache);
        printf("Tache %d (degre %d)\n", id, prListeTache[i].degreeEntree);
    }
    return prListeTache;
}

