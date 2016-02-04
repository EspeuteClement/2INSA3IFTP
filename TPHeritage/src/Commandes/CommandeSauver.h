/*************************************************************************
                           CommandeSauver  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Interface de la classe <CommandeSauver> (fichier CommandeSauver.h) ------
#if ! defined ( _COMMANDE_SAUVER_H_ )
#define _COMMANDE_SAUVER_H_

//--------------------------------------------------- Interfaces utilisées
#include "../Commande.h"
#include "../Objet.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <CommandeSauver>
// Implémente le Command pattern. 
// Permet de représenter concrètement un appel de CommandeSauver, et de pouvoir
// l'annuler.
//------------------------------------------------------------------------ 

class CommandeSauver : public Commande
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /** Execute la CommandeSauver
    *   
    *   @return <em>true</em> si la CommandeSauver s'est bien exécuté, 
    *   <em>false</em> si elle à échouée.
    */
    bool Executer();

    /** Annule la CommandeSauver
    */
    void Annuler();

//-------------------------------------------- Constructeurs - destructeur

    /** Constructeur de copie d'une CommandeSauver
    *   
    *   @param uneCommandeSauver la CommandeSauver à copier
    */
    CommandeSauver ( const CommandeSauver & uneCommandeSauver );

    /** Constructeur de la CommandeSauver
    *
    *   @param dessinHote le Dessin sur lequel on doit effectuer la CommandeSauver
    */
    CommandeSauver (Dessin* dessinHote, string chemin);

    virtual ~CommandeSauver ( );

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés

    // La où l'on doit écrire
    ofstream* sortie;

    string chemin;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés
    typedef Commande super;
};

//----------------------------------------- Types dépendants de <CommandeSauver>

#endif // _CommandeSauver_AJOUTER_OBJET_H
