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
#include "Entree.h"
#include "Clavier.h"
#include "Voiture.h"
#include "Sortie.h"

//#define DEBUG
//------------------------------------------------------------- Constantes
//----------------------------------------------------------- Types privés

//------------------------------------------------------------------- Enum

static const int DROITS_SEM = S_IRUSR | S_IWUSR;
static const int DROITS_SHM = S_IRUSR | S_IWUSR;
static const int DROITS_MSG = S_IRUSR | S_IWUSR;

//------------------------------------------------------------- Globales



//----------------------------------------------------- Méthodes Statiques

static void MereInitialisation();
static void MereMoteur();
static void MereDestruction();

//----------------------------------------------------- Variables Fichier

static int msgFilesVoiture[NOMBRE_FILE_VOITURE];
#ifdef DEBUG
static int semLog;
#endif
static char buff[55];

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
static pid_t pidSortie;


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
#ifdef DEBUG
	semLog = semget (IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | DROITS_SEM);
	semctl (semLog, 0, SETVAL, 1);
#endif

	sprintf(buff,"\t[[Mere]]\tInitialiserApplicatio()\n");
    ecrireLog(buff);

	InitialiserApplication(XTERM);

	sprintf(buff,"\t[[Mere]]Mise en place des signaux\t\n");
    ecrireLog(buff);
	// Masquer les signaux :
	struct sigaction ignorer;
	ignorer.sa_handler = SIG_IGN;
	sigemptyset(&ignorer.sa_mask);
	ignorer.sa_flags = 0;

	// Désactiver les interruptions indésirables
	sigaction(SIGINT, &ignorer, NULL);
	sigaction(SIGUSR2,&ignorer, NULL);
	sigaction(SIGCHLD,&ignorer, NULL);

	// ---------------------------------- Créer les ressources partagées :

	sprintf(buff,"\t[[Mere]]\tCreation des BaL\n");
    ecrireLog(buff);
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

	sprintf(buff,"\t[[Mere]]Création Sémaphore OuvrirPortes\t\n");
    ecrireLog(buff);
	// Sémaphores pour l'ouverture des portes
	semOuvrirPortes = semget(IPC_PRIVATE, NOMBRE_FILE_VOITURE, IPC_CREAT | IPC_EXCL | DROITS_SEM) ;
	for (int idBariere = 0; idBariere < NOMBRE_FILE_VOITURE; ++idBariere)
	{
		semctl (semOuvrirPortes, idBariere, SETVAL, 0);
	}


	sprintf(buff,"\t[[Mere]]Création BaL RequeteSortie\t\n");
    ecrireLog(buff);
	// Boite au lettre pour sortie
	msgRequeteSortie = msgget (IPC_PRIVATE, IPC_CREAT | IPC_EXCL | DROITS_MSG);

	// Zone mémoire pour VoituresParking
	sprintf(buff,"\t[[Mere]]Création Mémoire VoituresParking\t\n");
    ecrireLog(buff);
	shmVoituresParking = shmget (IPC_PRIVATE, sizeof(VoituresParking), IPC_CREAT | IPC_EXCL | DROITS_SHM);
	semVoituresParking = semget (IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | DROITS_SEM);
	semctl(semVoituresParking, 0, SETVAL, 1);
	
	// Initialisation de VoituresParking
	sprintf(buff,"\t[[Mere]]Création Pointeur VoituresParking\t\n");
    ecrireLog(buff);
	ptrVoituresParking = (VoituresParking*) shmat(shmVoituresParking, NULL, 0);

	ptrVoituresParking->placesLibres = NB_PLACES;



	// --------------------------------------------------- Lancer les tâches


	sprintf(buff,"\t[[Mere]]Lancer Tâche Sortie\t\n");
    ecrireLog(buff);
	if ((pidSortie = fork()) == 0)
	{
		Sortie(shmVoituresParking, msgRequeteSortie, semVoituresParking, semOuvrirPortes);
	}

	// Taches entrée
	for (int entree = 0; entree < NOMBRE_FILE_VOITURE; entree ++)
	{
		pidEntrees[entree] = CreerEntree(shmVoituresParking,semVoituresParking,msgFilesVoiture[entree],semOuvrirPortes,entree);
	}

	sprintf(buff,"\t[[Mere]]Lancer Tâche Heure\t\n");
    ecrireLog(buff);
	// Tache Heure
	pidHeure = ActiverHeure();

	// Tâche clavier
	sprintf(buff,"\t[[Mere]]Lancer Tâche clavier\t\n");
    ecrireLog(buff);
	if ((pidClavier = fork()) == 0 )
	{
		Clavier(msgFilesVoiture, msgRequeteSortie);
	}

	// ------------------------------------------------------- Phase moteur
}

static void MereMoteur()
{
	// Attendre la fin du clavier
	sprintf(buff,"\t[[Mere]]Attente fin clavier\t\n");
    ecrireLog(buff);
	MY_SA_RESTART(waitpid( pidClavier, NULL, 0));
}

static void MereDestruction()
{
	// Dire aux entrées de ce suicider
	for (int entree = 0; entree < NOMBRE_FILE_VOITURE; entree ++)
	{
		kill(pidEntrees[entree],SIGUSR2);
		waitpid(pidEntrees[entree], NULL, 0);
	}
	

	// Terminer sortie
	sprintf(buff,"\t[[Mere]]Détruire Sortie\t\n");
    ecrireLog(buff);
	kill(pidSortie, SIGUSR2);
	waitpid(pidSortie,NULL,0);

	// Terminer Heure

	sprintf(buff,"\t[[Mere]]Détruire Heure\t\n");
    ecrireLog(buff);
	kill(pidHeure,SIGUSR2);
	waitpid(pidHeure, NULL, 0);

	// ------------------------------- Liberer les ressources partagées :

	// Boites aux lettres files voitures
	sprintf(buff,"\t[[Mere]]Liberer BaL FilesVoiture\t\n");
    ecrireLog(buff);
	for (int file = 0; file < NOMBRE_FILE_VOITURE; file ++)
	{
		msgctl (msgFilesVoiture[file], IPC_RMID, 0);
	}

	// Sémaphores pour l'ouverture des portes
	sprintf(buff,"\t[[Mere]]Liberer OuvrirPortes\n");
    ecrireLog(buff);
	semctl(semOuvrirPortes,0, IPC_RMID,0);

	// Boite aux lettres pour sortie
	sprintf(buff,"\t[[Mere]]Détruire RequeteSortie\t\n");
    ecrireLog(buff);
	msgctl (msgRequeteSortie, IPC_RMID, 0);

	// Zone mémoire pour ComptePlacesLibres
	sprintf(buff,"\t[[Mere]]Détruire ComptePlacesLibres\t\n");
    ecrireLog(buff);
	semctl (semVoituresParking, IPC_RMID, 0);
	shmctl (shmVoituresParking, IPC_RMID, 0);


	// Achever l'application
	sprintf(buff,"\t[[Mere]]TerminerApplication()\t\n");
    ecrireLog(buff);
	TerminerApplication(true);

	// Liberer le sémaphore du ficher de log
#ifdef DEBUG
	semctl( semLog, 0,IPC_RMID, 0);
#endif
}


void ecrireLog(char const *message)
{
#ifdef DEBUG
	sembuf reserver = {0,-1,0};
	sembuf liberer  = {0,1,0};
	MY_SA_RESTART(semop( semLog, &reserver, 0));
	std::cerr << message;
	semop( semLog, &liberer, 0);
#endif
}