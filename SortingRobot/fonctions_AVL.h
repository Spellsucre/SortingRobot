#ifndef FONCTIONS_AVL_H
#define FONCTIONS_AVL_H

typedef struct _AVL{
    int j;
    int hauteur;
    
    struct _AVL *fd;
    struct _AVL *fg;
} AVL;

AVL* creeAVL(int val, AVL *fg, AVL *fd);

int max(int a, int b);
int min(int a, int b);
int distJ(int a, int b);

int hauteur(AVL *b);

void maj_hauteur(AVL *b);

AVL *creeAVL(int val, AVL *fg, AVL *fd);

AVL* insererAVL(AVL *b, int val);

AVL* equilibreAVL(AVL *b);

AVL* rotG(AVL *b);
AVL* rotD(AVL *b);

AVL *supprimeMaxAVL(AVL *b, int *pMax);
AVL *supprimeAVL(AVL *b, int val);

void afficherAVL(AVL *b);

void libererAVL(AVL *b);

void nodeToDot(AVL *b, FILE *f);
void AVLtoDot(AVL *b, int i, int j);


#endif
