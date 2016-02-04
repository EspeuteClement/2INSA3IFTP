/*************************************************************************
                           Reunion  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Reunion> (fichier Reunion.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel
#include "Reunion.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool Reunion::EstDedans ( const Point &unPoint )
// Algorithme :
//
{
	for(int i=0;i<listeObjets.size();i++)
	{
		if((*listeObjets[i]).EstDedans(unPoint))
		{
			return true;
		}
	}
	return false;
} //----- Fin de Méthode

std::string Reunion::Description ()
// Algorithme :
//
{
	string s=nom+" : Reunion\n";
	for(vector<Objet*>::iterator it=listeObjets.begin();
			it!=listeObjets.end();it++)
	{
		s+="\t"+(**it).Description();
	}
	return s;
} //----- Fin de Méthode

std::string Reunion::CommandeReconstruire()
// Algorithme :
//
{
	string s = "";
	for(int i=0;i<listeObjets.size();i++)
	{
		s+=(*listeObjets[i]).CommandeReconstruire();
	}
	s+="OR "+nom;
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

void Reunion::Deplacer(int dx,int dy)
{
	for(vector<Objet*>::iterator it=listeObjets.begin();
			it!=listeObjets.end();it++)
	{
		(**it).Deplacer(dx,dy);
	}
}

Objet* Reunion::CopierObjet()
// Algorithme :
//
{
	string s="copier"+nom;
	Reunion* unReunion=new Reunion(s,listeObjets);
	return unReunion;
} //----- Fin de Méthode




//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Reunion::Reunion ( const Reunion & unReunion )
	:ObjetMultiple(unReunion.nom)
// Algorithme :
//
{
	for(int i=0;i<unReunion.listeObjets.size();i++)
	{
		Objet* objet=(*unReunion.listeObjets[i]).CopierObjet();
		listeObjets.push_back(objet);
	}
#ifdef MAP
    cout << "Appel au constructeur de copie de <Reunion>" << endl;
#endif
} //----- Fin de Reunion (constructeur de copie)


Reunion::Reunion (string unNom, const vector<Objet*> &objetAReunir)
		:ObjetMultiple(unNom)
// Algorithme :
//
{
	for(int i=0;i<objetAReunir.size();i++)
	{
		Objet* objet=(*objetAReunir[i]).CopierObjet();
		listeObjets.push_back(objet);
	}
#ifdef MAP
    cout << "Appel au constructeur de <Reunion>" << endl;
#endif
} //----- Fin de Reunion


Reunion::~Reunion ( )
// Algorithme :
//
{
	for(int i=0;i<listeObjets.size();i++)
	{
		delete listeObjets[i];
	}
#ifdef MAP
    cout << "Appel au destructeur de <Reunion>" << endl;
#endif
} //----- Fin de ~Reunion


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

