/*************************************************************************
                           HistoriqueCommande  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Interface de la classe <HistoriqueCommande> (fichier HistoriqueCommande.h) ------
#if ! defined ( _HISTORIQUE_COMMANDE_H_ )
#define _HISTORIQUE_COMMANDE_H_

//--------------------------------------------------- Interfaces utilisées
#include <vector>
#include "Commande.h"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

using namespace std;
 
/** Rôle de la classe <HistoriqueCommande>
* Contient une liste de Commandes qui ont ou vont être exécutées.
* Permet d'ajouter une commande puis de l'exécutée, ou bien d'annuler
* la dernière commande effectuée, ou bien de la refaire.
*/
class HistoriqueCommande
{
//----------------------------------------------------------------- PUBLIC

public:
    /** Le nombre maximal de commandes à un instant donnée dans la
    liste des commandes */
    static const unsigned int MAX_COMMANDES;

//----------------------------------------------------- Méthodes publiques
    /** Ajoute laCommande à la liste des commandes et l'exécute.
    *   Contract : le pointeur laCommande ne doit pas être
    *   référencé autre part dans le programme, car
    *   HistoriqueCommande libérera ce pointeur à la fin
    *   de son existence
    *   @param laCommande Un pointeur vers la commande à 
    *   ajouter.
    *   @return TRUE si la commande à bien été ajoutée, FALSE
    *   sinon
    */
    bool AjouterCommande(Commande *laCommande);

    /** Annule la commande courante, de manière à remettre le
    *   Dessin dans le même état qu'avant l'exécution de cette
    *   commande.
    *   @return TRUE si la commande à bien été annulée, FALSE
    *   si il n'y à plus d'annulation possible
    */
    bool AnnulerCommande();

    /** Annule une annulation. Ne fonctionne que si l'on à appelé
    *   AnnulerCommande() et qu'on n'a pas appelé AjouterCommande()
    *   entre temps.
    *   @return TRUE si la commande à bien été reprise, FALSE
    *   si on ne peut plus reprendre de commandes.
    */
    bool ReprendreCommande();

//------------------------------------------------- Surcharge d'opérateurs
    HistoriqueCommande & operator = ( const HistoriqueCommande & unHistoriqueCommande );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    HistoriqueCommande ( const HistoriqueCommande & unHistoriqueCommande );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    HistoriqueCommande ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~HistoriqueCommande ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées
    
    /** Retourne l'index de la commande juste après la
    commande actuelle*/
    inline int getProchaineCommande()
    {
        return (positionCommandeCourante+1) % MAX_COMMANDES;
    }

    /** Retourne l'index de la commande juste avant la
        commande actuelle */
    inline int getPrecedanteCommande()
    {

        return (positionCommandeCourante + MAX_COMMANDES-1)
         % MAX_COMMANDES;
    }
protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
    /** Liste des commandes qui ont été effectuées. Le
    tableau est cyclique, c'est à dire que lorsqu'on atteint
    la fin de celui-ci, on reboucle au début.
    positionCommandeCourante et positionCommandeValide
    permettent d'indexer ce tableau. La taille max
    de ce tableau est MAX_COMMANDES */
    Commande** listeCommandes;

    /** Position dans la liste de la dernière commande exécutée */ 
    unsigned int positionCommandeCourante;

    /** Position dans la liste de la dernière commande qui peut 
    être exécutée (notamment lors de l'ajout d'une nouvelle commande
    ou lors d'un Undo/Redo*/
    unsigned int positionCommandeValide;

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <HistoriqueCommande>

#endif // _HISTORIQUE_COMMANDE_H_
