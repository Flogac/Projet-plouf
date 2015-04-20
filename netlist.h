#include <stdio.h>
#include <stdlib.h>
#include "entree_sortie.h"

struct segment ;

typedef struct Cell_Segment {
struct segment * seg ;
struct Cell_Segment * suiv ;
} Cell_Segment ;

typedef struct Cell_Segment_num {
    int i;
    struct Cell_Segment_num *suiv;
}Cell_Segment_Num;

typedef struct segment {
int NumRes ; /* Numero du reseau auquel appartient ce segment*/
int p1 , p2 ; /* Numero des points aux extremites du segment */
/* En utilisant la numerotation de T_Pt */
/* p1 est le point en bas a gauche par rapport a p2*/
int HouV ; /* 0 si Horizontal et 1 si Vertical */
struct Cell_Segment * Lintersec ; /* Liste des segments en intersection */
} Segment ;

typedef struct point {
double x , y ; /* Coordonnees du point */
int num_res ; /* Numero du reseau contenant ce point = Index du tableau T_res*/
Cell_Segment_Num * Lincid ; /* Liste des segments incidents a ce point */
} Point ;

typedef struct reseau {
int NumRes ; /* Numero du reseau = Indice dans le tableau T_Res */
int NbPt ; /* Nombre de points de ce reseau */
Point * * T_Pt ; /* Tableau de pointeurs sur chaque point de ce reseau */
int NbSeg ; // Nombre de segments de ce réseau.
Segment * * T_Seg ; // Tableau de poiteurs sur chaque segment de ce reseau.
} Reseau ;

typedef struct netlist {
int NbRes ; /* Nombre de reseaux */
Reseau * * T_Res ; /* Tableau pointant sur chaque reseau */
} Netlist ;

typedef struct extremite {
double x; /* Ordonnee du point */
int VouGouD ; /* 0 si segment V / 1 si pt gauche d'un segment H / 2 si pt droit d'un
segment H */
Segment * PtrSeg ; /* Pointeur sur le segment correspondant a l'extremite */
int NumPt ; /* si segment H: numero du point correspondant */
} Extremite ;

/* Fonctions de creations des differentes structures */
Cell_Segment * Creer_Cell_Segment() ;
Cell_Segment_Num * Creer_Cell_Segment_num() ;
Segment * Creer_Segment() ;
Point *  Creer_Point() ;
Reseau * Creer_Reseau() ;
Netlist * Creer_Netlist() ;
Extremite * Creer_Extremite() ;
Segment * * Allocation_Tableau_Segments( int nombre_segments ) ;
Point * * Allocation_Tableau_Points( int nombre_points ) ;
Reseau * * Allocation_Tableau_Reseaux( int nombre_reseaux ) ;
Extremite * * Allocation_Tableau_Extremite( int nombre_extremite ) ;


/* Fonctions de liberations des differentes structures */
void Liberation_Cell_Segment_Num( Cell_Segment_Num * libre ) ;
void Liberation_Cell_Segment( Cell_Segment * libre ) ;
void Liberation_Segment( Segment * libre ) ;
void Liberation_Point( Point * libre ) ;
void Liberation_Reseau( Reseau * libre ) ;
void Libetation_Netlist( Netlist * libre ) ;
void Liberation_Extremite( Extremite * libre ) ;

Segment * * Creer_Tableau_Segments_Netlist( Netlist * Net , int nombre_segments ) ;

Extremite * * Creer_Echeancier( Netlist * Net , int nombre_segments , Segment * * Tableau_Segments ) ;

/* Fonctions d'affichage de la structure netlist sous forme de .net */
void print_netlist(Netlist* n, char* name);

void VisuNetList(Netlist* n, char* name);
