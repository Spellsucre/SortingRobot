#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "exo1.h"
#include "Solution.h"

int main(){

	Solution S;
	Solution_init(&S);
	
	PlusCourtChemin(&S, 2, 3, 0, 0);

    Affiche(&S);

	return 0;
}
