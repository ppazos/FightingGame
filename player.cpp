#include <stdlib.h>
#include "player.h"
/*
typedef struct _player {
   unsigned short fighterId; /// Id del luchador que está usando el jugador.
   inputP keys; /// Controles con teclado del luchador.
} * player;
*/

player newPlayer (inputP keys) {
   player P = new struct _player;
   P->keys = keys;
   P->fighterId = 0; /// Hay que hacer que los ids de los luchadores empie4cen en 1.
   return P;
}

void setFighterPlayer (player & P, unsigned short fighterId) {
   P->fighterId = fighterId;
}

unsigned short getFighterPlayer (player P) {
   return P->fighterId;
}

char getKeyPlayer (player P, unsigned short action) {
   return getKeyInputPlayer (P->keys, action);
}

inputP getKeysPlayer (player P) { /// OJO RETORNA el puntero, cualquier cambio, cambia las teclas!!!!.
   return P->keys;
}

void setKeysPlayer (player & P, inputP keys) {
   destroyInputPlayer (P->keys);
   P->keys = keys;
}

void destroyPlayer (player & P) {
   if (P) {
      destroyInputPlayer (P->keys);
      delete P;
      P = NULL;
   }
}

