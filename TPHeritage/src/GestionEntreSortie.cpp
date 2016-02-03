#include "GestionEntreSortie.h"

#include "Objet.h"

#include "Commandes/CommandeAjouterObjet.h"
#include "Commandes/CommandeAppartenanceObjet.h"
#include "Commandes/CommandeClear.h"
#include "Commandes/CommandeDeplacerObjet.h"
#include "Commandes/CommandeSupprimerObjet.h"
#include "Commandes/CommandeCharger.h"

#include "ObjetTest.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>


GestionEntreSortie::Retour GestionEntreSortie::LireLigne(std::string ligne, Dessin* leDessin)
{
	//Extraire les parties de la ligne grâce à la STL
	using namespace std;
    istringstream iss(ligne);
	vector<string> tokens{istream_iterator<string>{iss},
                      istream_iterator<string>{}};

    int size = tokens.size();
    if (size > 0)
    {   

        // Gérer les exceptions liées à la conversion
        // INT -> STRING par stoi()
        try
        {
            // Gestion Commande AjouterSegment et AjouterRectangle
            // Note le corps de la gestion des 2 commandes est commun
            // Car elles ont les même paramètres
            if (size == 6 && 
                (tokens[0].compare("S") == 0 || tokens[0].compare("R") == 0)
                )
            {
                int x1 = stoi ( tokens[2] );
                int y1 = stoi ( tokens[3] );
                int x2 = stoi ( tokens[4] );
                int y2 = stoi ( tokens[5] );
                Retour r;

                if (tokens[0].compare("S") == 0)
                {
                    //Creer segment
                }
                else
                {
                    //Creer rectangle
                }

                r.commande = new CommandeAjouterObjet(
                    leDessin,
                    new ObjetTest(tokens[1])
                    //new Segment(Point(x1,y1),Point(x2,y2))
                );

                r.valeur = OK;
                return r;
            }
            //Gestion commande Polygone
            else if (size % 2 == 0 && tokens[0].compare("PC") == 0)
            {
                if (size>=8)
                {
                    // Creer une liste de points à partir
                    // de l'entrée
                    vector<Point*> points;
                    for (int i = 2; i < size; i+=2)
                    {
                        int x = stoi ( tokens[i] );
                        int y = stoi ( tokens[i+1] );
                        points.push_back(new Point(x,y));
                    }

                    Retour r;

                    r.commande = new CommandeAjouterObjet(
                        leDessin,
                        new ObjetTest(tokens[1])
                        //new Polygone(tokens[1],points)
                    );

                    r.valeur = OK;
                    return r;

                }
                else
                {
                    cout << "ERR" << endl;
                    cout << "#Il faut au moins 3 points pour faire un polygone" << endl;
                }
                
            }
            // Gestion Reunion et intersection
            else if (size >= 3 && 
                (tokens[0].compare("OR") == 0 || tokens[0].compare("OI") == 0)
                )
            {
                // Créer la liste des objets
                vector<Objet> listeObjets;
                for (int i = 2; i < size; i++)
                {
                    Objet* obj = leDessin->getObjet(tokens[i]);
                    
                    // Si l'objet n'existe pas, retourner une erreur
                    if (obj == NULL)
                    {
                        cout << "ERR" << endl;
                        cout << "#Objet " << tokens[i] << "n'existe pas" << endl;
                        Retour r;
                        r.valeur = ERR_PARAM;
                        r.commande = NULL;
                        return r;
                    }

                    // TODO : Implémenter ça avec une vraie copie
                    //Objet* objCopie = new Objet(*obj);
                    //listeObjets.push_back(objCopie);
                }

                Retour r;

                Objet* obj;
                if (tokens[0].compare("OR") == 0)
                {
                    //obj = new Reunion(tokens[1],listeObjets);
                }
                else
                {
                    //obj = new Intersection(tokens[1],listeObjets);
                }
                r.commande = new CommandeAjouterObjet(
                    leDessin,
                    new ObjetTest(tokens[1])
                    
                );

                r.valeur = OK;
                return r;
            }
            else if (size == 4 && 
                (tokens[0].compare("HIT") == 0 || tokens[0].compare("MOVE") == 0))
            {
                int x = stoi ( tokens[2] );
                int y = stoi ( tokens[3] );

                Retour r;
                r.valeur = OK;
                if (tokens[0].compare("HIT") == 0)
                {
                   r.commande = new CommandeAppartenanceObjet(
                    leDessin,
                    tokens[1],
                    Point(x,y)
                    ); 
                }
                else
                {
                    r.commande = new CommandeDeplacerObjet(
                    leDessin,
                    tokens[1],
                    x,y
                    );
                }
                
                return r;
            }
            else if (size == 1 && tokens[0].compare("LIST") == 0)
            {
                Retour r;
                r.commande = NULL;
                r.valeur = LIST;
                return r;
            }
            else if (size >= 2 && tokens[0].compare("DELETE") == 0 )
            {
                vector<string> nomsObjets;
                for (int i = 1; i<size; i++)
                {   
                    nomsObjets.push_back(tokens[i]);
                }
                Retour r;
                r.valeur = OK;

                r.commande = new CommandeSupprimerObjet(
                    leDessin,
                    nomsObjets
                    );
                return r;

            }
            else if (size == 2 && tokens[0].compare("LOAD") == 0)
            {
                Retour r;
                r.commande = new CommandeCharger(leDessin,tokens[1]);
                r.valeur = OK;
                return r; 
            }
            else if (tokens[0].compare("UNDO") == 0)
            {
                Retour r;
                r.commande = NULL;
                r.valeur = UNDO;
                return r;
            }
            else if (tokens[0].compare("REDO") == 0)
            {
                Retour r;
                r.commande = NULL;
                r.valeur = REDO;
                return r;
            }
            else if (tokens[0].compare("CLEAR") == 0)
            {
                Retour r;
                r.commande = new CommandeClear(leDessin);
                r.valeur = OK;
                return r;
            }
            else if (tokens[0].compare("EXIT") == 0)
            {
                Retour r;
                r.commande = NULL;
                r.valeur = EXIT;
                return r;
            }
            else
            {
                cout << "ERR" << endl;
                cout << "#Commande non reconnue" <<endl;
            }
        }
        catch (const exception& e)
        {
            cout << "ERR" << endl;
            cout << "#Mauvais arguments pour la commande" <<endl;
        }


        

    }

    // Créer la valeur de retour en cas d'erreur
    Retour r;
    r.valeur = ERR_PARAM;
    r.commande = NULL;
    return r;
}