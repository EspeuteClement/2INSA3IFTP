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
	virtual bool EstDedans ( Point unPoint ) = 0;

	/**Preparer la chaine de la description de l'objet pour l'affichage
	 *
	 *@return la chaine pour l'affichage de la description de l'objet
	 */
    virtual std::string Description () = 0;

	/**Preparer la chaine pour reconstruire l'objet au courant
	 *
	 *@return la chaine pour reconstruire l'objet
	 */
    virtual std::string CommandeReconstruire () = 0;

    std::string getNom()
    {
    	return nom;
    }

//------------------------------------------------- Surcharge d'opérateurs
    Objet & operator = ( const Objet & unObjet );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Objet ( const Objet & unObjet );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

	/**Creer un objet a partir d'un nom
	 *
	 *@param unNom le nom fourni pour l'objet
	 */
    Objet (std::string unNom ):nom(unNom){}

    virtual ~Objet ( );
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
    std::string nom;
    std::vector<Point*> listePoints;

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Objet>

#endif // OBJET_H

