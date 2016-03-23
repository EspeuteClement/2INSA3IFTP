// Fichier de configuration et de constantes propres au programme
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <sys/sem.h>
struct sembuf reserver = {0,-1,0};
struct sembuf liberer  = {0,1,0};

#endif