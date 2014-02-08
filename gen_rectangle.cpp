#include <stdlib.h>
#include <math.h>
using namespace std;

#include "gen_rectangle.h"

/*
typedef struct _genRect {
                     float m; // Coeficiente angular de la recta pricipal.
                     int x;
                     int y;
                     int w;
                     int h;
} * genGect;
*/

genRect newGenRect (int x, int y, int w, int h, float m) { /* Crea un nuevo rectangulo. */

   genRect GR = new struct _genRect;
   GR->x = x;
   GR->y = y;
   GR->w = w;
   GR->h = h;
   GR->m = m;
   
   return GR;
}

int getXGenRect (genRect GR) {
// Devuelve posición X del rectángulo. 
   return GR->x;
}

int getYGenRect (genRect GR) { /* Devuelve posición Y del rectángulo. */
   return GR->y;
}

int getWidthGenRect (genRect GR) { /* Devuelve largo del rectángulo. */
   return GR->w;
}

int getHeightGenRect (genRect GR) { /* Devuelve alto del rectángulo. */
   return GR->h;
}

void getVertexGenRect (genRect GR, int & x1, int & y1,
                                   int & x2, int & y2,
                                   int & x3, int & y3,
                                   int & x4, int & y4) {
// Devuelve coordenadas de los vértices del rectángulo.

   x1 = GR->x;
   y1 = GR->y;
   
   x2 = int ((GR->w) / sqrt( GR->m * GR->m + 1 ) + x1);
   y2 = int ((GR->w) / sqrt( GR->m * GR->m + 1 ) * GR->m + y1);
   
   x3 = int (GR->h * GR->m / sqrt( GR->m * GR->m + 1 ) + x2);
   y3 = int (- (GR->h) / sqrt( GR->m * GR->m + 1 ) + y2);

   x4 = int (GR->h * GR->m / sqrt( GR->m * GR->m + 1) + x1);
   y4 = int (- GR->h / sqrt( GR->m * GR->m + 1) + y1);
}

float getMGenRect (genRect GR) {
/* Devuelve el coeficiente angular de la recta principal del rectángulo. */
   return GR->m;
}

void setXGenRect (genRect & GR, int x) {
   GR->x = x;
}

void setYGenRect (genRect & GR, int y) {
   GR->y = y;
}

void setMGenRect (genRect & GR, float m) {
// Setea coeficiente angular.
   GR->m = m;
}

void destroyGenRect (genRect & GR) {
/* Libera memoria reservada por el rectángulo R. */
   if (GR) {
      delete GR;
      GR = NULL;
   }
}

