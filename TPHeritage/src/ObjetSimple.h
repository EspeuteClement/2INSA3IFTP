/*************************************************************************
                           ObjetSimple  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <ObjetSimple> (fichier ObjetSimple.h) ------
#if ! defined ( OBJETSIMPLE_H )
#define OBJETSIMPLE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include "Point.h"
#include "Objet.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <ObjetSimple>
//
//
//------------------------------------------------------------------------

class ObjetSimple : public Objet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
	/**Creer un objet a partir d'un objet existant
	 *
	 *@param unObjetSimple l'objet que l'on veut copier
	 */
    ObjetSimple ( const ObjetSimple & unObjetSimple )
		:Objet(unObjetSimple.nom){}

	/**Creer un objet a partir d'un nom
	 *
	 *@param unNom le nom fourni pour l'objet
	 */
    ObjetSimple (std::string unNom):Objet(unNom){}

    /**Supprimer les points de l'objet crees dynamiquement
     *
     */
    virtual ~ObjetSimple ( ){}

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
    std::vector<Point*> listePoints;

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <ObjetSimple>

#endif // OBJETSIMPLE_H

