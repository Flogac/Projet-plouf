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

