/*************************************************************************
                           Segment  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Segment> (fichier Segment.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cmath>
#include <sstream>

//------------------------------------------------------ Include personnel
#include "Segment.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool Segment::EstDedans ( const Point &unPoint )
// Algorithme :
//
{
	double x1=(*listePoints[0]).getX();
	double x2=(*listePoints[1]).getX();
	double y1=(*listePoints[0]).getY();
	double y2=(*listePoints[1]).getY();
	double x=unPoint.getX();
	double y=unPoint.getY();
	if((y>y1 && y>y2) || (y<y1 && y<y2)
			|| (x>x1 && x>x2) || (x<y1 && x<x2))
	{
		return false;
	}
	if(x1==x2)
	{
		if((x==x1) && ((y1<=y && y<=y2) || (y1>=y && y>=y2)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if(y1==y2)
	{
		if((y==y1) && ((x1<=x && x<=x2) || (x1>=x && x>=x2)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	double distance = (y1-y2)/(x1-x2)*x+(x1*y2-y1*x2)/(x1-x2)-y;
	if(abs(distance)<0.5)
	{
		return true;
	}
	else
	{
		return false;
	}
} //----- Fin de Méthode

string Segment::Description()
{
	string s=nom+" : Segment, ";
	int x=(*listePoints[0]).getX();
	int y=(*listePoints[0]).getY();
	stringstream sx1;
	stringstream sy1;
	stringstream sx2;
	stringstream sy2;
	sx1<<x;
	sy1<<y;
	s+=sx1.str()+ ", "+sy1.str()+ ", ";
	x=(*listePoints[1]).getX();
	y=(*listePoints[1]).getY();
	sx2<<x;
	sy2<<y;
	s+=sx2.str()+", "+sy2.str()+"\n";

	return s;
}

string Segment::CommandeReconstruire()
{
	string s="S " + nom + " ";
	int x=(*listePoints[0]).getX();
	int y=(*listePoints[0]).getY();
	stringstream sx1;
	stringstream sy1;
	stringstream sx2;
	stringstream sy2;
	sx1<<x;
	sy1<<y;
	s+=sx1.str()+ " "+sy1.str()+ " ";
	x=(*listePoints[1]).getX();
	y=(*listePoints[1]).getY();
	sx2<<x;
	sy2<<y;
	s+=sx2.str()+" "+sy2.str()+"\n";
	return s;
}

Objet* Segment::CopierObjet()
// Algorithme :
//
{
	string s="copier"+nom;
	Segment* unSegment=new Segment(s,*listePoints[0],*listePoints[1]);
	return unSegment;
} //----- Fin de Méthode



//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

