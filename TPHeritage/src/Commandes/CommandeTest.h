#ifndef _COMMANDE_TEST_H_
#define _COMMANDE_TEST_H_

#include "../Commande.h"

class CommandeTest : public Commande
{
public:
	bool Executer();
	void Annuler();

	CommandeTest();
	~CommandeTest();
private:
	static int nombreCommandes;
	int idCommande;

	typedef Commande super;
};

#endif