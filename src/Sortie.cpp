//---------------------- Réalisation <Sortie> ----------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
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
#include "libs/Outils.h"
#include "libs/Heure.h"
#include "Mere.h"
#include "Sortie.h"
#include "Clavier.h"
#include "Voiture.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//Memoire partagee qui stocke les voitures dans le parking, le nombre de
//places disponibles et les requetes
static int idMemoirePartagee;
//Boite aux lettres par laquelle Clavier passe le numero de voiture qui
//veut sortir
static int idFileVoitureSortie;

static void * memPartagee;

//Semaphore pour la memoire partagee indiquee ci-dessus
static int idSemMemPartagee;
//Tableau de semaphore pour indiquer la permission d'entree de la
//voiture en requete d'une entree 
static int idSemEntree;

static std::map<pid_t,int> pidSortie;

static char buff[60];

//------------------------------------------------------ Fonctions privées
static void finSortieVoiture(int numSignal)
// Algorithme : la methode appelee quand on recoit un SIGCHLD venu d'une
//              fille
//
{
	//La fille renvoie le numero de place de la voiture sortie
    int status;
    pid_t pidFille = wait(&status);
    unsigned int numS=WEXITSTATUS(status);

	//Etablir les operations necessaires des semaphores
    struct sembuf opP;
    opP.sem_num=0;
    opP.sem_op=-1;
    opP.sem_flg=0;

	struct sembuf opV;
    opV.sem_num=0;
    opV.sem_op=1;
    opV.sem_flg=0;
    
    //Eviter que handlerCHLD ne fasse sauter cette commande
    while(semop(idSemMemPartagee, &opP, 1) ==-1 && errno==EINTR);
    //Recuperer la voiture sortie
    Voiture uneVoiture = ((VoituresParking*)memPartagee)->voituresGarees[numS-1];
    //Incrementer le nombre de places disponibles
    ((VoituresParking*)memPartagee)->placesLibres++;
    semop(idSemMemPartagee, &opV, 1);   
    
    //Renouveler des messages sur l'ecran
    Effacer((TypeZone)numS);
    Effacer(MESSAGE);
	Afficher(MESSAGE, "Une voiture vient de sortir");
	AfficherSortie(uneVoiture.type,uneVoiture.numero,uneVoiture.arrivee,time(NULL));


    while(semop(idSemMemPartagee, &opP, 1) ==-1 && errno==EINTR);
    //Prendre le tableau des voitures en attente
    Voiture * lesVoitures = ((VoituresParking*)memPartagee)->voituresEnAttente;
    
    char buff[50];
    sprintf(buff,"\t[[Sortie]]\tPas de file ouverte\n");
    
    //Choisir la voiture la plus prioritaire et envoyer un message a
    //l'entree correspondante
	if(lesVoitures[FILE_PROF_BP].type==PROF && lesVoitures[FILE_GB].type!=PROF)
	{
		opV.sem_num=FILE_PROF_BP;
		semop(idSemEntree,&opV, 1);


        sprintf(buff,"\t[[Sortie]]\tOuvrir FILE_PROF_BP\n");

	}
	else if(lesVoitures[FILE_PROF_BP].type==PROF && lesVoitures[FILE_GB].type==PROF)
	{
		if(lesVoitures[FILE_PROF_BP].arrivee <= lesVoitures[FILE_GB].arrivee)
		{
			opV.sem_num=FILE_PROF_BP;
			semop(idSemEntree,&opV, 1);
			sprintf(buff,"\t[[Sortie]]\tOuvrir FILE_PROF_BP\n");
		}
		else
		{
			opV.sem_num=FILE_GB;
			semop(idSemEntree,&opV, 1);
			sprintf(buff,"\t[[Sortie]]\tOuvrir FILE_GB\n");
		}
	}
	else if(lesVoitures[FILE_PROF_BP].type!=PROF && lesVoitures[FILE_GB].type==PROF)
	{
		opV.sem_num=FILE_GB;
		semop(idSemEntree,&opV, 1);
		sprintf(buff,"\t[[Sortie]]\tOuvrir FILE_GB\n");
	}
	else if(lesVoitures[FILE_AUTRE_BP].type==AUTRE && lesVoitures[FILE_GB].type==AUTRE)
	{
		if(lesVoitures[FILE_AUTRE_BP].arrivee <= lesVoitures[FILE_GB].arrivee)
		{
			opV.sem_num=FILE_AUTRE_BP;
			semop(idSemEntree,&opV, 1);
			sprintf(buff,"\t[[Sortie]]\tOuvrir FILE_AUTRE_BP\n");
		}
		else
		{
			opV.sem_num=FILE_GB;
			semop(idSemEntree,&opV, 1);
			sprintf(buff,"\t[[Sortie]]\tOuvrir FILE_GB\n");
		}
	}
	else if(lesVoitures[FILE_AUTRE_BP].type==AUTRE && lesVoitures[FILE_GB].type==AUCUN)
	{
		opV.sem_num=FILE_AUTRE_BP;
		semop(idSemEntree,&opV, 1);
		sprintf(buff,"\t[[Sortie]]\tOuvrir FILE_AUTRE_BP\n");
	}
	else if(lesVoitures[FILE_AUTRE_BP].type==AUCUN && lesVoitures[FILE_GB].type==AUTRE)
	{
		opV.sem_num=FILE_GB;
		sprintf(buff,"\t[[Sortie]]\tOuvrir FILE_GB\n");
		semop(idSemEntree,&opV, 1);
	}
	opV.sem_num=0;
	ecrireLog(buff);
    semop(idSemMemPartagee, &opV, 1);
    
    //Effacer ce processus de la liste de destruction
    pidSortie.erase(pidFille);
}
//-----Fin de finSortieVoiture


static void finTache(int numSignal)
// Algorithme : la methode appelee quand on recoit un SIGUSR2 venu
//              de la mere
//
{
	//Terminer toutes les filles en train d'executer
	for (std::pair<const int, int> children : pidSortie)
    {
        kill(children.first, SIGUSR2);
    }
    //Detacher la memoire partagee
	shmdt(memPartagee);
	exit(0);
}//-----Fin de finTache


static void Initialisation(int idMP, int idFVS, int idSemMP, int idSemEnt)
{
// Algorithme : la phase d'initialisation
//
	sprintf(buff,"\t[[Sortie]]\tInitialisation\n");
    ecrireLog(buff);
    
    //Etablir les handlers
    struct sigaction handlerUSR2;
    handlerUSR2.sa_handler=finTache;
    sigemptyset(&handlerUSR2.sa_mask);
    handlerUSR2.sa_flags=0;
    sigaction(SIGUSR2, &handlerUSR2, NULL);
	
	struct sigaction handlerCHLD;
    handlerCHLD.sa_handler=finSortieVoiture;
    sigemptyset(&handlerCHLD.sa_mask);
    handlerCHLD.sa_flags=0;  
    sigaction(SIGCHLD, &handlerCHLD, NULL);
    
    //Initialiser les variables
    idMemoirePartagee=idMP;
    idFileVoitureSortie=idFVS;
    idSemMemPartagee=idSemMP;
    idSemEntree=idSemEnt;
    memPartagee=shmat(idMemoirePartagee,NULL,0);
    
}

static void Moteur()
{
	msgInt numS = {0};
	//Prendre le numero de la voiture sortie
    MY_SA_RESTART(msgrcv(idFileVoitureSortie, (void *) &numS, sizeof(msgInt),0,0));
    //Creer la fille
	pid_t pid = SortirVoiture(numS.numero);
	//Si la fille est bien creee, ajouter le pid du processus dans le 
	//tableau des filles pour preparer la destruction
	if (pid > 0){
		pidSortie.insert(std::pair<pid_t,int>(pid, numS.numero));
	}
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Sortie(int idMP, int idFVS, int idSemMP, int idSemEnt)
{
    Initialisation(idMP, idFVS, idSemMP, idSemEnt);
    
    for(;;)
	{
		Moteur();
	}
}
//-----Fin de Sortie
