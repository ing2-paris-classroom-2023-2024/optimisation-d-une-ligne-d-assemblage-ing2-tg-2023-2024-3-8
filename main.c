//
// Created by William on 12/11/2023.
//

#include "ToolBoxWilliam.h"



int main(){
    sTache *tListeTache;
    sParametre *sParametreListe=(sParametre*)malloc(sizeof(sParametre));
    float vTempsDeCycle=0;
    float *pTempsDeCycle=&vTempsDeCycle;
    tListeTache=wReadFileTimeOperation(pTempsDeCycle,sParametreListe);
    //wRepartitionStationTemps(tListeTache,vTempsDeCycle,sParametreListe);
    wTriTopologique(tListeTache,sParametreListe,vTempsDeCycle);
    return 0;
}



