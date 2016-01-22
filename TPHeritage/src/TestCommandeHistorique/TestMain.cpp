#include "../HistoriqueCommande.h"
#include "../CommandeTest.h"
#include "../Dessin.h"
int main()
{
	HistoriqueCommande liste;
	for (int i = 0; i < 500; i++)
	{
		liste.AjouterCommande(new CommandeTest());
	}

	for (int i = 0; i < 50; i++)
	{
		liste.AnnulerCommande();
	}

	for (int i = 0; i < 30; i++)
	{
		liste.ReprendreCommande();
	}

	for (int i = 0; i < 50; i++)
	{
		liste.AnnulerCommande();
	}

	for (int i = 0; i < 5; i++)
	{
		liste.ReprendreCommande();
	}

	liste.AjouterCommande(new CommandeTest());

	liste.ReprendreCommande();
	return 0;
}