#include <stdio.h>
#include <stdlib.h>

typedef struct _AVL{
  Seg* val;
  struct _AVL *fg;
  struct _AVL *fd;
}AVL;
