//---------------------- Réalisation de <Clavier> ------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
//------------------------------------------------------ Include personnel
#include "Clavier.h"
#include "Voiture.h"
#include "Mere.h"
#include "libs/Menu.h"
#include "libs/Outils.h"
#include "libs/Heure.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static int idfileVoitureEntree[NOMBRE_FILE_VOITURE];
static int idfileVoitureSortie;

//------------------------------------------------------ Fonctions privées
static unsigned int numeroter()
// Algorithme : Cette fonction remet à zéro quand on atteint 1000
//
{
	static unsigned int num=0;
	num++;
	if(num==1000)
	{
		num=1;
	}
	return num;
} //----- fin de Numeroter

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Clavier (int *filVoitureEntree, int filVoitureSortie)
// Algorithme : On récupère les id des files d'attente des portes et
//              appelle en boucle infinie Menu
//
{
	idfileVoitureEntree[0]=filVoitureEntree[0];
	idfileVoitureEntree[1]=filVoitureEntree[1];
	idfileVoitureEntree[2]=filVoitureEntree[2];
	idfileVoitureSortie=filVoitureSortie;
    for (;;) 
    {
        Menu();
    }
} //----- fin de Clavier

void Commande (char code , unsigned int valeur)
// Algorithme : C'est une méthode appelée par Menu qui, pour des codes
//              et valeur différents, s'agit différemment.
//
{
    Voiture uneVoiture;
    
    switch (code)
    {
        case 'E' :
            exit(0);
            break;
            
        case 'A' :
            uneVoiture.arrivee = 0;
            uneVoiture.type = AUTRE;
            uneVoiture.numero = numeroter();
            if (valeur == 1) {
                msgsnd (idfileVoitureEntree[FILE_AUTRE_BP], &uneVoiture, sizeof(uneVoiture), 0);
                Effacer(MESSAGE);
                Afficher(MESSAGE,"Une voiture d'autre vient d'arriver à la porte BPA");
            }
            else if (valeur == 2) {
                msgsnd (idfileVoitureEntree[FILE_GB], &uneVoiture, sizeof(uneVoiture), 0);
                Effacer(MESSAGE);
                Afficher(MESSAGE,"Une voiture d'autre vient d'arriver à la porte GB");
            }
            break;
            
        case 'P' :
            uneVoiture.arrivee = 0;
            uneVoiture.type = PROF;
            uneVoiture.numero = numeroter();
            if (valeur == 1) {
                msgsnd (idfileVoitureEntree[FILE_PROF_BP], &uneVoiture, sizeof(uneVoiture), 0);
                Effacer(MESSAGE);
                Afficher(MESSAGE,"Une voiture de prof vient d'arriver à la porte BPP");
            }
            else if (valeur == 2) {
                msgsnd (idfileVoitureEntree[FILE_GB], &uneVoiture, sizeof(uneVoiture), 0);
                Effacer(MESSAGE);
                Afficher(MESSAGE,"Une voiture de prof vient d'arriver à la porte GB");
            }
            break;

        case 'S' :
            int numS = valeur;
            msgsnd (idfileVoitureSortie, &numS, sizeof(int), 0);
            Effacer(MESSAGE);
		 	Afficher(MESSAGE,"Une voiture vient de sortir");
			break;
			
    }
} //----- fin de Commande
