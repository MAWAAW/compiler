#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
//les classes de lexemes.
typedef enum {	FinFichier=0,
				Lettre=1, 
				Chiffre=2, 
				Inconnu=3,
				Espace=4, 
				Date=5,
				Plaque=6, 
				Heure=7, 
				Entree=8, 
				Sortie=9,
				ErreurLettre=10,
				ErreurChiffre=11,
				ErreurPlaque=13,
				ErreurHeure=14,
				ErreurDate=15
				} LEXEME;

int valeur[100];	//Valeur des lexèmes pour interprétation
LEXEME classe[100];	//Classe des Lexèmes (0=FF, 1=mot, 2=nombre, 3=inconnu)
int indice=0;		
int AEF[9][21];
char *sAEF[26];
char sValeur[100][100];

/* *****************************************************************************
------------------------------------Remplir l'AEF-------------------------------
***************************************************************************** */
//Utilise les chaines de caractère définies dans init pour l'appel à l'AEF dans la fonction ALex
int Decouper(char* sTexte, int Item)
// Transforme l'item numéro Item (de taille 4) de la chaine sTexte en entier
// Renvoie 0 si l'item n'existe pas
{
        // Vérifie que le mot est un multiple de 4
        assert(strlen(sTexte) % 4 == 0);

        int nEmpan=4;
        char tmp[nEmpan+1]; // +1 pour le '\0'
        int debMot = nEmpan*(Item-1);
        int indTmp = 0;
        int res = 0;

        if(debMot >= strlen(sTexte)) // Si on veut un item qui n'est pas présent dans la chaine sTexte
        {
                printf("L'item %i est introuvable !\n", Item);
                return 0;
        }

        for(indTmp = 0; indTmp<nEmpan; indTmp++)
        {
                tmp[indTmp] = sTexte[debMot];
                debMot++;
        }
        tmp[indTmp] = '\0';

        return (res = atoi(tmp));
}

//initialise L'AEF  qui sera utilisé et les tableaux valeur et classe
void init()
{
	sAEF[0]=	"   1   2   4   4   0 -10   4  19  20";
	sAEF[1]=	"   1  21  21  21  -1  -1  21  21  21";
	sAEF[2]=	"  22   3  22  22  -2  -2  22  22  22";
	sAEF[3]=	"   5   8   6   7  -2  -2  22  22  22";
	sAEF[4]=	"   4   4   4   4  -3  -3   4   4   4";
	sAEF[5]=	"   9  23  23  23  -3  -3  23  23  23";
	sAEF[6]=	"  24  10  24  24  -3  -3  24  24  24";
	sAEF[7]=	"  25  11  25  25  -3  -3  25  25  25";
	sAEF[8]=	"  22   8  22  22  -2  -2  22  22  22";
	sAEF[9]=	"  23  12  23  23  -3  -3  23  23  23";
	sAEF[10]=	"  24  13  24  24  -3  -3  24  24  24";
	sAEF[11]=	"  25  14  25  25  -3  -3  25  25  25";
	sAEF[12]=	"  23  15  23  23  -3  -3  23  23  23";
	sAEF[13]=	"  24  24  24  24  -7  -7  24  24  24";
	sAEF[14]=	"  25  25  25  16  -3  -3  25  25  25";
	sAEF[15]=	"  23  23  23  23  -6  -6  23  23  23";
	sAEF[16]=	"  25  17  25  25  -3  -3  25  25  25";
	sAEF[17]=	"  25  18  25  25  -3  -3  25  25  25";
	sAEF[18]=	"  25  25  25  25  -5  -5  25  25  25";
	sAEF[19]=	"   4   4   4   4  -8  -8   4   4   4";
	sAEF[20]=	"   4   4   4   4  -9  -9   4   4   4";
	sAEF[21]=	"  21  21  21  21 -11 -11  21  21  21";
	sAEF[22]=	"  22  22  22  22 -12 -12  22  22  22";
	sAEF[23]=	"  23  23  23  23 -13 -13  23  23  23";
	sAEF[24]=	"  24  24  24  24 -14 -14  24  24  24";
	sAEF[25]=	"  25  25  25  25 -15 -15  25  25  25";
    
	indice=0;
	int i,j;
	for(i=0;i<100;i++)
	{	
		valeur[i]=-1;
		classe[i]=0;
	}
}

int estLettre(char c)
{
	return (c>='A' && c<='Z');
}

int estChiffre(char c)
{
	return (c>='0' && c<='9');
}

int estFF(char c)
{
	return(c == ';');
}

int estEspace(char c)
{
	return (c == ' ');
}

int estDeuxPoints(char c)
{
	return (c==':');
}

int estSlash(char c)
{
	return (c == '/');
}

int estEntree(char c)
{
	return (c=='$');
}

int estSortie(char c)
{
	return (c== '#');
}
	
int estInconnu(char c)
{
	return (!estChiffre(c) && !estLettre(c) && !estFF(c) && !estEspace(c) && !estDeuxPoints(c) && !estSlash(c) && !estEntree(c) && !estSortie(c));
}

/* ******************************************************************
----------------------------Définir la classe-----------------------
****************************************************************** */
//Complète la classe du caractère en fonction du caractère rencontré pour la fonction ALex
int definiClasse(char c)
{
	int laClasse=0;
	if(estLettre(c)>0 )
	{
		laClasse=0;
	}
	else if(estChiffre(c)>0 )
	{
		laClasse=1;
	}
	else if(estInconnu(c)>0 )
	{
		laClasse=6;
	}
	else if(estEspace(c)>0)
	{
		laClasse =4;
	}
	else if(estFF(c)>0 )
	{
		laClasse=5;
	}
	else if(estDeuxPoints(c)>0 )
	{
		laClasse=2;
	}
	else if(estSlash(c)>0 )
	{
		laClasse=3;
	}
	else if(estEntree(c)>0)
	{
		laClasse =7;
	}
	else if(estSortie(c)>0 )
	{
		laClasse=8;
	}
	
	return laClasse;
}

/* ************************************************************************** *
 * 			Fonction booléenne de classes			      *
 * ************************************************************************** */
// Retournent vrai si la classe passée en paramètre correspond à celle de la fonction
int bALexEstChiffre(LEXEME classe)
{
	return classe == Chiffre;
}

int bALexEstLettre(LEXEME classe)
{
	return classe == Lettre;
}

int bALexEstFF(LEXEME classe)
{
	return classe == FinFichier;
}

int bALexEstInconnu(LEXEME classe)
{
	return classe == Inconnu;
}

int bALexEstDate(LEXEME classe)
{
	return classe == Date;
}

int bALexEstPlaque(LEXEME classe)
{
	return classe == Plaque;
}

int bALexEstHeure(LEXEME classe)
{
	return classe == Heure;
}

int bALexEstBaliseEntree(LEXEME classe)
{
	return classe == Entree;
}

int bALexEstBaliseSortie(LEXEME classe)
{
	return classe == Sortie;
}

LEXEME iALexClasse(int ind)
{
	return classe[ind];
}

int iAlexValeur(int ind)
{
	return valeur[ind];
}

char* sALexValeur(int ind){
	return sValeur[ind];
}

/* *****************************************************************************
---------------------------------Fonction ALex---------------------------------
***************************************************************************** */
//Parcours une chaine de caractère et reconnai tous les lexèmes qui s'y trouvent, rempli les tableaux valeur et classe
void ALexReconnaitreLexeme(char * ligne)
{
	char mot[100];
	int i=0;			//Incrément pour parcourir caractère par caractère
	int etatActuel=0;	//La ligne de l'AEF pendant le parcours du lexeme
	int etatSuivant=0;	//La colonne de l'AEF : la prochaine ligne de l'AEF qui sera utilisée
	int val=0;			//La valeur du lexème, pour leur traduction ultérieure.
	int laClasse;		//Le type de lexème reconnu
	assert(ligne);
	int debut = 0;
	int fin=0;	
	for(i= 0; i<strlen(ligne); i++ )
	{
		fin = i;
		laClasse = definiClasse(ligne[i]);
		
		etatSuivant=Decouper(sAEF[etatActuel],laClasse+1);
//		printf("La classe à l'indice %i est: %i\n",indice,laClasse);

//	Si le lexème est entièrement consommé, sa classe est donnée :
		if(etatSuivant<0)
		{//état final
			switch(etatSuivant) {
				case -10:	classe[indice]= FinFichier; 
							break;
				case -1:	classe[indice]= Lettre; 
							break;
				case -2:	classe[indice]= Chiffre; 
							break;
				case -3:	classe[indice]= Inconnu;
							break;
				case -5:	classe[indice]= Date; 
							break;
				case -6:	classe[indice]= Plaque; 
							break;
				case -7:	classe[indice]= Heure;
							break;
				case -8:	classe[indice]= Entree; 
							break;
				case -9:	classe[indice]= Sortie;
							break;
				case -11:	classe[indice]= ErreurLettre;
							break;
				case -12:	classe[indice]=ErreurChiffre;
							break;
				case -13:	classe[indice]=ErreurPlaque;
							break;
				case -14:	classe[indice]=ErreurHeure;
							break;
				case -15:	classe[indice]=ErreurDate;
							break;
				default:	assert(0>1);
			}
			valeur[indice]=val;
			indice ++;
			val=0;
			etatActuel=0;
			mot[fin-debut] ='\0';
			strcpy(sValeur[indice], mot);
			debut = fin+1;
		}

//	Sinon, l'état actuel mène à un second état (autre ligne de l'AEF): le lexème est en train d'être parcouru
		else if(etatSuivant>0)
		{
			mot[fin-debut] = ligne[i];
			switch(etatSuivant)
			{
				case 1:	val=val*26 + ligne[i]-'A'; 
						break;
				case 2: val=val*10 + ligne[i]-'0';
						break;
				case 3: val=val*10 + ligne[i]-'0';
						break;
				case 4:	val = -25;
						break;
				case 5:	val=val*26 + ligne[i]-'A';
						break;
				case 6: break;
				case 7: break;
				case 8: val=val*10 + ligne[i]-'0';
						break;
				case 9:	val=val*26 + ligne[i]-'A';
						break;
				case 10:val=val*10 + ligne[i]-'0';
						break;
				case 11:val=val*10 + ligne[i]-'0';
						break;
				case 12:val=val*10 + ligne[i]-'0';
						break;
				case 13:val=val*10 + ligne[i]-'0';
						break;
				case 14:val=val*10 + ligne[i]-'0';	
						break;
				case 15:val=val*10 + ligne[i]-'0';
						break;
				case 16:break;
				case 17:val=val*10 + ligne[i]-'0';
						break;
				case 18:val=val*10 + ligne[i]-'0';
						break;
				case 19: val=-20;
						break;
				case 20:val = -15;
						break;
				case 21:val = -30; 
						break;
				case 22:val = -35; 
						break;
				case 23:val = -40; 
						break;
				case 24:val = -45; 
						break;
				case 25:val = -50;
						break;
			}
			etatActuel=etatSuivant;
		}
	}//fin while
}

/* ****************************************************************
----------------------Fonctions 'internes'------------------------
**************************************************************** */
//Donne les 100 premières valeurs du tableau de classes, puis du tableau de valeurs
void Affiche()
{
	int i;
	for(i=0;i<100;i++)
	{
		printf("%i ",classe[i]);
	}
	printf("\n");
	for(i=0;i<100;i++) 
	{
		printf("%i ",valeur[i]);
	}
	printf("\n");
	for(i=0; i<100; i++){
		printf("%s ", sValeur[i]);
	}
	printf("\n");
}

//Fonction de test pour vérification de l'analyse lexicale
void ALexTester()
{
	init();
	char * mot[5];
	mot[0] = "QUENTIN 42 10:20 01/01/01 42GG24 $ #;";
	mot[1] = "QUENTI2N 42 10:120 01/01/011 42GMG24 $ #;";
	mot[2] = "";
	mot[3] = "              ";
	mot[4] = ";";
	int i;
	for(i=0; i<5; i++){
		init();
		printf("Test sur la phrase : %s \n", mot[i]);
		ALexReconnaitreLexeme(mot[i]);
		Affiche();
	}
}


/* *************************************************************************** *
 * 						Fonction d'appel									   *
 * *************************************************************************** */
//Fonction d'appel pour intégration dans le compilateur
void ALexAmorcer(char * s)
{
	init();
	ALexReconnaitreLexeme(s);
}
/*
void main(){
	ALexTester();
}*/

