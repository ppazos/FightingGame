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
NOMBRE DEL ARCHIVO: rectangle.h
NOMBRE DEL TIPO DE DATO: rect
*/

/*
  ESTE M�DULO MODELA UN RECT�NGULO CON LOS LADOS PARALELOS A LOS LADOS DE LA PANTALLA,
  es decir rect�ngulos de esta forma:
  -----------
  |         |
  |         |
  -----------
  
  El nombre del tipo es "rect", el cual es un puntero a un tipo de dato estructurado llamado "_rect".
  El tipo de dato "rect" es un puntero porque las operaciones manejan el dato como din�mico, es decir,
  hay operaciones que reservan y liberan memoria para el rect�ngulo.
  
  Los datos dentro del estructurado "_rect" son:
     Un par de coordenadas que identifican el v�rtice superior izquierdo del rect�ngulo.
     Un par de n�meros que identifican las dimensiones del rect�ngulo, su largo y alto (width & height).
  
  La otra parte del m�dulo son las operaciones sobre el rect�ngulo.
  
  CONSTRUCTORAS:
     newRect: Dados todos los datos que componen al rect�ngulo, reserva memoria y asigna los datos.
     setXRect: Dado un rect�ngulo y una nueva coordenada, cambia su coordenada horizontal por la nueva.
     setYRect: Dado un rect�ngulo y una nueva coordenada, cambia su coordenada vertical por la nueva.
     setWidthRect: Dado un rect�ngulo y un n�mero, cambia su largo por el n�mero.
     setHeightRect: Dado un rect�ngulo y un n�mero, cambia su altura por el n�mero.
     
  SELECTORAS:
     getXRect: Dado un rect�ngulo, devuelve la coordenada horizontal del primer v�rtice del rect�ngulo.
     getYRect: Dado un rect�ngulo, devuelve la coordenada vertical del primer v�rtice del rect�ngulo.
     getWidthRect: Dado un rect�ngulo, devuelve el largo del rect�ngulo.
     getHeightRect: Dado un rect�ngulo, devuelve la altura del rect�ngulo.
     getVertexRect: Dado un rect�ngulo, devuelve las coordenadas de los 4 v�rtices.
     
  DESTRUCTORAS:
     destroyRect: Dado un rect�ngulo, libera la memoria asociada y deja al rect�ngulo en vac�o (NULL).
     
  La implementaci�n est� en el m�dulo rectangle.cpp.
  
*/

#ifndef _rect_h
#define _rect_h

typedef struct _rect {
                     int x; /* POS */
                     int y;
                     int w; /* TAMA�O */
                     int h;
} * rect;

/* CONSTRUCTORAS */
rect newRect (int x, int y, int w, int h); /* Crea un nuevo rectangulo. */

/* PARA CAMBIAR DE POSICION */
void setXRect (rect & R, int x);
void setYRect (rect & R, int y);
/* PARA CAMBIAR EL TAMA�O */
void setWidthRect (rect & R, int width);
void setHeightRect (rect & R, int height);

/* SELECTORAS */
int getXRect (rect R);      /* Devuelve posici�n X del rect�ngulo. */
int getYRect (rect R);      /* Devuelve posici�n Y del rect�ngulo. */
int getWidthRect (rect R);  /* Devuelve largo del rect�ngulo. */
int getHeightRect (rect R); /* Devuelve alto del rect�ngulo. */

/* Devuelve las coordenadas de todos los v�rtices del rect�ngulo. */
void getVertexRect (rect R, int & x1, int & y1, int & x2, int & y2,
                            int & x3, int & y3, int & x4, int & y4);


/* DESTRUCTORAS */
void destroyRect (rect & R); /* Libera memoria reservada por el rect�ngulo R. */

#endif
