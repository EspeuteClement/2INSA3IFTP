#include "../HistoriqueCommande.h"
#include "../Commandes/CommandeTest.h"
#include "../Dessin.h"
#include "../GestionEntreSortie.h"
int main()
{
	HistoriqueCommande liste;
	for (int i = 0; i < 50; i++)
	{
		liste.AjouterCommande(new CommandeTest());
	}

	for (int i = 0; i < 50; i++)
	{
		liste.AnnulerCommande();
	}

	for (int i = 0; i < 50; i++)
	{
		liste.ReprendreCommande();
	}

	// for (int i = 0; i < 50; i++)
	// {
	// 	liste.AnnulerCommande();
	// }

	liste.AjouterCommande(new CommandeTest());

	liste.ReprendreCommande();
	return 0;
}