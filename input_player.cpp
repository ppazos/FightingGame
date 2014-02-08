#include <stdlib.h>
#include "input_player.h"

/*
typedef struct _inputP {
   int * vector; /// Solo para guardar los nombres de las teclas.
   int size;
} * inputP; /// Es un puntero a un array de chars.
*/

inputP newInputPlayer (unsigned short numKeys) {
   inputP IP = new struct _inputP;
   IP->vector = new int [numKeys];
   for (int i=0; i<numKeys; i++) {
      IP->vector[i] = 0;
   }
   IP->size = numKeys;
   return IP;
}
/*
inputP newInputPlayer (unsigned short numKeys) {
   inputP IP = new struct _inputP;
   IP->vector = new char [numKeys];
   for (int i=0; i<numKeys; i++) {
      IP->vector[i] = 0;
   }
   IP->size = numKeys;
   return IP;
}
*/

void addKeyInputPlayer (inputP & IP, int key, int index) {
   IP->vector[index] = key;
}
/*
void addKeyInputPlayer (inputP & IP, char keyName, unsigned short action) {
   IP->vector[action] = keyName;
}
*/

int getKeyInputPlayer (inputP IP, int index) {
   return IP->vector[index];
}
/*
char getKeyInputPlayer (inputP IP, unsigned short action) {
   return IP->vector[action];
}
*/

void destroyInputPlayer (inputP & IP) {
   if (IP) {
      delete [] IP->vector;
      delete IP;
      IP = NULL;
   }
}
