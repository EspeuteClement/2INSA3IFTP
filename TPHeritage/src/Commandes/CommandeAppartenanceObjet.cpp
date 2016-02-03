/*************************************************************************
                           CommandeAppartenanceObjet  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Réalisation de la classe <CommandeAppartenanceObjet> (fichier CommandeAppartenanceObjet.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
using namespace std;
//------------------------------------------------------ Include personnel
#include "CommandeAppartenanceObjet.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool CommandeAppartenanceObjet::Executer()
{
	Objet *obj = dessinHote->getObjet(nomObjet);
#ifdef DEBUG
	cout << "#Appel de CommandeAppartenanceObjet" << endl;
	cout << "#" << static_cast<void*>(obj) << endl;
#endif
	

	if (obj && obj->EstDedans(lePoint))
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}

	//On retourn faux pour que la commande ne soit pas ajouté
	//à l'historique
    return false;
}

void CommandeAppartenanceObjet::Annuler()
{
	// NOTE : La commande ne peut pas être annulée
}
//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur



CommandeAppartenanceObjet::CommandeAppartenanceObjet (Dessin* dessinHote,
											     string nomObjet, Point lePoint) : 
	super(dessinHote),
	nomObjet(nomObjet),
	lePoint(lePoint)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <CommandeAppartenanceObjet>" << endl;
#endif
} //----- Fin de CommandeAppartenanceObjet


CommandeAppartenanceObjet::~CommandeAppartenanceObjet ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CommandeAppartenanceObjet>" << endl;
#endif

} //----- Fin de ~CommandeAppartenanceObjet


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
