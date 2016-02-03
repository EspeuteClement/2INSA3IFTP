/*************************************************************************
                           CommandeCharger  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Interface de la classe <CommandeCharger> (fichier CommandeCharger.h) ------
#if ! defined ( _COMMANDE_SAUVER_H_ )
#define _COMMANDE_SAUVER_H_

//--------------------------------------------------- Interfaces utilisées
#include "../Commande.h"
#include "../Objet.h"
#include "../HistoriqueCommande.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <CommandeCharger>
// Implémente le Command pattern. 
// Permet de représenter concrètement un appel de CommandeCharger, et de pouvoir
// l'annuler.
//------------------------------------------------------------------------ 

class CommandeCharger : public Commande
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /** Execute la CommandeCharger
    *   
    *   @return <em>true</em> si la CommandeCharger s'est bien exécuté, 
    *   <em>false</em> si elle à échouée.
    */
    bool Executer();

    /** Annule la CommandeCharger
    */
    void Annuler();

//-------------------------------------------- Constructeurs - destructeur

    /** Constructeur de copie d'une CommandeCharger
    *   
    *   @param uneCommandeCharger la CommandeCharger à copier
    */
    CommandeCharger ( const CommandeCharger & uneCommandeCharger );

    /** Constructeur de la CommandeCharger
    *
    *   @param dessinHote le Dessin sur lequel on doit effectuer la CommandeCharger
    */
    CommandeCharger (Dessin* dessinHote, string chemin);

    virtual ~CommandeCharger ( );

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
    // L'historique des commandes qui seront effectuées
    // pour recréer le dessin (ce qui permet d'annuler)
    // la commande
    HistoriqueCommande *historique;

    // La où l'on doit écrire
    ifstream* entre;

    string chemin;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés
    typedef Commande super;
};

//----------------------------------------- Types dépendants de <CommandeCharger>

#endif // _CommandeCharger_AJOUTER_OBJET_H
