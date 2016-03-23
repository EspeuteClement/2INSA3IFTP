#ifndef _MERE_H_
#define _MERE_H_

#include <sys/sem.h>

// Identifiants des FilesVoitures dans le tableau des filesVoitures
enum FileVoiture {
  FILE_PROF_BP,   // 0 : entrée du parking pour les profs
  FILE_AUTRE_BP,  // 1 : entrée du parking pour les autres
  FILE_GB, // 2 : entrée du parking pour les profs ou autres
  NOMBRE_FILE_VOITURE // 3 : le nombre max de files voitures
};

/** Ecrit message dans le log. La fonction est thread safe.
*  @param message un null terminated string à écrire dans le log
*/
void ecrireLog(char* message);

// -------------------------------------- Structure de controle des sémaphores
// struct sembuf reserver;
// struct sembuf liberer;

#endif