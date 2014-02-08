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
// File es un archivo de texto donde está la info de las imágenes a cargar.
// Crea un vector_imgs del tamaño de la cantidad de imágenes a cargar y carga el vector con las imágenes.


void destroyVImgs (vector_imgs & VI); 


#endif
