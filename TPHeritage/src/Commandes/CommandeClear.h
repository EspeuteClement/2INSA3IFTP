/*************************************************************************
                           CommandeClear  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Interface de la classe <CommandeClear> (fichier CommandeClear.h) ------
#if ! defined ( _COMMANDE_CLEAR_H )
#define _COMMANDE_CLEAR_H

//--------------------------------------------------- Interfaces utilisées
#include "../Commande.h"
#include "../Objet.h"
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <CommandeClear>
// Implémente le Command pattern. 
// Permet de représenter concrètement un appel de CommandeClear, et de pouvoir
// l'annuler.
//------------------------------------------------------------------------ 

class CommandeClear : public Commande
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /** Execute la CommandeClear
    *   
    *   @return <em>true</em> si la CommandeClear s'est bien exécuté, 
    *   <em>false</em> si elle à échouée.
    */
    bool Executer();

    /** Annule la CommandeClear
    */
    void Annuler();

//-------------------------------------------- Constructeurs - destructeur

    /** Constructeur de copie d'une CommandeClear
    *   
    *   @param uneCommandeClear la CommandeClear à copier
    */
    CommandeClear ( const CommandeClear & uneCommandeClear );

    /** Constructeur de la CommandeClear
    *
    *   @param dessinHote le Dessin sur lequel on doit effectuer la CommandeClear
    */
    CommandeClear ( Dessin* dessinHote);

    virtual ~CommandeClear ( );

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
    /* L'objet supprimé */
    unordered_map<KEY_VALUE_LISTE>* listeSupprime;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés
    typedef Commande super;
};

//----------------------------------------- Types dépendants de <CommandeClear>

#endif // _CommandeClear_AJOUTER_OBJET_H
