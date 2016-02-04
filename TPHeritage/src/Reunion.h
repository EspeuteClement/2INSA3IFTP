/*************************************************************************
                           Reunion  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Reunion> (fichier Reunion.h) ------
#if ! defined ( REUNION_H )
#define REUNION_H

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
// Rôle de la classe <Reunion>
//
//
//------------------------------------------------------------------------

class Reunion : public ObjetMultiple
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /**Tester si le point en parametre est dans la reunion
     *
     *@param unPoint le point que l'on fait le test
     *@return true si le point est dans la reunion et sinon false
     */
	virtual bool EstDedans ( const Point &unPoint );

	/**Preparer la chaine de la description de la reunion pour l'affichage
	 *
	 *@return la chaine pour l'affichage de la description de la reunion
	 */
    virtual std::string Description ();

	/**Preparer la chaine pour reconstruire la reunion
	 *
	 *@return la chaine pour reconstruire la reunion
	 */
    virtual std::string CommandeReconstruire ();

    /**Deplacer la reunion d'un vecteur (dx,dy)
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
    /**Creer une reunion a partir d'une reunion existante
     *
     * @param unReunion la reunion que l'on veut copier
     */
    Reunion ( const Reunion & unReunion );

    /**Creer une reunion a partir d'un nom et d'une liste d'objets
     *
     * @param unNom le nom pour la reunion
     * @param objetAReunir les objets constituant la reunion
     */
    Reunion (string unNom, const vector<Objet*> &objetAReunir);

    /**Supprimer les objets crees dynamiquement
     *
     */
    virtual ~Reunion ( );

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

//----------------------------------------- Types dépendants de <Reunion>

#endif // REUNION_H

