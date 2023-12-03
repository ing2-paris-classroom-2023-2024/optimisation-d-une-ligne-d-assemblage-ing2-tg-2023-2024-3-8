
#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_EXCLUSIONPRECEDENCES_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_EXCLUSIONPRECEDENCES_H

#include "Exclusionalexandre.h"
#include "Contrainteprecedences.h"

int** MatriceAdjacenceExPrece(int** matrice1, int** matrice2);

void ColorationExPrece(int** matrice1,int** matrice2,int** couleurs);

int NombreStations(int** couleurs);

void AffichageExclusionPrecedences(int** couleurs);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_EXCLUSIONPRECEDENCES_H
