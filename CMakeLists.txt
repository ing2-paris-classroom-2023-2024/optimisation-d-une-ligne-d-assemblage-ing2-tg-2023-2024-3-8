cmake_minimum_required(VERSION 3.24)
project(optimisation_d_une_ligne_d_assemblage_ing2_tg_2023_2024_3_8 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(optimisation_d_une_ligne_d_assemblage_ing2_tg_2023_2024_3_8 Exclusion_et_Exclusion_tempsDeCycles.c Exclusion_et_Exclusion_TempsDeCycles.h ContraintePrecedences.h ContrainteTemps.h Les3.c structures.h william.h toolbox.h TimeOperation.c main.c Les3.h FileReader.h Precedences_Temps_De_Cycles.c Precedences_Temps_De_cycles.h toolbox_tps_de_cycle.h wRSPT.c wRST.c)
