/*************************************************************************
                           Dessin  -  description
                             -------------------
    début                : 22/01/2015
    copyright            : (C) 2015-2016 par cespeute
*************************************************************************/

//---------- Interface de la classe <Dessin> (fichier dessin.h) ------
#if ! defined ( _DESSIN_H_ )
#define _DESSIN_H_

//--------------------------------------------------- Interfaces utilisées
#include <unordeored_map>
#include <string>

using namespace std;
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <Dessin>
//
//
//------------------------------------------------------------------------ 

class Dessin
{
//----------------------------------------------------------------- PUBLIC

public:

	typedef pair<String,int> TypeListeObjets;
	typedef unordered_map<TypeListeObjets>::const_iterator ListeIterateur;
//----------------------------------------------------- Méthodes publiques
    /** Ajoute l'Objet unObjet à la liste des objets
    *	du dessin.
    *	@param unObjet L'objet à rajouter à la liste
    *	
    *	@return TRUE si l'objet à bien été rajouté,
    *	FALSE si il n'à pas pu être ajouté (conflit de nom)
    */
    bool AjouterObjet(Objet unObjet);

    /** Supprime l'objet qui possède le nom nom
    *
    *	@param nom Le nom de l'objet à supprimer
    *	@param TRUE si l'objet à bien été supprimé,
    *	FALSE sinon.
    */
    bool SupprimerObjet(string nom);

    /** Fait la liste et la description de tous les objets
    *	du dessin et l'imprime dans sortie
    *	@param sortie L'OutputStream dans lequel
    */
    void Enumere(ostream sortie);

    /** Écrit une liste de commande qui permet de retrouver
    *	un état identique à celui du dessin si exécuté.
	*/
    void Sauver(ostream sortie);

//------------------------------------------------- Surcharge d'opérateurs
    Dessin & operator = ( const Dessin & unDessin );


//-------------------------------------------- Constructeurs - destructeur
    /** Constructeur de copie du Dessin
    *
    */
    Dessin ( const Dessin & unDessin );

    /** Constructeur de Dessin */
    Dessin ( );

    /** Destructeur de Dessin*/
    virtual ~Dessin ( );

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
//TODO : Changer int en Objet
unordered_map<TypeListeObjets> ListeObjets;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Dessin>

#endif // _DESSIN_H_
