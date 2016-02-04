/*************************************************************************
                           CommandeAjouterObjet  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Réalisation de la classe <CommandeAjouterObjet> (fichier CommandeAjouterObjet.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
using namespace std;
//------------------------------------------------------ Include personnel
#include "CommandeAjouterObjet.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool CommandeAjouterObjet::Executer()
{
#ifdef DEBUG
	cout << "#Appel de CommandeAjouterObjet" << endl;
#endif
	bool estValide =  dessinHote->AjouterObjet(objet);
    if (estValide)
	estAnnule = !estValide;
	return estValide;
}

void CommandeAjouterObjet::Annuler()
{
	cout << "#Annulation de CommandeAjouterObjet" << endl;
	estAnnule = true;
	dessinHote->SupprimerObjet(objet->getNom());
}
//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur



CommandeAjouterObjet::CommandeAjouterObjet (Dessin* dessinHote,
											Objet* objetAjouter) : 
	super(dessinHote),
	objet(objetAjouter),
	estAnnule(true)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <CommandeAjouterObjet>" << endl;
#endif	
} //----- Fin de CommandeAjouterObjet


CommandeAjouterObjet::~CommandeAjouterObjet ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CommandeAjouterObjet>" << endl;
#endif
    // On supprime l'objet si la commande à été annulée
    // (Elle ne fait plus partie du Dessin)
    if (estAnnule)
    {
    	delete objet;
    }
} //----- Fin de ~CommandeAjouterObjet


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
