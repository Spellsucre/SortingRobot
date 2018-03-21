#ifndef AVL_H
#define AVL_H

typedef struct _AVL{
    int j;
    int hauteur;
    
    struct _AVL *fd;
    struct _AVL *fg;
} AVL;

AVL* creeAVL(int val, AVL *fg, AVL *fd);

int max(int a, int b);

AVL* insererAVL(AVL *b, int val);

void maj_hauteur(AVL *b);

AVL* equilibreAVL(AVL *b);

AVL* rotG(AVL *b);
AVL* rotD(AVL *b);

AVL *rechercheAVL(AVL *b, int val);

AVL *supprimeMaxAVL(AVL *b, int *pMax);
AVL *supprimeAVL(AVL *b, int val);

void afficherAVL(AVL *b);

void libererAVL(AVL *b);

void 
nodeToDot(AVL *b, FILE *f);
void AVLtoDot(AVL *b, int i);


#endif
