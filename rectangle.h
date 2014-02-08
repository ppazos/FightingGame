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
NOMBRE DEL ARCHIVO: rectangle.h
NOMBRE DEL TIPO DE DATO: rect
*/

/*
  ESTE MÓDULO MODELA UN RECTÁNGULO CON LOS LADOS PARALELOS A LOS LADOS DE LA PANTALLA,
  es decir rectángulos de esta forma:
  -----------
  |         |
  |         |
  -----------
  
  El nombre del tipo es "rect", el cual es un puntero a un tipo de dato estructurado llamado "_rect".
  El tipo de dato "rect" es un puntero porque las operaciones manejan el dato como dinámico, es decir,
  hay operaciones que reservan y liberan memoria para el rectángulo.
  
  Los datos dentro del estructurado "_rect" son:
     Un par de coordenadas que identifican el vértice superior izquierdo del rectángulo.
     Un par de números que identifican las dimensiones del rectángulo, su largo y alto (width & height).
  
  La otra parte del módulo son las operaciones sobre el rectángulo.
  
  CONSTRUCTORAS:
     newRect: Dados todos los datos que componen al rectángulo, reserva memoria y asigna los datos.
     setXRect: Dado un rectángulo y una nueva coordenada, cambia su coordenada horizontal por la nueva.
     setYRect: Dado un rectángulo y una nueva coordenada, cambia su coordenada vertical por la nueva.
     setWidthRect: Dado un rectángulo y un número, cambia su largo por el número.
     setHeightRect: Dado un rectángulo y un número, cambia su altura por el número.
     
  SELECTORAS:
     getXRect: Dado un rectángulo, devuelve la coordenada horizontal del primer vértice del rectángulo.
     getYRect: Dado un rectángulo, devuelve la coordenada vertical del primer vértice del rectángulo.
     getWidthRect: Dado un rectángulo, devuelve el largo del rectángulo.
     getHeightRect: Dado un rectángulo, devuelve la altura del rectángulo.
     getVertexRect: Dado un rectángulo, devuelve las coordenadas de los 4 vértices.
     
  DESTRUCTORAS:
     destroyRect: Dado un rectángulo, libera la memoria asociada y deja al rectángulo en vacío (NULL).
     
  La implementación está en el módulo rectangle.cpp.
  
*/

#ifndef _rect_h
#define _rect_h

typedef struct _rect {
                     int x; /* POS */
                     int y;
                     int w; /* TAMAÑO */
                     int h;
} * rect;

/* CONSTRUCTORAS */
rect newRect (int x, int y, int w, int h); /* Crea un nuevo rectangulo. */

/* PARA CAMBIAR DE POSICION */
void setXRect (rect & R, int x);
void setYRect (rect & R, int y);
/* PARA CAMBIAR EL TAMAÑO */
void setWidthRect (rect & R, int width);
void setHeightRect (rect & R, int height);

/* SELECTORAS */
int getXRect (rect R);      /* Devuelve posición X del rectángulo. */
int getYRect (rect R);      /* Devuelve posición Y del rectángulo. */
int getWidthRect (rect R);  /* Devuelve largo del rectángulo. */
int getHeightRect (rect R); /* Devuelve alto del rectángulo. */

/* Devuelve las coordenadas de todos los vértices del rectángulo. */
void getVertexRect (rect R, int & x1, int & y1, int & x2, int & y2,
                            int & x3, int & y3, int & x4, int & y4);


/* DESTRUCTORAS */
void destroyRect (rect & R); /* Libera memoria reservada por el rectángulo R. */

#endif
