#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"GenCode.h"
#include"asem.h"
/*
typedef struct date{
	int quantieme;
	int mois;
	int annee;
}date;


typedef struct heure{
        int heures;
        int minutes;
}heure;

typedef struct ticket { 
	char balise; 
	char * plaque; 
	char* nom;
	date d;
	heure h;
	int place;
}ticket;
*/

void GeneAmorcer(){
    
}

int GenerationCode(){
    return 0;
}


// date fixe des trimestre
date Trim1;
date Trim2;
date Trim3;
date Trim4;

// fonction pour comparer si le jour et le mois de 2 dates sont identiques
int bDateIdentique(date d1, date d2){
    return(d1.quantieme == d2.quantieme && d1.mois == d2.mois && d1.annee == d2.annee);
}

int bTrimestreFin(date dateCour)
{	// On regarde si la date courante est un début de trimestre
    int jour1 = dateCour.quantieme;
	// Date de début de trimestre fixé en dur
	Trim1.quantieme = jour1;
	Trim2.quantieme = jour1;
	Trim3.quantieme = jour1;
	Trim4.quantieme = jour1;

	Trim1.mois = 01;
	Trim2.mois = 04;
	Trim3.mois = 07;
	Trim4.mois = 10;

	if(bDateIdentique(dateCour,Trim1) == 1 || bDateIdentique(dateCour,Trim2) == 1 || bDateIdentique(dateCour,Trim3) == 1 || bDateIdentique(dateCour,Trim4) == 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//retourne 1 si pa est supérieur à pb, -1 si pa est inférieur à pb, 0 sinon
int compareMouvements(const void *pa, const void *pb){
	const mouvement *a = pa, *b = pb;
	//comparaison des noms
	if(strcmp(a->nom,b->nom)>0)
		return 1;
	else if(strcmp(a->nom,b->nom)<0)
		return -1;
	else{
		//comparaison des plaques
		if(strcmp(a->plaque,b->plaque)>0)
			return 1;
		else if(strcmp(a->plaque,b->plaque)<0)
			return -1;
		else{
			//comparaison des dates
			if(a->date.annee>b->date.annee)
				return 1;
			else if(a->date.annee<b->date.annee)
				return -1;
			else
				if(a->date.mois>b->date.mois)
					return 1;
				else if(a->date.mois<b->date.mois)
					return -1;
				else
					if(a->date.quantieme>b->date.quantieme)
						return 1;
					else if(a->date.quantieme<b->date.quantieme)
						return -1;
					else{
						//comparaison des horaires
						if(a->heure.heures>b->heure.heures)
							return 1;
						else if(a->heure.heures<b->heure.heures)
							return -1;
						else
							if(a->heure.minutes>b->heure.minutes)
								return 1;
							else if(a->heure.minutes<b->heure.minutes)
								return -1;
							else
								return 0;
						
			}
		}
	}
}

int calculPrix(mouvement entree, mouvement sortie){
	int prixMax = 60*24*30*3;

	int nbAnnees = sortie.date.annee - entree.date.annee;
	int nbMois = sortie.date.mois - entree.date.mois;
	int nbJours = sortie.date.quantieme - entree.date.quantieme;
	
	int nbHeures = sortie.heure.heures - entree.heure.heures;
	int nbMinutes = sortie.heure.minutes - entree.heure.minutes;
	
	int prixTotal = nbMinutes + nbHeures*60 + nbJours*60*24 + nbMois*60*24*30;
	if(prixTotal > prixMax)
		return prixMax;
	else
		return prixTotal;
}

	
int GCFacture(date dateCour){
	if(bTrimestreFin(dateCour)==1){
		int tailleTab=0;
		int j=0;
		mouvement tmp;
		mouvement *tabMvt=malloc(sizeof(mouvement));
	
		//Remplissage du tableau depuis la pile
		while(!pileVide()){
			depiler(&tmp);
			tabMvt=realloc(tabMvt,sizeof(mouvement)*(tailleTab+1));
			tabMvt[tailleTab]=tmp;
			tailleTab++;
		}

		//Tri du tableau
		qsort (tabMvt, tailleTab, sizeof(mouvement), &compareMouvements);

		//Creation des factures
		j=0;
		char nomTmp[30];
		char plaqueTmp[10];
		int prixTmp;
		while(j<tailleTab-1){
			int prix=0;
			strcpy(nomTmp, tabMvt[j].nom);
			printf("\n%s\n\n", nomTmp);
			do{
				strcpy(plaqueTmp, tabMvt[j].plaque);
				printf("véhicule : %s\n",tabMvt[j].plaque);
				do{
					printf("entree : %i/%i/%i %i:%i\n",tabMvt[j].date.quantieme,
						tabMvt[j].date.mois, 
						tabMvt[j].date.annee,
						tabMvt[j].heure.heures,
						tabMvt[j].heure.minutes);
					printf("sortie : %i/%i/%i %i:%i\n",tabMvt[j+1].date.quantieme,
						tabMvt[j+1].date.mois, 
						tabMvt[j+1].date.annee,
						tabMvt[j+1].heure.heures,
						tabMvt[j+1].heure.minutes);
					prixTmp = calculPrix(tabMvt[j],tabMvt[j+1]);
					printf("prix : %i\n\n", prixTmp);
					prix += prixTmp;
					j+=2;
				if(j>=tailleTab-1) break;
				}while(strcmp(plaqueTmp,tabMvt[j].plaque)==0);
				if(j>=tailleTab-1) break;
			}while(strcmp(nomTmp,tabMvt[j].nom)==0);
			printf("prix total : %i\n\n",prix);
		}		
		return 0;
	}
}

int GCEmpilerMouvement(char* ePLQ, char*  eNOM,date eDATE, heure eHEURE){
	mouvement m;
	strcpy(m.plaque, ePLQ);
	strcpy(m.nom, eNOM);
	m.date = eDATE;
	m.heure = eHEURE;	
	empiler(m);
	return 1;
}

/*int main(){
	
	mouvement m;
		m.nom="Berrabah";
		m.plaque="5552GG33";
		m.date.annee=12;
		m.date.mois=04;
		m.date.quantieme=15;
		m.heure.heures=12;
		m.heure.minutes=54;
	mouvement m4;
		m4.nom="Berrabah";
		m4.plaque="5552GG33";
		m4.date.annee=12;
		m4.date.mois=04;
		m4.date.quantieme=15;
		m4.heure.heures=12;
		m4.heure.minutes=55;
	mouvement m1;
		m1.nom="Abouaf";
		m1.plaque="6552GG33";
		m1.date.annee=13;
		m1.date.mois=04;
		m1.date.quantieme=15;
		m1.heure.heures=12;
		m1.heure.minutes=54;
	mouvement m2;
		m2.nom="Abouaf";
		m2.plaque="6552GG33";
		m2.date.annee=13;
		m2.date.mois=04;
		m2.date.quantieme=17;
		m2.heure.heures=12;
		m2.heure.minutes=54;
	mouvement m3;
		m3.nom="Charpentier";
		m3.plaque="7552GG33";
		m3.date.annee=13;
		m3.date.mois=04;
		m3.date.quantieme=15;
		m3.heure.heures=12;
		m3.heure.minutes=54;
	mouvement m5;
		m5.nom="Charpentier";
		m5.plaque="7552GG33";
		m5.date.annee=13;
		m5.date.mois=04;
		m5.date.quantieme=16;
		m5.heure.heures=12;
		m5.heure.minutes=58;
	mouvement m6;
		m6.nom="Abouaf";
		m6.plaque="8552GG33";
		m6.date.annee=13;
		m6.date.mois=04;
		m6.date.quantieme=18;
		m6.heure.heures=12;
		m6.heure.minutes=54;
	mouvement m7;
		m7.nom="Abouaf";
		m7.plaque="8552GG33";
		m7.date.annee=13;
		m7.date.mois=04;
		m7.date.quantieme=19;
		m7.heure.heures=12;
		m7.heure.minutes=54;
	
	//Remplissage de la pile
	empiler(m);
	empiler(m1);
	empiler(m2);
	empiler(m3);
	empiler(m4);
	empiler(m5);
	empiler(m6);
	empiler(m7);
	AmorcerGenCode();
}*/
