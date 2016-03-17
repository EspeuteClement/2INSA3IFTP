// Fichier de configuration et de constantes propres au programme
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <sys/sem.h>
const struct sembuf reserver = {0,-1,0};
const struct sembuf liberer  = {0,1,0};

#endif