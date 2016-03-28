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
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>


//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "libs/Outils.h"
#include "libs/Heure.h"
#include "Config.h"
#include "Entree.h"
#include "Clavier.h"
#include "Voiture.h"
//------------------------------------------------------------- Constantes
//----------------------------------------------------------- Types privés

//------------------------------------------------------------------- Enum

static const int DROITS_SEM = S_IRUSR | S_IWUSR;
static const int DROITS_SHM = S_IRUSR | S_IWUSR;
static const int DROITS_MSG = S_IRUSR | S_IWUSR;


//------------------------------------------------------------- Globales
static sembuf reserver = {0,-1,0};
static sembuf liberer  = {0,1,0};

//----------------------------------------------------- Méthodes Statiques

static void MereInitialisation();
static void MereMoteur();
static void MereDestruction();

//----------------------------------------------------- Variables Fichier

static int msgFilesVoiture[NOMBRE_FILE_VOITURE];
static int semLog;

// ------- Ressources

// Tableau de sémaphore indiquant la libération d'une place à une des entrées
static int semOuvrirPortes;

// File de message indiquant une requete de sortie 
static int msgRequeteSortie;

// Zone mémoire qui contient les voitures présentes dans le parking
static int shmVoituresParking;

// Mutex régulant l'acces à VoituresParking
static int semVoituresParking;	

// Pointeur sur la zone mémoire VoituresParking pour Mere
static VoituresParking *ptrVoituresParking;

// ------- PID des tâches

static pid_t pidClavier;		// Tâche Clavier 
static pid_t pidEntrees[NOMBRE_FILE_VOITURE] = {-1};
								// Tâches Entree
static pid_t pidHeure;			// Pid de l'affichage de l'Heure

// Tâche principale du programme
int main()
{
	
	MereInitialisation();
	MereMoteur();
	MereDestruction();

	return 0;
}

static void MereInitialisation()
{
	// ------------------------------ Créer un mutex pour le fichier log
	semLog = semget (IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | DROITS_SEM);
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

	// ---------------------------------- Créer les ressources partagées :

	// Boites aux lettres files voitures:

	for (unsigned int file = 0; file < NOMBRE_FILE_VOITURE; file ++)
	{
		int msgId = msgget (IPC_PRIVATE, IPC_CREAT | IPC_EXCL | DROITS_MSG);
		if (msgId != -1)
		{
			msgFilesVoiture[file] = msgId;
		}
		else
		{
			// Prévoir en cas de problème
		}
	}

	// Sémaphores pour l'ouverture des portes
	semOuvrirPortes = semget(IPC_PRIVATE, NOMBRE_FILE_VOITURE, IPC_CREAT | IPC_EXCL | DROITS_SEM) ;

	// Boite au lettre pour sortie
	msgRequeteSortie = msgget (IPC_PRIVATE, IPC_CREAT | IPC_EXCL);

	// Zone mémoire pour VoituresParking
	shmVoituresParking = shmget (IPC_PRIVATE, sizeof(VoituresParking), IPC_CREAT | IPC_EXCL | DROITS_SHM);
	semVoituresParking = semget (IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | DROITS_SEM);

	// Initialisation de VoituresParking
	ptrVoituresParking = (VoituresParking*) shmat(shmVoituresParking, NULL, 0);

	ptrVoituresParking->placesLibres = NB_PLACES;

	semctl(semVoituresParking, 0, SETVAL, 1);

	// --------------------------------------------------- Lancer les tâches
	// Tâche clavier
	if ((pidClavier = fork()) == 0 )
	{
		Clavier(msgFilesVoiture, msgRequeteSortie);
	}

	// Taches entrée
	for (int entree = 0; entree < NOMBRE_FILE_VOITURE; entree ++)
	{
		pidEntrees[entree] = CreerEntree(AUCUNE,shmVoituresParking,semVoituresParking,msgFilesVoiture[entree],semOuvrirPortes,entree);
	}

	// Tache Heure
	pidHeure = ActiverHeure();

	// ------------------------------------------------------- Phase moteur
}

static void MereMoteur()
{
	// Attendre la fin du clavier
	waitpid( pidClavier, NULL, 0);
}

static void MereDestruction()
{
	// Dire aux entrées de ce suicider
	for (int entree = 0; entree < NOMBRE_FILE_VOITURE; entree ++)
	{
		kill(pidEntrees[entree],SIGUSR2);
		waitpid(pidEntrees[entree], NULL, 0);
	}

	// Terminer Heure
	kill(pidHeure,SIGUSR2);
	waitpid(pidHeure, NULL, 0);

	// ------------------------------- Liberer les ressources partagées :

	// Boites aux lettres files voitures
	for (int file = 0; file < NOMBRE_FILE_VOITURE; file ++)
	{
		msgctl (msgFilesVoiture[file], IPC_RMID, 0);
	}

	// Sémaphores pour l'ouverture des portes
	semctl(semOuvrirPortes,0, IPC_RMID,0);

	// Boite aux lettres pour sortie
	msgctl (msgRequeteSortie, IPC_RMID, 0);

	// Zone mémoire pour ComptePlacesLibres
	shmctl (shmVoituresParking, IPC_RMID, 0);
	semctl (semVoituresParking, IPC_RMID, 0);

	// Achever l'application
	TerminerApplication(true);

	// Liberer le sémaphore du ficher de log
	semctl( semLog, 0,IPC_RMID, 0);
}

void ecrireLog(char const *message)
{
	semop( semLog, &reserver, 0);
	std::cerr << message;
	semop( semLog, &liberer, 0);
}