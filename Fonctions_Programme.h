#include "Graphe.h"
#include "Lecture_fichier.h"

/* Teste la fonction postscript, entrez vos valeur lors de l'appel*/
void VisuNetList(void) ;

void Faire_Test_Intersection() ;

/* Ecrit le fichier post script a partir du nom du fichier .net et renvoie 0 si tout s'est bien passe, 1 s'il y a une erreur sur le fichier f. */
int Ecrire_Fichier_Ps_Netlist(char* nom, Netlist* n);
