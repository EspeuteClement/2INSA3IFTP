//---------------------- Réalisation de <Clavier> ------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
//------------------------------------------------------ Include personnel
#include "Clavier.h"
#include "Voiture.h"
#include "/public/tp/tp-multitache/Menu.h"
#include "/public/tp/tp-multitache/Outils.h"
#include "/public/tp/tp-multitache/Heure.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static int idfilVoitureBPP;
static int idfilVoitureBPA;
static int idfilVoitureGB;
static int idfilVoitureSortie;

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
void Clavier (key_t clefBPP, key_t clefBPA, key_t clefGB, key_t clefS)
// Algorithme :
//
{
	idfilVoitureBPP=msgget(clefBPP, 0);
	idfilVoitureBPA=msgget(clefBPA, 0);
	idfilVoitureGB=msgget(clefGB, 0);
	idfilVoitureSortie=msgget(clefS, 0);
    for (;;) 
    {
        Menu();
    }
} //----- fin de Clavier

void Commande (char code , unsigned int valeur)
// Algorithme :
//
{
    Voiture uneVoiture;
    
    switch (code)
    {
        case 'Q' :
            exit(0);
            break;
            
        case 'A' :
            uneVoiture.arrivee = time(NULL);
            uneVoiture.type = AUTRE;
            uneVoiture.numero = numeroter();
            if (valeur == 1) {
                msgsnd (idfilVoitureBPA, &uneVoiture, sizeof(uneVoiture), 0);
                Effacer(MESSAGE);
                Afficher(MESSAGE,"Une voiture d'autre vient d'arriver à la porte BPA");
            }
            else if (valeur == 2) {
                msgsnd (idfilVoitureGB, &uneVoiture, sizeof(uneVoiture), 0);
                Effacer(MESSAGE);
                Afficher(MESSAGE,"Une voiture d'autre vient d'arriver à la porte GB");
            }
            break;
            
        case 'P' :
            uneVoiture.arrivee = time(NULL);
            uneVoiture.type = PROF;
            uneVoiture.numero = numeroter();
            if (valeur == 1) {
                msgsnd (idfilVoitureBPP, &uneVoiture, sizeof(uneVoiture), 0);
                Effacer(MESSAGE);
                Afficher(MESSAGE,"Une voiture de prof vient d'arriver à la porte BPP");
            }
            else if (valeur == 2) {
                msgsnd (idfilVoitureGB, &uneVoiture, sizeof(uneVoiture), 0);
                Effacer(MESSAGE);
                Afficher(MESSAGE,"Une voiture de prof vient d'arriver à la porte GB");
            }
            break;

        case 'S' :
            int numS = valeur;
            msgsnd (idfilVoitureSortie, &numS, sizeof(int), 0);
            Effacer(MESSAGE);
		 	Afficher(MESSAGE,"Une voiture vient de sortir");
			break;
			
    }
} //----- fin de Commande
