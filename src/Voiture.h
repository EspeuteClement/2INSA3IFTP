//------------------- Interface de <Voiture> -----------------------------
#if ! defined ( Voiture_H )
#define Voiture_H

//------------------------------------------------------------------------
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "libs/Outils.h"
#include <time.h>
#include "Mere.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

typedef struct {
	TypeUsager  type;
	unsigned int numero;
	time_t  arrivee;
}Voiture;

typedef struct {
	unsigned int placesLibres;
	Voiture voituresGarees[NB_PLACES];
	Voiture voituresEnAttente[NOMBRE_FILE_VOITURE];
} VoituresParking;

#endif // VOITURE_H



