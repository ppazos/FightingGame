#ifndef _gen_rect_h
#define _gen_rect_h

typedef struct _genRect {
                     float m; // Coeficiente angular de la recta pricipal.
                     int x; /* POS */
                     int y;
                     int w; /* TAMAÑO */
                     int h;
} * genRect;


/* CONSTRUCTORAS */
genRect newGenRect (int x, int y, int w, int h, float m);
/* Crea un nuevo rectangulo. */

/* SELECTORAS */
int getXGenRect (genRect GR);
/* Devuelve posición X del rectángulo. */

int getYGenRect (genRect GR);
/* Devuelve posición Y del rectángulo. */

int getWidthGenRect (genRect GR);
/* Devuelve largo del rectángulo. */

int getHeightGenRect (genRect GR);
/* Devuelve alto del rectángulo. */

void getVertexGenRect (genRect GR, int & x1, int & y1,
                                   int & x2, int & y2,
                                   int & x3, int & y3,
                                   int & x4, int & y4);

/* Devuelve coordenadas de los vértices del rectángulo.*/

float getMGenRect (genRect GR);
/* Devuelve el coeficiente angular de la recta principal del rectángulo. */

/* PARA CAMBIAR DE POSICION, operaciones propias de los rectángulos. */
void setXGenRect (genRect & GR, int x);
void setYGenRect (genRect & GR, int y);
void setMGenRect (genRect & GR, float m); // Setea coeficiente angular.

/* DESTRUCTORAS */
void destroyGenRect (genRect & GR);
/* Libera memoria reservada por el rectángulo R. */

#endif
