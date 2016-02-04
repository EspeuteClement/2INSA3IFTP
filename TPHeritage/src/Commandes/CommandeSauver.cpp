/*************************************************************************
                           CommandeSauver  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Réalisation de la classe <CommandeSauver> (fichier CommandeSauver.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
#include <algorithm>
using namespace std;
//------------------------------------------------------ Include personnel
#include "CommandeSauver.h"
#include "../GestionEntreSortie.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool CommandeSauver::Executer()
{
#ifdef DEBUG
	cout << "#Appel de CommandeSauver" << endl;
#endif
    sortie->open(chemin);
    if (sortie->is_open())
    {
        dessinHote->Sauver(*sortie);
        cout << "#Fichier sauvé" << endl;
        cout << "OK" << endl;
    }
    else
    {
        cout << "#Impossible d'ouvrir le fichier" << endl;
        cout << "ERR" << endl;
    }
    // On retourne false pour ne pas être sauvé dans l'historique.
    return false;
}

void CommandeSauver::Annuler()
{
    // Commande non annulable
}
//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur



CommandeSauver::CommandeSauver (Dessin* dessinHote,
											     string chemin) : 
	super(dessinHote),
    chemin(chemin)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <CommandeSauver>" << endl;
#endif
    // Compter le nombre de lignes d'instructions
    sortie = new ofstream();
} //----- Fin de CommandeSauver


CommandeSauver::~CommandeSauver ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CommandeSauver>" << endl;
#endif
    delete sortie;
} //----- Fin de ~CommandeSauver


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
