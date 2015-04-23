#include "netlist.h"

// 0 si aucune intersection, 1 si intersection. 0 si segments inexistant(s) ou Netlist inexistante.
int intersection(Netlist *N, Segment *s1, Segment *s2) ;

void Sauvegarde_intersection(Segment* *segp, int NbSeg, char* name);

void Creer_intersection( Segment * s1 , Segment * s2 ) ;

void intersec_naif( Segment * * Tableau_Segments , int nombre_segments , Netlist * Net ) ;

void Echanger( Extremite * * Tableau , int premier , int second ) ;

int Partionner_Tableau_Extremite( Extremite * * Tableau , int premier , int dernier , int pivot ) ;

void Tri_Rapide_Echeancier( Extremite * * Tableau , int premier , int dernier ) ;

void Tri_Tableau_Echeancier( Extremite * * Tableau , int nombre_extremite ) ;

void Intersection_Balayage_Liste_Chainee( Netlist * Net , int nombre_segments , Segment * * Tableau_Segments) ;

void Coordonnees_Max_Min_Reseau( double * xmax , double * ymax , double * xmin , double * ymin , Reseau * Res ) ;

void Coordonnees_Max_Min_Netlist( double * xmax , double * ymax , double * xmin , double * ymin , Netlist * Net ) ;
