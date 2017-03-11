#include<stdio.h>
#include<stdlib.h>
#include"asynt.h"


#define NOERROR 0



int main(void)
{
	int i=1;
	int error=NOERROR;
	DicoAmorcer();//Dubois
	ErrAmorcer();// Girod
	//Mettre le texte en paramètre.
	ALexAmorcer("QUENTIN 42 10:20 01/01/01 42GG24 $ #;");//Fenouil
	printf("Test\n");
	ASyntAmorcer();//Simonnet
	ASemAmorcer();//Voisin
	GeneAmorcer();//Carpentier
	do{
		switch(i){
			case 1: error=AnalyseSynt();
			case 2: error=AnalyseSem();
			case 3:	error=GenerationCode();
		}
		i++;
	}while(i<4 && error==NOERROR);

	if(error==NOERROR){
		printf("execution sans problemes\n");
	}
	else{
		ErrAfficher(error);
	}
	exit(0);
}
