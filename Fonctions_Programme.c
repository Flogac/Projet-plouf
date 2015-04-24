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

void Debug(){
}
