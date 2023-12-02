//
// Created by William on 12/11/2023.
//

#include "ToolBoxWilliam.h"



int main(){
    sTache *tListeTache;
    float vTempsDeCycle=0;
    float *pTempsDeCycle=&vTempsDeCycle;
    tListeTache=wReadFileTimeOperation(pTempsDeCycle);
    wRepartitionStationTemps(tListeTache,vTempsDeCycle);
    return 0;
}



