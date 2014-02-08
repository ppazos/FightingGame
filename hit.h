/* Definición del tipo golpe, guarda la info de cada golpe del luchador. */

#ifndef _hit_h
#define _hit_h

#include "gen_rectangle.h"

typedef struct _hit {

   char hitType; // tipo d golpe, p o k (punch or kick) No se si va a ser necesario.
   unsigned short id; // identificador para hacer referencia al golpe.
   unsigned short duration; // duracion del golpe
   float damage; // daño del golpe.
   
   // Hay necesidad de tener 2 rectángulos para un mismo golpe, porque
   // el golpe depende de para donde está mirando el luchador (orientación)
   
   //genRect GRectLL; // looking left, a partir del rect del archivo, sale este rect.
   //genRect GRectLR; // looking right, el rectángulo que se carga desde el archivo.
   
// todos los golpes posibles.
   genRect j_izq; //jump izq
   genRect j_der;
   genRect c_izq; //crowch
   genRect c_der;
   genRect s_izq; //stand
   genRect s_der;

} * hit;

//hit newHit (unsigned short Hid, unsigned short Hdur, float Hdmg, genRect GRectLL, genRect GRectLR);
hit newHit (unsigned short Hid, unsigned short Hdur, float Hdmg,
            genRect j_izq, genRect j_der,
            genRect c_izq, genRect c_der,
            genRect s_izq, genRect s_der);
// el rectángulo debe venir hecho de afuera con los datos del archiov.

unsigned short getDurationHit (hit H);
// La duracion de los golpes viene predefinida, por eso no hay set.

float getDmgHit (hit H); // Devuelve daño del golpe H.
// no hay set.

unsigned short getIdHit (hit H); // Devuelve id
// no hay set.

genRect getGRectHit (hit H, int id);
// Devuelve el GenRect del golpe H relacionado con la orientación or del luchador.

//genRect getRectHit (hit H);

void destroyHit (hit & H);

#endif
