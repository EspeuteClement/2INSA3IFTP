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
#include <iostream>
#include <unordered_map>
#include <string>
#include "Objet.h"
//#include "CommandeClear.h"

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

#define KEY_VALUE_LISTE string,Objet*
	//typedef pair<KEY_VALUE_LISTE> TypeListeObjets;
	typedef unordered_map<KEY_VALUE_LISTE>::iterator ListeIterateur;
//----------------------------------------------------- Méthodes publiques
    /** Ajoute l'Objet unObjet à la liste des objets
    *	du dessin.
    *   </br>
    *   Contact : Si l'Objet est toujours dans le Dessin à la 
    *   fin de la vie du Dessin, il serra automatiquement
    *   delete.
    *	@param unObjet L'objet à rajouter à la liste
    *	
    *	@return TRUE si l'objet à bien été rajouté,
    *	FALSE si il n'à pas pu être ajouté (conflit de nom)
    */
    bool AjouterObjet(Objet* unObjet);

    /** Supprime l'objet qui possède le nom nom
    *   </br>
    *   Contrat : L'objet n'est pas delete. Cette
    *   opération est laissée à la charge de 
    *   l’utilisateur.
    *	@param nom Le nom de l'objet à supprimer
    *	@return NULL si aucun objet ne correspond
    *   à nom dans le tableau, sinon renvoie un pointeur
    *   vers l'objet qui à été supprimé.
    */
    Objet* SupprimerObjet(const string nom);

    /** Fait la liste et la description de tous les objets
    *	du dessin et l'imprime dans sortie
    *	@param sortie L'OutputStream dans lequel
    */
    void Enumere(ostream& sortie);

    /** Écrit une liste de commande qui permet de retrouver
    *	un état identique à celui du dessin si exécuté.
	*/
    void Sauver(ostream& sortie);

    /** Renvoie l'objet dans le dessin qui possède le nom nom
    *   
    *   @param nom Le nom de l'objet à récuperer
    *   @return Un pointeur vers l'objet demmandé, ou NULL si l'objet
    *   n'existe pas.
    */
    inline Objet* getObjet(const string nom)
    {
        ListeIterateur trouver = ListeObjets->find(nom);
        if (trouver != ListeObjets->end())
        {
            return (*ListeObjets)[nom];
        }
        return NULL;
    }

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
unordered_map<KEY_VALUE_LISTE>* ListeObjets;
//---------------------------------------------------------- Classes amies
friend class CommandeClear;
//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Dessin>

#endif // _DESSIN_H_
