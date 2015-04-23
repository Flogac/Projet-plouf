#include "Fonctions_Programme.h"

void VisuNetList(void){

    char* fichier_netlist;
    char* fichier_ps;
    Netlist* n;

    fichier_netlist = Lire_Entree_Standard(".net");
    fichier_ps = Lire_Entree_Standard(".ps");
    n = Recuperer_Netlist(fichier_netlist);

    if (!n){
        perror("VisuNetList : netlist is NULL\n");
        free(fichier_netlist);
        free(fichier_ps);
        return;
    }

    if (Ecrire_Fichier_Ps_Netlist(fichier_ps, n) == 1){
        free(fichier_netlist);
        free(fichier_ps);
        Liberation_Netlist(n);
        perror("VisuNetList : file cannot be open\n");
        return;
    }

    Liberation_Netlist(n);
    return;
}

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
