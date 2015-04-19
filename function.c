#include "netlist.c"

void VisuNetList(netlist n){
    int i,j,k;
    char* nom;
    Reseau r;
    Point p;
    Segment s;
    FILE* f;

    if (!n || !name){
        perror("VisuNetList : your netlist is NULL or name is NULL");
        return;
    }

    nom = malloc(sizeof(char*));
    nom = strcat(strcat(nom, name),".ps");

    f = fopen(nom, w);
    if (!f){
        perror("VisuNetList : file cannot be open");
        free(nom);
        return;
    }

    for (i = 0; i < n->NbRes; i++){
        r= n->T_Res[i];
        for (j = 0; j < r->nbPt; j++){
            p = r->T_Pt[j];
            fprintf(f, "%d %d 2.5 0 360 arc\n",
                    p->x,
                    p->y);
            fprintf(f, "fill\n");
            fprintf(f, "stroke\n");
        }
        for(k = 0; k < r->nbSeg; k++){
            s = r->T_Seg;
            fprintf(f, "%d %d moveto\n",
                    r->T_pt[s->p1],
                    sr->T_pt[s->p1]);
            fprintf(f, "%d %d lineto\n",
                    r->T_pt[s->p2],
                    sr->T_pt[s->p2]);
            fprintf(f, "stroke\n");
        }
    }
    fclose(f);
    return;
}
