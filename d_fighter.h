#ifndef _d_fighter_h
#define _d_fighter_h

#include "SDL.h" // por el Uint32

typedef struct _d_fighter {

   int x; int y; // Posici�n.
   float energy;
   unsigned short orientation;
   
   unsigned short idHit; // Identificador del golpe actual.
                         // Es l�gico acceder SOLO cuando el status de pelea dice que est� pegando.
   Uint32 hitTime; // tiempo para el golpe.
                   // Cuando ahy un golpe, se setea como el tiempo actual + la duracion del golpe.
   
   //int ouchDuration; // Duraci�n de estatus de "siendo golpeado".
                     // HACER que el ouchDur. sea directamente proporcional al da�o del golpe.
                     // La duracion del ouch va a depender de la duraci�n del golpe recibido.
   int ouchTime; // Tiempo auxiliar para saber cuanto transcurri�n desde el golpe.
   // Puede ser que alcance con poner solo uochTime.
   
   unsigned short idFight; // Si pega, si es golpeado o si no est� haciendo nada.
   unsigned short idVertMove; // Id. de movimiento vertical. (salto, agachado, etc).
   unsigned short idHorMove; // Id de movimiento horizontal. (llendo derecha o izquierda o quieto).
   
   Uint32 jumpTime1; // Tiempos para saber cuanto transcurri� desde que salt�.
   Uint32 jumpTime2;
   
   // El movimiento horizontal depende de los bucles, por eso en m�quinas r�pidas se mueve demasiado r�pido
   // horizontalmente, por eso es necesario agregar un tiempo de movimiento horizontal para que este movimiento
   // dependa solo del tiempo y no de la cantidad de bucles que pasan mientras se presiona la tecla de moverse.
   Uint32 horTime;
   
   // Solo voy a guardar el id del golpe!!!
   /*
   genRect hit; // Hace referancia a alguno de los golpers cargados desde e archivo.
   Uint32 hitTime; // tiempo para el golpe.
   unsigned short hitDuration; // Duraci�n del golpe.
   */
   
} * d_fighter;

d_fighter newDFighter (int x, int y, float energy);

/// Posici�n.
int getXDFighter (d_fighter DF);
void setXDFighter (d_fighter & DF, int x);
int getYDFighter (d_fighter DF);
void setYDFighter (d_fighter & DF, int y);
/// Posici�n.


/// ENERG�A
float getEnergyDFighter (d_fighter DF);
void setEnergyDFighter (d_fighter & DF, float energy);

/// Orientaci�n.
unsigned short getOrientationDFighter (d_fighter DF);
void setOrientationDFighter (d_fighter & DF, unsigned short Or);

/// Golpe din�mico
unsigned short getIdHitDFighter (d_fighter DF); // Si est� golpeandoo, devuelve el id del golpe.
void setIdHitDFighter (d_fighter & DF, unsigned short id);

/// Tiempo del golpe.
Uint32 getHitTimeDFighter (d_fighter DF);
void setHitTimeDFighter (d_fighter & DF, Uint32 time);

/// Siendo Golpeado.
/* La duracion del ouch va a depender de la duraci�n del golpe recibido.
int getOuchDurDFighter (d_fighter DF); // Devuelve la duraci�n del siendo golpeado.
void setOuchDurDFighter (d_fighter & DF, int time); // Setea duraci�n del siendo golpeado.
*/
int getOuchTimeDFighter (d_fighter DF); // Devuelve el tiempo del siendo golpeado.
void setOuchTimeDFighter (d_fighter & DF, int time); // Setea el tiempo del siendo golpeado.

// NUEVO
int getHorTimeDFighter (d_fighter DF); // Devuelve el tiempo del movimiento horizontal.
void setHorTimeDFighter (d_fighter & DF, Uint32 time); // Setea el tiempo del movimiento horizontal.
// NUEVO

/// Movimiento Horizontal.
unsigned short getHorMoveDFighter (d_fighter DF);
void setHorMoveDFighter (d_fighter & DF, unsigned short stat);

/// Movimiento Vertical.
unsigned short getVertMoveDFighter (d_fighter DF);
void setVertMoveDFighter (d_fighter & DF, unsigned short stat);

/// Lucha.
unsigned short getStatDFighter (d_fighter DF); /// Devuelve estatus de lucha.
void setStatDFighter (d_fighter & DF, unsigned short stat);

/// Tiempos de Salto.
Uint32 getJTime1DFighter (d_fighter DF); // Tiempo inicial de salto.
void setJTime1DFighter (d_fighter & DF, Uint32 time);
Uint32 getJTime2DFighter (d_fighter DF); // Tiempo actual de salto.
void setJTime2DFighter (d_fighter & DF, Uint32 time);

int getYJDFighter (d_fighter DF);
/// Operacion interna para saber la coordenada y actual en el salto, se fija en
//los tiempos de salto del fighter y devuelve, con la ecuaci�n de una par�bola
//la coordenada y en la que tiene que estar el luchador en el momento de estar saltando.

void destroyDFighter (d_fighter & DF);

#endif
