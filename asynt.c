#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GenCode.h"
#include "asynt.h"
#include "asem.h"
#include "ALex.h"
#include<ctype.h>

#define ASYNT 1
#define ALEX 2
#define GENECODE 3
#define ASEM 4
#define NoErr 0


int mode=1;
int TABclass[4]={1, 2, 3, 4};
char *TABlexi[4]={"D","17","05","FF"};

//S->Prg.FF
//Prg->List
//List->Mvt.Suite
//Suite->List+FF
//Mvt->BAL.PLQ.NOM.DATE.HEURE.PLACE
//BAL->lxmENTREE+lxmSORTIE
//PLQ->lxmPLAQUE
//NOM->lxmLETTRE
//DATE->lxmDATE
//HEURE->lxmHEURE
//PLACE->lxmCHIFFRE

int ERREUR_nbArg;
int ERREUR_DString;
int ERREUR_QInt;
int ERREUR_MInt;

int ERREUR_bMvt;
int ERREUR_bSuite;
int ERREUR_bPLACE;
int ERREUR_bHEURE;
int ERREUR_bDATE;
int ERREUR_bNOM;
int ERREUR_bPLQ;
int ERREUR_bBAL;

int ErrFinal;

//S->Prg.FF
int bS(int iD,int *piF)
{
	int iM,bSucces,iF;
	bSucces=bPrg(iD,&iM)&&bFF(iM,&iF);/*doit on garder ce PGen -> y a plus vraiment de nb de param */
	*piF=(bSucces)?iF:iD;
	return(bSucces);
}

//Prg->List
int bPrg(int iD,int *piF)
{
	int bSucces;
    bSucces=bList(iD,piF);
	return(bSucces);
}


//FF->lxmFF
int bFF(int iD,int *piF)
{
	int bSucces=bALexEstFF(iALexClasse(iD));
	*piF=(bSucces)?iD+1:iD;
	return(bSucces);
}

date asyntDateDecouper(char* s){
	date d;
	d.quantieme = (s[0]-'0')*10+s[1]-'0';
	d.mois = (s[3]-'0')*10+s[4]-'0';
	d.annee = (s[6]-'0')*10+s[7]-'0';
	return d;
}

heure asyntHeureDecouper(char* s){
	heure h;
	h.heures = (s[0]-'0')*10+s[1]-'0';
	h.minutes = (s[3]-'0')*10+s[4]-'0';
	return h;
}


//List->Mvt.Suite
int bList(int iD,int *piF)
{
	int bSucces;
	int eBAL, ePLQ, eNOM, eDATE, eHEURE, ePLACE;
    int iM,iF;
    int err=0;
    if((bSucces=bMvt(iD,&iM,&eBAL,&ePLQ,  &eNOM, &eDATE, &eHEURE, &ePLACE )))
		{
				if(mode==ASEM)
				{
                    ticket t;
					t.balise = (sALexValeur(eBAL))[0];
					strcpy(t.plaque,sALexValeur(ePLQ));
					strcpy(t.nom, sALexValeur(eNOM));
					t.d = asyntDateDecouper(sALexValeur(eDATE));
					t.h = asyntHeureDecouper(sALexValeur(eHEURE));
					t.place = atoi(sALexValeur(ePLACE));
					
					pileEmpiler(t);
				}
				if(mode==GENECODE)
				{
					GCEmpilerMouvement(sALexValeur(ePLQ),sALexValeur(eNOM), asyntDateDecouper(sALexValeur(eDATE)), asyntHeureDecouper(sALexValeur(eHEURE)));
				}
                if(bSucces=bSuite(iM,&iF))
				{
					printf("");
				}
				else
				{
					if(ErrFinal==0)
						err=ERREUR_bSuite;
				}
    	}
		else
		{
			if(ErrFinal==0)
				err=ERREUR_bMvt;
		}
     if(err!=0)
    	ErrFinal=err;
    	
    *piF=(bSucces)?iF:iD;
    return(bSucces);
}


//Suite->List+FF
int bSuite(int iD,int *piF)
{
    int bSucces=bList(iD,piF)||bFF(iD,piF);
	return(bSucces);
}


//Mvt->BAL.PLQ.NOM.DATE.HEURE.PLACE
int bMvt(int iD,int *piF,int *eBAL,int *ePLQ, int* eNOM, int* eDATE, int *eHEURE, int *ePLACE )
{
	int bSucces;
	int err=0;
  int iM,iN,iO,iP,iQ,iF;
    if(bSucces=bBAL(iD,&iM,eBAL))
		{
        		if(bSucces=bPLQ(iM,&iN,ePLQ))
				{
           				 if(bSucces=bNOM(iN,&iO,eNOM))
						{
                            date d = asyntDateDecouper(sALexValeur(*eDATE));
                				if(bSucces=bDATE(iO,&iP,eDATE)&& bDateVerifier(&d))
								{
									if(mode==GENECODE)
									{
										GCFacture(asyntDateDecouper(sALexValeur(*eDATE)));
									}
                                    heure h = asyntHeureDecouper(sALexValeur(*eHEURE));
                   					if(bSucces=bHEURE(iP,&iQ,eHEURE)&&bHeureVerifier(&h))
									{
                        					if(bSucces=bPLACE(iQ,&iF,ePLACE))
											{
											 	printf("");
											}
                        					else
											{
                         						if(ErrFinal==0)
                         							err=ERREUR_bPLACE;
											}
                    					}
										else
										{
											if(ErrFinal==0)
                    							err=ERREUR_bHEURE;
										}
             					   }
								else
								{
									if(ErrFinal==0)
                						err=ERREUR_bDATE;
								}
           				 }
						else
						{
							if(ErrFinal==0)
            					err=ERREUR_bNOM;
						}
        		}
				else
				{
					if(ErrFinal==0)
        				err=ERREUR_bPLQ;
				}
   		 }
		else
		{
			if(ErrFinal==0)
    			err=ERREUR_bBAL;
		}
     if(err!=0)
    	ErrFinal=err;
    *piF=(bSucces)?iF:iD;
    return(bSucces);
}



//BAL->lxmENTREE+lxmSORTIE
int bBAL(int iD,int *piF, int *eBAL)
{
    int bSucces=bALexEstBaliseEntree(iALexClasse(iD))||bALexEstBaliseSortie(iALexClasse(iD));
    *piF=(bSucces)?iD+1:iD;
		*eBAL=(bSucces)?iD+1:iD;
    return(bSucces);
}


//PLQ->lxmPLAQUE
int bPLQ(int iD,int *piF, int *ePLQ)
{
    int bSucces=bALexEstPlaque(iALexClasse(iD));
    *piF=(bSucces)?iD+1:iD;
		*ePLQ=(bSucces)?iD+1:iD;
    return(bSucces);
}


//NOM->lxmLETTRE
int bNOM(int iD,int *piF, int * eNOM)
{
    int bSucces=bALexEstLettre(iALexClasse(iD));
    *piF=(bSucces)?iD+1:iD;
		*eNOM=(bSucces)?iD+1:iD;
    return(bSucces);
}


//DATE->lxmDATE
int bDATE(int iD,int *piF, int* eDATE)
{
    int bSucces=bALexEstDate(iALexClasse(iD));
    *piF=(bSucces)?iD+1:iD;
		*eDATE=(bSucces)?iD+1:iD;
    return(bSucces);
}


//HEURE->lxmHEURE
int bHEURE(int iD,int *piF, int *eHEURE)
{
    int bSucces=bALexEstHeure(iALexClasse(iD));
    *piF=(bSucces)?iD+1:iD;
		*eHEURE=(bSucces)?iD+1:iD;
    return(bSucces);
}


//PLACE->lxmCHIFFRE
int bPLACE(int iD,int *piF, int *ePLACE)
{
    int bSucces=bALexEstChiffre(iALexClasse(iD));
    *piF=(bSucces)?iD+1:iD;
		*ePLACE=(bSucces)?iD+1:iD;
    return(bSucces);
}


int bASyntReconnu()
{
	int bReconnu;
	int Fin;
	
	bReconnu=bS(0,&Fin);
	
	return(bReconnu);
}

/* --- */

void ASyntAmorcer()
{
	/*ERREUR_bMvt=ErrTraiter("ERREUR_nbArg");
	ERREUR_bSuite=ErrTraiter("ERREUR_nbArg");
	ERREUR_bPLACE=ErrTraiter("ERREUR_nbArg");
	ERREUR_bHEURE=ErrTraiter("ERREUR_nbArg");
 	ERREUR_bDATE=ErrTraiter("ERREUR_nbArg");
 	ERREUR_bNOM=ErrTraiter("ERREUR_nbArg");
 	ERREUR_bPLQ=ErrTraiter("ERREUR_nbArg");
	ERREUR_bBAL=ErrTraiter("ERREUR_nbArg");*/
	
}

int AnalyseSynt()
{
	mode=ASYNT;
	int bSucces=bASyntReconnu();
	if(bSucces)
		return NoErr;
	else
		return ErrFinal;
}
int AnalyseSem()
{
	mode=ASEM;
	int bSucces=bASyntReconnu();
	if(bSucces)
		return NoErr;
	else
		return ErrFinal;
}
int generationCode()
{
	mode=GENECODE;
	int bSucces=bASyntReconnu();
	if(bSucces)
		return NoErr;
	else
		return ErrFinal;
}


