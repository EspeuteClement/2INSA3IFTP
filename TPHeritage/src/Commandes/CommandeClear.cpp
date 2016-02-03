/*************************************************************************
                           CommandeClear  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Réalisation de la classe <CommandeClear> (fichier CommandeClear.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
using namespace std;
//------------------------------------------------------ Include personnel
#include "CommandeClear.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool CommandeClear::Executer()
{
#ifdef DEBUG
	cout << "#Appel de CommandeClear" << endl;
#endif
    unordered_map<KEY_VALUE_LISTE>* tampon = listeSupprime;
    listeSupprime = dessinHote->ListeObjets;
    dessinHote->ListeObjets = tampon;

    return true;
}

void CommandeClear::Annuler()
{
    // L'opération est identique à l'exécution
	Executer();
}
//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur



CommandeClear::CommandeClear (Dessin* dessinHote) : 
	super(dessinHote),
    listeSupprime(NULL)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <CommandeClear>" << endl;
#endif	
    listeSupprime = new unordered_map<KEY_VALUE_LISTE>();
} //----- Fin de CommandeClear


CommandeClear::~CommandeClear ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CommandeClear>" << endl;
#endif
    for(Dessin::ListeIterateur iterateur = listeSupprime->begin();
        iterateur != listeSupprime->end();
        iterateur ++)
    {
        delete iterateur->second;
    }
    delete listeSupprime;
} //----- Fin de ~CommandeClear


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
