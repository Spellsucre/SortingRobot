#ifndef __ENSEMBLE_H__
#define __ENSEMBLE_H__

// Structure de liste doublement chainee
// contenant deux entiers i et j

typedef struct elem_ensemble{
  int i,j; // Elements stockes dans la liste
  int indice;
} ElemEnsemble;

typedef struct {
    int taille;
    int nbElem;
    ElemEnsemble **tab;
} Ensemble;



/* Alloue et retourne une cellule */
ElemEnsemble* creerElem(int i, int j, int indice);

void EnsembleInitialise(Ensemble *Ensemble);

/* Test si liste vide */
int EnsembleVide(Ensemble* Ensemble);

void EnsembleAdd(Ensemble* E, int i,int j);

void EnsemblePop(Ensemble* E, ElemEnsemble * el);

void Ensembleafficher(Ensemble* E);

void Ensembledesalloue(Ensemble* E);

#endif
