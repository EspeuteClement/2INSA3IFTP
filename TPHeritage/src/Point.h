/*************************************************************************
                           Point  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Point> (fichier Point.h) ------
#if ! defined ( POINT_H )
#define POINT_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Point>
//
//
//------------------------------------------------------------------------

class Point
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	/**Deplacer un point de dx unites sur l'axe x et dy sur l'axe y
     *
     * @param dx l'unite de deplacement sur l'axe x
     * @param dy l'unite de deplacement sur l'axe y
     */
	void Deplacer ( int dx, int dy )
    {
    	x+=dx;
    	y+=dy;
    }

	/**Retourner la valeur de x du point
     *
     * @return la valeur de x retournee
     */
	int getX () const
	{
		return x;
	}

	/**Retourner la valeur de y du point
     *
     * @return la valeur de y retournee
     */
	int getY () const
	{
		return y;
	}


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

    /**Creer un point a partir d'un point
     *
     *@param unX la coordonnee du point sur l'axe x
     *@param unY la coordonnee du point sur l'axe y
     */
    Point ( const Point & unPoint ):x(unPoint.x), y(unPoint.y){}


    /**Creer un point avec ses coordonnees
     *
     *@param unX la coordonnee du point sur l'axe x
     *@param unY la coordonnee du point sur l'axe y
     */
    Point (int unX, int unY):x(unX), y(unY){}


    virtual ~Point ( ){};

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés

    int x;
    int y;

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Point>

#endif // POINT_H


