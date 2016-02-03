/*************************************************************************
                           CommandeCharger  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Réalisation de la classe <CommandeCharger> (fichier CommandeCharger.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
#include <algorithm>
using namespace std;
//------------------------------------------------------ Include personnel
#include "CommandeCharger.h"
#include "../GestionEntreSortie.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool CommandeCharger::Executer()
{
#ifdef DEBUG
	cout << "#Appel de CommandeCharger" << endl;
#endif
    entre->open(chemin);
    
    if (entre->is_open())
    {
       std::string ligne;
        GestionEntreSortie::Retour retour;

        while( std::getline(*entre,ligne))
        {
            retour = GestionEntreSortie::LireLigne(ligne,dessinHote);
            if (retour.valeur != GestionEntreSortie::OK)
            {
                // On annule toutes les commandes en cours
                std::cout.setstate(std::ios_base::failbit);
                while(historique->AnnulerCommande());
                std::cout.clear();

                cout << "ERR" << endl;
                cout << "#Ficher de sauvegarde corrompu" << endl;
                // Et on quite :D
                entre->close();
                return false;
            }

            std::cout.setstate(std::ios_base::failbit);
            bool commandeOK = historique->AjouterCommande(
                retour.commande
            );
            std::cout.clear();
            
            if (!commandeOK)
            {
                // On annule toutes les commandes en cours
                std::cout.setstate(std::ios_base::failbit);
                while(historique->AnnulerCommande());
                std::cout.clear();

                cout << "ERR" << endl;
                cout << "#Un des objets est déjà présent dans le dessin." << endl;
                // Et on quite :D
                entre->close();
                return false;
            }
            
        }
        cout << "OK" << endl;
        entre->close();
        return true; 
    }
    cout << "ERR" << endl;
    cout << "#Ficher non existant" << endl;
    entre->close();
    return false;
    
}

void CommandeCharger::Annuler()
{
	cout << "#Annulation de CommandeCharger" << endl;
    while(historique->AnnulerCommande());
}
//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur



CommandeCharger::CommandeCharger (Dessin* dessinHote,
											     string chemin) : 
	super(dessinHote),
    chemin(chemin)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <CommandeCharger>" << endl;
#endif
    // Compter le nombre de lignes d'instructions
    entre = new ifstream();
    entre->open(chemin);
    int nbre = 0;
    if (entre->is_open())
    {
        nbre = std::count(istreambuf_iterator<char>(*entre),std::istreambuf_iterator<char>(),'\n');
        nbre ++;
    }
    entre->close();
    historique = new HistoriqueCommande(nbre);
} //----- Fin de CommandeCharger


CommandeCharger::~CommandeCharger ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CommandeCharger>" << endl;
#endif
    delete entre;
    // On supprime l'objet si la commande n'a pas été annulée
    // (Donc l'objet ne fait plus partie du déssin)
    delete historique;
} //----- Fin de ~CommandeCharger


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
