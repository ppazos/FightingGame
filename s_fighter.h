#ifndef _s_fighter_h
#define _s_fighter_h

#include "rectangle.h" // para el  cuerpo.
#include "gen_rectangle.h" // para los golpes.
#include "vector_hit.h"

// Los rectángulos que voy a poner son todos solidos.

typedef struct _s_fighter {

   char * name;
   
   int spd; // Velocidad de movimiento.

   rect body; // Referencia al cuerpo actual, es dinámico ero igual lo pongo aquí carajo!.
   rect bodyParado; // cuerpo solido
   rect bodyAgachado; // solido.
   rect bodySaltando;

   vectorHit hits; // Array de golpes, cada golpe tiene toda su info.

} * s_fighter;

/// Constructoras.
s_fighter newSFighter (char * name, int spd, rect bParado, rect bAgachado, rect bSaltando);
/* Los rectángulos vienen creados de afuera, con la data del archivo. */

void setHitsSFighter (s_fighter & SF, vectorHit hits);
// El array de golpes viene armado de afuera con los datos del archivo.
hit getHitSFighter (s_fighter SF, int idHit);

// Velocidad.
int getSpdSFighter (s_fighter SF);
// Puede haber un set SPD si hubiera power ups que den + velocidad, sino, la velocidad no cambia y viene marcada por la info del archivo.

// Cuerpo.
rect getBodySFighter (s_fighter SF); // Devuelve el cuerpo actual.
void setBodySFighter (s_fighter & SF, int stat); // Dependiendo del status, el cuerpo cambia.
// OBS: esta operación necesita ver los status de movimiento para cambiar el cuerpo.


// Tamaño del luchador //
int getWidthFighter (s_fighter SF);
int getHeightFighter (s_fighter SF);


// Destructoras.
void destroySFighter (s_fighter & SF);

#endif
