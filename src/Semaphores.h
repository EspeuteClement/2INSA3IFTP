// Simple librairie pour mieux gérer les sémaphores pour l'application
#ifndef _SEMAPHORES_H_
#define _SEMAPHORES_H_

/** Initialise les sémaphores nécessaires à l'application
*/
void initialiserSemaphores();

/** Détruits les sémaphores de l'application
*/
void detruireSemaphores();

/** Réserve le sémaphore donné en paramètre
*/
void reserverSemaphore(semaphore leSemaphore);



/** Libere le sémaphore donné en paramètre
*/
void libererSemaphore(semaphore leSemaphore);

enum Semaphore
#endif