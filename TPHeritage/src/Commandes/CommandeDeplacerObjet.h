/*************************************************************************
                           CommandeDeplacerObjet  -  description
                             -------------------
    début                : 17/01/2016
    copyright            : (C) 2016 par cespeute
*************************************************************************/

//---------- Interface de la classe <CommandeDeplacerObjet> (fichier CommandeDeplacerObjet.h) ------
#if ! defined ( _COMMANDE_DEPLACER_OBJET_H_ )
#define _COMMANDE_DEPLACER_OBJET_H_

//--------------------------------------------------- Interfaces utilisées
#include "../Commande.h"
#include "../Objet.h"
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <CommandeDeplacerObjet>
// Implémente le Command pattern. 
// Permet de représenter concrètement un appel de CommandeDeplacerObjet, et de pouvoir
// l'annuler.
//------------------------------------------------------------------------ 

class CommandeDeplacerObjet : public Commande
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /** Execute la CommandeDeplacerObjet
    *   
    *   @return <em>true</em> si la CommandeDeplacerObjet s'est bien exécuté, 
    *   <em>false</em> si elle à échouée.
    */
    bool Executer();

    /** Annule la CommandeDeplacerObjet
    */
    void Annuler();

//-------------------------------------------- Constructeurs - destructeur

    /** Constructeur de copie d'une CommandeDeplacerObjet
    *   
    *   @param uneCommandeDeplacerObjet la CommandeDeplacerObjet à copier
    */
    CommandeDeplacerObjet ( const CommandeDeplacerObjet & uneCommandeDeplacerObjet );

    /** Constructeur de la CommandeDeplacerObjet
    *
    *   @param dessinHote le Dessin sur lequel on doit effectuer la CommandeDeplacerObjet
    *   @param nomObjet le nom de l'objet à déplacer
    *   @param dx le déplacement sur l'axe x de l'objet
    *   @param dy le déplacement sur l'axe y de l'objet
    */
    CommandeDeplacerObjet ( Dessin* dessinHote, const string nomObjet, long dx, long dy);

    virtual ~CommandeDeplacerObjet ( );

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
    string nomObjet;

    /* L'objet supprimé */
    Objet* objetDeplace;

    long dx;
    long dy;

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés
    typedef Commande super;
};

//----------------------------------------- Types dépendants de <CommandeDeplacerObjet>

#endif // _CommandeDeplacerObjet_AJOUTER_OBJET_H
