#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "Dico.h"

#define TAILLE_DICO 100
#define TAILLE_MOT 50

char Dico[TAILLE_DICO][TAILLE_MOT];

// On commence à l'index 1 du dico, l'index 0  correspond à l'absence d'un mot dans le dico
int LIBRE = 1;
// PLEIN == 0 s'il n'est pas PLEIN, -1 sinon
int PLEIN = 0;

int motVide(char * mot);
int motTropLong(char* mot);
int motFiable(char * mot);


void DicoAmorcer(){
}

int DicoEstPlein(){
// renvoi vrai si le dico est PLEIN
	return (PLEIN == -1);
}

int motVide(char* mot){
// renvoi vrai si le mot est vide
	return (strcmp(mot,"") == 0) ;
}

int motTropLong(char* mot){
// renvoi vrai si le mot est trop long
	return (strlen(mot) >= TAILLE_MOT);
}

int motFiable(char * mot){
// le mot est fiable si sa taille ne dépasse pas la taille limite d'un mot, si le mot n'est pas une chaine vide
	return ( !motVide(mot) && !motTropLong(mot) );
}

int iDicoAjouter(char * mot){
// renvoi l'index de la chaine ajoutée ou déjà présente, ou -1 si le mot n'est pas fiable, et si le dico est PLEIN
	int index;
			
	// le mot est fiable	
	if(motFiable(mot)){
		index = iDicoPresent(mot);

		// le mot est pas présent
		if( index == 0 ){
			// le dico n'est pas PLEIN
			if (!DicoEstPlein()){
				index = LIBRE;
				strcpy(Dico[index],mot);
				LIBRE++;
				PLEIN = (LIBRE >= TAILLE_DICO);
			}
			// le dico est PLEIN
			else{
				index = -1;
			}
		}
	}
	// le mot est pas fiable
	else{
		index = -1;
	}
	return index;
}

int iDicoPresent(char * mot){
// renvoie l'index de la chaine si elle est dans le dictionnaire, sinon 0
	int index;
	assert(mot);
	for(index = 1; index < LIBRE; index++)
	{
		if (strcmp(Dico[index],mot) == 0)
			return index;
	}
	index = 0;
	return index;
}

char* sDicoMot(int index){
	return Dico[index];
}

void DicoAfficher(){
	int index;
	for(index = 1; index < LIBRE; index++)
		printf("%d - %s\n",index,Dico[index]);
}

// On suppose a<b
int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}


void DicoTester()
{
	int longMot = 0;
	int indMot = 0;
	char mot[TAILLE_MOT];
	int alea = 0;
	
	srand(time(NULL)); // initialisation de rand

	for(longMot = 0; longMot < TAILLE_MOT; longMot++)
	{
		mot[0] = '\0';
		for(indMot = 0; indMot < longMot; indMot++)
		{
			alea = rand_a_b('0','}');
			//printf("chiffre : %i, lettre : %c\n", alea, alea);
			mot[indMot] = alea;
		}
		mot[indMot] = '\0';
		//printf("mot %i : %s\n",longMot , mot);
		iDicoAjouter(mot);		
	}
	
	printf("Le dico contient : \n");
	DicoAfficher();
	
}

