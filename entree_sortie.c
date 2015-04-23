#include "entree_sortie.h"
#include <string.h>
#include <ctype.h>


/*LIT LE PROCHAIN CARACTERE NON VIDE */
char ReadChar(FILE *f){
    char c ;
    do
        c = getc(f) ;
    while (isspace(c)) ;
    return c ;
}

/* SAUT DES ESPACES LORS DE LA LECTURE DANS UN FICHIER POINTE PAR f */

void Skip(FILE *f) {

    char c ;

    while (isspace(c=getc(f))) ;
    ungetc(c,f) ;

}

/* LECTURE DES CARACTERES JUSQU'A LA FIN DU FICHIER OU DE LA LIGNE */

void SkipLine(FILE *f){
    char c ;

    do
        c = getc(f) ;
    while ((c!=EOF)&&(c!='\n')) ;

}

/* LECTURE DE CHAINE DE CARACTERES JUSQU'A UN ESPACE, LA FIN DE LA LIGNE OU LA FIN DE FICHIER */

void GetChaine(FILE *f,int taille_max,char *s)
{
    char c ;
    int i;

    Skip(f) ;
    i=0;
    c = getc(f) ;
    while (!(isspace(c))&&(c!=EOF)&&(c!='\n')&&(i<taille_max-1)){
        s[i]=c;
        c = getc(f) ;    
        i++;
    }
    s[i]='\0';
    ungetc(c,f) ;
}

/* LECTURE ET TRANSFORMATION DE CARACTERES EN ENTIERS */

int GetEntier(FILE *f)  {
    char c ;
    int v, sign ;

    c = ReadChar(f) ;
    v = 0 ;
    sign = 0 ;
    if (c=='-')
    {
        sign=1 ;
        c = getc(f) ;
    }
    if (c=='.')
        c = getc(f) ;
    while ((isdigit((int)c)&&(c!='.')))
    {
        v = 10*v+(c-'0') ;
        c = getc(f) ;
    }
    if (sign)
        v = -1*v ;
    ungetc(c,f) ;
    return v ; 
}

/* LECTURE ET TRANSFORMATION DE CARACTERES EN ENTIERS REELS */

double GetReel(f)
    FILE *f;
{
    char c, ReadChar();
    int v,v1,puiss,i, sign;
    double nbr;
    int entrer;

    c = ReadChar(f);
    sign = 0;
    v = 0;v1=0;

    if (c == '-'){
        sign = 1;
        c = getc(f);
    }
    puiss=0;entrer=0;
    while (isdigit(c)){

        if(entrer)
        {
            v1=10*v1 + (c - '0');
            c = getc(f);
            puiss++;

        }
        else
        {    
            v = 10*v + (c - '0');
            c = getc(f);
        } 
        if(c=='.') {
            c=getc(f); 
            entrer=1;
        } 
    }
    nbr=v1;

    for(i=0;i<puiss;i++)
        nbr=nbr/10;

    nbr=nbr+v;  
    if (sign)
        nbr = -1*nbr;

    ungetc(c, f);
    return nbr;
}


char* Extension(char* name, char* extension){

    int i,j;
    long name_long = strlen(name);
    long extension_long = strlen(extension);
    char *nom = calloc(name_long, sizeof(char));
    // creation du nom du fichier
    for (i = 0; i < name_long; i++)
    {
        nom[i] = name[i];
    }
    // ajout de l'extension
    for (j = 0; j < extension_long; j++){
        nom[i+j] = extension[j];
    }
    return nom;
}


char* Lire_Entree_Standard(char* extension){

    char* nom;

    printf("Donnez le nom de votre fichier\n");
    nom =  malloc(256*sizeof(char));
    scanf("%s", nom);
    nom = Extension(nom, extension);
    return nom;
}
