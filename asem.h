#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STRUCT
#define STRUCT 0
typedef struct date{
	int quantieme;
	int mois;
	int annee;
}date;

typedef struct heure{
        int heures;
        int minutes;
}heure;

typedef struct ticket{
	char balise;
	char* plaque;
	char* nom;
	int num;
	date d;
	heure h;
	int place;
}ticket;
#endif
int bHeureVerifier(heure* h);
int bMinutesVerifier(heure* h);
int bMoisVerifier(date* d);
int bQuantiemeVerifier(date* d);
int bDateVerifier(date* d);
int bChiffre(int iD,int *piF,char* sMOT);
int bQuantieme(int iD,int *piF,char* sMOT);
int bFF();
int bS(int iD,int *piF);
int bNumPlaceVerifier( int n );
int bAnneeBissextileVerifier( int a );
int numPersonneVerifier(ticket t);
int bGrammaireBonne();

//int quelJour(date d);
//int estUnDimanche(date d);
//int bParkingVide();

