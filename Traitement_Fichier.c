#include "Traitement_Fichier.h"

int Ecrire_Fichier_Ps_Netlist(char* nom, Netlist* n){

    int i,j,k;
    double x,y;
    double xmax = 0;
    double ymax = 0;
    double xmin = 0;
    double ymin = 0;
    double XMAX, YMAX;
    Reseau* r;
    Point* p;
    Point* q;
    Segment* s;
    FILE* f;


    f = fopen(nom, "w");
    if (!f){
        perror("Ecrire_fichier_ps_Netlist : file cannot be open\n");
        fclose(f);
        return 1;
    }
    XMAX = 585;
    YMAX = 832;
    Coordonnees_Max_Min_Netlist(&xmax, &ymax, &xmin, &ymin, n);

    for (i = 0; i < n->NbRes; i++){
        r = n->T_Res[i];
        for (j = 0; j < r->NbPt; j++){
            p = r->T_Pt[j];

            x = (p->x * XMAX) / xmax + 5;
            y = (p->y * YMAX) / ymax + 5;
            fprintf(f, "%g %g 2.5 0 360 arc\n", x, y);
            fprintf(f, "fill\n");

            fprintf(f, "stroke\n");
        }
        for(k = 0; k < r->NbSeg; k++){
            s = r->T_Seg[k];
            p = r->T_Pt[s->p1];
            q = r->T_Pt[s->p2];

            x = (p->x * XMAX) / xmax + 5;
            y = (p->y * YMAX) / ymax + 5;
            fprintf(f, "%g %g moveto\n", x, y);


            x = (q->x * XMAX) / xmax + 5;
            y = (q->y * YMAX) / ymax + 5;
            fprintf(f, "%g %g lineto\n", x, y);

            fprintf(f, "stroke\n");
        }
    }
    fclose(f);
    return 0;
}


Netlist * Recuperer_Netlist( char * nom_fichier_en_net ){
    if( nom_fichier_en_net == NULL ) return NULL;

    Netlist * Net;
    FILE * f;
    Reseau * Net_Res;
    Segment * Net_Seg;
    Point * Net_Pt;
    int i , j;
    Cell_Segment_Num * incidence;
    Cell_Segment_Num * temp_incidence;

    f = fopen( nom_fichier_en_net, "r" );
    Net = Creer_Netlist();

    Net->NbRes = GetEntier( f );
    SkipLine( f );
    Net->T_Res = Allocation_Tableau_Reseaux( Net->NbRes );

    for( i = 0 ; i < Net->NbRes ; i++ ){

        Net_Res = Creer_Reseau();
        GetEntier( f );
        Net->T_Res[i] = Net_Res;
        Net->T_Res[i]->NumRes = i;
        Skip( f );
        Net->T_Res[i]->NbPt = GetEntier( f );
        Skip( f );
        Net->T_Res[i]->T_Pt = Allocation_Tableau_Points( Net->T_Res[i]->NbPt );
        Net->T_Res[i]->NbSeg = GetEntier( f );
        Net->T_Res[i]->T_Seg = Allocation_Tableau_Segments( Net->T_Res[i]->NbSeg );

        SkipLine( f );

        for( j = 0 ; j < Net->T_Res[i]->NbPt ; j++){

            Skip( f );
            GetEntier( f );
            Net_Pt = Creer_Point();
            Net->T_Res[i]->T_Pt[j] = Net_Pt;
            Net->T_Res[i]->T_Pt[j]->num_res = i;
            Net->T_Res[i]->T_Pt[j]->x = GetReel( f );
            Net->T_Res[i]->T_Pt[j]->y = GetReel( f );

            SkipLine( f );

        }

        for( j = 0 ; j < Net->T_Res[i]->NbSeg ; j++){

            Net_Seg = Creer_Segment();
            Net->T_Res[i]->T_Seg[j] = Net_Seg;
            Net->T_Res[i]->T_Seg[j]->NumRes = i;
            Net->T_Res[i]->T_Seg[j]->p1 = GetEntier( f );
            Skip( f );
            Net->T_Res[i]->T_Seg[j]->p2 = GetEntier( f );
            SkipLine( f );
            Net->T_Res[i]->T_Seg[j]->seg_iteratif = j;

            if( Net->T_Res[i]->T_Pt[Net->T_Res[i]->T_Seg[j]->p1]->x
             == Net->T_Res[i]->T_Pt[Net->T_Res[i]->T_Seg[j]->p2]->x
             ) Net->T_Res[i]->T_Seg[j]->HouV = 1;

            if( Net->T_Res[i]->T_Pt[Net->T_Res[i]->T_Seg[j]->p1]->y
             == Net->T_Res[i]->T_Pt[Net->T_Res[i]->T_Seg[j]->p2]->y
             ) Net->T_Res[i]->T_Seg[j]->HouV = 1;

            incidence = Creer_Cell_Segment_num();
            incidence->i = j;
            temp_incidence = Net->T_Res[i]->T_Pt[Net->T_Res[i]->T_Seg[j]->p1]->Lincid;
            if( temp_incidence ) while( temp_incidence->suiv ) temp_incidence = temp_incidence->suiv;
            if( temp_incidence ){
                temp_incidence->suiv = incidence;
            } else {
                    Net->T_Res[i]->T_Pt[Net->T_Res[i]->T_Seg[j]->p1]->Lincid = incidence;
            }

            incidence = Creer_Cell_Segment_num();
            incidence->i = j;
            temp_incidence = Net->T_Res[i]->T_Pt[Net->T_Res[i]->T_Seg[j]->p2]->Lincid;
            if( temp_incidence ) while( temp_incidence->suiv ) temp_incidence = temp_incidence->suiv;
            if( temp_incidence ){
                temp_incidence->suiv = incidence;
            } else {
                    Net->T_Res[i]->T_Pt[Net->T_Res[i]->T_Seg[j]->p2]->Lincid = incidence;
            }

        }

    }

    fclose( f );
    return Net;
}

void print_netlist(Netlist* n, char* name){
    int i,j,k;
    char* nom;
    Reseau* r;
    Point* p;
    Segment* s;
    FILE* f;

    if ( !n ){
        perror("print_netlist : your netlist is NULL or name is NULL");
        return;
    }
    nom = Extension(name, ".net");

    f = fopen(nom, "w");
    if (!f){
        perror("print_netlist : file cannot be open");
        free(nom);
        return;
    }

    fprintf(f, "%d\n", n->NbRes);
    for (i = 0; i < n->NbRes; i++){
        r = n->T_Res[i];
        fprintf(f, "%d %d %d\n",
                r->NumRes,
                r->NbPt,
                r->NbSeg);
        for (j = 0; j < r->NbPt; j++){
            p = r->T_Pt[j];
            fprintf(f, " %d %g %g",
                    j,
                    p->x,
                    p->y);
        }
        for(k = 0; k < r->NbSeg; k++){
            s = r->T_Seg[k];
            fprintf(f, " %d %d",
                    s->p1,
                    s->p2);
        }
    }
    fclose(f);
    return;
}

void Sauvegarde_intersection(Segment* *segp, int NbSeg, char* name){

    int i;
    //char * nom;
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
/*
    nom = malloc(sizeof(char*));
    nom = Extension(name, ".int");
*/
 //   f = fopen(nom, "w");
    f = fopen( name , "w" );
    if (!f){
        perror("Sauvegarde_intersection : file cannot be open");
        free(name);
        return;
    }

    for (i = 0; i < NbSeg; i++){
        s = segp[i];
        ls = s->Lintersec;

        while (ls){
            if (s->NumRes < ls->seg->NumRes){
                fprintf( f ,
                        "%d %d %d %d %d %d\n",
                        s->NumRes,
                        s->p1,
                        s->p2,
                        ls->seg->NumRes,
                        ls->seg->p1,
                        ls->seg->p2);
            }
            if (s->NumRes == ls->seg->NumRes){
                if (s->p1 < ls->seg->p1){
                    fprintf(f ,
                            "%d %d %d %d %d %d\n",
                            s->NumRes,
                            s->p1,
                            s->p2,
                            ls->seg->NumRes,
                            ls->seg->p1,
                            ls->seg->p2);
                }else{
                    if (s->p2 < ls->seg->p2){
                        fprintf( f ,
                                "%d %d %d %d %d %d\n",
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

