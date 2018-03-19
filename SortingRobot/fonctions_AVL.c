#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "methode_AVL.h"


int max(int a, int b){
    return (b>a?b:a);
}


void maj_hauteur(AVL *b){
    if(!b)
        return;
    if(!b->fg && !b->fd){
        b->hauteur=0;
        return;
    }
    maj_hauteur(b->fg);
    maj_hauteur(b->fd);
    b->hauteur= max(b->fg->hauteur, b->fd->hauteur) + 1;
}


AVL* equilibreAVL(AVL *b){
    if( (b->fg->hauteur) - (b->fd->hauteur) == 2 ){
        if( (b->fg->fg->hauteur) > (b->fg->fd->hauteur) )
            rotG(b->fg);
        rotD(b);
    }
    
    if( (b->fg->hauteur) - (b->fd->hauteur) == -2 ){
        if( (b->fd->fg->hauteur) > (b->fd->fd->hauteur) )
            rotG(b->fd);
        rotD(b);
    }

    
    return b;
}


AVL* rotG(AVL *b){
    AVL *nvb=b->fd;
    
    b->fd=nvb->fg;
    nvb->fg=b;
    
    maj_hauteur(b);
    maj_hauteur(nvb);
    
    return nvb;
}


AVL* rotD(AVL *b){
    AVL *nvb=b->fg;
    
    b->fg=nvb->fd;
    nvb->fd=b;
    
    maj_hauteur(b);
    maj_hauteur(nvb);
    
    return nvb;
}


AVL* creeAVL(int val, AVL *fg, AVL *fd){
    AVL* n = malloc( sizeof(AVL) );
    
    n->j = val;
    n->fg = fg;
    n->fd = fd;
    n->hauteur = max(fg->hauteur, fd->hauteur) + 1;
    return n;
}


AVL* insererAVL(AVL *b, int val){
    if(!b)
        return creeAVL(val, NULL, NULL);
    if(val<b->j){
        if(!b->fg){
            AVL *nv= creeAVL(val, NULL, NULL);
            b->fg = nv;
        } else
            b->fg = insererAVL(b->fg, val);
    } else {
        if(!b->fd){
            AVL *nv= creeAVL(val, NULL, NULL);
            b->fd = nv;
        } else
            b->fd = insererAVL(b->fd, val);
    }
    maj_hauteur(b);
    b=equilibreAVL(b);
    return b;
}


AVL *rechercheAVL(AVL *b, int val){
    if (!b) return NULL;
    if (b->j == val) return b;
    
    if (b->j > val) return rechercheAVL(b->fg, val);
    else return rechercheAVL(b->fd, val);
}


AVL *supprimeMaxAVL(AVL *b, int *pMax){
    if (!b->fd){
        *pMax = b->j;
        AVL *res = b->fg;
        free(b);
        return res;
    }else{
        b->fd = supprimeMaxAVL(b->fd, pMax);
        return b;
    }
}


AVL *supprimeAVL(AVL *b, int val){
    AVL *res = b;
    
    if (b->j < val){
        b->fg = supprimeAVL(b->fg, val);
    }else if (b->j > val){
        b->fd = supprimeAVL(b->fd, val);
    }else{
        if (!b->fg){
            res = b->fd;
            free(b);
        }else{
            int max;
            b->fg = supprimeMaxAVL(b->fg, &max);
            b->j = max;
        }
    }
    
    return res;
}




