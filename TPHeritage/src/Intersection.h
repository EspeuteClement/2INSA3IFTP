/*************************************************************************
                           Intersection  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Intersection> (fichier Intersection.h) ------
#if ! defined ( INTERSECTION_H )
#define INTERSECTION_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include "ObjetMultiple.h"
#include "Point.h"
#include "Segment.h"
#include "Rectangle.h"
#include "PolygoneConvexe.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Intersection>
//
//
//------------------------------------------------------------------------

class Intersection : public ObjetMultiple
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /**Tester si le point en parametre est dans l'intersection
     *
     *@param unPoint le point que l'on fait le test
     *@return true si le point est dans l'intersection et sinon false
     */
	virtual bool EstDedans ( const Point &unPoint );

	/**Preparer la chaine de la description de l'intersection pour l'affichage
	 *
	 *@return la chaine pour l'affichage de la description de l'intersection
	 */
    virtual std::string Description ();

	/**Preparer la chaine pour reconstruire l'intersection
	 *
	 *@return la chaine pour reconstruire l'intersection
	 */
    virtual std::string CommandeReconstruire ();

    /**Deplacer l'intersection d'un vecteur (dx,dy)
     *
     * @param dx l'unite de deplacement sur l'axe x
     * @param dy l'unite de deplacement sur l'axe y
     */
    virtual void Deplacer(int dx, int dy);

    /**Creer une copie de l'objet
     *
     * @return l'objet copie de l'objet au courant
     */
    Objet* CopierObjet();


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    /**Creer une intersection a partir d'une intersection existante
     *
     * @param unIntersection l'intersection que l'on veut copier
     */
    Intersection ( const Intersection & unIntersection );

    /**Creer une intersection a partir d'un nom et d'une liste d'objets
     *
     * @param unNom le nom pour l'intersection
     * @param objetACroiser les objets constituant l'intersection
     */
    Intersection (std::string unNom, const std::vector<Objet*> &objetACroiser );

    /**Supprimer les objets crees dynamiquement
     *
     */
    virtual ~Intersection ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Intersection>

#endif // INTERSECTION_H

