//---------------------- Réalisation <Sortie> ----------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
##include <sys/types.h>
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
#include "Config.h"
#include "Sortie.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques



//------------------------------------------------------ Fonctions privées
static void finVoiturier(int noSignal)
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
{
    int crdu;
    pid_t pidTacheFille = wait(&crdu);
    unsigned int numPlace=WEXITSTATUS(crdu);
    
    struct sembuf operationP;
    operationP.sem_num=0;
    operationP.sem_op=-1;
    operationP.sem_flg=0;
    
	struct sembuf operationV;
    operationV.sem_num=0;
    operationV.sem_op=1;
    operationV.sem_flg=0;
    
    semop(idSemMP, &operationP, 1);
    Voiture uneVoiture = ((Parking*)parkingPtr)->tabVoiture[numPlace-1]；
    semop(idSemMP, &operationV, 1);
    
    switch (numPlace)
    {
        case 1 :
        	Effacer(ETAT_P1);
            break;
    
        case 2 :
        	Effacer(ETAT_P2);
            break;
        
        case 3 :
        	Effacer(ETAT_P3);
            break;
        
        case 4 :
        	Effacer(ETAT_P4);
            break;
        
        case 5 :
        	Effacer(ETAT_P5);
            break;
        
        case 6 :
        	Effacer(ETAT_P6);
            break;
        
        case 7 :
        	Effacer(ETAT_P7);
            break;
        
        case 8 :
        	Effacer(ETAT_P8);
            break;
        
        default :
         break;
    }
    
    semop(idSemMP, &operationP, 1);
    Voiture * attente = ((Parking*)parkingPtr)->filAttente;
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
}


static void finTache(int numSignal)
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
{
	shmdt(parkingPtr);
	close(descCanal);
	exit(0);
}//Fin finTache



//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Sortie(int idVA, int idNP)
{
    struct sigaction handlerUSR2;
    handlerUSR2.sa_handler=finTache;
    sigemptyset(&handlerUSR2.sa_mask);
    handlerUSR2.sa_flags=0;
    sigaction(SIGUSR2, &handlerUSR2, NULL);
	
	struct sigaction handlerCHLD;
    handlerCHLD.sa_handler=finVoiturier;
    sigemptyset(&actionFinVoiturier.sa_mask);
    actionFinVoiturier.sa_flags=0;
    
    sigaction(SIGCHILD, &actionFinVoiturier, NULL);
    
    
    descCanal = open(CHEMIN_SORTIE, O_RDONLY);
    
    idSemBPP = semBPP;
    idSemBPA = semBPA;
    idSemGB = semGB;
    idSemMP = semMP;
    idMemoirePartage = memoirePartage;
    parkingPtr = shmat(idMemoirePartage, NULL, 0);
    
    for(;;)
	{
        int numPlace;
        read(descCanal, &numPlace, sizeof(numPlace));
		Effacer(MESSAGE);
		Afficher(MESSAGE, "Une voiture vient de sortir");
		SortirVoiture(numPlace);
	}
}
