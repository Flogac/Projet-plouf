#include "netlist.h"
// 0 si aucune intersection, 1 si intersection. 0 si segments inexistant(s) ou Netlist inexistante.
int intersection(Netlist *N, Segment *s1, Segment *s2) ;

void Sauvegarde_intersection(Netlist* n);

void Creer_intersection( Segment * s1 , Segment * s2 ) ;

void intersec_naif( Segment * * Tableau_Segments , int nombre_segments , Netlist * Net ) ;
