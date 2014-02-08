#ifndef _vector_imgs_h
#define _vector_imgs_h

#include "SDL.h"

typedef struct _vector_imgs {

   SDL_Surface ** vector;
   int size;

} * vector_imgs;


vector_imgs newVImgs (int size);

void addImgVImgs (vector_imgs & VI, SDL_Surface * img, int index);
SDL_Surface * getImgVImgs (vector_imgs VI, int index);


vector_imgs loadVImgs (char * File);
// File es un archivo de texto donde est� la info de las im�genes a cargar.
// Crea un vector_imgs del tama�o de la cantidad de im�genes a cargar y carga el vector con las im�genes.


void destroyVImgs (vector_imgs & VI); 


#endif
