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

void Sauvegarde_intersection(Segment* *segp, int NbSeg, char* name){

    int i;
    char * nom;
    Segment *s;
    Cell_Segment *ls;
    FILE* f;

    if (!segp){
        perror("Sauvegarde_intersection : your segp is NULL is NULL");
        return;
    }

    if (!name){
        perror("Sauvegarde_intersection : your name is NULL");
        return;
    }

    nom = malloc(sizeof(char*));
    nom = extension(name, ".int");

    f = fopen(nom, "w");
    if (!f){
        perror("Sauvegarde_intersection : file cannot be open");
        free(name);
        return;
    }

    for (i = 0; i < NbSeg; i++){
        s = segp[0];
        ls = s->Lintersec;

        while (ls){
            if (s->NumRes < ls->seg->NumRes){
                fprintf( f ,
                        "%d %d %d %d %d %d",
                        s->NumRes,
                        s->p1,
                        s->p2,
                        ls->seg->NumRes,
                        ls->seg->p1,
                        ls->seg->p2);
            }
            if (s->NumRes = ls->seg->NumRes){
                if (s->p1 < ls->seg->p1){
                    fprintf(f ,
                            "%d %d %d %d %d %d",
                            s->NumRes,
                            s->p1,
                            s->p2,
                            ls->seg->NumRes,
                            ls->seg->p1,
                            ls->seg->p2);
                }else{
                    if (s->p2 < ls->seg->p2){
                        fprintf( f ,
                                "%d %d %d %d %d %d",
                                s->NumRes,
                                s->p1,
                                s->p2,
                                ls->seg->NumRes,
                                ls->seg->p1,
                                ls->seg->p2);

                    }
                }
            }
            ls = ls->suiv;
        }
    }

    fclose(f);
    return;
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

