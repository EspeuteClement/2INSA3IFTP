/*************************************************************************
                           Segment  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Segment> (fichier Segment.h) ------
#if ! defined ( SEGMENT_H )
#define SEGMENT_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include "ObjetSimple.h"
#include "Point.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Segment>
//
//
//------------------------------------------------------------------------

class Segment : public ObjetSimple
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /**Tester si le point en parametre est sur le segment
     *
     *@param unPoint le point que l'on fait le test
     *@return true si le point est sur le segment et sinon false
     */
	virtual bool EstDedans ( const Point &unPoint );

	/**Preparer la chaine de la description du segment pour l'affichage
	 *
	 *@return la chaine pour l'affichage de la description du segment
	 */
    virtual std::string Description ();

	/**Preparer la chaine pour reconstruire le segment
	 *
	 *@return la chaine pour reconstruire le segment
	 */
    virtual std::string CommandeReconstruire ();

    /**Deplacer le segment d'un vecteur (dx,dy)
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

    /**Creer un segment a partir d'un segment existant
     *
     * @param unSegment le segment que l'on veut copier
     */
    Segment ( const Segment & unSegment ):ObjetSimple(unSegment.nom)
    {
    	Point* leDebut=new Point ((*unSegment.listePoints[0]));
    	Point* laFin=new Point((*unSegment.listePoints[1]));
    	listePoints.push_back(leDebut);
    	listePoints.push_back(laFin);
    }

    /**Creer un segment a partir d'un nom et de deux points
     *
     * @param unNom le nom pour le segment
     * @param leDebut le debut du segment
     * @param laFin la fin du segment
     */
    Segment ( std::string unNom, Point &leDebut, Point &laFin ):ObjetSimple(unNom)
    {
    	Point* debut=new Point(leDebut);
    	Point* fin=new Point(laFin);
    	listePoints.push_back(debut);
    	listePoints.push_back(fin);
    }

    /**Supprimer les points du segment crees dynamiquement
     *
     */
    virtual ~Segment ( )
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

//----------------------------------------- Types dépendants de <Segment>

#endif // SEGMENT_H

