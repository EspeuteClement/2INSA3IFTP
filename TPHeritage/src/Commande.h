/*************************************************************************
                           Commande  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Interface de la classe <Commande> (fichier Commande.h) ------
#if ! defined ( _COMMANDE_H )
#define _COMMANDE_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <Commande>
// Implémente le Command pattern. 
// Permet de représenter concrètement un appel de commande, et de pouvoir
// l'annuler.
//------------------------------------------------------------------------ 

class Commande
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /** Execute la commande
    *   
    *   @return <em>true</em> si la commande s'est bien exécuté, 
    *   <em>false</em> si elle à échouée.
    */
    virtual bool Executer() = 0;

    /** Annule la commande
    */
    virtual void Annuler() = 0;

//-------------------------------------------- Constructeurs - destructeur

    /** Constructeur de copie d'une commande
    *   
    *   @param uneCommande la commande à copier
    */
    Commande ( const Commande & uneCommande );

    /** Constructeur de la commande
    *
    *   @param dessinHote le Dessin sur lequel on doit effectuer la commande
    */
    Commande ( Dessin* dessinHote);

    virtual ~Commande ( );

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
    Dessin* dessinHote;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Commande>

#endif // _COMMANDE_H
