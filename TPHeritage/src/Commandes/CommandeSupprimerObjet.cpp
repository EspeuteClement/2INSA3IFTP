/*************************************************************************
                           CommandeSupprimerObjet  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Réalisation de la classe <CommandeSupprimerObjet> (fichier CommandeSupprimerObjet.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
using namespace std;
//------------------------------------------------------ Include personnel
#include "CommandeSupprimerObjet.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool CommandeSupprimerObjet::Executer()
{
#ifdef DEBUG
	cout << "#Appel de CommandeSupprimerObjet" << endl;
#endif
    estSupprime = true;
    // Vérifier que les objets existent bien
    for (auto& s : nomsObjet)
    {
        Objet* obj = dessinHote->getObjet(s);
        if (obj == NULL)
        {
            estSupprime = false;
#ifdef DEBUG
            cout << "#Un des objets n'est pas présent dans le dessin." << endl;
#endif
            return false;
        }
    }

    if (estSupprime)
    {
        for (auto& s : nomsObjet)
        {
            Objet* obj = dessinHote->SupprimerObjet(s);
            if (obj != NULL)
            {
                objetsSupprime.push_back(obj);
            }   
        }
    }
    return estSupprime;
}

void CommandeSupprimerObjet::Annuler()
{
	cout << "#Annulation de CommandeSupprimerObjet" << endl;
	if (estSupprime)
    {
        for (auto& obj : objetsSupprime)
        {
            dessinHote->AjouterObjet(obj);
        }
        objetsSupprime.clear();
        estSupprime = false;
    }
}
//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur



CommandeSupprimerObjet::CommandeSupprimerObjet (Dessin* dessinHote,
											     vector<string> nomsObjet) : 
	super(dessinHote),
	nomsObjet(nomsObjet),
    estSupprime(false)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <CommandeSupprimerObjet>" << endl;
#endif
    objetsSupprime.clear();	
} //----- Fin de CommandeSupprimerObjet


CommandeSupprimerObjet::~CommandeSupprimerObjet ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CommandeSupprimerObjet>" << endl;
#endif
    // On supprime l'objet si la commande n'a pas été annulée
    // (Donc l'objet ne fait plus partie du déssin)
    if (estSupprime)
    {
        for (int i = 0; i < objetsSupprime.size(); i++)
        {
            delete objetsSupprime[i];
        }
    }
} //----- Fin de ~CommandeSupprimerObjet


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
