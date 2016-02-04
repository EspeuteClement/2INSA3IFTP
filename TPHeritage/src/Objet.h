/*************************************************************************
                           Objet  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Objet> (fichier Objet.h) ------
#if ! defined ( OBJET_H )
#define OBJET_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include "Point.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Objet>
//
//
//------------------------------------------------------------------------

class Objet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /**Tester si le point en parametre est dans l'objet au courant
     *
     *@param unPoint le point que l'on fait le test
     *@return true si le point est dans l'objet et sinon false
     */
	virtual bool EstDedans ( const Point &unPoint )=0;

	/**Preparer la chaine de la description de l'objet pour l'affichage
	 *
	 *@return la chaine pour l'affichage de la description de l'objet
	 */
    virtual std::string Description ()=0;

	/**Preparer la chaine pour reconstruire l'objet au courant
	 *
	 *@return la chaine pour reconstruire l'objet
	 */
    virtual std::string CommandeReconstruire ()=0;

	/**Retourner le nom de l'objet
	 *
	 *@return le nom de l'objet
	 */
    std::string getNom()
    {
    	return nom;
    }

    /**Deplacer l'objet d'un vecteur (dx,dy)
     *
     * @param dx l'unite de deplacement sur l'axe x
     * @param dy l'unite de deplacement sur l'axe y
     */
    virtual void Deplacer(int dx, int dy)=0;

    /**Creer une copie de l'objet
     *
     * @return l'objet copie de l'objet au courant
     */
    virtual Objet* CopierObjet()=0;


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
	/**Creer un objet a partir d'un objet existant
	 *
	 *@param unObjet l'objet que l'on veut copier
	 */
    Objet ( const Objet & unObjet ):nom(unObjet.nom){}


	/**Creer un objet a partir d'un nom
	 *
	 *@param unNom le nom fourni pour l'objet
	 */
    Objet (std::string unNom):nom(unNom){}

    virtual ~Objet (){}

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
    std::string nom;

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Objet>

#endif // OBJET_H

