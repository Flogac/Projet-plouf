#include<stdio.h>
#include<stdlib.h>

struct segment ;

typedef struct cell_segment {
struct segment * seg ;
struct cell_segment * suiv ;
} Cell_segment ;

typedef strcut cell_segment_num {
    int i;
    struct cell_segment_num *suiv;
}Cell_Segment_Num;

typedef struct segment {
int NumRes ; /* Numero du reseau auquel appartient ce segment*/
int p1 , p2 ; /* Numero des points aux extremites du segment */
/* En utilisant la numerotation de T_Pt */
/* p1 est le point en bas a gauche par rapport a p2*/
int HouV ; /* 0 si Horizontal et 1 si Vertical */
struct cell_segment * Lintersec ; /* Liste des segments en intersection */
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
