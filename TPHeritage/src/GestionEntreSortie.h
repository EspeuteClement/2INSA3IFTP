#ifndef _GESTION_ES_H_
#define _GESTION_ES_H_

#include <string>
#include "Commande.h"
namespace GestionEntreSortie
{
	/** Enumérations de valeurs de retour possibles
	*	de la commande LireLigne
	*/
	enum ValeursRetour
	{
		OK,			// Une Commande a bien pu être crée
		UNDO,		// On veut faire un UNDO
		HIT,		//
		REDO,		// On veut faire un REDO
		SAVE,		// On veut faire une sauvegarde
		LIST,		// On veut faire une LIST
		ERR_PARAM,	// Les paramètres d'une commande sont erronés
		EXIT		// L'instruction exit a été entrée
	};

	typedef struct 
	{
		ValeursRetour valeur;
		Commande* commande;
	} Retour;

	

	/** Lis la ligne de commande ligne et l'interprète
	*	comme une commande.
	*	
	*	@param ligne Un string représentant la ligne à lire
	*	@param leDessin Un pointeur sur le Dessin sur laquelle
	*	la commande sera exécutée.
	*
	*	@return Un Retour contenant le code de retour de la
	*	fonction et un pointeur vers une commande si une
	*	Commande a pu être crée à partir de la ligne lue
	*/
	Retour LireLigne(std::string ligne,Dessin* leDessin);
}


#endif