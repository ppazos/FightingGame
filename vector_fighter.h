#ifndef _vector_fighter_h
#define _vector_fighter_h

#include "vector_SDL_Surf.h" // para guardar las im�genes de los tipos.
#include "s_fighter.h"
#include "d_fighter.h"

typedef struct _nodoVF {
   vector_imgs imgs; // im�gnes del luchador
   s_fighter staticF;
   d_fighter dynamicF;
   unsigned short id; /// va a ser el lugar del array, se carga del archivo.
} nodoVF;

typedef struct _vectorFighter {
   nodoVF * vector; /// Vector de fighters. (parte din�mica y est�tica.)
   unsigned short cardinal; /// Numero de elementos.
} * vectorFighter;

vectorFighter newVectorF (unsigned short cardinal); /// Crea vector vac�o.

void addFVectorF (vectorFighter & VF, s_fighter SF, d_fighter DF, unsigned short id,
                  vector_imgs imgs); /// Agrega un nodo con la info especificada.

void getFVectorF (vectorFighter VF, s_fighter & SF, d_fighter & DF, unsigned short id); /// Devuelve la info del nodo en el �ndice id.

SDL_Surface * getImgVF (vectorFighter VF, unsigned short idFighter, int idImg);
// El idImg es el id asociado a la acci�n del luchador en las im�genes, no es lo mismo
// que los estatus de movimiento del luchador. Estos ids van a estar definidos en cte_game.

void destroyVectorF (vectorFighter & VF);

#endif
