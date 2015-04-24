#include "Graphe.h"

/* Ecrit le fichier post script a partir du nom du fichier .net et renvoie 0 si tout s'est bien passe, 1 s'il y a une erreur sur le fichier f. */
int Ecrire_Fichier_Ps_Netlist(char* nom, Netlist* n);

Netlist * Recuperer_Netlist( char * nom_fichier_en_net ) ;

/* Fonctions d'affichage de la structure netlist sous forme de .net */
void print_netlist(Netlist* n, char* name);
