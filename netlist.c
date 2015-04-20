#include "netlist.h"

Cell_Segment * Creer_Cell_Segment(){
    Cell_Segment * nouv;
    nouv = ( Cell_Segment * ) malloc ( sizeof( Cell_Segment ) );
    nouv->suiv = NULL;
    nouv->seg = NULL;

    return nouv;
}

Cell_Segment_Num * Creer_Cell_Segment_num(){
    Cell_Segment_Num * nouv;

    nouv = ( Cell_Segment_Num * ) malloc ( sizeof( Cell_Segment_Num ) );
    nouv->suiv = NULL;
    nouv->i = -1;

    return nouv;
}

Segment * Creer_Segment(){
    Segment * nouv;

    nouv = ( Segment * ) malloc ( sizeof( Segment ) );
    nouv->HouV = -1;
    nouv->Lintersec = NULL;
    nouv->NumRes = -1;
    nouv->p1 = -1;
    nouv->p2 = -1;

    return nouv;
}

Point * Creer_Point(){
    Point * nouv;

    nouv = ( Point * ) malloc ( sizeof( Point ) );
    nouv->Lincid = NULL;
    nouv->num_res = -1;
    nouv->x = -1;
    nouv->y = -1;

    return nouv;
}

Reseau * Creer_Reseau(){
    Reseau * nouv;

    nouv = ( Reseau * ) malloc ( sizeof( Reseau ) );
    nouv->NbPt = -1;
    nouv->NbSeg = -1;
    nouv->NumRes = -1;
    nouv->T_Pt = NULL;
    nouv->T_Seg = NULL;

    return nouv;
}

Netlist * Creer_Netlist(){
    Netlist * nouv;

    nouv = ( Netlist * ) malloc ( sizeof( Netlist ) );
    nouv->NbRes = -1;
    nouv->T_Res = NULL;

    return nouv;
}

Extremite * Creer_Extremite(){
    Extremite * nouv;

    nouv = ( Extremite * ) malloc ( sizeof( Extremite ) );
    nouv->NumPt = -1;
    nouv->PtrSeg = NULL;
    nouv->VouGouD = -1;
    nouv->x = -1;

    return nouv;
}

Segment * * Allocation_Tableau_Segments( int nombre_segments ){
    if( nombre_segments < 1 ) return NULL;

    Segment * * tab;
    int i;

    tab = ( Segment * * ) malloc ( sizeof( Segment * ) );
    for( i = 0 ; i < nombre_segments ; i++ ) tab[i] = NULL;

    return tab;
}

Point * * Allocation_Tableau_Points( int nombre_points ){
    if( nombre_points < 1 ) return NULL;

    Point * * tab;
    int i;

    tab = ( Point * * ) malloc ( sizeof( Point * ) );
    for( i = 0 ; i < nombre_points ; i++ ) tab[i] = NULL;

    return tab;
}

Reseau * * Allocation_Tableau_Reseaux( int nombre_reseaux ){
    if( nombre_reseaux < 1 ) return NULL;

    Reseau * * tab;
    int i;

    tab = malloc ( sizeof( Reseau * ));
    for( i = 0 ; i < nombre_reseaux ; i++ ) tab[i] = NULL;

    return tab;
}

void Liberation_Cell_Segment_Num( Cell_Segment_Num * libre ){
    if( libre == NULL ) return;

    if( libre->suiv != NULL ) Liberation_Cell_Segment_Num( libre->suiv );

    free( libre );
}

void Liberation_Cell_Segment( Cell_Segment * libre ){
    if( libre == NULL ) return;

    if( libre->suiv != NULL ) Liberation_Cell_Segment( libre->suiv );

    free( libre );
}

void Liberation_Segment( Segment * libre ){
    if( libre == NULL ) return;

    Liberation_Cell_Segment( libre->Lintersec );

    free( libre );
}

void Liberation_Point( Point * libre ){
    if( libre == NULL ) return;

    Liberation_Cell_Segment_Num( libre->Lincid );

    free( libre );
}

void Liberation_Reseau( Reseau * libre ){
    if( libre == NULL ) return;

    int i;

    for( i = 0 ; i < libre->NbPt ; i++ ) Liberation_Point( libre->T_Pt[i] );
    for( i = 0 ; i < libre->NbSeg ; i++ ) Liberation_Segment( libre->T_Seg[i] );

    free( libre->T_Pt );
    free( libre->T_Seg );
    free( libre );
}

void Libetation_Netlist( Netlist * libre ){
    if( libre == NULL ) return;

    int i;

    for( i = 0 ; i < libre->NbRes ; i++ ) Liberation_Reseau( libre->T_Res[i] );

    free( libre->T_Res );
    free( libre );
}

void Liberation_Extremite( Extremite * libre ){
    if( !libre ) return;

    free( libre );
    // LOLOLOLOLOLOLOLOLOLOLOLOL
}

Segment * * Creer_Tableau_Segments_Netlist( Netlist * Net , int nombre_segments ){
    if( !Net || nombre_segments > 0 );

    Segment * * Tableau_Segments;
    int i , j , k;

    Tableau_Segments = ( Segment * * ) malloc ( sizeof( Segment * ) );
    k = 0;

    for( i = 0 ; i < Net->NbRes ; i++ ) for( j = 0 ; j < Net->T_Res[i]->NbSeg ; j++ ) Tableau_Segments[k++] = Net->T_Res[i]->T_Seg[j];

    return Tableau_Segments;
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

    f = fopen( nom_fichier_en_net, "w" );
    Net = Creer_Netlist();

    Net->NbRes = GetEntier( f );
    SkipLine( f );
    Net->T_Res = Allocation_Tableau_Reseaux( Net->NbRes );

    for( i = 0 ; i < Net->NbRes ; i++ ){

        Net_Res = Creer_Reseau();
        Net->T_Res[i] = Net_Res;
        Net->T_Res[i]->NumRes = i;
        Net->T_Res[i]->NbPt = GetEntier( f );
        Net->T_Res[i]->NbSeg = GetEntier( f );
        SkipLine( f );

        for( j = 0 ; j < Net->T_Res[i]->NbPt ; j++){

            GetEntier( f );
            Net_Pt = Creer_Point();
            Net->T_Res[i]->T_Pt[j] = Net_Pt;
            Net->T_Res[i]->T_Pt[j]->num_res = i;
            Net->T_Res[i]->T_Pt[j]->x = GetEntier( f );
            Net->T_Res[i]->T_Pt[j]->y = GetEntier( f );
            SkipLine( f );

        }

        for( j = 0 ; j < Net->T_Res[i]->NbSeg ; j++){

            Net_Seg = Creer_Segment();
            Net->T_Res[i]->T_Seg[j] = Net_Seg;
            Net->T_Res[i]->T_Seg[j]->NumRes = i;
            Net->T_Res[i]->T_Seg[j]->p1 = GetEntier( f );
            Net->T_Res[i]->T_Seg[j]->p2 = GetEntier( f );
            SkipLine( f );

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
    nom = extension(name, ".net");

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

void VisuNetList(Netlist* n, char* name){
    int i,j,k;
    char* nom;
    Reseau* r;
    Point* p;
    Point* q;
    Segment* s;
    FILE* f;

    if (!n){
        perror("VisuNetList : your netlist is NULL or name is NULL");
        return;
    }

    nom = malloc(sizeof(char*));
    nom = extension(name, ".net");

    f = fopen(nom, "w");
    if (!f){
        perror("VisuNetList : file cannot be open");
        free(nom);
        return;
    }

    for (i = 0; i < n->NbRes; i++){
        r = n->T_Res[i];
        for (j = 0; j < r->NbPt; j++){
            p = r->T_Pt[j];
            fprintf(f, "%g %g 2.5 0 360 arc\n",
                    p->x,
                    p->y);
            fprintf(f, "fill\n");
            fprintf(f, "stroke\n");
        }
        for(k = 0; k < r->NbSeg; k++){
            s = r->T_Seg[k];
            p = r->T_Pt[s->p1];
            q = r->T_Pt[s->p2];
            fprintf(f, "%g %g moveto\n",
                    p->x,
                    p->y);
            fprintf(f, "%g %g lineto\n",
                    q->x,
                    q->y);
            fprintf(f, "stroke\n");
        }
    }
    fclose(f);
    return;
}

int nb_segment(Netlist* n){

    int i,res;
    Reseau *tmp;

    if (!n){
        perror("nb_segment : n == NULL");
    }

    for (i = n->NbRes; i > 0; i--){
        tmp = n->T_Res[i];
        res = res + tmp->NbSeg;
    }
    return res;
}

