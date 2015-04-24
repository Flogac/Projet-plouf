#include "Lecture_fichier.h"
#include <stdio.h>
#include <string.h>

char * ajout_extension_nom_fichier( char * nomfichier, char * extension){
    if( nomfichier == NULL ) return NULL;
    if( extension == NULL ) return nomfichier;

    int longueurextension, longueurnomfichier, /*i=0 ,*/ longueurnomfichier_etendu;

    longueurextension=strlen(extension);
    longueurnomfichier=strlen(nomfichier);
    longueurnomfichier_etendu = longueurextension + longueurnomfichier + 1;

    //printf( "%s %s %d %d %d\n", nomfichier , extension , longueurnomfichier , longueurextension , longueurnomfichier_etendu );

    char * nomfichier_etendu = (char *) malloc(sizeof(char)*( longueurnomfichier_etendu ));

    /*for( i = 0 ; i < longueurnomfichier_etendu ; i++ ){
        if(i < longueurnomfichier)nomfichier_etendu[i] = nomfichier[i];
        if(i == longueurnomfichier)nomfichier_etendu[i] = '.';
        if(i > longueurnomfichier) nomfichier_etendu[i] = *(extension + i - longueurnomfichier - 1);
        i++;
        printf( "%s\n" , nomfichier_etendu );
    }*/

    nomfichier_etendu[0]='\0';
    strcat( nomfichier_etendu , nomfichier );
    strcat( nomfichier_etendu , extension );
    printf( "%s\n" , nomfichier_etendu );

    return nomfichier_etendu;
}


// Demande d'un nom de fichier à l'utilisateur avec une extension de fichier.

char * demande_nom_fichier(char * extension ){ // extension du fichier. Si extension==NULL, tout fichier pourra être lu.
    char * nomfichier ;
    int longueurnomfichier=0, option=0;
    int boo=1; // Variable de contrôle des boucles.

    nomfichier = (char *) malloc (sizeof(char)*256);
    printf("Quel fichier souhaitez-vous lire? (Taille limitée à 256 caractères.) \n");

    while(boo==1){

        boo=0;

        if(scanf("%s", nomfichier)==0){
            printf("Erreur lors de la saisie, le programme va maintenant se fermer.\n");
            exit (0);
            }

        longueurnomfichier=strlen(nomfichier);

        if(longueurnomfichier==0){

            printf("Aucun nom de fichier saisi. \nSouhaitez-vous réessayer de saisir un fichier? 1 pour oui, 2 pour non.\n");

             while( boo==0){

                    if(scanf("%d", &option)==0){
                    printf("Erreur lors de la saisie, le programme va maintenant se fermer.\n");
                    exit (0);
                    }

                if(option==1){

                    boo=1;
                    printf("Quel fichier souhaitez-vous lire? \n");

                }else if(option==2){

                    boo=-1;

                }else{

                    printf("Vous n'avez choisi aucune des options proposées. La question va vous être reposée.\nSouhaitez-vous réessayer? 1 pour oui, 2 pour non.\n");

                    }

                }

            }else{

            if(extension) ajout_extension_nom_fichier( nomfichier , extension );

                }
        }

    return nomfichier;
}
