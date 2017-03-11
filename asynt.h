#include "asem.h"


//S->Prg.FF
int bS(int iD,int *piF);

//Prg->List
int bPrg(int iD,int *piF);

//FF->lxmFF
int bFF(int iD,int *piF);
date asyntDateDecouper(char* s);

heure asyntHeureDecouper(char* s);


//List->Mvt.Suite
int bList(int iD,int *piF);

//Suite->List+FF
int bSuite(int iD,int *piF);

//Mvt->BAL.PLQ.NOM.DATE.HEURE.PLACE
int bMvt(int iD,int *piF,int *eBAL,int *ePLQ, int* eNOM, int* eDATE, int *eHEURE, int *ePLACE );




//BAL->lxmENTREE+lxmSORTIE
int bBAL(int iD,int *piF, int *eBAL);


//PLQ->lxmPLAQUE
int bPLQ(int iD,int *piF, int *ePLQ);

//NOM->lxmLETTRE
int bNOM(int iD,int *piF, int * eNOM);
//DATE->lxmDATE
int bDATE(int iD,int *piF, int* eDATE);

//HEURE->lxmHEURE
int bHEURE(int iD,int *piF, int *eHEURE);

//ok
//PLACE->lxmCHIFFRE
int bPLACE(int iD,int *piF, int *ePLACE);



int bASyntReconnu();

/* --- */

void ASyntAmorcer();


int analyseSynt();
int analyseSem();
int generationCode();


