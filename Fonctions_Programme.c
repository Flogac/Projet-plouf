#include "Fonctions_Programme.h"

void VisuNetList(void){

    char * nomfichier;
    char* fichier_netlist;
    char* fichier_ps;
    Netlist* n;

    //fichier_netlist = Lire_Entree_Standard(".net");
    //fichier_ps = Lire_Entree_Standard(".ps");
    nomfichier = demande_nom_fichier( NULL );
    fichier_netlist = ajout_extension_nom_fichier( nomfichier , ".net" );
    free( nomfichier );
    nomfichier = demande_nom_fichier( NULL );
    fichier_ps = ajout_extension_nom_fichier( nomfichier , ".ps" );
    free( nomfichier );
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

    free(fichier_netlist);
    free(fichier_ps);
    Liberation_Netlist(n);
    return;
}

void Faire_Test_Intersection(){
    Netlist * Net;
    char * nom_fichier;
    char * nom_fichier_net;
    char * option_scanf;
    Segment * * Tab;
    int nombre_segments;

    printf( "Sali sali sala salut. Nous allons maintenant comparer la vitesse de d'utilisation de différents");
    printf( "alorithmes de calcul d'intersection.");

    option_scanf = ( char * ) malloc ( sizeof( char ) * 256 );
    nom_fichier = demande_nom_fichier( NULL );
    nom_fichier_net = ajout_extension_nom_fichier( nom_fichier , ".net" );

    Net = Recuperer_Netlist( nom_fichier_net );
    printf( "Quel algorithme voulez-vous utiliser pour le premier test?\n");
    printf("1 : Naïf\n2 : Balayage par liste chaînée\n3 : Balayage par AVL\n");
    scanf( "%s" , option_scanf );
    nombre_segments = nb_segment( Net );
    Tab = Creer_Tableau_Segments_Netlist( Net , nombre_segments );
    if( option_scanf[0] == '1' ){ intersec_naif( Tab , nombre_segments , Net );
    }else if( option_scanf[0] == '2' ){ Intersection_Balayage_Liste_Chainee( Net , nombre_segments , Tab);
    }else if( option_scanf[0] == '3' ){ Intersection_Balayage_Avl( Net , nombre_segments , Tab);
    }else { printf("Vous auriez au moins pu vous donner la peine d'entrer une option valide.\n");
            printf( "Puisque c'est comme ça, je boude. Na!" );
            free( Tab );
            Liberation_Netlist( Net );
            free( nom_fichier_net);
            free( nom_fichier);
            free( option_scanf );
            exit( 666 );
            }
    printf( " Fini.\n" );

    free( Tab );
    Liberation_Netlist( Net );
    free( option_scanf );

    option_scanf = ( char * ) malloc ( sizeof( char ) * 256 );
    Net = Recuperer_Netlist( nom_fichier_net );
    printf( "Quel algorithme voulez-vous utiliser pour le second test?\n");
    printf("1 : Naïf\n2 : Balayage par liste chaînée\n3 : Balayage par AVL\n");
    scanf( "%s" , option_scanf );
    nombre_segments = nb_segment( Net );
    Tab = Creer_Tableau_Segments_Netlist( Net , nombre_segments );
    if( option_scanf[0] == '1' ){ intersec_naif( Tab , nombre_segments , Net );
    }else if( option_scanf[0] == '2' ){ Intersection_Balayage_Liste_Chainee( Net , nombre_segments , Tab);
    }else if( option_scanf[0] == '3' ){ Intersection_Balayage_Avl( Net , nombre_segments , Tab);
    }else { printf("Vous auriez au moins pu vous donner la peine d'entrer une option valide.\n");
            printf( "Puisque c'est comme ça, je boude. Na!" );
            free( Tab );
            Liberation_Netlist( Net );
            free( nom_fichier_net);
            free( nom_fichier);
            free( option_scanf );
            exit( 666 );
            }
    printf( " Fini.\n" );

    free( Tab );
    Liberation_Netlist( Net );
    free( nom_fichier);
    free( nom_fichier_net);
    free( option_scanf );
}

void Debug(){
    Netlist * Net;
    char * nom_fichier;
    char * nom_fichier_net;
    char * nom_fichier_int;
    int nombre_segments;
    Segment * * Tableau_segments;

    nom_fichier = demande_nom_fichier( NULL );
    nom_fichier_int = ajout_extension_nom_fichier( nom_fichier , ".int" );
    nom_fichier_net = ajout_extension_nom_fichier( nom_fichier , ".net" );

    Net = Recuperer_Netlist( nom_fichier_net );
    nombre_segments = nb_segment( Net );
    Tableau_segments = Creer_Tableau_Segments_Netlist( Net , nombre_segments );
    Intersection_Balayage_Avl( Net , nombre_segments , Tableau_segments );
    Sauvegarde_intersection( Tableau_segments , nombre_segments , nom_fichier_int );

    Liberation_Netlist( Net );
    free( Tableau_segments );
    free( nom_fichier );
    free( nom_fichier_int );
    free( nom_fichier_net );
}
