#include "avl.h"

typedef struct sommet_graphe{
    int type; // 1 Si segment, 2 si point.
    Point * pt;
    Segment * seg;
    int * arretes; // tableau de int. 1 si arrête, initialisé à 0.
} Sommet_Graphe ;
