#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fonctions_AVL.h"

int main(){
    
    int i, val;
    
    srand(time(NULL));

    AVL *b = NULL;
    
    //int tab[] = {7,6,9,2,3,4,5,8,10,1};
	
	for (i=0; i<30; i++){
		val = rand()%300;
		//val = tab[i];
		b = insererAVL(b, val);
		
		printf("nb_val = %d\n", i+1);
		printf("val = %d\n", val);
		afficherAVL(b);
		printf("\nhauteur = %d\n", b->hauteur);
		printf("\n\n");
		
		AVLtoDot(b, i+1, 0);
	}
	/*
	AVLtoDot(b, 1);
	
	int v = 6;
	AVL *res = rechercheAVL(b, v);
	
	
	printf("res = %d\n", res!=NULL?(res->j):-1 );
	
	b = supprimeAVL(b, v);
	b = insererAVL(b, v);
	AVLtoDot(b, 2);
	*/
	
	
	libererAVL(b);
	
    return 0;
}
