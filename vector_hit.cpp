#include <stdlib.h>
#include <iostream>
#include "vector_hit.h"

using namespace std;

/*
typedef struct _vectorHit {

   hit * vector;
   int cardinal; // numero de elementos, necesario para el borrado.

} * vectorHit;
*/

vectorHit newVHit (int cardinal) {

   vectorHit VH = new struct _vectorHit;
   VH->vector = new hit [cardinal]; // array de cardinal elementos de tipo hit.
   VH->cardinal = cardinal;
   return VH;
}

hit getHitVHit (vectorHit VH, int index) { // devuelve el hit del lugar index.
   
   if (0<=index && index<VH->cardinal) {
      return VH->vector[index];
   } else {
      return NULL;
      cerr << "Index fuera de rango: getHitVHit\n";
   }
}

void addHitVHit (vectorHit VH, hit H) { // el indice donde será puesto el hit es el id del mismo hit.
   //unsigned short i = getIdHit (H);
   VH->vector [getIdHit(H)] = H;
}

void destroyVHit (vectorHit & VH) {
   if (VH) {
      for (int i=0; i<VH->cardinal; i++) { // Borra los golpes del array
         destroyHit (VH->vector[i]);
      }
      delete [] VH->vector; // borra el array.
      delete VH; // borra el struct.
      VH = NULL; // desvincula.
   }
}
