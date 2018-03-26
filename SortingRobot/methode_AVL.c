#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fonctions_base.h"
#include "methode_AVL.h"
#include "methode_circulaire.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
t_AVL *creer_t_AVL(int nbcoul, int nblig){
	int c, i;
	
	//malloc de t_AVL*
	t_AVL *tavl = malloc(sizeof(t_AVL));
	if (!tavl) { printf("Erreur lors de l'allocation"); return NULL; }
	tavl->nbcoul = nbcoul;
	tavl->nblig = nblig;
	
	//malloc de M[nbcoul][nblig]
	tavl->M = malloc( sizeof(AVL**) * nbcoul );
	if (!tavl->M) { printf("Erreur lors de l'allocation"); return NULL; }
	for (i=0; i<nbcoul; i++){
		tavl->M[i] = malloc( sizeof(AVL*) * nblig );
		if (!tavl->M[i]) { printf("Erreur lors de l'allocation"); return NULL; }
	}
	
	//init des AVL* à NULL
	for (c=0; c<nbcoul; c++){
		for (i=0; i<nblig; i++){
			tavl->M[c][i] = NULL;
		}
	}

	return tavl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
t_AVL *initialiser_t_AVL(Grille *G){
	int c, m, n;
	
	t_AVL *tavl = creer_t_AVL(G->nbcoul, G->m);
	tavl->cptr_noire = G->cptr_noire;
	
    for (m=0; m<G->m; m++){
		for (n=0; n<G->n; n++){
			if( caseNoire(G, m, n) ) continue;
		    c = G->T[m][n].fond;	    
		    tavl->M[c][m] = insererAVL(tavl->M[c][m], n);
        }
    }
	
	return tavl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ok??
void liberer_t_AVL(t_AVL *tavl){
	int c, i;
	if (!tavl) return;
	
	for (c=0; c < tavl->nbcoul; c++){
		for (i=0; i < tavl->nblig; i++){
			libererAVL(tavl->M[c][i]);
		}
	}
	free(tavl);
}
/*
    if(!b){
        return -1;
    }
    if(b->fg && b->fd ){
        if (dMin > distJ(b->fg->j,l)){
            return AVLrecherche;
        }
        else if (dCour > distJ(b->fd->j,l)){
            continue;
        }
        else
            break;
    }
    else if (b->fg && dCour > distJ(b->fg->j,l)){
        continue;
    }
    else if (b->fd && dCour > distJ(b->fd->j,l)){
        cour=b->fd;
        continue;
    }
    else
        break;
*/

int AVLrechercheJ(AVL *b, int l, int dMin){
    if(!b) return -1;
    if(b->fg && b->fd){
        if(distJ(b->fg->j,l) > distJ(b->fd->j,l)){
            if(dMin > distJ(b->fd->j,l)){
                dMin=distJ(b->fd->j,l);
                return AVLrechercheJ(b->fd, l, dMin);
            }
        }
        else{
            if(dMin > distJ(b->fg->j,l)){
                dMin=distJ(b->fg->j,l);
                return AVLrechercheJ(b->fg, l, dMin);
            } 
        }           
    }else if (b->fg && dMin > distJ(b->fg->j,l)){
        dMin=distJ(b->fg->j,l);
        return AVLrechercheJ(b->fg, l, dMin);
    }
    else if (b->fd && dMin > distJ(b->fd->j,l)){
        dMin=distJ(b->fd->j,l);
        return AVLrechercheJ(b->fd, l, dMin);
    }
    return b->j;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void AVLrechercherPlusProcheCase(t_AVL *tavl, int c, int k, int l, int *u, int *v){
	if (!tavl){ printf("tavl non existant"); return; }
	
	int jtmp, dMin, dCour, cpt=0;
	AVL *cour;
	
	*u= tavl->nblig * tavl->nblig; *v = tavl->nblig * tavl->nblig;
    dMin = distance(k,l,*u,*v);
    
    
    while (k+cpt < tavl->nblig || k-cpt >= 0){
        
        if(k+cpt < tavl->nblig){
            cour = tavl->M[c][k+cpt];
            
            jtmp = AVLrechercheJ(cour, l, dMin);
            dCour = distance(k, l, k+cpt, jtmp);
            if(dCour<dMin){
                dMin=dCour;
                *u=k+cpt;
                *v=jtmp;
            }
        }
        
        if (k-cpt >= 0){
            cour = tavl->M[c][k-cpt];
            
            jtmp = AVLrechercheJ(cour, l, dMin);
            dCour = distance(k, l, k-cpt, jtmp);
            if(dCour<dMin){
                dMin=dCour;
                *u=k-cpt;
                *v=jtmp;
            }
        }
        cpt++;

        
    }
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ok??
void algorithme_AVL(Grille *G, Solution *S){
	if (!G){ printf("Grille NULL, fin algo AVL"); return; }
	if (!S){ printf("Solution NULL, fin algo AVL"); return; }
	
	int c, u, v;
	
	t_AVL * tavl = initialiser_t_AVL(G);
	
	//application de l'algorithme
	while ( !grilleTerminee(G) ){
		if( !robotPortePiece(G) ){
		    RechercherCaseCirculaire_nn( G, G->ir, G->jr, &u, &v );
		    PlusCourtChemin( S, G->ir, G->jr, u, v);
		    changement_case(G, u, v);
		}else{
			AVLrechercherPlusProcheCase(tavl, getCouleurPieceRobot(G), G->ir, G->jr, &u, &v);
			PlusCourtChemin( S, G->ir, G->jr, u, v);
			changement_case(G, u, v);
			
			c = getCouleurPieceRobot(G);
			tavl->M[c][u] = supprimeAVL(tavl->M[c][u], v);
		}
		swap_case(G);
		Ajout_action( S, 'S');
	}
	
	liberer_t_AVL(tavl);
}


