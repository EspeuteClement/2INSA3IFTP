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

//les boites aux lettres pour les voitures qui entrent
static int idfileVoitureEntree[NOMBRE_FILE_VOITURE];
//la boite aux lettres pour le numero sorti
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
// Algorithme : On récupère les id des files d'attente des entrees et
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
		//Quand on a 'E' comme code, le processus se termine.
        case 'E' :
            exit(0);
            break;
        //Quand on a 'A' comme code, on pose une voiture de type autre 
        //dans la boite aux lettres de la porte choisie.
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
        //Quand on a 'P' comme code, on pose une voiture de type prof 
        //dans la boite aux lettres de la porte choisie.
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
        //Quand on a 'S' comme code, on transmet la valeur au processus
        //Sortie pour indiquer la sortie de la voiture d'une certaine
        //place.
        case 'S' :
            msgInt numS = {valeur};
            msgsnd (idfileVoitureSortie, &numS, sizeof(msgInt), 0);
            Effacer(MESSAGE);
		 	Afficher(MESSAGE,"Une voiture vient de sortir");
			break;
			
    }
} //----- fin de Commande
