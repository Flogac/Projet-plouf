#include "Traitement_Netlist.h"

int intersection(Netlist *N, Segment *s1, Segment *s2){
    if( !N || !s1 || !s2 ) return 0;

    /*
    N->T_Res[s1->NumRes]->T_Pt[s1->p1]->x s1 p1 x
    N->T_Res[s1->NumRes]->T_Pt[s1->p1]->y s1 p1 y
    N->T_Res[s1->NumRes]->T_Pt[s1->p2]->x s1 p2 x
    N->T_Res[s1->NumRes]->T_Pt[s1->p2]->y s1 p2 y
    N->T_Res[s1->NumRes]->T_Pt[s2->p1]->x s2 p1 x
    N->T_Res[s1->NumRes]->T_Pt[s2->p1]->y s2 p1 y
    N->T_Res[s1->NumRes]->T_Pt[s2->p2]->x s2 p2 x
    N->T_Res[s1->NumRes]->T_Pt[s2->p2]->y s2 p2 y
    */

    if( s1->HouV == s2->HouV && s1->HouV == 0 && N->T_Res[s1->NumRes]->T_Pt[s1->p1]->y != N->T_Res[s1->NumRes]->T_Pt[s2->p2]->y );
    if( s1->HouV == s2->HouV && s1->HouV == 1 && N->T_Res[s1->NumRes]->T_Pt[s1->p1]->x != N->T_Res[s1->NumRes]->T_Pt[s2->p2]->x );
    if( N->T_Res[s1->NumRes]->T_Pt[s1->p2]->x > N->T_Res[s1->NumRes]->T_Pt[s2->p1]->x ) return 0;
    if( N->T_Res[s1->NumRes]->T_Pt[s2->p2]->x > N->T_Res[s1->NumRes]->T_Pt[s1->p1]->x ) return 0;
    if( N->T_Res[s1->NumRes]->T_Pt[s1->p2]->y > N->T_Res[s1->NumRes]->T_Pt[s2->p1]->y ) return 0;
    if( N->T_Res[s1->NumRes]->T_Pt[s2->p2]->y > N->T_Res[s1->NumRes]->T_Pt[s1->p1]->y ) return 0;

    return 1;
}


