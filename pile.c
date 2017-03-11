#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ALex.h"
#include "asem.h"

//Pile pour stocker les tickets 
int compt = 0;

ticket* tab_pile_ticket[1000];
int sommet = -1;



 void retirer ( ticket t){
	int i;
	ticket tmp; 
	for(i=0;i<1000;i++){
		tmp=*(tab_pile_ticket[i]);
		if(strcmp(tmp.plaque,t.plaque)==0){
				tab_pile_ticket[i]=NULL;
		}
	}		

}
 //Faire empiler a la prochaine casse vide 
void pileEmpiler(ticket t){
        int i, bFound = 0;
        if(sommet<1000){
		if(t.balise=='e'){/*Si c'est une entrée*/
			for(i = sommet; i >= 0; i--){
				if(!strcmp(t.plaque,tab_pile_ticket[i]->plaque) && tab_pile_ticket[i]->balise == 'e'){
				/*Si c'est une entree et qu'il y a deja eu une entree on en veut pas */
					bFound = 1;
					break;
				}
				else if(!strcmp(t.plaque,tab_pile_ticket[i]->plaque) && tab_pile_ticket[i]->balise == 's'){
				/*Si c''est une entree et qu'il y a deja eu une sortie c'est BON */
					bFound = 1;
					tab_pile_ticket[sommet]=&t;
					compt++;
					sommet++;
				}
			}
			if(!bFound){
				tab_pile_ticket[sommet]=&t;
				compt++;
				sommet++;
			}
		}else{/*si c'est une sortie*/
			for(i = sommet; i >= 0; i--){
				if(!strcmp(t.plaque,tab_pile_ticket[i]->plaque) && tab_pile_ticket[i]->balise == 's'){
					/*Si c'est une sortie et qu'il y a deja eu une sortie on en veut pas */
					bFound = 1;
					break;
				}
				else if(!strcmp(t.plaque,tab_pile_ticket[i]->plaque) && tab_pile_ticket[i]->balise == 'e'){
					/*Si c''est une sortie et qu'il y a deja eu une entree c'est BON */
					bFound = 1;
					tab_pile_ticket[sommet]=&t;
					compt--;
					sommet++;
				}
			}
			if(!bFound){
				tab_pile_ticket[sommet]=&t;
				compt--;
				sommet++;
			}
		}
        }else{
		printf("Pile pleine\n");
	}
}




