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

	int getX ()
	{
		return x;
	}

	int getY ()
	{
		return y;
	}


//------------------------------------------------- Surcharge d'opérateurs
    Point & operator = ( const Point & unPoint );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur

    /**Creer un point a partir d'un point
     *
     *@param unX la coordonnee du point sur l'axe x
     *@param unY la coordonnee du point sur l'axe y
     */
    Point ( const Point & unPoint )
    {
        this->x = unPoint.x;
        this->y = unPoint.y;
    }


    /**Creer un point avec ses coordonnees
     *
     *@param unX la coordonnee du point sur l'axe x
     *@param unY la coordonnee du point sur l'axe y
     */
    Point (int unX, int unY):x(unX), y(unY){};


    virtual ~Point ( ) {};
    // Mode d'emploi :
    //
    // Contrat :
    //

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


