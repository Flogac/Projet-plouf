Cell_segment * Creer_Cell_segment(){
    Cell_segment * nouv;
    nouv = ( Cell_segment * ) malloc ( sizeof( Cell_segment ) );
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

    tab = ( Point * * ) malloc ( sizeof( Point * ) );
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

void print_netlist(netlist n, char* name){
    int i,j,k;
    char* nom;
    Reseau r;
    Point p;
    Segment s;
    FILE* f;

    if (!n || !name){
        perror("print_netlist : your netlist is NULL or name is NULL");
    }

    nom = malloc(sizeof(char*));
    nom = strcat(strcat(nom, name),".net");

    f = fopen(nom, w);
    if (!f){
        perror("print_netlist : file cannot be open");
        free(nom);
    }

    fprintf(f, "%d\n", n->NbRes);
    for (i = 0; i < n->NbRes; i++){
        r= n->T_Res[i];
        fprintf(f, "%d %d %d\n",
                r->NumRes,
                r->NbPt,
                r->NbSeg);
        for (j = 0; j < r->nbPt; j++){
            p = r->T_Seg[j];
            fprintf(f, " %d %d %d",
                    j,
                    p->x,
                    p->y);
        }
        for(k = 0; k < r->nbSeg; k++){
            s = r->T_Seg;
            fprintf(" %d %d",
                    s->p1,
                    s->p2);
        }
    }
    fclose(f);
    return;
}
