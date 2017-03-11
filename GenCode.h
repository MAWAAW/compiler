#include"asem.h"
typedef struct mouvement{
        char *nom; //nom du proprio
        char *plaque; //plaque d'immatriculation du véhicule
        date date;	
        heure heure;
        int place;
}mouvement;
// fonction pour comparer si le jour et le mois de 2 dates sont identiques
int bDateIdentique(date d1,date d2);
int bTrimestreFin(date dateCour);
//retourne 1 si pa est supérieur à pb, -1 si pa est inférieur à pb, 0 sinon
int compareMouvements(const void *pa, const void *pb);

int calculPrix(mouvement entree, mouvement sortie);

int GCFacture(date dateCour);

int GCEmpilerMouvement(char* ePLQ,char*  eNOM,date eDATE, heure eHEURE);
