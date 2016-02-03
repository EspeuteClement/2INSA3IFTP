/*************************************************************************
                           CommandeAjouterObjet  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Interface de la classe <CommandeAjouterObjet> (fichier CommandeAjouterObjet.h) ------
#if ! defined ( _COMMANDE_AJOUTER_OBJET_H )
#define _COMMANDE_AJOUTER_OBJET_H

//--------------------------------------------------- Interfaces utilisées
#include "../Commande.h"
#include "../Objet.h"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <CommandeAjouterObjet>
// Implémente le Command pattern. 
// Permet de représenter concrètement un appel de CommandeAjouterObjet, et de pouvoir
// l'annuler.
//------------------------------------------------------------------------ 

class CommandeAjouterObjet : public Commande
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /** Execute la CommandeAjouterObjet
    *   
    *   @return <em>true</em> si la CommandeAjouterObjet s'est bien exécuté, 
    *   <em>false</em> si elle à échouée.
    */
    bool Executer();

    /** Annule la CommandeAjouterObjet
    */
    void Annuler();

//-------------------------------------------- Constructeurs - destructeur

    /** Constructeur de copie d'une CommandeAjouterObjet
    *   
    *   @param uneCommandeAjouterObjet la CommandeAjouterObjet à copier
    */
    CommandeAjouterObjet ( const CommandeAjouterObjet & uneCommandeAjouterObjet );

    /** Constructeur de la CommandeAjouterObjet
    *
    *   @param dessinHote le Dessin sur lequel on doit effectuer la CommandeAjouterObjet
    */
    CommandeAjouterObjet ( Dessin* dessinHote, Objet* objetAjouter   );

    virtual ~CommandeAjouterObjet ( );

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
    /* L'objet crée par la commande*/
    Objet* objet;

    /* Si la commande a été annulée*/
    bool estAnnule;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés
    typedef Commande super;
};

//----------------------------------------- Types dépendants de <CommandeAjouterObjet>

#endif // _CommandeAjouterObjet_AJOUTER_OBJET_H
