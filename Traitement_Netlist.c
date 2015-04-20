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

void Sauvegarde_intersection(Segment* *segp, int NbSeg, char* name){

    int i;
    Segment *s, *ls;
    Point *p;
    FILE* f;

    if (!n){
        perror("Sauvegarde_intersection : your segp is NULL or name is NULL");
        return;
    }

    nom = malloc(sizeof(char*));
    nom = extension(name, ".int");

    f = fopen(name, "w");
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
                fprintf(" %d %d %d %d %d %d",
                        s->NumRes,
                        s->p1,
                        s->p2,
                        ls->seg->NumRes,
                        ls->seg->p1,
                        ls->seg->p2);
            }
            if (s->NumRes = ls->seg->NumRes){
                if (s->p1 < ls->seg->p1){
                    fprintf(" %d %d %d %d %d %d",
                            s->NumRes,
                            s->p1,
                            s->p2,
                            ls->seg->NumRes,
                            ls->seg->p1,
                            ls->seg->p2);
                }else{
                    if (s->p2 < ls->seg->p2){
                        fprintf(" %d %d %d %d %d %d",
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
        fclose(f);
        return;
    }
}
