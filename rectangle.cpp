/*
Módulo creado por Pablo Pazos.
http://urutech.iespana.es
pablito@chek.com

Cualquier duda o aporte que tengas puedes
enviarlo a mi correo.

Si ves que este módulo es de utilidad para
tus proyectos, me gustaría saber de ellos.

Siéntete libre de utilizar este módulo para
lo que quieras, la única condición es dejar
este texto intacto, gracias. 

NOMBRE DEL MÓDULO: rectangle.
NOMBRE DEL ARCHIVO: rectangle.cpp
NOMBRE DEL TIPO DE DATO: rect
*/


#include <stdlib.h>

using namespace std;

#include "rectangle.h"

/*
typedef struct _rect {
                     int x;
                     int y;
                     int w; 
                     int h;
} * rect;
*/

rect newRect (int x, int y, int w, int h) { /* Crea un nuevo rectangulo. */

   rect R = new struct _rect; // Reserva memoria para el rectángulo.
   R->x = x;                  // Asigna datos.
   R->y = y;
   R->w = w;
   R->h = h;
   
   return R;                  // Devuelve el rectángulo construido.
}

int getXRect (rect R) {return R->x;}
/* Devuelve posición X del rectángulo. */

int getYRect (rect R) {return R->y;}
/* Devuelve posición Y del rectángulo. */

int getWidthRect (rect R) {return R->w;}
/* Devuelve largo del rectángulo. */

int getHeightRect (rect R) {return R->h;}
/* Devuelve alto del rectángulo. */

void setXRect (rect & R, int x) {R->x = x;}
void setYRect (rect & R, int y) {R->y = y;}

/* PARA CAMBIAR EL TAMAÑO */
void setWidthRect (rect & R, int width) {R->w = width;}
void setHeightRect (rect & R, int height) {R->h = height;}

void getVertexRect (rect R, int & x1, int & y1, int & x2, int & y2,
                            int & x3, int & y3, int & x4, int & y4) {

    x1 = R->x; y1 = R->y;
    x2 = x1 + R->w; y2 = y1;
    x3 = x2; y3 = y2 + R->h;
    x4 = x1; y4 = y3;
}

void destroyRect (rect & R) {
/* Libera memoria reservada por el rectángulo R. */
   if (R) {        // Si el rectángulo no es vacío, no es NULL.
      delete R;    // Libera memoria asociada al rectángulo.
      R = NULL;    // Desvincula del lugar de memoria al que apuntaba R. (*)
   }
}

/*
(*) En C++ una vez que se libera la memoria de una variable dinámica (puntero a algo),
    ese puntero sigue apuntando a la dirección de memoria donde estaba la variable que
    ha sido eliminada, para no tener errores posteriores de querer acceder a una variable
    que fue liberada su memoria, ponemos el puntero en NULL para que no siga apuntando al
    lugar de los datos inexistentes, así, antes de intentar operar con la variable podemos
    ver si no es NULL y luego tomar una decición en función de lo que sea.
*/

