#ifndef _gen_rect_h
#define _gen_rect_h

typedef struct _genRect {
                     float m; // Coeficiente angular de la recta pricipal.
                     int x; /* POS */
                     int y;
                     int w; /* TAMA�O */
                     int h;
} * genRect;


/* CONSTRUCTORAS */
genRect newGenRect (int x, int y, int w, int h, float m);
/* Crea un nuevo rectangulo. */

/* SELECTORAS */
int getXGenRect (genRect GR);
/* Devuelve posici�n X del rect�ngulo. */

int getYGenRect (genRect GR);
/* Devuelve posici�n Y del rect�ngulo. */

int getWidthGenRect (genRect GR);
/* Devuelve largo del rect�ngulo. */

int getHeightGenRect (genRect GR);
/* Devuelve alto del rect�ngulo. */

void getVertexGenRect (genRect GR, int & x1, int & y1,
                                   int & x2, int & y2,
                                   int & x3, int & y3,
                                   int & x4, int & y4);

/* Devuelve coordenadas de los v�rtices del rect�ngulo.*/

float getMGenRect (genRect GR);
/* Devuelve el coeficiente angular de la recta principal del rect�ngulo. */

/* PARA CAMBIAR DE POSICION, operaciones propias de los rect�ngulos. */
void setXGenRect (genRect & GR, int x);
void setYGenRect (genRect & GR, int y);
void setMGenRect (genRect & GR, float m); // Setea coeficiente angular.

/* DESTRUCTORAS */
void destroyGenRect (genRect & GR);
/* Libera memoria reservada por el rect�ngulo R. */

#endif
