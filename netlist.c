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
