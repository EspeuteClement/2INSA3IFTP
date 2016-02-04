/*************************************************************************
                           Rectangle  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Rectangle> (fichier Rectangle.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <sstream>

//------------------------------------------------------ Include personnel
#include "Rectangle.h"


//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool Rectangle::EstDedans ( const Point &unPoint )
// Algorithme :
//
	{
		if(unPoint.getX()>=(*listePoints.front()).getX() &&
				unPoint.getX()<=(*listePoints.back()).getX() &&
				unPoint.getY()<=(*listePoints.front()).getY() &&
				unPoint.getY()>=(*listePoints.back()).getY())
		{
			return true;
		}
		else
		{
			return false;
		}
	} //----- Fin de Méthode

string Rectangle::Description()
{
	string s=nom+" : Rectangle, ";
	int x=(*listePoints.front()).getX();
	int y=(*listePoints.front()).getY();
	stringstream sx1;
	stringstream sy1;
	stringstream sx2;
	stringstream sy2;
	sx1<<x;
	sy1<<y;
	s+=sx1.str()+ ", "+sy1.str()+ ", ";
	x=(*listePoints.back()).getX();
	y=(*listePoints.back()).getY();
	sx2<<x;
	sy2<<y;
	s+=sx2.str()+", "+sy2.str()+"\n";

	return s;
}

string Rectangle::CommandeReconstruire()
{
	string s="R " + nom + " ";
	int x=(*listePoints.front()).getX();
	int y=(*listePoints.front()).getY();
	stringstream sx1;
	stringstream sy1;
	stringstream sx2;
	stringstream sy2;
	sx1<<x;
	sy1<<y;
	s+=sx1.str()+ " "+sy1.str()+ " ";
	x=(*listePoints.back()).getX();
	y=(*listePoints.back()).getY();
	sx2<<x;
	sy2<<y;
	s+=sx2.str()+" "+sy2.str()+"\n";
	return s;
}

Objet* Rectangle::CopierObjet()
// Algorithme :
//
{
	string s="copier"+nom;
	Rectangle* unRectangle=new Rectangle(s,*listePoints[0],*listePoints[1]);
	return unRectangle;
} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

