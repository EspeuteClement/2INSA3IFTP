/*************************************************************************
                           Test  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Test> (fichier Test.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include "TestConvexe.h"

//------------------------------------------------------ Include personnel

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
bool TestConvexe::EstPolygoneConvexe(vector<Point*> &lesPoints)
// Algorithme :
//
{
	if(lesPoints.size()<3)
	{
		return false;
	}
	double v1x=(*lesPoints[1]).getX()-(*lesPoints[0]).getX();
	double v1y=(*lesPoints[1]).getY()-(*lesPoints[0]).getY();
	double v2x=(*lesPoints[2]).getX()-(*lesPoints[1]).getX();
	double v2y=(*lesPoints[2]).getY()-(*lesPoints[1]).getY();
	double prodVectZRef=v1x*v2y-v2x*v1y;
	double prodVectZ;
	int i=3;
	while(prodVectZRef==0 && i<lesPoints.size())
	{
		v1x=v2x;
		v1y=v2y;
		v2x=(*lesPoints[i]).getX()-(*lesPoints[i-1]).getX();
		v2y=(*lesPoints[i]).getY()-(*lesPoints[i-1]).getY();
		prodVectZRef=v1x*v2y-v2x*v1y;
		i++;
	}
	if(i==lesPoints.size() && prodVectZRef==0)
	{
		v1x=v2x;
		v1y=v2y;
		v2x=(*lesPoints[0]).getX()-(*lesPoints[lesPoints.size()-1]).getX();
		v2y=(*lesPoints[0]).getY()-(*lesPoints[lesPoints.size()-1]).getY();
		prodVectZRef=v1x*v2y-v2x*v1y;
		if(prodVectZRef==0)
		{
			return false;
		}
		v1x=v2x;
		v1y=v2y;
		v2x=(*lesPoints[1]).getX()-(*lesPoints[0]).getX();
		v2y=(*lesPoints[1]).getY()-(*lesPoints[0]).getY();
		prodVectZ=v1x*v2y-v2x*v1y;
		if(prodVectZ*prodVectZRef<0)
		{
			return false;
		}
	}
	else
	{
		while(i<lesPoints.size())
		{
			v1x=v2x;
			v1y=v2y;
			v2x=(*lesPoints[i]).getX()-(*lesPoints[i-1]).getX();
			v2y=(*lesPoints[i]).getY()-(*lesPoints[i-1]).getY();
			prodVectZ=v1x*v2y-v2x*v1y;
			if(prodVectZ*prodVectZRef<0)
			{
				return false;
			}
			i++;
		}
		v1x=v2x;
		v1y=v2y;
		v2x=(*lesPoints[0]).getX()-(*lesPoints[lesPoints.size()-1]).getX();
		v2y=(*lesPoints[0]).getY()-(*lesPoints[lesPoints.size()-1]).getY();
		prodVectZ=v1x*v2y-v2x*v1y;
		if(prodVectZRef*prodVectZRef<0)
		{
			return false;
		}
		v1x=v2x;
		v1y=v2y;
		v2x=(*lesPoints[1]).getX()-(*lesPoints[0]).getX();
		v2y=(*lesPoints[1]).getY()-(*lesPoints[0]).getY();
		prodVectZ=v1x*v2y-v2x*v1y;
		if(prodVectZ*prodVectZRef<0)
		{
			return false;
		}
	}

	return true;
} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

