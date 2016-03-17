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



//------------------------------------------------------ Include personnel
//#include "Mere.h"
#include "libs/Outils.h"
#include "Config.h"
//------------------------------------------------------------- Constantes
//----------------------------------------------------------- Types privés

//------------------------------------------------------------------- Enum
enum FileVoiture {
  FILE_PROF_BP,   // 0 : entrée du parking pour les profs
  FILE_AUTRE_BP,  // 1 : entrée du parking pour les autres
  FILE_GB, // 2 : entrée du parking pour les profs ou autres
  NOMBRE_FILE_VOITURE // 3 : le nombre max de files voitures
};

static const int DROITS_SEM = 0660;

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

		for (int file = 0; file < NOMBRE_FILE_VOITURE; file ++)
		{
			int msId = msgget (IPC_PRIVATE, IPC_CREAT | IPC_EXCL);
			if (msId != -1)
			{
				FilesVoiture[file] = msId;
			}
			else
			{
				// Prévoir en cas de problème
				fprintf(log,"Erreur : Impossible de créer FileVoiture %d",file);
			}
		}


		// ------------------------------------------------------- Phase moteur
		sleep(5);

		// ----------------------------------------------  Phase de destruction
		

		// Liberer les ressources partagées :

		// Boites aux lettres files voitures
		for (int file = 0; file < NOMBRE_FILE_VOITURE; file ++)
		{
			msgctl (FilesVoiture[file], IPC_RMID, 0);
		}


		TerminerApplication(true);

		// Liberer le sémaphore du ficher de log
		semctl( semLog, IPC_RMID, 0);

		fclose(log);
	}

	return 0;
}