/*************************************************************************
                           PolygoneConvexe  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//--- Interface de la classe <PolygoneConvexe> (fichier PolygoneConvexe.h) ------
#if ! defined ( POLYGONECONVEXE_H )
#define POLYGONECONVEXE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include "ObjetSimple.h"
#include "Point.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <PolygoneConvexe>
//
//
//------------------------------------------------------------------------

class PolygoneConvexe : public ObjetSimple
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /**Tester si le point en parametre est sur le polygone convexe
     *
     *@param unPoint le point que l'on fait le test
     *@return true si le point est sur le polygone convexe et sinon false
     */
	virtual bool EstDedans ( const Point &unPoint );

	/**Preparer la chaine de la description du polygone convexe pour
	 * l'affichage
	 *
	 *@return la chaine pour l'affichage de la description du polygone convexe
	 */
    virtual std::string Description ();

	/**Preparer la chaine pour reconstruire le PolygoneConvexe
	 *
	 *@return la chaine pour reconstruire le PolygoneConvexe
	 */
    virtual std::string CommandeReconstruire ();

    /**Deplacer le polygone d'un vecteur (dx,dy)
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
    /**Creer un polygone convexe a partir d'un existant
     *
     * @param unPolygoneConvexe le polygone que l'on veut copier
     */
    PolygoneConvexe ( const PolygoneConvexe & unPolygoneConvexe );

    /**Creer un polygone convexe a partir d'un nom et d'une liste de points
     *
     * @param unNom le nom pour le polygone
     * @param lesPoints les points constituant le polygone
     */
    PolygoneConvexe ( std::string unNom, vector<Point*> &lesPoints );

    /**Supprimer les points du polygone crees dynamiquement
     *
     */
    virtual ~PolygoneConvexe ( );

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

//---------------------------------- Types dépendants de <PolygoneConvexe>

#endif // POLYGONECONVEXE_H

