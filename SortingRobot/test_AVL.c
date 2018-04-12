#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fonctions_AVL.h"

int main(){
    
    int i, val;
    
    srand(time(NULL));

    AVL *b = NULL;
    
    //int tab[] = {1,0,3,2,4};
	
	for (i=0; i<20; i++){
		val = rand()%300;
		//val = tab[i];
		b = insererAVL(b, val);
		
		printf("nb_val = %d\n", i+1);
		printf("val = %d\n", val);
		afficherAVL(b);
		printf("\nhauteur = %d\n", b->hauteur);
		printf("\n\n");
		
		//AVLtoDot(b, i+1, 0);
	}
	
	AVLtoDot(b, 0, 0);
/*
	b = supprimeAVL(b, 1);
	AVLtoDot(b, 10, 1);
	
	b = supprimeAVL(b, 4);
	AVLtoDot(b, 11, 4);
*/	
	
	libererAVL(b);
	
    return 0;
}
