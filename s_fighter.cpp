#include <stdlib.h>

#include "s_fighter.h"
#include "cte_move.h" // Para el set body.

/*
typedef struct _s_fighter {

   char * name;
   int spd; // Velocidad de movimiento.

   rect body; // Referencia al cuerpo actual, es dinámico ero igual lo pongo aquí carajo!.
   rect bodyParado; // cuerpo solido
   rect bodyAgachado; // solido.
   rect bodySaltando;

   vectorHit hits; // Array de golpes.

} * s_fighter;
*/

s_fighter newSFighter (char * name, int spd, rect bParado, rect bAgachado, rect bSaltando) {

   s_fighter SF = new struct _s_fighter;
   SF->name = name;
   SF->spd = spd;
   SF->bodyParado = bParado;
   SF->bodyAgachado = bAgachado;
   SF->bodySaltando = bSaltando;
   SF->body = SF->bodyParado; // Al principio, está parado.
   
   return SF;
}

void setHitsSFighter (s_fighter & SF, vectorHit hits) {
   SF->hits = hits;
}


hit getHitSFighter (s_fighter SF, int idHit) {
   return getHitVHit(SF->hits, idHit);
}


// Velocidad.
int getSpdSFighter (s_fighter SF) {
   return SF->spd;
}


// Cuerpo.
rect getBodySFighter (s_fighter SF) {
// Devuelve el cuerpo actual.
   return SF->body;
}

void setBodySFighter (s_fighter & SF, int stat) {
// Dependiendo del status, el cuerpo cambia.
// OBS: esta operación necesita ver los status de movimiento para cambiar el cuerpo.
   switch (stat) {
   case Standing:
                 SF->body = SF->bodyParado;
   break;
   case Jumping:
                 SF->body = SF->bodySaltando;
   break;
   case Crowched:
                 SF->body = SF->bodyAgachado;
   break;
   }
}


// Tamaño del luchador //
int getWidthFighter (s_fighter SF) {
   return getWidthRect( SF->body );
}
    
int getHeightFighter (s_fighter SF) {
    return getHeightRect( SF->body );
}    
// =================== //

// Destructoras.
void destroySFighter (s_fighter & SF) {
   if (SF) {
      SF->body = NULL;
      destroyRect (SF->bodyParado);
      destroyRect (SF->bodyAgachado);
      destroyRect (SF->bodySaltando);
      delete [] SF->name;
      delete SF;
      SF = NULL;
   }
}
