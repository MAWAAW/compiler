#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ************************************************** *
 *			Fonctions Booléennes de classe			  *
 * ************************************************** */

int bALexEstChiffre(int classe);
//retournent vrai si la classe passée en paramètre correspond à celle d'une suite de chiffres

int bALexEstLettre(int classe);
//retournent vrai si la classe passée en paramètre correspond à celle d'une suite de lettres

int bALexEstFF(int classe) ;
//retournent vrai si la classe passée en paramètre correspond à celle de la fin de fichier

int bALexEstInconnu(int classe);
//retournent vrai si la classe passée en paramètre correspond à celle d'un léxème inconnu

int bALexEstDate(int classe);
//retournent vrai si la classe passée en paramètre correspond à celle d'une date

int bALexEstPlaque(int classe);
//retournent vrai si la classe passée en paramètre correspond à celle d'une plaque d'immatriculation

int bALexEstHeure(int classe);
//retournent vrai si la classe passée en paramètre correspond à celle d'une heure

int bALexEstBaliseEntree(int classe);
//retournent vrai si la classe passée en paramètre correspond à celle de la balise d'entrée

int bALexEstBaliseSortie(int classe);
//retournent vrai si la classe passée en paramètre correspond à celle de la balise de sortie


/* **************************************************** *
 * 		Fonctions d'accès aux classes et valeurs		*
 * **************************************************** */
int iALexClasse(int ind);
//retourne la classe de la cellule dont l'indice est passé en paramètre

int iAlexValeur(int ind);
//retourne la valeur de la cellule dont l'indice est passé en paramètre

char* sALexValeur(int ind);

/* **************************************************** *
 * 				Fonction de test						*
 * **************************************************** */


/* **************************************************** *
 * 		Fonction d'amorçage de l'analyse Lexicale		*
 * **************************************************** */
void ALexAmorcer(char * s);
//analyse la chaine de caractères passée en paramètre

