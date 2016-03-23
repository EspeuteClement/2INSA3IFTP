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
static int idSemMemPartagee;

//------------------------------------------------------ Fonctions privées
static void finSortieVoiture(int numSignal)
// Mode d'emploi :
//
{
    int status;
    pid_t pidFille = wait(&status);
    unsigned int numS=WEXITSTATUS(status);

 
    struct sembuf opP;
    opP.sem_num=0;
    opP.sem_op=-1;
    opP.sem_flg=0;

	struct sembuf opV;
    opV.sem_num=0;
    opV.sem_op=1;
    opV.sem_flg=0;
    
    semop(idSemMP, &operationP, 1);
    Voiture uneVoiture = ((VoituresParking*)memPartagee)->voituresGarees[numS-1]；
    semop(idSemMP, &operationV, 1);   
    Effacer(numS);
    Effacer(MESSAGE);
	Afficher(MESSAGE, "Une voiture vient de sortir");
	AfficherSortie(uneVoiture.type,uneVoiture.numero,uneVoiture.arrivee,time(null));

    semop(idSemMP, &operationP, 1);
    Voiture * lesVoitures = ((VoituresParking*)memPartagee)->voituresEnAttente;

	if(lesVoitures[FILE_PROF_BP].type==PROF && lesVoitures[FILE_GB].type!=PROF)
	{
		//BPP
	}
	else if(lesVoitures[FILE_PROF_BP].type==PROF && lesVoitures[FILE_GB].type==PROF)
	{
		if(lesVoitures[FILE_PROF_BP].arrivee <= lesVoitures[FILE_GB].arrivee)
		{
			//BPP
		}
		else
		{
			//GB
		}
	else if(lesVoitures[FILE_PROF_BP].type!=PROF && lesVoitures[FILE_GB].type==PROF)
	{
		//GB
	}
	else if(lesVoitures[FILE_AUTRE_BP].type==AUTRE && lesVoitures[FILE_GB].type==AUTRE)
	{
		if(lesVoitures[FILE_AUTRE_BP].arrivee <= lesVoitures[FILE_GB].arrivee)
		{
			//BPA
		}
		else
		{
			//GB
		}
	else if(lesVoitures[FILE_AUTRE_BP].type==AUTRE && lesVoitures[FILE_GB].type==AUCUN)
	{
		//BP
	}
	else if(lesVoitures[FILE_AUTRE_BP].type==AUCUN && lesVoitures[FILE_GB].type==AUTRE)
	{
		//GB
	}
    semop(idSemMP, &operationV, 1);
}//-----Fin de finSortieVoiture


static void finTache(int numSignal)
// Mode d'emploi :
//
{
	shmdt(memPartagee);
	exit(0);
}//-----Fin de finTache


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Sortie(int idMP, int idFVS, int idSemMP)
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
    idSemMemPartagee=idSemMP;
    memPartagee=shmat(idMemoirePartagee,NULL,0);
    
    for(;;)
	{
        int numS;
        msgrcv (idFileVoitureSortie, &numS, sizeof(int), 0);
		SortirVoiture(numS);
	}
}//-----Fin de Sortie
