/*********************************************************
/* Posibles errores:
/* 1- Querer agregar un elemento sin ahber creado el vector.
/* 2- Querer agregar un elemento estando el vector completo,
/*    o en una posici�n no permitida (por que ya est� ocupada
/*    o por que se quiere poner en un lugar cuyo �ndice es mayor que el m�ximo �ndice.)
/* 3- Solicitar un elemento en un �ndice no cargado. (vac�o).
/* 4- Crear un vector sobre un vector ya creado, crear 2 veces usando la misma variable (p�rdida de memoria).

/*********************************************************/

#include <stdlib.h>
#include "vector_fighter.h"
/* struct _nodoVF {
   s_fighter staticF;
   d_fighter dynamicF;
   unsigned short id; /// va a ser el lugar del array, se carga del archivo.
} nodoVF;

typedef struct _vectorFighter {
   nodoVF * vector; /// Vector de fighters. (parte din�mica y est�tica.)
   unsigned short cardinal; /// Numero de elementos (en verdad no es el cardinal sino el n�mero m�ximo de elementos posibles de cargar en el vector).
} * vectorFighter;
*/

vectorFighter newVectorF (unsigned short cardinal) {

   vectorFighter VF = new struct _vectorFighter;
   VF->vector = new nodoVF [cardinal];
   for (int i=0; i<cardinal; i++) {
      VF->vector[i].staticF = NULL;
      VF->vector[i].dynamicF = NULL;
   }
   VF->cardinal = cardinal;
   
   return VF;
}

void addFVectorF (vectorFighter & VF, s_fighter SF, d_fighter DF, unsigned short id,
                  vector_imgs imgs) {

   VF->vector[id].staticF = SF;
   VF->vector[id].dynamicF = DF;
   VF->vector[id].imgs = imgs;
   VF->vector[id].id = id;
}

void getFVectorF (vectorFighter VF, s_fighter & SF, d_fighter & DF, unsigned short id) {
   SF = VF->vector[id].staticF;
   DF = VF->vector[id].dynamicF;
}

SDL_Surface * getImgVF (vectorFighter VF, unsigned short idFighter, int idImg) {
// El idImg es el id asociado a la acci�n del luchador en las im�genes, no es lo mismo
// que los estatus de movimiento del luchador. Estos ids van a estar definidos en cte_game.

   return getImgVImgs (VF->vector[idFighter].imgs, idImg);
}

void destroyVectorF (vectorFighter & VF) {
   if (VF) {
      for (int i=0; i<VF->cardinal; i++) {
         destroySFighter (VF->vector[i].staticF);
         destroyDFighter (VF->vector[i].dynamicF);
      }
      delete [] VF->vector;
      delete VF;
      VF = NULL;
   }
}


