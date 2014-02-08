#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <strings.h>

#include "SDL_image.h"

#include "vector_SDL_Surf.h"

using namespace std;

/*
typedef struct _vector_imgs {

   SDL_Surface ** vector;
   int size;

} * vector_imgs;
*/

vector_imgs newVImgs (int size) {

   vector_imgs VI = new struct _vector_imgs;
   VI->vector = new SDL_Surface * [size]; /// vector de punteros a sdl surf.
   
   for (int i=0; i<size; i++) {
   
      VI->vector[i] = NULL;
   
   }
   
   VI->size = size;
   return VI;
}


void addImgVImgs (vector_imgs & VI, SDL_Surface * img, int index) {

   VI->vector[index] = img;
}


SDL_Surface * getImgVImgs (vector_imgs VI, int index) {

   if (0<=index && index<VI->size) {
      return VI->vector[index];
   } else {
      return NULL;
      cerr << "Imagen Pedida: " << index << " no está! (vector_SDL_Surf::getImgVImgs)" << endl;
   }
}


vector_imgs loadVImgs (char * File) {

   string line;
   //string archivo;
   int numImgs;
   vector_imgs VI;
   SDL_Surface * img;
   SDL_Surface * imgDFormat;

   ifstream iFile (File);
   
   if (iFile) {
   
      getline (iFile, line, '='); iFile >> numImgs; getline (iFile, line); // come endl
      //cerr << line << " " << numImgs << endl;
 
      VI = newVImgs (numImgs);
      //cerr << "Pasa creación\n";
      
      for (int i=0; i<numImgs; i++) {
      
         //iFile >> archivo;
         getline (iFile, line); // agarra nombre de la imagen.
         
         //cerr << line << endl;
         //cout << &archivo[0] << "\n";
         
         img = IMG_Load(&line[0]); // carga la imagen.
         //if (img) {cout << "OK\n";}
         //else {cout << "NO\n";}
         //imgDFormat = SDL_DisplayFormat(img); // pasa la imagen al formato del display.
         //SDL_FreeSurface(img);
         
         //if (!SDL_SetAlpha (VI->vector[i], SDL_SRCALPHA | SDL_RLEACCEL, 0)) {cout << "set alpha OK\n";}
         //else {cerr << "set alpha KO\n";}

         //VI->vector[i] = SDL_DisplayFormatAlpha(img);
         //SDL_FreeSurface(img);
    
         //VI->vector[i] = imgDFormat; // agrego imagen al vector.
         VI->vector[i] = img; // agrego imagen al vector.
         //VI->vector[i] = SDL_DisplayFormat(img); // agrego imagen al vector.
         
      }
   
   } else { /// Si no se abrió el archivo.
      VI = NULL;
   }

   return VI;

}


void destroyVImgs (vector_imgs & VI) {

   for (int i=0; i<VI->size; i++) {
      SDL_FreeSurface(VI->vector[i]);
   }
   delete [] VI->vector;
   delete VI;
   VI = NULL;
}




