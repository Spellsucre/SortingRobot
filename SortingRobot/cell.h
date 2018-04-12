#ifndef CELL_H
#define CELL_H

typedef struct celluleLDC{
    int i,j;
    struct celluleLDC* prec;
    struct celluleLDC* suiv;
} CelluleLDC;

typedef struct{
    CelluleLDC* premier;
    CelluleLDC* dernier;
} LDC;

CelluleLDC* creerCellule(int i, int j);

void LDCInitialise(LDC *ldc);

int LDCvide(LDC *ldc);

void LDCInsererEnFin(LDC *ldc, int i, int j);

void LDCEnleverCellule(LDC* ldc, CelluleLDC *cel);

void LDCafficher(LDC *ldc);

void LDCdesalloue(LDC *ldc);

#endif
