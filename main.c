#include "Fonctions_Programme.h"
//#include "function.c"

int main(){

int quitter;
char * choixmenu;

choixmenu = ( char * ) malloc ( sizeof( char ) * 256 );
printf( "Bienvenue dans le projet de Florent \"Jean-Yves\" Gacougnolle et William \"Jean-Yves\" Fabre.\n" );

quitter = 0;
while( quitter == 0 ){

    printf( "Menu:\n" );
    printf( "0_ Informations\n");
    printf( "1 Programme fini\n");
    printf( "2 VisuNetList\n");
    printf( "3 Test intersections\n" );
    printf( "9 Quitter\n");
    printf( "Nous allons maintenant proc�der � la saisie. Tout caract�re superflu ne sera pas pris en compte.");
    printf( "Tout caract�re non propos� sera consid�r� comme une demande de r��crire le menu.\n");

    scanf( "%s" , choixmenu );

    if( choixmenu[0] == '0' ) printf( "Cette fonctionnalit� n'a pas encore �t� implent�e. LOLOLOLOLOLOLOL\n");
    if( choixmenu[0] == '1' ) printf( "Le programme est en construction.\n" );
    if( choixmenu[0] == '2' ) VisuNetList();
    if( choixmenu[0] == '3' ) printf( "C'est pour bient�t.\n");
    if( choixmenu[0] == '9' ){
        printf( "C'est si triste de nous quitter si t�t.\n" );
        quitter = 1;
    }
}

free( choixmenu );
return 0;
}
