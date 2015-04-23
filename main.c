#include "Fonctions_Programme.h"
//#include "function.c"

int main(){

Netlist * Net;

Net = Recuperer_Netlist( "c1.net");

VisuNetList( Net ,"c1");

return 0;
}
