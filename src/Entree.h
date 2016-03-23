/*************************************************************************
                           Entree  -  description
                             -------------------
    début                : 2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Interface de la classe <Entree> (fichier Entree.h) ------
#if ! defined ( _ENTREE_H_ )
#define _ENTREE_H_

//--------------------------------------------------- Interfaces utilisées
#include "libs/Outils.h"
//------------------------------------------------------------- Constantes 
#include "Mere.h"
//------------------------------------------------------------------ Types 

// ------------------------------------------------------------- Fonctions

/** Crée une nouvelle tâche entrée
* @param shmComptePlaceLibre l'id de la zone de mémoire partagée qui compte
*        le nombre de places libres
* @param semComptePlacesLibres l'id du mutex qui régule l'accés à la
*        zone de mémoire shmComptePlaceLibre
* @param fileVoiture l'id de la boite aux lettres qui contient les
*         voitures qui font la file devant l'entrée
* @param semOuvrirPortes l'id du tabeau de sémaphores qui permet de
*        signifier à la porte qu'une place c'est libérée
* @param idBariere l'id de la barière pour la situer dans le tableau
         semOuvrirPortes
* @return Le pid de la tâche Entree qui a été crée.
*/
int CreerEntree(TypeBarriere bariere, 
                int shmComptePlacesLibres, 
                int semComptePlacesLibres, 
                int fileVoiture,
                int semOuvrirPortes,
                int idBariere
                );

//----------------------------------------- Types dépendants de <Entree>

#endif // _ENTREE_H_
