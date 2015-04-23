#include "Fonctions_Programme.h"

void VisuNetList(void){
    int i,j,k;
    char* fichier_netlist;
    char* fichier_ps;
    Netlist* n;
    Reseau* r;
    Point* p;
    Point* q;
    Segment* s;
    FILE* f;

    fichier_netlist = Lire_Entree_Standard(".net");
    fichier_ps = Lire_Entree_Standard(".ps");

    printf("%s %s\n", fichier_netlist, fichier_ps);

    n = Recuperer_Netlist(fichier_netlist);

    if (!n){
        perror("VisuNetList : netlist is NULL\n");
        free(fichier_netlist);
        free(fichier_ps);
        Liberation_Netlist(n);
        return;
    }

    f = fopen(fichier_ps, "w");
    if (!f){
        free(fichier_netlist);
        free(fichier_ps);
        Liberation_Netlist(n);
        perror("VisuNetList : file cannot be open\n");
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
    Liberation_Netlist(n);
    return;
}
