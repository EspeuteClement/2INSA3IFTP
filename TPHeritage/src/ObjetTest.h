#include "Objet.h"

class ObjetTest : public Objet
{
public: 
	bool EstDedans (Point unPoint) {
		return true;
	}

	std::string Description ()
	{
		return "Je suis le point " + id;
	}

	std::string CommandeReconstruire()
	{
		return "Je suis le point " + id;
	}

	ObjetTest(std::string unNom) : nom(unNom)
	{
	}

	int id;
	static int nombreId = 0;
};

ObjetTest::nombreId = 0;