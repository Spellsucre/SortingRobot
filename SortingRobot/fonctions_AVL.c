#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fonctions_AVL.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int max(int a, int b){
    return (b>a?b:a);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void maj_hauteur(AVL *b){
    if (!b) return;
    if (!b->fg && !b->fd){
        b->hauteur = 0;
        return;
    }
    
    maj_hauteur(b->fg);
    maj_hauteur(b->fd);
    
    int hg=0, hd=0;
    if (b->fg) hg = b->fg->hauteur;
    if (b->fd) hd = b->fd->hauteur;
    b->hauteur = max(hg, hd) + 1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AVL *rotG(AVL *b){
    AVL *nvb = b->fd;
    
    b->fd = nvb->fg;
    nvb->fg = b;
    
    maj_hauteur(b);
    maj_hauteur(nvb);
    
    return nvb;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AVL *rotD(AVL *b){
    AVL *nvb = b->fg;
    
    b->fg = nvb->fd;
    nvb->fd = b;
    
    maj_hauteur(b);
    maj_hauteur(nvb);
    
    return nvb;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AVL *equilibreAVL(AVL *b){
	if (!b) return NULL;
	
    if ( b->fg && b->fd &&
    	(b->fg->hauteur - b->fd->hauteur) == 2 ){
        if ( b->fg->fg && b->fg->fd &&
        	(b->fg->fg->hauteur) < (b->fg->fd->hauteur) ) b=rotG(b->fg);
        b=rotD(b);
    }
    
    if ( b->fg && b->fd &&
    	(b->fg->hauteur - b->fd->hauteur) == -2 ){
        if ( b->fd->fg && b->fd->fd &&
        	(b->fd->fg->hauteur) > (b->fd->fd->hauteur) ) b=rotD(b->fd);
        b=rotG(b);
    }
	
	maj_hauteur(b);
    return b;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AVL *creeAVL(int val, AVL *fg, AVL *fd){
    AVL *n = malloc( sizeof(AVL) );
    if (!n) { printf("pb allocation memoire"); return NULL; }
    
    n->j = val;
    n->fg = fg;
    n->fd = fd;
    n->hauteur = 1;
    
    int hg=0, hd=0;
    if (fg) hg += fg->hauteur;
    if (fd) hd += fd->hauteur;
    n->hauteur = max(hg, hd) +1 ;
    return n;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AVL *insererAVL(AVL *b, int val){
    if (!b) return creeAVL(val, NULL, NULL);
    
    if (val < b->j){
        if (!b->fg){
            AVL *nv= creeAVL(val, NULL, NULL);
            b->fg = nv;
        } else {
            b->fg = insererAVL(b->fg, val);
        }
    } else {
        if (!b->fd){
            AVL *nv= creeAVL(val, NULL, NULL);
            b->fd = nv;
        } else {
        	b->fd = insererAVL(b->fd, val);
		}
    }
    
    maj_hauteur(b);
    
    b = equilibreAVL(b);
    
    return b;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AVL *rechercheAVL(AVL *b, int val){
    if (!b) return NULL;
    if (b->j == val) return b;
    
    if (b->j > val) return rechercheAVL(b->fg, val);
    else return rechercheAVL(b->fd, val);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AVL *supprimeMaxAVL(AVL *b, int *pMax){
	if (!b) return NULL;
	
    if (!b->fd){
        *pMax = b->j;
        AVL *res = b->fg;
        free(b);
        return res;
    } else {
        b->fd = supprimeMaxAVL(b->fd, pMax);
        return b;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AVL *supprimeAVL(AVL *b, int val){
	if (!b) return NULL;
    AVL *res = b;
    
    if (b->j > val){
        b->fg = supprimeAVL(b->fg, val);
    } else if (b->j < val){
        b->fd = supprimeAVL(b->fd, val);
    } else {
        if (!b->fg){
            res = b->fd;
            free(b);
        } else {
            int max;
            b->fg = supprimeMaxAVL(b->fg, &max);
            b->j = max;
        }
    }
    
    res = equilibreAVL(res);
    
    return res;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void afficherAVL(AVL *b){
	if (!b) return;
	afficherAVL(b->fg);
	printf("%d ", b->j);
	afficherAVL(b->fd);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void libererAVL(AVL *b){
	if (!b) return;
	libererAVL(b->fg);
	libererAVL(b->fd);
	free(b);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void nodeToDot(AVL *b, FILE *f){
	if (!b) return;
	
	if (b->fg) fprintf(f, "\t%d--%d;\n", b->j, b->fg->j);
	if (b->fd) fprintf(f, "\t%d--%d;\n", b->j, b->fd->j);
	
	if (b->fg || b->fd)
		fprintf(f, "\t%d [label=\"%d\\nh=%d\"];\n", b->j, b->j, b->hauteur);
	else
		fprintf(f, "\t%d [label=\"%d\\nh=%d\", color=blue];\n", b->j, b->j, b->hauteur);
	
	nodeToDot(b->fg, f);
	nodeToDot(b->fd, f);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void AVLtoDot(AVL *b, int i){
	if (!b) { printf("Arbre vide, conversion .dot impossible\n"); return; }
	char str_dot[32], str_ps[32], str[256];
	sprintf(str_dot, "graphviz/graph_%d.dot", i);
	sprintf(str_ps, "graphviz/graph_%d.ps", i);
	
	FILE *f = fopen(str_dot, "w");
	fprintf(f, "graph G {\n\tnode [shape=circle];\n");
	
	nodeToDot(b, f);
	
	fprintf(f, "}");
	fclose(f);
	
	sprintf(str, "dot -Tps -o %s %s", str_ps, str_dot);
	system(str);
}


