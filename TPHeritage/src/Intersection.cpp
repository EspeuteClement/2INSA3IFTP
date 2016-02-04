/*************************************************************************
                           Intersection  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Intersection> (fichier Intersection.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel
#include "Intersection.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool Intersection::EstDedans ( const Point &unPoint )
// Algorithme :
//
{
	for(int i=0;i<listeObjets.size();i++)
	{
		if(!(*listeObjets[i]).EstDedans(unPoint))
		{
			return false;
		}
	}
	return true;
} //----- Fin de Méthode

std::string Intersection::Description ()
// Algorithme :
//
{
	string s=nom+" : Intersection\n";
	for(vector<Objet*>::iterator it=listeObjets.begin();
			it!=listeObjets.end();it++)
	{
		s+="\t"+(**it).Description();
	}
	return s;
} //----- Fin de Méthode

std::string Intersection::CommandeReconstruire()
// Algorithme :
//
{
	string s="";
	for(int i=0;i<listeObjets.size();i++)
	{
		s+=(*listeObjets[i]).CommandeReconstruire();
	}
	s+="OI "+nom;
	for(vector<Objet*>::iterator it=listeObjets.begin();
			it!=listeObjets.end();it++)
	{
		s+=" "+(**it).getNom();
	}
	s+="\nDELETE ";
	for(int i=0;i<listeObjets.size();i++)
	{
		s+=(*listeObjets[i]).getNom()+" ";
	}
	s+="\n";
	return s;
}//----- Fin de Méthode

void Intersection::Deplacer(int dx,int dy)
{
	for(vector<Objet*>::iterator it=listeObjets.begin();
			it!=listeObjets.end();it++)
	{
		(**it).Deplacer(dx,dy);
	}
}

Objet* Intersection::CopierObjet()
// Algorithme :
//
{
	string s="copier"+nom;
	Intersection* unIntersection=new Intersection(s,listeObjets);
	return unIntersection;
} //----- Fin de Méthode




//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Intersection::Intersection ( const Intersection & unIntersection )
	:ObjetMultiple(unIntersection.nom)
// Algorithme :
//
{
	for(int i=0;i<unIntersection.listeObjets.size();i++)
	{
		Objet* objet=(*unIntersection.listeObjets[i]).CopierObjet();
		listeObjets.push_back(objet);
	}
#ifdef MAP
    cout << "Appel au constructeur de copie de <Intersection>" << endl;
#endif
} //----- Fin de Intersection (constructeur de copie)


Intersection::Intersection (string unNom, const vector<Objet*> &objetACroiser)
	:ObjetMultiple(unNom)
// Algorithme :
//
{
	for(int i=0;i<objetACroiser.size();i++)
	{
		Objet* objet=(*objetACroiser[i]).CopierObjet();
		listeObjets.push_back(objet);
	}
#ifdef MAP
    cout << "Appel au constructeur de <Intersection>" << endl;
#endif
} //----- Fin de Intersection


Intersection::~Intersection ( )
// Algorithme :
//
{
	for(int i=0;i<listeObjets.size();i++)
	{
		delete listeObjets[i];
	}
#ifdef MAP
    cout << "Appel au destructeur de <Intersection>" << endl;
#endif
} //----- Fin de ~Intersection


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

