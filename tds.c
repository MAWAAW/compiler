//interroge le dictionnaire, associe la valeur au symbole dans la table
#include <stdio.h>
#define MAX_TDS 8
#define TRUE 1
#define FALSE 0


#include "tds.h"

int tds[MAX_TDS];

void tdsAmorcer(){
	int i;	
	for(i=0; i<MAX_TDS; i++){
		tds[i] = 0;
	}
}
int tdsSet(int e){
// rajoute e dans le tableau de symboles tds[] sans doublons, sinon renvoie 0	
	if(!present(e)){
		tds[prochaineCaseVide()] = e;
		return TRUE;
	}
	printf("le symbole n'a pas pu être rajouté dans la TDS\n");
	return FALSE;
}
int tdsGetValeur(int i){
// renvoie valeur à l'index demandé si existant, sinon 0
	if(tds[i]){
		return tds[i];
	}
	printf("impossible de récupérer la valeur depuis le dictionnaire\n");
	return FALSE;
}
int present(int x){
// verifie presence de x dans tds[]
	int i;	
	for(i=0; i<MAX_TDS; i++){
		if (tds[i] == x) return TRUE;
	}
	printf("symbole non présent dans la TDS\n");
	return FALSE;
}
int prochaineCaseVide(){
// renvoie l'indexe de la premiere case vide, qu'on trouve dans tds[]
	int i;	
	for(i=0; i<MAX_TDS; i++){
		if(tds[i] == 0){
			return i;
		}
	}
	printf("pas de case libre dans la TDS\n");
	return FALSE;
}
