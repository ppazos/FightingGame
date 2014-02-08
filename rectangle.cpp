/*
M�dulo creado por Pablo Pazos.
http://urutech.iespana.es
pablito@chek.com

Cualquier duda o aporte que tengas puedes
enviarlo a mi correo.

Si ves que este m�dulo es de utilidad para
tus proyectos, me gustar�a saber de ellos.

Si�ntete libre de utilizar este m�dulo para
lo que quieras, la �nica condici�n es dejar
este texto intacto, gracias. 

NOMBRE DEL M�DULO: rectangle.
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

   rect R = new struct _rect; // Reserva memoria para el rect�ngulo.
   R->x = x;                  // Asigna datos.
   R->y = y;
   R->w = w;
   R->h = h;
   
   return R;                  // Devuelve el rect�ngulo construido.
}

int getXRect (rect R) {return R->x;}
/* Devuelve posici�n X del rect�ngulo. */

int getYRect (rect R) {return R->y;}
/* Devuelve posici�n Y del rect�ngulo. */

int getWidthRect (rect R) {return R->w;}
/* Devuelve largo del rect�ngulo. */

int getHeightRect (rect R) {return R->h;}
/* Devuelve alto del rect�ngulo. */

void setXRect (rect & R, int x) {R->x = x;}
void setYRect (rect & R, int y) {R->y = y;}

/* PARA CAMBIAR EL TAMA�O */
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
/* Libera memoria reservada por el rect�ngulo R. */
   if (R) {        // Si el rect�ngulo no es vac�o, no es NULL.
      delete R;    // Libera memoria asociada al rect�ngulo.
      R = NULL;    // Desvincula del lugar de memoria al que apuntaba R. (*)
   }
}

/*
(*) En C++ una vez que se libera la memoria de una variable din�mica (puntero a algo),
    ese puntero sigue apuntando a la direcci�n de memoria donde estaba la variable que
    ha sido eliminada, para no tener errores posteriores de querer acceder a una variable
    que fue liberada su memoria, ponemos el puntero en NULL para que no siga apuntando al
    lugar de los datos inexistentes, as�, antes de intentar operar con la variable podemos
    ver si no es NULL y luego tomar una decici�n en funci�n de lo que sea.
*/

