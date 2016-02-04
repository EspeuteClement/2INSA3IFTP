#ifndef OBJET_TEST_H
#define OBJET_TEST_H

#include "Objet.h"
#include <iostream>
#include <sstream>

class ObjetTest : public Objet
{
public: 
	bool EstDedans (const Point &unPoint) {
		return false;
	}

	std::string Description ()
	{
		std::ostringstream retour;
		retour << "Je suis le point " << id << " " << nom;
		return retour.str();
	};

	std::string CommandeReconstruire()
	{
		std::ostringstream retour;
		retour << "S " << nom << " 0 0 0 0";
		return retour.str();
	};

	ObjetTest(std::string unNom): Objet(unNom)
	{
		id = nombreId ++;
	};

	~ObjetTest() {};
	int id;
	static int nombreId;
};



#endif