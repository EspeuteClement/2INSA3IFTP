/*************************************************************************
                           CommandeSupprimerObjet  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Interface de la classe <CommandeSupprimerObjet> (fichier CommandeSupprimerObjet.h) ------
#if ! defined ( _COMMANDE_SUPPRIMER_OBJET_H_ )
#define _COMMANDE_SUPPRIMER_OBJET_H_

//--------------------------------------------------- Interfaces utilisées
#include "../Commande.h"
#include "../Objet.h"
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <CommandeSupprimerObjet>
// Implémente le Command pattern. 
// Permet de représenter concrètement un appel de CommandeSupprimerObjet, et de pouvoir
// l'annuler.
//------------------------------------------------------------------------ 

class CommandeSupprimerObjet : public Commande
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /** Execute la CommandeSupprimerObjet
    *   
    *   @return <em>true</em> si la CommandeSupprimerObjet s'est bien exécuté, 
    *   <em>false</em> si elle à échouée.
    */
    bool Executer();

    /** Annule la CommandeSupprimerObjet
    */
    void Annuler();

//-------------------------------------------- Constructeurs - destructeur

    /** Constructeur de copie d'une CommandeSupprimerObjet
    *   
    *   @param uneCommandeSupprimerObjet la CommandeSupprimerObjet à copier
    */
    CommandeSupprimerObjet ( const CommandeSupprimerObjet & uneCommandeSupprimerObjet );

    /** Constructeur de la CommandeSupprimerObjet
    *
    *   @param dessinHote le Dessin sur lequel on doit effectuer la CommandeSupprimerObjet
    */
    CommandeSupprimerObjet ( Dessin* dessinHote, const vector<string> nomsObjet);

    virtual ~CommandeSupprimerObjet ( );

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
    vector<string> nomsObjet;

    /* L'objet supprimé */
    vector<Objet*> objetsSupprime;

    /* Si l'objet est bien supprimé */
    bool estSupprime;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés
    typedef Commande super;
};

//----------------------------------------- Types dépendants de <CommandeSupprimerObjet>

#endif // _CommandeSupprimerObjet_AJOUTER_OBJET_H
