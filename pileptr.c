# include <stdlib.h>

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

void initpile()
{
	pile=NULL;
}
	
int pileVide(void)
{
	return(pile==NULL);
}
	
void empiler(mouvement n)
{
	struct elem * nouveau;
	nouveau=(struct elem*)malloc(sizeof(struct elem));
	nouveau->m=n;
	nouveau->suivant=pile;
	pile=nouveau;
}
	
void depiler(mouvement *n)
{
	struct elem * sommet;
	if (pile!=NULL)
	{
		*n=pile->m;
		sommet=pile;
		pile=sommet->suivant;
		free(sommet);
	}
}
	
mouvement sommetpile(void)
{
	if (pile!=NULL)
	{
		return(pile->m);
	}
}


