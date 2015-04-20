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


<<<<<<< HEAD
void Sauvegarde_intersection(Netlist* n, char* name){







}
=======
>>>>>>> 1752372dd851e027ccba6417d894c497fc83c4d6

void Creer_intersection( Segment * s1 , Segment * s2 ){
    if( !s1 || !s2 ) return;

    Cell_Segment * temp;
    Cell_Segment * temp_ajout;

    temp_ajout = s1->Lintersec;
    if( temp_ajout ) while( temp_ajout->suiv ) temp_ajout = temp_ajout->suiv;
    temp = Creer_Cell_Segment();
    if( !temp_ajout ){
        temp->seg = s2;
        s2->Lintersec = temp;
    } else {
       temp_ajout->suiv = temp;
    }

    temp_ajout = s2->Lintersec;
    if( temp_ajout ) while( temp_ajout->suiv ) temp_ajout = temp_ajout->suiv;
    temp = Creer_Cell_Segment();
    if( !temp_ajout ){
        temp->seg = s1;
        s2->Lintersec = temp;
    } else {
       temp_ajout->suiv = temp;
    }

}

void intersec_naif( Segment * * Tableau_Segments , int nombre_segments , Netlist * Net ){
    if( !Tableau_Segments || nombre_segments < 1 ) return;

    int i, j;

    for( i = 0 ; i < nombre_segments ; i++ ) for( j = i ; j < nombre_segments ; j++ ) if( intersection( Net , Tableau_Segments[i] , Tableau_Segments[j] ) == 1 ) Creer_intersection( Tableau_Segments[i] , Tableau_Segments[j] );
}
