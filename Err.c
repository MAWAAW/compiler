#include"Dico.h"

#include<stdio.h>
#include<stdlib.h>

void ErrAfficher(int i)
{
	printf("Le mot est : %s\n",sDicoMot(i));
}


int ErrTester()
{
	char* s="test";
	DicoTester();
	int i=iDicoPresent(s);
	ErrAfficher(i);
	return i;
}

void ErrAmorcer(char *s)
{
	int i=iDicoPresent(s);
	//printf("le mot %s se situe à l'index: %i\n",ErrAfficher(i),i);
	//Rajouter par PA
	
}


