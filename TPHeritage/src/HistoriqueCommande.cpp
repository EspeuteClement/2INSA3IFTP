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
	if (laCommande != NULL)
	{
		// On execute la commande, et on l'ajoute à la liste
		//de l'historique si elle renvoie true
		if (laCommande->Executer())
		{
			// Supprimer la commande qui occupe la liste
			positionCommandeCourante = getProchaineCommande();
			if (listeCommandes[positionCommandeCourante] != NULL)
			{
				delete listeCommandes[positionCommandeCourante];
			}
			listeCommandes[positionCommandeCourante] = laCommande;
			niveauAnnulation = 0;
			return true;
		}
		// Si la commande a échouée, on la delete
		delete laCommande;
	}
	return false;
}

bool HistoriqueCommande::AnnulerCommande()
{
	int precedanteCommande = getPositionAnnulation();
	// Si on n'a pas rebouclé dans le tableau (donc qu'on
	// n'a pas atteint un niveau d'annulation >= maxCommandes) et que
	// il y a bien une commande à annuler ...
	if (niveauAnnulation < maxCommandes
		&& listeCommandes[precedanteCommande] != NULL)
	{
		std::cout.setstate(std::ios_base::failbit);
		listeCommandes[precedanteCommande]->Annuler();
		std::cout.clear();
		niveauAnnulation ++;
		std::cout << "OK" << std::endl;
		return true;
	}
	std::cout << "ERR" << std::endl;
	return false;
}

bool HistoriqueCommande::ReprendreCommande()
{
	if (niveauAnnulation > 0)
	{
		niveauAnnulation --;
		std::cout.setstate(std::ios_base::failbit);
		listeCommandes[getPositionAnnulation()]->Executer();
		std::cout.clear();

		std::cout << "OK" << std::endl;
		return true;
	}
	std::cout << "ERR" << std::endl;
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


HistoriqueCommande::HistoriqueCommande (int nombreCommandes) :
	positionCommandeCourante(0),
	niveauAnnulation(0),
	maxCommandes(nombreCommandes)
// Algorithme :
//
{
	listeCommandes = new Commande*[maxCommandes];
	for (unsigned int positionHistorique = 0; 
			positionHistorique < maxCommandes;
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
		positionHistorique < maxCommandes ;
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
