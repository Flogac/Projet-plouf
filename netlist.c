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

    tab = ( Segment * * ) malloc ( sizeof( Segment * ) * nombre_segments );
    for( i = 0 ; i < nombre_segments ; i++ ) tab[i] = NULL;

    return tab;
}

Point * * Allocation_Tableau_Points( int nombre_points ){
    if( nombre_points < 1 ) return NULL;

    Point * * tab;
    int i;

    tab = ( Point * * ) malloc ( sizeof( Point * ) * nombre_points);
    for( i = 0 ; i < nombre_points ; i++ ) tab[i] = NULL;

    return tab;
}

Reseau * * Allocation_Tableau_Reseaux( int nombre_reseaux ){
    if( nombre_reseaux < 1 ) return NULL;

    Reseau * * tab;
    int i;

    tab = malloc ( sizeof( Reseau * ) * nombre_reseaux);
    for( i = 0 ; i < nombre_reseaux ; i++ ) tab[i] = NULL;

    return tab;
}

Extremite * * Allocation_Tableau_Extremite( int nombre_extremite ){
    if( nombre_extremite < 1 ) return NULL;

    Extremite * * tab;
    int i;

    tab = malloc ( sizeof( Extremite * ) * nombre_extremite);
    for( i = 0 ; i < nombre_extremite ; i++ ) tab[i] = NULL;

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

    Tableau_Segments = Allocation_Tableau_Segments( nombre_segments );
    k = 0;

    for( i = 0 ; i < Net->NbRes ; i++ ) for( j = 0 ; j < Net->T_Res[i]->NbSeg ; j++ ) Tableau_Segments[k++] = Net->T_Res[i]->T_Seg[j];

    return Tableau_Segments;
}

Extremite * * Creer_Echeancier( Netlist * Net , int nombre_segments , Segment * * Tableau_Segments ){
    if( !Net || nombre_segments > 0 || !Tableau_Segments );

    Extremite * * Echeancier;
    int i, j;
    Extremite * temp;
    int num_point;

    Echeancier = Allocation_Tableau_Extremite( nombre_segments * 2 );

    for( i = 0 ; i < nombre_segments ; i++ ){

        for( j = 0 ; j < 2 ; j++ ){

            if( j == 0 ) num_point = Tableau_Segments[i]->p1;
            if( j == 1 ) num_point = Tableau_Segments[i]->p2;
            temp = Creer_Extremite();
            temp->PtrSeg = Tableau_Segments[i];
            temp->x = Net->T_Res[Tableau_Segments[i]->NumRes]->T_Pt[num_point]->x;
            temp->NumPt = num_point;
            if( Tableau_Segments[i]->HouV == 1 ) {
                temp->VouGouD = 0;
            }else{
                temp->VouGouD = num_point + 1;
            }

            Echeancier[ 2 * i + j] = temp;

        }

    }

    return Echeancier;
}

void Liberer_Echeancier( Extremite * * Echeancier , int nombre_extremites ){
    if( !Echeancier || nombre_extremites < 1 ) return;

    int i;

    for( i = 0 ; i < nombre_extremites ; i++ ) Liberation_Extremite( Echeancier[i] );
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
        Net->T_Res[i] = Net_Res;
        Net->T_Res[i]->NumRes = i;
        Net->T_Res[i]->NbPt = GetEntier( f );
        Net->T_Res[i]->T_Pt = Allocation_Tableau_Points( Net->T_Res[i]->NbPt );
        Net->T_Res[i]->NbSeg = GetEntier( f );
        Net->T_Res[i]->T_Seg = Allocation_Tableau_Segments( Net->T_Res[i]->NbSeg );

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
            Skip( f );
            Net->T_Res[i]->T_Seg[j]->p1 = GetEntier( f );
            Skip( f );
            Net->T_Res[i]->T_Seg[j]->p2 = GetEntier( f );
            SkipLine( f );

            printf ("%d %d\n",
                Net->T_Res[i]->T_Seg[j]->p1,
                Net->T_Res[i]->T_Seg[j]->p2);

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

Cell_Segment * Inserer_Segment_Liste_Cell_Segment( Cell_Segment * Liste , Segment * seg , int mettre_zero_ici_ne_pas_chercher_pourquoi_car_les_voix_de_la_recursion_sont_impenetrables ){
    if( !Liste && mettre_zero_ici_ne_pas_chercher_pourquoi_car_les_voix_de_la_recursion_sont_impenetrables != 0 ) return NULL;
    if( !seg ) return NULL;

    Cell_Segment * temp;

    if( !Liste || Inserer_Segment_Liste_Cell_Segment( Liste->suiv , seg , mettre_zero_ici_ne_pas_chercher_pourquoi_car_les_voix_de_la_recursion_sont_impenetrables + 1 ) == NULL ){
        temp = Creer_Cell_Segment();
        temp->seg = seg;
    }

    return temp;
}

Cell_Segment * Supprimer_Cell_Segment_A_Partir_D_Un_Pointeur_Sur_Segment( Cell_Segment * Liste , Segment * seg ){
    if( !Liste || !seg ) return NULL;

    Cell_Segment * temp;

    temp = NULL;
    if( Liste->seg != seg ) Liste = Supprimer_Cell_Segment_A_Partir_D_Un_Pointeur_Sur_Segment( Liste->suiv , seg );
    if( Liste->suiv ) temp = Liste->suiv;
    free( Liste );
    return temp;
}
