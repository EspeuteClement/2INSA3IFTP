/*************************************************************************
                           HistoriqueCommande  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Réalisation de la classe <HistoriqueCommande> (fichier HistoriqueCommande.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <vector>

using namespace std;
//------------------------------------------------------ Include personnel
#include "HistoriqueCommande.h"

//------------------------------------------------------------- Constantes
const unsigned int HistoriqueCommande::MAX_COMMANDES = 30;
//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
// type HistoriqueCommande::Méthode ( liste de paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

bool HistoriqueCommande::AjouterCommande(Commande *laCommande)
{
	positionCommandeCourante = getProchaineCommande();
	// Supprimer la commande qui occupe la liste
	if (listeCommandes[positionCommandeCourante] != NULL)
	{
		delete listeCommandes[positionCommandeCourante];
	}
	listeCommandes[positionCommandeCourante] = laCommande;
	laCommande->Executer();
	positionCommandeValide = positionCommandeCourante;

	return true;
}

bool HistoriqueCommande::AnnulerCommande()
{
	int precedanteCommande = getPrecedanteCommande();
	// Si on n'a pas rebouclé dans le tableau (donc qu'on
	// n'a pas atteint la positionCommandeValide) et que
	// il y a bien une commande à annuler ...
	if (precedanteCommande != positionCommandeValide
		&& listeCommandes[precedanteCommande] != NULL)
	{
		listeCommandes[precedanteCommande]->Annuler();
		positionCommandeCourante = precedanteCommande;
		return true;
	}
	return false;
}

bool HistoriqueCommande::ReprendreCommande()
{
	if (positionCommandeCourante != positionCommandeValide)
	{
		positionCommandeCourante = getProchaineCommande();
		listeCommandes[positionCommandeCourante]->Executer();
	}
	return false;
}

//------------------------------------------------- Surcharge d'opérateurs
HistoriqueCommande & HistoriqueCommande::operator = ( const HistoriqueCommande & unHistoriqueCommande )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
HistoriqueCommande::HistoriqueCommande ( const HistoriqueCommande & unHistoriqueCommande )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <HistoriqueCommande>" << endl;
#endif
} //----- Fin de HistoriqueCommande (constructeur de copie)


HistoriqueCommande::HistoriqueCommande ( )
// Algorithme :
//
{
	listeCommandes = new Commande*[MAX_COMMANDES];
	for (unsigned int positionHistorique = 0; 
			positionHistorique < MAX_COMMANDES;
			positionHistorique ++)
	{
		listeCommandes[positionHistorique] = NULL;
	}
#ifdef MAP
    cout << "Appel au constructeur de <HistoriqueCommande>" << endl;
#endif
} //----- Fin de HistoriqueCommande


HistoriqueCommande::~HistoriqueCommande ( )
{
	// On itère à travers la liste des commandes et on
	// supprime chaque commande une par une
	for(int positionHistorique = 0; 
		positionHistorique < MAX_COMMANDES ;
		positionHistorique ++)
	{
		if (listeCommandes[positionHistorique] != NULL)
		{
			delete listeCommandes[positionHistorique];
		}
	}

	// On peut supprimer de manière propre la liste
	delete [] listeCommandes;

#ifdef MAP
    cout << "Appel au destructeur de <HistoriqueCommande>" << endl;
#endif
} //----- Fin de ~HistoriqueCommande


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
