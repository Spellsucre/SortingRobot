#include<stdlib.h>
#include"Graphe.h"
#include"ListeDC.h"
#include<stdio.h>


void Graphe_init(Graphe *H, int m, int n){
  int i,j;

  H->m=m;
  H->n=n;
  H->Tsom=(Sommet***)malloc(m*sizeof(Sommet**));
  for (i=0;i<m;i++){
	H->Tsom[i]=(Sommet**)malloc(n*sizeof(Sommet*));
	for (j=0;j<n;j++)
	  H->Tsom[i][j]=(Sommet*)malloc(sizeof(Sommet));
  }

  for (i=0;i<m;i++)
	for (j=0;j<n;j++){
	  H->Tsom[i][j]->i=i;
	  H->Tsom[i][j]->j=j;
	  H->Tsom[i][j]->Lsucc=NULL;
	  H->Tsom[i][j]->visit=-1;
	}
  

}

void Graphe_ajout_arc(Graphe *H, int i1, int j1, int i2, int j2){
  Arc *a=(Arc*) malloc(sizeof(Arc));
  a->succ=H->Tsom[i2][j2];
  a->poids=(i2-i1<0?-(i2-i1):i2-i1)+(j2-j1<0?-(j2-j1):j2-j1);
  a->suiv=H->Tsom[i1][j1]->Lsucc;
  H->Tsom[i1][j1]->Lsucc=a;  
}


void Graphe_creation(Grille *G, Graphe *H){

  int i,j,k;
  CelluleLDC *cour1,*cour2;

  Graphe_init(H,G->m,G->n);

  LDC* TC=(LDC*) malloc(sizeof(LDC)*G->nbcoul);
  
  for (i=0;i<G->m;i++)
	for (j=0;j<G->n;j++){
	  if (G->T[i][j].fond!=G->T[i][j].piece)
	LDCInsererEnTete(&TC[G->T[i][j].fond],i,j);
	  else
	    H->Tsom[i][j]->visit=-2;
	}

  for (k=0;k<G->nbcoul;k++){
	cour1=TC[k].premier;
	while(cour1!=NULL){
	  cour2=TC[G->T[cour1->i][cour1->j].piece].premier;
	  while (cour2!=NULL){
	Graphe_ajout_arc(H,cour1->i,cour1->j,cour2->i,cour2->j);
	cour2=cour2->suiv;
	  }	  
	  cour1=cour1->suiv;
	}
  }
  
  for (k=0;k<G->nbcoul;k++)
	LDCdesalloue(&(TC[k]));
	  
}


void Graphe_affiche(Graphe *H){
	int i,j;
	Arc *cour;

	printf("Graphe H :\n");
	for (i=0; i<H->m; i++){
		for (j=0; j<H->n; j++){
			printf("(%d,%d) status : %d ", i, j, H->Tsom[i][j]->visit);
			if (H->Tsom[i][j]->Lsucc==NULL){
				printf(" noir\n");
			} else {
				printf(" arc vers ");
				cour = H->Tsom[i][j]->Lsucc;
				while (cour!=NULL){
					printf("(%d,%d) ", cour->succ->i, cour->succ->j);
					cour = cour->suiv;
				}
				printf("\n");
			}
		}
	}
}


