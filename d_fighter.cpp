#include <stdlib.h>
#include "d_fighter.h"
#include "cte_move.h"
/*
typedef struct _d_fighter {

   int x; int y; // Posición.
   float energy;
   unsigned short orientation;
   
   unsigned short idHit; // Identificador del golpe actual.

   Uint32 hitTime; // tiempo para el golpe.
  
   //int ouchDuration; // Duración de estatus de "siendo golpeado"
   int ouchTime; // Tiempo auxiliar para saber cuanto transcurrión desde el golpe.
   
   unsigned short idFight; // Si pega, si es golpeado o si no está haciendo nada.
   unsigned short idVertMove; // Id. de movimiento vertical. (salto, agachado, etc).
   unsigned short idHorMove; // Id de movimiento horizontal. (llendo derecha o izquierda o quieto).
   
   Uint32 jumpTime1; // Tiempos para saber cuanto transcurrió desde que saltó.
   Uint32 jumpTime2;

} * d_fighter;
*/

int getYJDFighter (d_fighter DF) { // deveulve el y del salto actual.
// NO tiene sentido llamar a esta función si no se está saltando!.

   int t = DF->jumpTime2 - DF->jumpTime1; // Tiempo desde que se comenzó el salto.
   
   /// Ecuación a seguir.
   //int y = int (t/50 * (t/50 - 25));
   int y = int (1.5*(t/50 * (t/50 - 20))); //salta más rápido con altura normal
   
   return y;
}

d_fighter newDFighter (int x, int y, float energy) {

   d_fighter DF = new struct _d_fighter;
   DF->x = x;
   DF->y = y;
   DF->energy = energy;
   DF->orientation = lookingRight; /// Al principio todos miran para el mismo lado, luego se setea.
   
   DF->idHit = 0; // Inicializo en 0 pero en realidaD no está pergando.
   DF->hitTime = 0;
  
   //DF->ouchDuration = 0;
   DF->ouchTime = 0;
   
   DF->idFight = notFighting; // Al inicio no está peleando.
   DF->idVertMove = Standing; // Está parado.
   DF->idHorMove = movingNone; // No se está moviendo.
   
   DF->jumpTime1 = 0;
   DF->jumpTime2 = 0;
   
   // NEW
   DF->horTime = 0;
   
   return DF;
}

// NUEVO
int getHorTimeDFighter (d_fighter DF) { return DF->horTime; } // Devuelve el tiempo del movimiento horizontal.
void setHorTimeDFighter (d_fighter & DF, Uint32 time) { DF->horTime = time; } // Setea el tiempo del movimiento horizontal.
// NUEVO


/// Posición.
int getXDFighter (d_fighter DF) {return DF->x;}
void setXDFighter (d_fighter & DF, int x) {DF->x = x;}
int getYDFighter (d_fighter DF) {return DF->y;}
void setYDFighter (d_fighter & DF, int y) {DF->y = y;}

/// ENERGÍA
float getEnergyDFighter (d_fighter DF) {return DF->energy;}
void setEnergyDFighter (d_fighter & DF, float energy) {DF->energy = energy;}

/// Orientación.
unsigned short getOrientationDFighter (d_fighter DF) {return DF->orientation;}
void setOrientationDFighter (d_fighter & DF, unsigned short Or) {DF->orientation = Or;}

/// Golpe dinámico
unsigned short getIdHitDFighter (d_fighter DF) {return DF->idHit;} // PRE: El luchador DEBE estar GOLPEANDO.
void setIdHitDFighter (d_fighter & DF, unsigned short id) {DF->idHit = id;}

/// Tiempo del golpe.
Uint32 getHitTimeDFighter (d_fighter DF) {return DF->hitTime;}
void setHitTimeDFighter (d_fighter & DF, Uint32 time) {DF->hitTime = time;}

/// Siendo Golpeado.
/* La duracion del ouch va a depender de la duración del golpe recibido.
int getOuchDurDFighter (d_fighter DF) {return DF->ouchDuration;}
void setOuchDurDFighter (d_fighter & DF, int time) {DF->ouchDuration = time;}
*/
int getOuchTimeDFighter (d_fighter DF) {return DF->ouchTime;}
void setOuchTimeDFighter (d_fighter & DF, int time) {DF->ouchTime = time;}

/// Movimiento Horizontal.
unsigned short getHorMoveDFighter (d_fighter DF) {return DF->idHorMove;}
void setHorMoveDFighter (d_fighter & DF, unsigned short stat) {DF->idHorMove = stat;}

/// Movimiento Vertical.
unsigned short getVertMoveDFighter (d_fighter DF) {return DF->idVertMove;}
void setVertMoveDFighter (d_fighter & DF, unsigned short stat) {DF->idVertMove = stat;}

/// Lucha.
unsigned short getStatDFighter (d_fighter DF) {return DF->idFight;}
void setStatDFighter (d_fighter & DF, unsigned short stat) {DF->idFight = stat;}

/// Tiempos de Salto.
Uint32 getJTime1DFighter (d_fighter DF) {return DF->jumpTime1;}
void setJTime1DFighter (d_fighter & DF, Uint32 time) {DF->jumpTime1 = time;}
Uint32 getJTime2DFighter (d_fighter DF) {return DF->jumpTime2;}
void setJTime2DFighter (d_fighter & DF, Uint32 time) {DF->jumpTime2 = time;}

void destroyDFighter (d_fighter & DF) {
   if (DF) {
      delete DF;
      DF = NULL;
   }
}
