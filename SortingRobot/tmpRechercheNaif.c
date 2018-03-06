void RechercherCaseNaif_c(Grille *G, int c, int i, int j, int *k, int *l){
	int m, n;
	*k = G->n;
	*l = G->m;
	int dmin=abs(l-j)+abs(k-i);
	for (m=0; m<G->m; m++){
		for (n=0; n<G->n; n++){	//parcours de la grille
			
			if ( !caseNoire(G,m,n) && G->T[m][n].fond == c ){	//si la case est de couleur c:
				if (abs(m-i)+abs(n-j)<dmin){	//si la distance en lignes est inf.:
				    	//et la dist. en col. aussi:
						//printf("Couleur case: %d\nCouleur robot: %d\n", G->T[m][n].fond, c);
						*k = m;	//cette case est de la couleur demandée et est
						*l = n;	//plus proche au point (i,j) que la case (k_,l_)
				}
			}
			
		}
	}
	
	//si k_ ou l_ vallent m*n, cela signifie qu'il n'y a pas de case de couleur c

	
}
