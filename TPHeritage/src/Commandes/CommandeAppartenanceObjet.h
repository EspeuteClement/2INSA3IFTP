/*************************************************************************
                           CommandeAppartenanceObjet  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Interface de la classe <CommandeAppartenanceObjet> (fichier CommandeAppartenanceObjet.h) ------
#if ! defined ( _COMMANDE_APPARTENANCE_OBJET_H_ )
#define _COMMANDE_APPARTENANCE_OBJET_H_

//--------------------------------------------------- Interfaces utilisées
#include "../Commande.h"
#include "../Objet.h"
#include "../Point.h"
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <CommandeAppartenanceObjet>
// Implémente le Command pattern. 
// Permet de représenter concrètement un appel de CommandeAppartenanceObjet, et de pouvoir
// l'annuler.
//------------------------------------------------------------------------ 

class CommandeAppartenanceObjet : public Commande
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /** Execute la CommandeAppartenanceObjet
    *   
    *   @return <em>true</em> si la CommandeAppartenanceObjet s'est bien exécuté, 
    *   <em>false</em> si elle à échouée.
    */
    bool Executer();

    /** Annule la CommandeAppartenanceObjet
    */
    void Annuler();

//-------------------------------------------- Constructeurs - destructeur

    /** Constructeur de copie d'une CommandeAppartenanceObjet
    *   
    *   @param uneCommandeAppartenanceObjet la CommandeAppartenanceObjet à copier
    */
    CommandeAppartenanceObjet ( const CommandeAppartenanceObjet & uneCommandeAppartenanceObjet );

    /** Constructeur de la CommandeAppartenanceObjet
    *
    *   @param dessinHote le Dessin sur lequel on doit effectuer la CommandeAppartenanceObjet
    */
    CommandeAppartenanceObjet ( Dessin* dessinHote, const string nomObjet, Point lePoint );

    virtual ~CommandeAppartenanceObjet ( );

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
    /* L'objet de la commande*/
    string nomObjet;
    Point lePoint;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés
    typedef Commande super;
};

//----------------------------------------- Types dépendants de <CommandeAppartenanceObjet>

#endif // _CommandeAppartenanceObjet_AJOUTER_OBJET_H
