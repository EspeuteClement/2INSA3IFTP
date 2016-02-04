/*************************************************************************
                           Rectangle  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Rectangle> (fichier Rectangle.h) ------
#if ! defined ( RECTANGLE_H )
#define RECTANGLE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include "ObjetSimple.h"
#include "Point.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Rectangle>
//
//
//------------------------------------------------------------------------

class Rectangle : public ObjetSimple
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /**Tester si le point en parametre est dans le rectangle
     *
     *@param unPoint le point que l'on fait le test
     *@return true si le point est dans le rectangle et sinon false
     */
	virtual bool EstDedans ( const Point &unPoint );

	/**Preparer la chaine de la description du rectangle pour l'affichage
	 *
	 *@return la chaine pour l'affichage de la description du rectangle
	 */
    virtual std::string Description ();

	/**Preparer la chaine pour reconstruire le rectangle
	 *
	 *@return la chaine pour reconstruire le rectangle
	 */
    virtual std::string CommandeReconstruire ();

    /**Deplacer le rectangle d'un vecteur (dx,dy)
     *
     * @param dx l'unite de deplacement sur l'axe x
     * @param dy l'unite de deplacement sur l'axe y
     */
    virtual void Deplacer(int dx, int dy)
    {
    	(*listePoints[0]).Deplacer(dx,dy);
    	(*listePoints[1]).Deplacer(dx,dy);
    }

    /**Creer une copie de l'objet
     *
     * @return l'objet copie de l'objet au courant
     */
    Objet* CopierObjet();


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    /**Creer un rectangle a partir d'un rectangle existant
     *
     * @param unRectangle le rectangle que l'on veut copier
     */
    Rectangle ( const Rectangle & unRectangle ):ObjetSimple(unRectangle.nom)
    {
    	Point* leDebut=new Point ((*unRectangle.listePoints[0]));
    	Point* laFin=new Point((*unRectangle.listePoints[1]));
    	listePoints.push_back(leDebut);
    	listePoints.push_back(laFin);
    }

    /**Creer un rectangle a partir d'un nom et de deux points
     *
     * @param unNom le nom pour le rectangle
     * @param leDebut le point en haut a gauche
     * @param laFin le point en bas a droite
     */
    Rectangle ( std::string unNom, Point &leDebut, Point &laFin ):ObjetSimple(unNom)
    {
    	Point* debut=new Point(leDebut);
    	Point* fin=new Point(laFin);
        listePoints.push_back(debut);
        listePoints.push_back(fin);
    }

    /**Supprimer les points du rectangle crees dynamiquement
     *
     */
    virtual ~Rectangle ( )
    {
    	delete listePoints[0];
    	delete listePoints[1];
    }

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

//----------------------------------------- Types dépendants de <Rectangle>

#endif // RECTANGLE_H


