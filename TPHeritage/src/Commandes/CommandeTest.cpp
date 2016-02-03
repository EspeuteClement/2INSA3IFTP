#include "CommandeTest.h"
#include <iostream>

using namespace std;

int CommandeTest::nombreCommandes = 0;


bool CommandeTest::Executer()
{
	cout << "Commande " << idCommande << " executée" << endl;
}

void CommandeTest::Annuler()
{
	cout << "Commande " << idCommande << " annulée" << endl;
}


CommandeTest::CommandeTest() : CommandeTest::super(NULL)
{
	idCommande = nombreCommandes ++;
}

CommandeTest::~CommandeTest()
{

}