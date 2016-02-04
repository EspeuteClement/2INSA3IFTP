/*************************************************************************
                           ObjetMultiple  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <ObjetMultiple> (fichier ObjetMultiple.h) ------
#if ! defined ( OBJETMULTIPLE_H )
#define OBJETMULTIPLE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include "Point.h"
#include "Objet.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <ObjetMultiple>
//
//
//------------------------------------------------------------------------

class ObjetMultiple : public Objet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
	/**Creer un objet a partir d'un objet existant
	 *
	 *@param unObjetMultiple l'objet que l'on veut copier
	 */
    ObjetMultiple ( const ObjetMultiple & unObjetMultiple )
		:Objet(unObjetMultiple.nom){}

	/**Creer un objet a partir d'un nom
	 *
	 *@param unNom le nom fourni pour l'objet
	 */
    ObjetMultiple (std::string unNom):Objet(unNom){}

    /**Supprimer les objets crees dynamiquement
     *
     */
    virtual ~ObjetMultiple ( ){}

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
    std::vector<Objet*> listeObjets;

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <ObjetMultiple>

#endif // OBJETMULTIPLE_H
