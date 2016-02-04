/*************************************************************************
                           PolygoneConvexe  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

// Réalisation de la classe <PolygoneConvexe> (fichier PolygoneConvexe.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

//------------------------------------------------------ Include personnel
#include "PolygoneConvexe.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool PolygoneConvexe::EstDedans ( const Point &unPoint )
// Algorithme :
//
	{
		vector<Point*>::iterator it1=listePoints.begin();
		vector<Point*>::iterator it2=listePoints.begin()+1;
		bool haut=false;
		bool bas=false;
		double distance;
		double x1;
		double x2;
		double y1;
		double y2;
		double x=unPoint.getX();
		double y=unPoint.getY();
		while(it1!=listePoints.end())
		{
			if(it2==listePoints.end())
			{
				x1=(**it1).getX();
				x2=(**listePoints.begin()).getX();
				y1=(**it1).getY();
				y2=(**listePoints.begin()).getY();
			}
			else
			{
				x1=(**it1).getX();
				x2=(**it2).getX();
				y1=(**it1).getY();
				y2=(**it2).getY();
			}
			if(x1==x2)
			{
				if(x==x1)
				{
					if((y1<=y && y<=y2) || (y1>=y && y>=y2))
					{
						haut=true;
						bas=true;
					}
					else if (y<y1 && y<y2)
					{
						haut=true;
					}
					else if (y>y1 && y>y2)
					{
						bas=true;
					}
				}

			}
			else if ( x1!=x2 && ((x1<=x && x<=x2 ) || ( x2<=x && x<=x1)) )
			{
				distance=(y1-y2)/(x1-x2)*x+(x1*y2-y1*x2)/(x1-x2)-y;
				if(abs(distance)<1)
				{
					haut=true;
					bas=true;
				}
				else if(distance>=1)
				{
					haut=true;
				}
				else
				{
					bas=true;
				}
			}
			if(haut && bas)
			{
				return true;
			}
			it1++;
			it2++;
		}

		return false;
	} //----- Fin de Méthode

string PolygoneConvexe::Description ()
{
	string s=nom + " : PolygoneConvexe, ";
	vector<Point*>::iterator it=listePoints.begin();
	stringstream sx;
	stringstream sy;
	sx<<(**it).getX();
	sy<<(**it).getY();
	s+=sx.str() + ", "+ sy.str();
	sx.str("");
	sy.str("");
	it++;
	while(it!=listePoints.end())
	{
		s+=", ";
		sx<<(**it).getX();
		sy<<(**it).getY();
		s+=sx.str() + ", "+ sy.str();
		sx.str("");
		sy.str("");
		it++;
	}
	s+="\n";
	return s;
}

string PolygoneConvexe::CommandeReconstruire ()
{
	string s="PC " + nom + " ";
	vector<Point*>::iterator it=listePoints.begin();
	stringstream sx;
	stringstream sy;
	sx<<(**it).getX();
	sy<<(**it).getY();
	s+=sx.str() + " "+ sy.str();
	sx.str("");
	sy.str("");
	it++;
	while(it!=listePoints.end())
	{
		s+=" ";
		sx<<(**it).getX();
		sy<<(**it).getY();
		s+=sx.str() + " "+ sy.str();
		sx.str("");
		sy.str("");
		it++;
	}
	s+="\n";
	return s;
}

void PolygoneConvexe::Deplacer(int dx, int dy)
{
	vector<Point*>::iterator it=listePoints.begin();
	while(it!=listePoints.end())
	{
		(**it).Deplacer(dx,dy);
		it++;
	}
}

Objet* PolygoneConvexe::CopierObjet()
// Algorithme :
//
{
	string s="copier"+nom;
	PolygoneConvexe* unPolygoneConvexe=new PolygoneConvexe(s,listePoints);
	return unPolygoneConvexe;
} //----- Fin de Méthode

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
PolygoneConvexe::PolygoneConvexe (const PolygoneConvexe & unPolygoneConvexe):
		ObjetSimple(unPolygoneConvexe.nom)
// Algorithme :
//
{
	for(vector<Point*>::const_iterator it=unPolygoneConvexe.listePoints.begin();
			it!=unPolygoneConvexe.listePoints.end();it++)
	{
		Point* unPoint=new Point((**it).getX(),(**it).getY());
		listePoints.push_back(unPoint);
	}
#ifdef MAP
    cout << "Appel au constructeur de <PolygoneConvexe>" << endl;
#endif
} //----- Fin de PolygoneConvexe

PolygoneConvexe::PolygoneConvexe (std::string unNom, vector<Point*> &lesPoints):
		ObjetSimple(unNom)
// Algorithme :
//
{
	for(vector<Point*>::iterator it=lesPoints.begin();it!=lesPoints.end();it++)
	{
		Point* unPoint=new Point(**it);
		listePoints.push_back(unPoint);
	}
#ifdef MAP
    cout << "Appel au constructeur de <PolygoneConvexe>" << endl;
#endif
} //----- Fin de PolygoneConvexe

PolygoneConvexe::~PolygoneConvexe ( )
// Algorithme :
//
{
	for(int i=0;i<listePoints.size();i++)
	{
    	delete listePoints[i];
	}
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

