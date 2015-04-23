#include "Fonctions_Programme.h"

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
