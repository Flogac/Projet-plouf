#include "avl.h"

Avl* Creer_Avl(){
    Avl *nouv;
    nouv = malloc(sizeof(Avl));
    nouv->fg = NULL;
    nouv->fd = NULL;
    nouv->clef = -1;
    nouv->seg = NULL;
    return nouv;
}

void Liberation_Avl(Avl *racine){

    if (!racine) return;

    if (racine->fg) Liberation_Avl(racine->fg);

    if (racine->fd) Liberation_Avl(racine->fd);

    free(racine);
}

int AB_hauteur(Avl *racine){

    if(racine==NULL)
        return-1;
    int hg=AB_hauteur(racine->fg);
    int hd=AB_hauteur(racine->fd);
    if(hg<hd)
        return 1+hd;
    else
        return 1+hg;
}

Avl *AB_RotationDroite(Avl *racine){

    Avl* g = racine->fg;
    racine->fg=g->fd;
    g->fg=racine;
    return g;
}

Avl *AB_RotationGauche(Avl *racine){

    Avl* d=racine->fd;
    racine->fd=d->fg;
    d->fg=racine;
    return d;
}

void Equilibre(Avl* racine){

    int hfg=AB_hauteur(racine->fg);
    int hfd=AB_hauteur(racine->fd);
    if(hfg-hfd==-2){
        int hfd_d=AB_hauteur(racine->fd->fd);
        int hfd_g=AB_hauteur(racine->fd->fg);
        if(hfd_d<hfd_g){
            racine->fd=AB_RotationDroite(racine->fd);
        }
        racine=AB_RotationGauche(racine);

    }else{
        if(hfg-hfd==2){
            int hfgg=AB_hauteur(racine->fg->fg);
            int hfgd=AB_hauteur(racine->fg->fd);
            if(hfgg<hfgd){
                racine->fg=AB_RotationGauche(racine->fg);
            }
            racine=AB_RotationDroite(racine);
        }
    }
    return;
}

Avl* Inserer_Element_Avl(Extremite* e, Avl* racine){

    if (!e) return racine;

    Avl *tmp;

    if (!racine){
        tmp = Creer_Avl();
        tmp->seg = e->PtrSeg;
        tmp->clef = e->x;
        racine = tmp;
    }

    if (racine->clef <= e->x){
        racine->fg = Inserer_Element_Avl(e, racine->fg);
    }
    if (racine->clef > e->x){
        racine->fd = Inserer_Element_Avl(e, racine->fd);
    }
    Equilibre(racine);
    return racine;
}

Avl* Noeud_Pour_Suppression(Avl *racine){

    Avl* tmp;

    if (!racine) return NULL;

    if (!racine->fd) return racine;

    tmp = racine->fd;

    while (tmp->fg) tmp = tmp->fg;
    return tmp;
}

Avl* Supprimer_Element_Avl(Extremite* e, Avl* racine){

    if (!e) return racine;

    Avl *tmp;
    Avl *plus_petit;
    Segment *s;
    Segment *extremite_s;

    if (!racine) return NULL;

    if (e->x == racine->clef){
        s = racine->seg;
        extremite_s = e->PtrSeg;
        if (s == extremite_s){
            plus_petit = Noeud_Pour_Suppression(racine);
            tmp = racine;
            racine = plus_petit;
            plus_petit = tmp;
            Liberation_Avl(plus_petit);
        }
    }
    if (racine->clef <= e->x){
        racine->fg = Supprimer_Element_Avl(e, racine->fg);
    }
    if (racine->clef > e->x){
        racine->fd = Supprimer_Element_Avl(e, racine->fd);
    }
    Equilibre(racine);
    return racine;
}

void Intersection_Balayage_Avl_rec(Netlist* n, Avl* a, Segment* h, Extremite* e, int y2){

    if (!a || !n || !h || !e) return;

    double y = n->T_Res[h->NumRes]->T_Pt[h->p1]->y;
    if (y <= y2 && h->NumRes != e->PtrSeg->NumRes){
        Creer_intersection(h, e->PtrSeg);
    }

    if(a->fg) Intersection_Balayage_Avl_rec(n, a->fg, h, e, y2);

    if(a->fd) Intersection_Balayage_Avl_rec(n, a->fd, h, e, y2);

    return;
}


void Intersection_Balayage_Avl( Netlist * n , int nombre_segments , Segment * * Tableau_Segments){

    if ( !n || nombre_segments < 1 ) return;

    int i;
    Extremite * * Echeancier;
    Extremite * e;
    Avl * Avl_Segments_Balayes;
    Avl * Avl_tmp;
    int nombres_extremites;
    double y2;

    Echeancier = Creer_Echeancier(n, nombre_segments, Tableau_Segments);
    nombres_extremites = 2 * nombre_segments;
    Tri_Tableau_Echeancier(Echeancier, nombres_extremites);
    Avl_Segments_Balayes = NULL;

    for ( i = 0 ; i < nombres_extremites ; i++ ){
        e = Echeancier[i];
        switch (e->VouGouD){
            case 1:
                Avl_Segments_Balayes = Inserer_Element_Avl(e, Avl_Segments_Balayes);
                break;
            case 2:
                Avl_Segments_Balayes = Supprimer_Element_Avl(e, Avl_Segments_Balayes);
                break;
            case 0:
                Avl_tmp = Avl_Segments_Balayes;
                if (Avl_tmp){
                    y2 = n->T_Res[e->PtrSeg->NumRes]->T_Pt[e->PtrSeg->p2]->y;
                    Intersection_Balayage_Avl_rec(n, Avl_tmp,  Avl_tmp->seg, e, y2);
                }
        }
        break;
    }
}
