/*************************************************************************
                           Dessin  -  description
                             -------------------
    début                : 22/01/2015
    copyright            : (C) 2015-2016 par cespeute
*************************************************************************/

//---------- Réalisation de la classe <Dessin> (fichier dessin.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
//#include <iostream>
//#include <unordered_map>
#include <string>

using namespace std;
//------------------------------------------------------ Include personnel
#include "Dessin.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
// type Dessin::Méthode ( liste de paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

bool Dessin::AjouterObjet(Objet* unObjet)
{
	string nom = unObjet->getNom();
	ListeIterateur trouver = ListeObjets.find(nom);

	/* Si l'objet existe déjà, on renvoie false*/
	if (trouver != ListeObjets.end())
	{
		return false;
	}

	ListeObjets[nom] = unObjet;
	return true;
}

bool Dessin::SupprimerObjet(string nom)
{
	ListeIterateur trouver = ListeObjets.find(nom);

	/** Si l'objet n'existe pas, on renvoie false */
	if (trouver == ListeObjets.end())
	{
		return false;
	}

	ListeObjets.erase(nom);
	return true;
}

void Dessin::Enumere(ostream sortie)
{
	for(ListeIterateur iterateur = ListeObjets.begin();
		iterateur != ListeObjets.end();
		iterateur ++)
	{
		sortie << iterateur->second->Description() << endl;
	}
}

void Dessin::Sauver(ostream sortie)
{
	for(ListeIterateur iterateur = ListeObjets.begin();
	iterateur != ListeObjets.end();iterateur ++)
	{
		sortie << iterateur->second->CommandeReconstruire() << endl;
	}
}


//------------------------------------------------- Surcharge d'opérateurs
Dessin & Dessin::operator = ( const Dessin & unDessin )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Dessin::Dessin ( const Dessin & unDessin )
// Algorithme :
//
{
	ListeObjets = unDessin.ListeObjets;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Dessin>" << endl;
#endif
} //----- Fin de Dessin (constructeur de copie)


Dessin::Dessin ( )
// Algorithme :
//
{
	ListeObjets = unordered_map<KEY_VALUE_LISTE>();
#ifdef MAP
    cout << "Appel au constructeur de <Dessin>" << endl;
#endif
} //----- Fin de Dessin


Dessin::~Dessin ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Dessin>" << endl;
#endif
} //----- Fin de ~Dessin


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
