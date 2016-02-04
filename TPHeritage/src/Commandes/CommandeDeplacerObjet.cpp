/*************************************************************************
                           CommandeDeplacerObjet  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Réalisation de la classe <CommandeDeplacerObjet> (fichier CommandeDeplacerObjet.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
using namespace std;
//------------------------------------------------------ Include personnel
#include "CommandeDeplacerObjet.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool CommandeDeplacerObjet::Executer()
{
#ifdef DEBUG
	cout << "#Appel de CommandeDeplacerObjet" << endl;
#endif
    if (objetDeplace != NULL)
    {
        objetDeplace->Deplacer(dx,dy);
        return true;
    }
    return false;
}

void CommandeDeplacerObjet::Annuler()
{
	cout << "#Annulation de CommandeDeplacerObjet" << endl;
	if (objetDeplace != NULL)
    {
        objetDeplace->Deplacer(-dx,-dy);
    }
}
//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur



CommandeDeplacerObjet::CommandeDeplacerObjet (Dessin* dessinHote,
											     string nomObjet, long dx, long dy) : 
	super(dessinHote),
	nomObjet(nomObjet),
    dx(dx),
    dy(dy)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <CommandeDeplacerObjet>" << endl;
#endif
    objetDeplace = dessinHote->getObjet(nomObjet);
} //----- Fin de CommandeDeplacerObjet


CommandeDeplacerObjet::~CommandeDeplacerObjet ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CommandeDeplacerObjet>" << endl;
#endif
    // On supprime l'objet si la commande n'a pas été annulée
    // (Donc l'objet ne fait plus partie du déssin)
} //----- Fin de ~CommandeDeplacerObjet


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
