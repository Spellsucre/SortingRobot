#include<stdlib.h>
#include<stdio.h>

#include "ListeDC.h"
#include "Lcircuit.h"

Cell_circuit* creerCell_circuit(LDC *L){
  Cell_circuit* e =(Cell_circuit*)malloc(sizeof(Cell_circuit));
  e->suiv=NULL;  /* Inutile mais bon reflexe */
  e->L=*L;
  e->jmin=-1;
  e->jmax=-1;
  return e;

}

void LcircuitInitialise(Lcircuit *Lcircuit){
  Lcircuit->premier=NULL;
  Lcircuit->dernier=NULL;
  Lcircuit->nb_circuit=0;
}

int LcircuitVide(Lcircuit* Lcircuit){
 return (Lcircuit->premier==NULL);
}

void LcircuitInsererEnTete(Lcircuit* Lcircuit, LDC *L){
  Cell_circuit* nouv=creerCell_circuit(L);
  if (LcircuitVide(Lcircuit)) 
    Lcircuit->dernier=nouv;
  nouv->suiv=Lcircuit->premier;
  Lcircuit->premier=nouv;
}


void LcircuitInsererEnFin(Lcircuit* Lcircuit, LDC *L){
  Cell_circuit* nouv=creerCell_circuit(L);
  if (LcircuitVide(Lcircuit)) 
    Lcircuit->premier=nouv;
  else 
    Lcircuit->dernier->suiv=nouv;
  nouv->suiv=NULL;
  Lcircuit->dernier=nouv;
}

void LcircuitenleverCellule(Lcircuit* Lcircuit, Cell_circuit* c){
  free(c);
}

void Lcircuitafficher(Lcircuit* Lcircuit){
  Cell_circuit* cour= Lcircuit->premier;
  while(cour != NULL) {
    LDCafficher(&(cour->L));
    cour=cour->suiv;
  }
  printf("\n");
}

void Lcircuitdesalloue(Lcircuit *Lcircuit){
  Cell_circuit *cour, *mort;
  cour=Lcircuit->premier;
  while(cour!=NULL){
    LDCdesalloue(&(cour->L));
    mort=cour;
    cour=cour->suiv;
    free(mort);
  }
  Lcircuit->premier=NULL;
  Lcircuit->dernier=NULL;

}
