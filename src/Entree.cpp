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

//------------------------------------------------------ Include personnel
#include "Entree.h"
//#include "Config.h"
//#include "Mere.h"

//------------------------------------------------------------- Constantes

//-------------------------------------------------------------- Fonctions

int CreerEntree(TypeBarriere bariere, 
                int shmComptePlacesLibres, 
                int semComptePlacesLibres, 
                int fileVoiture,
                int semOuvrirPortes,
                int idBariere
                )
{
    pid_t pid = fork();
	if(pid == 0)
	{
        ecrireLog("Process Creer Entree Fils\n");
		exit(1);
	}
    char str[50];
    sprintf(str, "Process Creer Entree Pere%d\n", pid);
    ecrireLog(str);
	return pid;
}