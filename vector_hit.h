#ifndef _vector_hit_h
#define _vector_hit_h

#include "hit.h"

typedef struct _vectorHit {

   hit * vector;
   int cardinal; // numero de elementos

} * vectorHit;


vectorHit newVHit (int cardinal);

hit getHitVHit (vectorHit VH, int index); // devuelve el hit del lugar index.
void addHitVHit (vectorHit VH, hit H); // el indice donde será puesto el hit es el id del mismo hit.

void destroyVHit (vectorHit & VH);

#endif
