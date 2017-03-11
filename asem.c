#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "grammaire.h"
#include "ALex.h"
#include "asem.h"

int cpt = 0;

int bHeureVerifier(heure* h){
//on exclut 24h00 
		if(  h->heures>=4 && h->heures<24 && bMinutesVerifier(h))
			return 1;
		return 0;
}
int bMinutesVerifier(heure* h){
		if(  h->minutes>=0 && h->minutes<60)
			return 1;
		return 0;
}
int bMoisVerifier(date* d){
		if(d->mois<12)
			return 1;
		return 0;
}
int bQuantiemeVerifier(date* d){
		if(d->quantieme<=31)
			return 1;
		return 0;
}

int bAnneeBissextileVerifier( int a ) {
        if( a%400 == 0 ) {
                return 1;
        } else if( a%100 == 0 ) {
                return 0;
        } else if( a%4 == 0 ) {
                return 1;
        } else {
                return 0;
        }
}

int bDateVerifier(date* d)
{
	if(bQuantiemeVerifier(d) && bMoisVerifier(d)){
		switch(d->mois){
			case 2: if((d->quantieme <=28 && !bAnneeBissextileVerifier(d->annee))||(d->quantieme <=29 && bAnneeBissextileVerifier(d->annee)))return 1;break; //Fevrier
			case 4: if(d->quantieme <=30)return 1;break; //Avril
			case 6: if(d->quantieme <=30)return 1;break; //Juin
			case 9: if(d->quantieme <=30)return 1;break; // Septembre
			case 11: if(d->quantieme <=30)return 1;break; //Novembre
		}
	}
	return 0;
}

int bNumPlaceVerifier( int n ) {
        return ( 0 < n && n <= 500 );
}

/*
int quelJour(date d){
	int kAn2013=1;
	int referencesMois[12]={-1,0,3,3,6,1,4,6,2,5,0,3,5};
	int jour=d->quantieme;
	int mois= referencesMois[d->mois];
	return (mois+jour+kAn2013)%7;
}
int estUnDimanche(date d){
	return (quelJour(d)==0);
}
int bParkingVide() {      
        return( cpt == 0 );
}
*/ 
int numPersonneVerifier(ticket t){
	int numero=t.place;
	return(numero<=500);
}

void ASemAmorcer(){
    
}
