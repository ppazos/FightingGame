#include <stdlib.h>
#include <iostream>
#include "cte_game.h"
#include "cte_move.h" // por los estatus de la orientación para saber que golpe devolver en getRectHit.
#include "hit.h"

using namespace std;

/*
typedef struct _hit {

   char hitType; // tipo d golpe, p o k (punch or kick) No se si va a ser necesario.
   unsigned short id; // identificador para hacer referencia al golpe.
   unsigned short duration; // duracion del golpe
   float damage; // daño del golpe.
   //genRect GRect; // Representación del golpe omo un rectángulo generico.
   genRect GRectLL; // looking left, a partir del rect del archivo, sale este rect.
   genRect GRectLR; // looking right, el rectángulo que se carga desde el archivo.
   
   genRect jp_izq; //jump punch izq
   genRect jp_der;
   genRect jk_izq; //jump kick izq
   genRect jk_der;
   genRect cp_izq; //crowch punch
   genRect cp_der;
   genRect ck_izq; //crowch kick
   genRect ck_der;
   genRect sp_izq; //stand punch
   genRect sp_der;
   genRect sk_izq; //stand kick
   genRect sk_der;

} * hit;
*/

/*
hit newHit (unsigned short Hid, unsigned short Hdur, float Hdmg, genRect GRectLL, genRect GRectLR) {
   hit H = new struct _hit;
   H->id = Hid;
   H->duration = Hdur;
   H->damage = Hdmg;
   H->GRectLL = GRectLL;
   H->GRectLR = GRectLR;
   
   return H;
}
*/

hit newHit (unsigned short Hid, unsigned short Hdur, float Hdmg,
            genRect j_izq, genRect j_der,
            genRect c_izq, genRect c_der,
            genRect s_izq, genRect s_der)
{
   hit H = new struct _hit;
   H->id = Hid;
   H->duration = Hdur;
   H->damage = Hdmg;

   H->j_izq = j_izq;
   H->j_der = j_der;
   H->c_izq = c_izq;
   H->c_der = c_der;
   H->s_izq = s_izq;
   H->s_der = s_der;
   
   return H;
}

unsigned short getDurationHit (hit H) {return H->duration;}

float getDmgHit (hit H) {return H->damage;}

unsigned short getIdHit (hit H) {return H->id;}

//genRect getRectHit (hit H) {return H->GRect;}

genRect getGRectHit (hit H, int id) {
// Devuelve el GenRect del golpe H relacionado con la combinacion de status id.
// Son los ids de todos los posibles estatus del luchador definidos en cte_game.h

   //cerr << "getGRectHit pedido:" << id << endl;

/*
#define jump_punch_izq 6
#define jump_punch_der 7
#define jump_kick_izq 8
#define jump_kick_der 9
#define crouch_punch_izq 10
#define crouch_punch_der 11
#define crouch_kick_izq 12
#define crouch_kick_der 13
#define stand_punch_izq 14
#define stand_punch_der 15
#define stand_kick_izq 16
#define stand_kick_der 17
*/
/// Depende 

   

   switch (id) {
      case jump_punch_izq: 
         return H->j_izq;
      break;
      case jump_punch_der:
         return H->j_der;
      break;
      case jump_kick_izq: 
         return H->j_izq;
      break;
      case jump_kick_der:
         return H->j_der;
      break;
      case crowch_punch_izq: 
         return H->c_izq;
      break;
      case crowch_punch_der:
         return H->c_der;
      break;
      case crowch_kick_izq: 
         return H->c_izq;
      break;
      case crowch_kick_der:
         return H->c_der;
      break;
      case stand_punch_izq: 
         return H->s_izq;
      break;
      case stand_punch_der:
         return H->s_der;
      break;
      case stand_kick_izq: 
         return H->s_izq;
      break;
      case stand_kick_der:
         return H->s_der;
      break;
   }


/*
   if (Or == lookingRight) {
      return H->GRectLR;
   } else {
      return H->GRectLL;
   }
*/

}

void destroyHit (hit & H) {
   if (H) { // si H != NULL
      //destroyGenRect (H->GRectLL);
      //destroyGenRect (H->GRectLR);
      delete H;
      H = NULL;
   }
}
