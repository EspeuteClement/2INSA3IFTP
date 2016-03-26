/*************************************************************************
                           Entree  -  description
                             -------------------
    début                : 2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Réalisation de la classe <Entree> (fichier Entree.cpp)---

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#include <map>

//------------------------------------------------------ Include personnel
#include "Entree.h"
#include "Voiture.h"
#include "libs/Outils.h"

//#include "Config.h"
//#include "Mere.h"
//------------------------------------------------------------- Prototypes

/** Execute la phase d'initialisation de la tâche
*/
static void EntreePhaseInitialisation();

/** Execute la phase moteur de la tâche
*/
static void EntreePhaseMoteur();

/** Execute la phase de destruction de la tâche
*/
static void EntreePhaseDestruction();

static void EnregisterHandlers();
static void QuitterHandler(int sig);
static void ChildHandler(int sig);



//------------------------------------------------------------- Constantes

//------------------------------------------------------ Variables fichier

static int shmVoituresParking;  // Shared memory pour les voitures dans
                                // le parking
static int semVoituresParking;  // Sémaphore pour les voitures
static int msgFileVoiture;      // File de messages pour les voitures
                                // en attente
static int semOuvrirPortes;     // Sémaphores pour indiquer qu'une voiture
                                // à quitté le parking
static int idBariere;           // Le numéro d'identification de la barrière

static VoituresParking *parking;

static std::map<pid_t,Voiture> pidGarage;

static char buff[60];           // Buffer pour la manipulation de strings c

//----------------------------------------------  Outils pour les sémaphores
static sembuf reserver = {0,-1,0};
static sembuf liberer  = {0,1,0};
//-------------------------------------------------------------- Fonctions



int CreerEntree(TypeBarriere bariere, 
                int _shmVoituresParking, 
                int _semVoituresParking, 
                int _msgFileVoiture,
                int _semOuvrirPortes,
                int _idBariere
                )
{
    pid_t pid = fork();
	if(pid == 0)
	{
        // Initialiser toutes les variables fichier
        shmVoituresParking = _shmVoituresParking;
        semVoituresParking = _semVoituresParking;
        msgFileVoiture = _msgFileVoiture;
        semOuvrirPortes = _semOuvrirPortes;
        idBariere = _idBariere;

        EntreePhaseInitialisation();
        EntreePhaseMoteur();

        // Au cas où quelquechose d'étrange se passerait dans PhaseMoteur
        EntreePhaseDestruction();
	}

    sprintf(buff, "Processus Entree crée avec pid : %d\n", pid);
    ecrireLog(buff);
	return pid;
}

static void EntreePhaseInitialisation()
{
    sprintf(buff,"\t[[Entree n°%d]]\tInitialisation\n",idBariere);
    ecrireLog(buff);

    parking = (VoituresParking*) shmat( shmVoituresParking, NULL, 0);

    EnregisterHandlers();
}

static void EntreePhaseMoteur()
{
    Voiture v = {AUCUN,0,0};
    for(;;)
    {
        // Eviter que le ChildHandler ne fasse sauter cette commande
        while(msgrcv(msgFileVoiture, (void *) &v, sizeof(Voiture),0, 0)==-1);
        
        // Dessiner la voiture
        DessinerVoitureBarriere((TypeBarriere) (idBariere+1),v.type);
        
        parking->voituresEnAttente[idBariere].type      = v.type;
        parking->voituresEnAttente[idBariere].numero    = v.numero;
        parking->voituresEnAttente[idBariere].arrivee   = v.arrivee;

        // Si il n'y à plus de places disponibles
        semop(semVoituresParking,&reserver, 0);
        if (parking->placesLibres <= 0)
        {
            // Metre la voiture en attente
            //semop(semVoituresParking,&reserver, 0);
            semop(semVoituresParking,&liberer, 0);

            // Attendre la sortie d'une nouvelle voiture
            semctl (semOuvrirPortes, 0, SETVAL, 0);
            //semop(semOuvrirPortes,&reserver, idBariere);
            while(1)
            {

            };
        }
        else
        {
            semop(semVoituresParking,&liberer, 0);
        }
        semop(semVoituresParking,&reserver, 0);
        parking->placesLibres --;
        semop(semVoituresParking,&liberer, 0);
        
        //Voiture voitureAInserer = new Voiture(parking->voituresEnAttente[idBariere]);
        pid_t pid = GarerVoiture((TypeBarriere) (idBariere+1));
        pidGarage.insert(std::pair<pid_t,Voiture>(pid, parking->voituresEnAttente[idBariere]) );

        sprintf(buff,"Reception d'une voiture pour Entree n°%d\n",idBariere);
        
        sleep(1);
        ecrireLog(buff);
    }
}

static void EntreePhaseDestruction()
{
    sprintf(buff,"\t[[Entree n°%d]]\tDestruction\n",idBariere);
    ecrireLog(buff);

    // Désactiver ChildHandler pour eviter qu'il se déclence

    struct sigaction ignorer;
    ignorer.sa_handler = SIG_IGN;
    sigemptyset(&ignorer.sa_mask);
    ignorer.sa_flags = 0;

    sigaction(SIGCHLD,&ignorer,NULL);


    for (std::pair<const int, Voiture> couple : pidGarage)
    {
        // Dire aux process de se terminer
        kill(couple.first, SIGUSR2);
    }
    shmdt(parking);

    exit(0);
}


static void EnregisterHandlers()
{
    struct sigaction QuitterSigaction;
    QuitterSigaction.sa_handler = &QuitterHandler;
    sigaction(SIGUSR2,&QuitterSigaction,NULL);

    struct sigaction ChildSigaction;
    ChildSigaction.sa_handler = &ChildHandler;
    ChildSigaction.sa_flags = SA_RESTART;
    sigaction(SIGCHLD,&ChildSigaction,NULL);
}

static void QuitterHandler(int sig)
{
    sprintf(buff,"\t[[Entree n°%d]]\t\tSIGUSR2 recu\n",idBariere);
    ecrireLog(buff);

    EntreePhaseDestruction();
}

static void ChildHandler(int sig)
{
    // Récuperer absolument tout les enfants qui ont terminé
    int status;
    pid_t pid;
    while (( pid = waitpid(-1, &status, WNOHANG))>0) {
        int place = WEXITSTATUS(status);

        pidGarage.erase(pid);
        sprintf(buff,"\t[[Entree n°%d]]\tVoiture garée en place %d\n",idBariere,place);
        ecrireLog(buff);
    }
}