/*************************************************************************
                           Dessin  -  description
                             -------------------
    début                : 22/01/2015
    copyright            : (C) 2015-2016 par cespeute
*************************************************************************/

//---------- Réalisation de la classe <Dessin> (fichier dessin.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
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
#ifdef DEBUG
	cout << "#Dessin.AjouterObjet" << endl;
#endif
	string nom = unObjet->getNom();
	ListeIterateur trouver = ListeObjets->find(nom);

	/* Si l'objet existe déjà, on renvoie false*/
	if (trouver != ListeObjets->end())
	{
		return false;
	}

	(*ListeObjets)[nom] = unObjet;
	return true;
}

Objet* Dessin::SupprimerObjet(string nom)
{
	Objet* obj = getObjet(nom);
	#ifdef DEBUG
	cout << "#Dessin.SupprimerObjet " << (void*) obj << endl;
	#endif
	//ListeIterateur trouver = ListeObjets.find(nom);

	

	/** Si l'objet n'existe pas, on renvoie false */
	if (obj == NULL)
	{
		cout <<"#Objet null" <<endl;
		return NULL;
	}
	ListeObjets->erase(nom);
	#ifdef DEBUG
	cout << "#Dessin.SupprimerObjet after erase " << (void*) obj << endl;
	#endif
	return obj;

}

void Dessin::Enumere(ostream& sortie)
{
#ifdef DEBUG
	cout << "#Dessin.Enumere" << endl;
#endif
	for(ListeIterateur iterateur = ListeObjets->begin();
		iterateur != ListeObjets->end();
		iterateur ++)
	{
		sortie << iterateur->second->Description();
	}
}

void Dessin::Sauver(ostream& sortie)
{
#ifdef DEBUG
	cout << "#Dessin.Sauver" << endl;
#endif
	for(ListeIterateur iterateur = ListeObjets->begin();
	iterateur != ListeObjets->end();iterateur ++)
	{
		sortie << iterateur->second->CommandeReconstruire();
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
	ListeObjets = new unordered_map<KEY_VALUE_LISTE>();
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
    for(ListeIterateur iterateur = ListeObjets->begin();
		iterateur != ListeObjets->end();
		iterateur ++)
	{
		delete iterateur->second;
	}
	delete ListeObjets;
} //----- Fin de ~Dessin


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
