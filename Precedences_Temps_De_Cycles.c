
#include "toolbox_tps_de_cycle.h"
#include "FileReader.h"


int prec_tps_cycles(){
    sTache *tListeTache;
    sParametre *sParametreListe=(sParametre*)malloc(sizeof(sParametre));
    float vTempsDeCycle=0;
    float *pTempsDeCycle=&vTempsDeCycle;
    tListeTache= ReadFileTimeOperations(pTempsDeCycle,sParametreListe);
    RepartitionStationTemps(tListeTache,vTempsDeCycle,sParametreListe);
    TriTopologiques(tListeTache,sParametreListe,vTempsDeCycle);
    return 0;
}