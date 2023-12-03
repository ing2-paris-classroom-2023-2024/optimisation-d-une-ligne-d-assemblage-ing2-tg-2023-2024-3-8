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
    //wTriTopologique(tListeTache,tListeTache[0].id);
    wRepartitionStationTemps(tListeTache,vTempsDeCycle,sParametreListe);
    return 0;
}



