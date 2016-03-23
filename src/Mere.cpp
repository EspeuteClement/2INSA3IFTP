/*************************************************************************
                           Mere  -  Classe principale pour l'application multitâche
                             -------------------
    début                : 2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Réalisation de la tâche <Mere> (fichier Mere.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <unistd.h>
#include <signal.h>
#include <sys/msg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>




//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "libs/Outils.h"
#include "Config.h"
//------------------------------------------------------------- Constantes
//----------------------------------------------------------- Types privés

//------------------------------------------------------------------- Enum

static const int DROITS_SEM = S_IRUSR | S_IWUSR;
static const int DROITS_SHM = S_IRUSR | S_IWUSR;

// Tâche principale du programme
int main()
{
	// --------------------------------------------- Phase d'initialisation
	
	// Ouvrir un fichier de log
	FILE* log = fopen("log.txt","w");
	if (log)
	{
		// Créer un mutex pour le fichier log
		int semLog = semget (IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | DROITS_SEM);
		semctl (semLog, 0, SETVAL, 1);

		InitialiserApplication(XTERM);

		// Masquer les signaux :
		struct sigaction ignorer;
		ignorer.sa_handler = SIG_IGN;
		sigemptyset(&ignorer.sa_mask);
		ignorer.sa_flags = 0;

		// Pour éviter qu'on puisse CTRL-C le programme
		sigaction(SIGINT, &ignorer, NULL);
		sigaction(SIGUSR2,&ignorer, NULL);

		// Créer les ressources partagées :

		// Boites aux lettres files voitures:
		int FilesVoiture[NOMBRE_FILE_VOITURE];


		for (unsigned int file = 0; file < NOMBRE_FILE_VOITURE; file ++)
		{
			int msgId = msgget (IPC_PRIVATE, IPC_CREAT | IPC_EXCL);
			if (msgId != -1)
			{
				semop( semLog, &reserver, 1);
				fprintf(log,"Création de la FileVoiture %d\n",file);
				semop( semLog, &liberer, 1);
				FilesVoiture[file] = msgId;
			}
			else
			{
				// Prévoir en cas de problème
				semop( semLog, &reserver, 1);
				fprintf(log,"Erreur : Impossible de créer FileVoiture %d\n",file);
				semop( semLog, &liberer, 1);
			}
		}

		// Sémaphores pour l'ouverture des portes
		int semOuvrirPortes = semget(IPC_PRIVATE, NOMBRE_FILE_VOITURE, IPC_CREAT | IPC_EXCL | DROITS_SEM) ;

		// Boite au lettre pour sortie
		int RequeteSortie = msgget (IPC_PRIVATE, IPC_CREAT | IPC_EXCL);

		// Zone mémoire pour ComptePlacesLibres
		int shmComptePlacesLibres = shmget (IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | DROITS_SHM);
		int semComptePlacesLibres = semget (IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | DROITS_SEM);

		semctl(semComptePlacesLibres, 0, SETVAL, 1);

		// ------------------------------------------------------- Phase moteur
		sleep(2);

		// ----------------------------------------------  Phase de destruction
		

		// Liberer les ressources partagées :

		// Boites aux lettres files voitures
		for (int file = 0; file < NOMBRE_FILE_VOITURE; file ++)
		{
			msgctl (FilesVoiture[file], IPC_RMID, 0);
		}

		// Sémaphores pour l'ouverture des portes
		semctl(semOuvrirPortes,0, IPC_RMID,0);

		// Boite aux lettres pour sortie
		msgctl (RequeteSortie, IPC_RMID, 0);

		// Zone mémoire pour ComptePlacesLibres
		shmctl (shmComptePlacesLibres, IPC_RMID, 0);
		semctl (semComptePlacesLibres, IPC_RMID, 0);

		TerminerApplication(true);

		// Liberer le sémaphore du ficher de log
		semctl( semLog, 0,IPC_RMID, 0);

		fclose(log);
	}

	return 0;
}