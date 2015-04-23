#include <stdio.h>
#include <stdlib.h>
#include "netlist.h"

typedef struct _AVL{
    double clef;
    Segment* seg;
    struct _AVL *fg;
    struct _AVL *fd;
}Avl;


/* Fonction de creation d'un Avl */
Avl* Creer_Avl();

/* Fonction de desallocation d'un Avl */
void Liberation_Avl(Avl *racine);

/* Renvoie un entier hauteur qui est la hauteur de la racine actuelle */
int AB_hauteur(Avl *racine);

/* Pere devient le fils droit */
Avl *AB_RotationDroite(Avl *racine);

/* Pere devient le fils gauche */
Avl *AB_RotationGauche(Avl *racine);

/* Fonction d'equilibrage de l'arbre grace aux rotations et aux mis a jour des hauteurs */
void Equilibre(Avl* racine);

/* Insere un element dans l'arbre a sa place et reequilibre l'arbre apres insertion */
Avl* Inserer_Element_Avl(Extremite* e, Avl* racine);

/* C'est le plus petit des plus grands noeuds existants a partir de la racine choisie, il sera utilise pour la suppression dans un Avl */
Avl* Noeud_Pour_Suppression(Avl *racine);

/* Supprime un element Extremite dans l'arbre et le reequilibre apres suppression. */
Avl* Supprimer_Element_Avl(Extremite* e, Avl* racine);

/* Fonction de recurssion pour la fonction Intersection_Balayage_Avl, elle va verifier h et l'ordonnee et va ajouter ou non les segments a leur intersect respectifs. */
void Intersection_Balayage_Avl_rec(Netlist* n, Avl* a, Segment* h, Extremite* e, int y2);

/* Fonction de balayage de l'Avl */
void Intersection_Balayage_Avl( Netlist * n , int nombre_segments , Segment * * Tableau_Segments);

/*
Créer l'échéancier E trié selon les abscisses
T <- NULL ;
pour chaque point r de E dans l'ordre croissant faire
    si r est extrémité gauche d'un segment horizontal h alors
        Insérer(h,T)
    Fin
    si r est extrémité droite d'un segment horizontal h alors
        Supprimer(h,T)
    Fin
    si r est l'abscisse d'un segment vertical v alors
        y1 <- ordonnée du point le plus bas de v
        y2 <- ordonnée du point le plus haut de v
        h <- Prem segment apres(y,T)
        tant que h !=NULL et ordonnee de h <= y2 faire
            si h et v de réseaux différents alors
                Ajouter h à Lintersec de v
                Ajouter v à Lintersec de h
            Fin
            h <- AuDessus(h,T)
        Fin
    Fin
Fin
*/
