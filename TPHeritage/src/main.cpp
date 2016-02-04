#include "HistoriqueCommande.h"


#include "Dessin.h"
#include "ObjetTest.h"

#include "Commandes/CommandeAjouterObjet.h"
#include "Commandes/CommandeSupprimerObjet.h"
#include "Commandes/CommandeAppartenanceObjet.h"
#include "Commandes/CommandeClear.h"
#include "Commandes/CommandeSauver.h"
#include "GestionEntreSortie.h"

#include <iostream>
#include <sstream>
int main()
{
	Dessin* des = new Dessin();
	HistoriqueCommande* historique = new HistoriqueCommande();

	GestionEntreSortie::Retour retour;
	retour.commande = NULL;
	retour.valeur = GestionEntreSortie::OK;
	while(retour.valeur != GestionEntreSortie::EXIT)
	{
		string ligne;
		getline(cin,ligne);
		retour = GestionEntreSortie::LireLigne(ligne,des);
		if (retour.valeur != GestionEntreSortie::EXIT)
		{
			switch (retour.valeur)
			{
				case GestionEntreSortie::OK:
					if(historique->AjouterCommande(retour.commande))
					{
						cout << "OK" << endl;
					}
					else
					{
						cout << "ERR" << endl;
					}
				break;
				case GestionEntreSortie::HIT:
					historique->AjouterCommande(retour.commande);
					break;
				case GestionEntreSortie::SAVE:
					historique->AjouterCommande(retour.commande);
					break;
				case GestionEntreSortie::UNDO:
					if(historique->AnnulerCommande())
					{
						cout << "OK" << endl;
					}
					else
					{
						cout << "ERR" << endl;
					}
				break;
				case GestionEntreSortie::REDO:
					if(historique->ReprendreCommande())
					{
						cout << "OK" << endl;
					}
					else
					{
						cout << "ERR" << endl;
					}
				break;
				case GestionEntreSortie::LIST:
					des->Enumere(cout);
				break;
				case GestionEntreSortie::ERR_PARAM:
					cout << "ERR" <<endl;
				break;
			}
		}
	}

	delete historique;

	delete des;
}