#include "../HistoriqueCommande.h"


#include "../Dessin.h"
#include "../ObjetTest.h"

#include "../Commandes/CommandeAjouterObjet.h"
#include "../Commandes/CommandeSupprimerObjet.h"
#include "../Commandes/CommandeAppartenanceObjet.h"
#include "../Commandes/CommandeClear.h"
#include "../GestionEntreSortie.h"

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
					historique->AjouterCommande(retour.commande);
				break;
				case GestionEntreSortie::UNDO:
					historique->AnnulerCommande();
				break;
				case GestionEntreSortie::REDO:
					historique->ReprendreCommande();
				break;
				case GestionEntreSortie::LIST:
					des->Enumere(cout);
				break;
			}
		}
	}


	// historique->AjouterCommande(
	// 	new CommandeAjouterObjet(des, obj)
	// );

	// GestionEntreSortie::Retour ret = GestionEntreSortie::LireLigne("PC Coucou 0 0 0 0 0 0",des);
	// if (ret.valeur == GestionEntreSortie::OK)
	// {
	// 	historique->AjouterCommande(
	// 		ret.commande
	// 	);
	// }

	

	// /*for (int i = 0; i < 10; i++)
	// {
	// 	ostringstream s;
	// 	s << "Test" << i;
	// 	historique->AjouterCommande(
	// 		new CommandeAjouterObjet(des, 
	// 			new ObjetTest(s.str())
	// 			)
	// 	);
	// }*/
	// des->Enumere(std::cout);

	// historique->AjouterCommande(
	//  	new CommandeClear(des)
	//  );

	// des->Enumere(std::cout);
		
	// historique->AnnulerCommande();

	// des->Enumere(std::cout);
	
	// // historique->AnnulerCommande();

	// // des->Enumere(std::cout);

	// // historique->ReprendreCommande();

	// // des->Enumere(std::cout);

	// // historique->AjouterCommande(
	// // 	new CommandeSupprimerObjet(des,"Test88")
	// // );

	// // des->Enumere(std::cout);

	// // historique->AnnulerCommande();

	// // des->Enumere(std::cout);

	// // historique->AjouterCommande(
	// // 	new CommandeAppartenanceObjet(des,"Test", Point(0,0))
	// // );
	
	// // historique->ReprendreCommande();

	
	

	delete historique;

	delete des;
}