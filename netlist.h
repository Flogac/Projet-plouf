#include<stdio.h>
#include<stdlib.h>

struct segment;

typedef struct cell_segment{
  struct segment* seg;
  struct cell_segment *suiv;
} Cell_segment;

typedef struct segment
{
  int NumRes;
  int p1,p2;
  int HouV;//H=0,V=1
  struct cell_segment *Lintersec;
} Segment;

typedef struct point
{
  int x,y;
  int num_res;
  Cell_segment *Lincid;
} Point;

typedef struct reseau
{
  int NumRes;
  int NbPt;
  int NbSeg; //Nombre de segment
  Point* *T_Pt;
  Segment * *T_Seg; // Tableau de segment
} Reseau;

typedef struct netlist
{
  int Nbres;
  int Nbex; //Nombres etremites
  Reseau* *T_Res;
} Netlist;
