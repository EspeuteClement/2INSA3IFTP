//---------------------- Réalisation <Sortie> ----------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <vector>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <map>
#include <iostream>
//------------------------------------------------------ Include personnel
#include "/public/tp/tp-multitache/Outils.h"
#include "/public/tp/tp-multitache/Heure.h"
#include "Mere.h"
#include "Sortie.h"
#include "Clavier.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

static int idMemoirePartagee;
static int idFileVoitureSortie;
static void * memPartagee;
static int idSemVoitureAttente;
static int idSemVoitureSortie;

//------------------------------------------------------ Fonctions privées
static void finSortieVoiture(int numSignal)
// Mode d'emploi :
//
{
    int status;
    pid_t pidFille = wait(&status);
    unsigned int numS=WEXITSTATUS(status);

//Sem a voir 
    struct sembuf opP;
    opP.sem_num=0;
    opP.sem_op=-1;
    opP.sem_flg=0;
//Sem a voir
	struct sembuf opV;
    opV.sem_num=0;
    opV.sem_op=1;
    opV.sem_flg=0;
    
    semop(idSemVS, &operationP, 1);
    Voiture uneVoiture = ((VoituresParking*)memPartagee)->voituresGarees[numS-1]；
    semop(idSemVS, &operationV, 1);   
    Effacer(numS);
    Effacer(MESSAGE);
	Afficher(MESSAGE, "Une voiture vient de sortir");

    semop(idSemMP, &operationP, 1);
    Voiture * lesVoitures = voitureEnAttente->requete;
    if (attente[REQUETEBPP].type == PROF) {
        if (attente[REQUETEGB].type != PROF) {
            semop(idSemBPP, &operationV, 1);
        }
        else {
            if (attente[REQUETEBPP].temps < attente[REQUETEGB].temps) {
                semop(idSemBPP, &operationV, 1);
            }
            else {
                semop(idSemGB, &operationV, 1);
            }
        }
    }
    else if (attente[REQUETEBPP].type == AUTRE) {
        if (attente[REQUETEGB].type == PROF) {
            semop(idSemGB, &operationV, 1);
        }
        else if (attente[REQUETEGB].type == AUTRE) {
            if (attente[REQUETEBPA].type == AUTRE) {
                if (attente[REQUETEBPA].temps < attente[REQUETEBPP].temps && attente[REQUETEBPA].temps < attente[REQUETEGB].temps) {
                    semop(idSemBPA, &operationV, 1);
                }
                else if (attente[REQUETEBPP].temps < attente[REQUETEBPA].temps && attente[REQUETEBPP].temps < attente[REQUETEGB].temps) {
                    semop(idSemBPP, &operationV, 1);
                }
                else if (attente[REQUETEGB].temps < attente[REQUETEBPA].temps && attente[REQUETEGB].temps < attente[REQUETEBPP].temps) {
                    semop(idSemGB, &operationV, 1);
                }
            }
            else {
                if (attente[REQUETEBPP].temps < attente[REQUETEGB].temps) {
                    semop(idSemBPP, &operationV, 1);
                }
                else {
                    semop(idSemGB, &operationV, 1);
                }
            }
        }
        else {
            if (attente[REQUETEBPA].TYPE == AUTRE) {
                if (attente[REQUETEBPP].temps < attente[REQUETEBPA].temps) {
                    semop(idSemBPP, &operationV, 1);
                }
                else {
                    semop(idSemBPA, &operationV, 1);
                }
            }
            else {
                semop(idSemBPP, &operationV, 1);
            }
        }
    }
    else {
        if (attente[REQUETEGB].type == PROF) {
            semop(idSemGB, &operationV, 1);
        }
        else if (attente[REQUETEGB].type == AUTRE) {
            if (attente[REQUETEBPA].type == AUTRE) {
                if (attente[REQUETEBPA].temps < attente[REQUETEGB].temps) {
                    semop(idSemBPA, &operationV, 1);
                }
                else {
                    semop(idSemGB, &operationV, 1);
                }
            }
            else {
                semop(idSemGB, &operationV, 1);
            }
        }
        else {
            if (attente[REQUETEBPA].type == AUTRE) {
                semop(idSemBPA, &operationV, 1);
            }
            else {
                ((Parking*)parkingPtr)->placesDisponibles++；
            }
        }
    }
    semop(idSemMP, &operationV, 1);
}//-----Fin de finSortieVoiture


static void finTache(int numSignal)
// Mode d'emploi :
//
{
	shmdt(voitureEnAttente);
	shmdt(nbDePlaceLibres);
	exit(0);
}//-----Fin de finTache


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Sortie(int idMP, int idFVS, int idSemVA, int idSemVS)
{
    struct sigaction handlerUSR2;
    handlerUSR2.sa_handler=finTache;
    sigemptyset(&handlerUSR2.sa_mask);
    handlerUSR2.sa_flags=0;
    sigaction(SIGUSR2, &handlerUSR2, NULL);
	
	struct sigaction handlerCHLD;
    handlerCHLD.sa_handler=finSortieVoiture;
    sigemptyset(&handlerCHLD.sa_mask);
    handlerCHLD.sa_flags=0;  
    sigaction(SIGCHILD, &actionFinVoiturier, NULL);
    
    idMemoirePartagee=idMP;
    idFileVoitureSortie=idFVS;
    idSemVoitureAttente=idSemVA;
    idSemVoitureSortie=idSemVS;
    memPartagee=shmat(idMemoirePartagee,NULL,0);
    
    for(;;)
	{
        int numS;
        msgrcv (idFileVoitureSortie, &numS, sizeof(int), 0);
		SortirVoiture(numS);
	}
}//-----Fin de Sortie
