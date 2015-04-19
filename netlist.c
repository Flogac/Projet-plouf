
void print_netlist(netlist n, char* name){
    int i,j,k;
    Reseau r;
    Point p;
    Segment s;

    if (!n){
        perror("print_netlist : your netlist is NULL")
    }
    FILE* f = fopen(name,w);
    if (!f){
        perror("print_netlist : file cannot be open");
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
    return;
}
