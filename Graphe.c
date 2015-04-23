#include "Graphe.h"

Sommet_Graphe Creer_Sommet( int nombre_sommets ){
    if ( nombre_sommets < 1 ) return NULL;

    int i;
    Sommet_Graphe * nouv;

    nouv->arretes = ( int * ) malloc ( sizeof( int ) * nombre_sommets );
    for( i = 0 ; i < nombre_sommets ; i++ ) nouv->arretes[i] = 0;
    nouv->pt = NULL;
    nouv->seg = NULL;
    nouv->type;
}
