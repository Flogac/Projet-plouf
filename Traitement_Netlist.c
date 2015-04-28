#include "Traitement_Netlist.h"

int intersection( Netlist * N , Segment * s1 , Segment * s2 ){
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

    if( s1->HouV == s2->HouV && s1->HouV == 0 && N->T_Res[s1->NumRes]->T_Pt[s1->p1]->y != N->T_Res[s2->NumRes]->T_Pt[s2->p2]->y ) return 0;
    if( s1->HouV == s2->HouV && s1->HouV == 1 && N->T_Res[s1->NumRes]->T_Pt[s1->p1]->x != N->T_Res[s2->NumRes]->T_Pt[s2->p2]->x ) return 0;
    if( N->T_Res[s1->NumRes]->T_Pt[s1->p2]->x > N->T_Res[s2->NumRes]->T_Pt[s2->p1]->x ) return 0;
    if( N->T_Res[s2->NumRes]->T_Pt[s2->p2]->x > N->T_Res[s1->NumRes]->T_Pt[s1->p1]->x ) return 0;
    if( N->T_Res[s1->NumRes]->T_Pt[s1->p2]->y > N->T_Res[s2->NumRes]->T_Pt[s2->p1]->y ) return 0;
    if( N->T_Res[s2->NumRes]->T_Pt[s2->p2]->y > N->T_Res[s1->NumRes]->T_Pt[s1->p1]->y ) return 0;

    return 1;
}

void Creer_intersection( Segment * s1 , Segment * s2 ){
    if( !s1 || !s2 ) return;

    s1->Lintersec = Inserer_Segment_Liste_Cell_Segment( s1->Lintersec , s2 , 0 );
    s2->Lintersec = Inserer_Segment_Liste_Cell_Segment( s2->Lintersec , s1 , 0 );

}

void intersec_naif( Segment * * Tableau_Segments , int nombre_segments , Netlist * Net ){
    if( !Tableau_Segments || nombre_segments < 1 ) return;

    int i, j;
    //int debug = 1;

    for( i = 0 ; i < nombre_segments ; i++ )
        for( j = i ; j < nombre_segments ; j++ )
            if( intersection( Net , Tableau_Segments[i] , Tableau_Segments[j] ) == 1 )
                /*if( debug++ )*/ Creer_intersection( Tableau_Segments[i] , Tableau_Segments[j] );
    //printf( "%d\n" , debug );
}

/*
partitionner(tableau T, entier premier, entier dernier, pivot)
    échanger T[pivot] et T[dernier]
    j := premier
    pour i de premier à dernier - 1
        si T[i] <= T[dernier] alors
            échanger T[i] et T[j]
            j := j + 1
    échanger T[dernier] et T[j]
    renvoyer j

tri_rapide(tableau T, entier premier, entier dernier)
    début
        si premier < dernier alors
            pivot := choix_pivot(T, premier, dernier)
            pivot := partitionner(T, premier, dernier, pivot)
            tri_rapide(T ,premier, pivot-1)
            tri_rapide(T, pivot+1, dernier)
        fin si
    fin
*/

void Echanger( Extremite * * Tableau , int premier , int second ){
    if( !Tableau ) return;

    Extremite * temp;

    temp = Tableau[second];
    Tableau[second] = Tableau[premier];
    Tableau[premier] = temp;
}

int Partionner_Tableau_Extremite( Extremite * * Tableau , int premier , int dernier , int pivot ){
    if( !Tableau ) return premier;

    int i , j;

    Echanger( Tableau , pivot , dernier );
    j = premier;
    for( i = premier ; i < dernier ; i++ ) if( Tableau[i]->x <= Tableau[dernier]->x ) Echanger( Tableau , i , j++ );
    Echanger( Tableau , dernier , j );

    return j;
}

void Tri_Rapide_Echeancier( Extremite * * Tableau , int premier , int dernier ){
    if( !Tableau ) return;

    int pivot;

    if( Tableau[premier]->x < Tableau[dernier]->x ){
        pivot = Partionner_Tableau_Extremite( Tableau , premier , dernier , premier );
        Tri_Rapide_Echeancier( Tableau , premier , pivot - 1 );
        Tri_Rapide_Echeancier( Tableau , pivot + 1 , dernier );
    }

}

void Tri_Tableau_Echeancier( Extremite * * Tableau , int nombre_extremite ){
    Tri_Rapide_Echeancier( Tableau , 0 , nombre_extremite - 1 );
}

/*
Créer l'échéancier E trié selon les abscisses
T <- NULL ;
pour chaque point r de E dans l'ordre croissant faire
    si r est extrémité gauche d'un segment horizontal h alors
        Insérer(h,T)
    Fin
    si r est extrémité droite d'un segment horizontal h alors
        Supprimer(h,T)
    Fin
    si r est l'abscisse d'un segment vertical v alors
        y1 <- ordonnée du point le plus bas de v
        y2 <- ordonnée du point le plus haut de v
        h <- Prem segment apres(y,T)
        tant que h !=NULL et ordonnee de h <= y2 faire
            si h et v de réseaux différents alors
                Ajouter h à Lintersec de v
                Ajouter v à Lintersec de h
            Fin
            h <- AuDessus(h,T)
        Fin
    Fin
Fin
*/

void Intersection_Balayage_Liste_Chainee( Netlist * Net , int nombre_segments , Segment * * Tableau_Segments){
    if( !Net || nombre_segments < 1 ) return;

    Extremite * * Echeancier;
    Cell_Segment * Liste_Segments_Balayes;
    Cell_Segment * temp_Liste_Segments_Balayes;
    int nombre_extremites;
    int i;
    int y2;
    Segment * h;

    Echeancier = Creer_Echeancier( Net , nombre_segments , Tableau_Segments );
    nombre_extremites = 2 * nombre_segments;
    Tri_Tableau_Echeancier( Echeancier , nombre_extremites );
    Liste_Segments_Balayes = NULL;

    for ( i = 0 ; i < nombre_extremites ; i++ ){
        if( Echeancier[i]->VouGouD == 1 ) Liste_Segments_Balayes = Inserer_Segment_Liste_Cell_Segment( Liste_Segments_Balayes , Echeancier[i]->PtrSeg , 0 );
        if( Echeancier[i]->VouGouD == 2 ) Liste_Segments_Balayes = Supprimer_Cell_Segment_A_Partir_D_Un_Pointeur_Sur_Segment( Liste_Segments_Balayes , Echeancier[i]->PtrSeg );
        if( Echeancier[i]->VouGouD == 0 ) if( Liste_Segments_Balayes ){

            temp_Liste_Segments_Balayes = Liste_Segments_Balayes;
            y2 = Net->T_Res[Echeancier[i]->PtrSeg->NumRes]->T_Pt[Echeancier[i]->PtrSeg->p2]->y;

            while( temp_Liste_Segments_Balayes ){

                h = temp_Liste_Segments_Balayes->seg;
                if( Net->T_Res[h->NumRes]->T_Pt[h->p1]->y <= y2
                 && h->NumRes != Echeancier[i]->PtrSeg->NumRes ) Creer_intersection( h , Echeancier[i]->PtrSeg );
                temp_Liste_Segments_Balayes = temp_Liste_Segments_Balayes->suiv;

            }

        }

    }

    Liberer_Echeancier( Echeancier , nombre_extremites );
}

void Coordonnees_Max_Min_Reseau( double * xmax , double * ymax , double * xmin , double * ymin , Reseau * Res ){
    if( !xmax || !ymax || !xmin || !ymin || !Res ) return;

    int i;

    for( i = 0 ; i < Res->NbPt ; i++ ){
        *xmax = Maximum( *xmax , Res->T_Pt[i]->x );
        *ymax = Maximum( *ymax , Res->T_Pt[i]->y );
        *xmin = Minimum( *xmin , Res->T_Pt[i]->x );
        *ymin = Minimum( *ymin , Res->T_Pt[i]->y );
    }
}

void Coordonnees_Max_Min_Netlist( double * xmax , double * ymax , double * xmin , double * ymin , Netlist * Net ){
    if( !xmax || !ymax || !xmin || !ymin || !Net ) return;

    int i;

    for( i = 0 ; i < Net->NbRes ; i++ ) Coordonnees_Max_Min_Reseau( xmax , ymax , xmin , ymin , Net->T_Res[i] );
}
