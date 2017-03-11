#ifndef _PILEPTR_H        
#define _PILEPTR_H

typedef struct date{
	int quantieme;
	int mois;
	int annee;
}date;


typedef struct heure{
        int heures;
        int minutes;
}heure;

typedef struct mouvement{
        char *nom; //nom du proprio
        char *plaque; //plaque d'immatriculation du véhicule
        date date;	
        heure heure;
}mouvement;

struct elem {mouvement m; struct elem * suivant;};
struct elem * pile;

void initpile();
	
int pileVide(void);

void empiler(mouvement n);

void depiler(mouvement *n);
	
mouvement sommetpile(void);

#endif
