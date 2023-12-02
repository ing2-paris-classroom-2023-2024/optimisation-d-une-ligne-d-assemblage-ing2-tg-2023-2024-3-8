cmake_minimum_required(VERSION 3.23.2)
project(optimisation_d_une_ligne_d_assemblage_ing2_tg_2023_2024_3_8 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(optimisation_d_une_ligne_d_assemblage_ing2_tg_2023_2024_3_8
        main.c
        ToolBoxWilliam.h
        ContraintePrecedences.c
)
