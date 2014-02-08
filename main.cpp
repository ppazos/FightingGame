#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

#include "SDL_prim.h"
#include "font/SFont.h" // Para mostrar texto //

#include "cte_move.h"
#include "cte_game.h"
#include "setup.h"
#include "player.h"
#include "game_ops.h"

using namespace std;

// == ESTADOS PRINCIPALES EL JUEGO ========================================== //
// ========================================================================== //

int GAME_STAT = GAME_STAT_MAIN_MENU; // Estado inicial en Menu principal //

   // == ESTADOS SECNDARIOS ================================================= //
   int MAIN_MENU_SELECTED_BUTTON = MAIN_MENU_BUTTON1; // Por defecto Jugar está seleccionado //

// ========================================================================== //
// ========================================================================== //

// Para prueba de cambiar colores
SDL_Color colors[256];
        


/* The screen surface */
SDL_Surface *screen = NULL;

SDL_Surface * top_img = NULL; // para las energías.
SDL_Surface * shadow_izq = NULL;
SDL_Surface * shadow_der = NULL;

/// Texto.
SFont_Font * Arial;

//// Variables globales para carga y recorrida.
vectorFighter VF;

s_fighter SF1;
d_fighter DF1; /// Auxiliares para pedir luchadores.

s_fighter SF2;
d_fighter DF2;

rect rectBody; /// Para referenciar el cuerpo de los luchadores.


// Para tardar un poco en empezar el round
int startFight = 0; // 1 cuando comienza el round, es para que se denmore un poco en comenzar.
int startFightDelay = 2000;
int startFightTime;
int antesPelea = 1; // Activa tiempo antes de pelea ( sirve Para dibujar)

// Para saber si terminó un round
int endRound = 0;
int endRoundDelay = 2000; // Tiempo en ms que demora, cuando termina un round, en empezar el otro
int endRoundTime;         // Tiempo en el que se terminó el round


/*

typedef struct _vector_imgs {

   SDL_Surface ** vector;
   int size;

} * vector_imgs;

*/
                         // Imágenes del menu! //
static void drawMainMenu ( vector_imgs MMImages ) {  // Dibujar menu principal //

// Según el estado actual del menu (qué está seleccionado en el momento)
// se va a dibujar algo.
// Las posiciones de dibujo de los distintos elementos están definidos
// dentro de esta misma función, luego pueden pasar a ser constantes generales.

// Posición del titulo (logo presentación del juego) ??? Luego!
#define X_TITLE 0
#define Y_TITLE 0

// Hay 3 botones
#define X_BUTTON 135 // Todos tienen el mismo x, están alineados a la izquierda
//#define X_BUTTON1 40
#define Y_BUTTON1 220
//#define X_BUTTON2 40
#define Y_BUTTON2 260
//#define X_BUTTON3 40
#define Y_BUTTON3 300

// En el vecgtor de imágenes, las cosas son:
// 0 -> boton 1
// 1 -> boton 2
// 2 -> boton 3
// 3 -> boton 1 seleccionado
// etc...
// etc...
// 6 -> titulo


// Screen es GLOBAL !!! //

   SDL_Rect rect;
   Uint32 color;
   SDL_Surface * img; // Para guardar la referencia a la imagen que se tiene que dibujar.
   SDL_Rect dest;
   
 
   // Borra contenido anterior
   color = SDL_MapRGB (screen->format, 70, 70, 95);
   rect.w = screen->w;
   rect.h = screen->h;
   rect.x = 0; rect.y = 0;
   SDL_FillRect (screen, &rect, color);
 
 
   SFont_Write ( screen, Arial, 160, 90, "World Rulers!");
   SFont_Write ( screen, Arial, 20, 120, " _.-·| primer juego Uruguayo de lucha |·-._ ");
 
   dest.x = X_BUTTON; // Todos los botones tienen mismo X
   
   
   switch ( MAIN_MENU_SELECTED_BUTTON ) { // Si Jugar está seleccionado //
   
   case MAIN_MENU_BUTTON1:
       
      img = getImgVImgs ( MMImages, B1_IMG_SELECTED );
      dest.y = Y_BUTTON1; dest.w = img->w; dest.h = img->h;
      SDL_BlitSurface ( img, NULL, screen, &dest );
      
      img = getImgVImgs ( MMImages, B2_IMG_NORMAL );
      dest.y = Y_BUTTON2; dest.w = img->w; dest.h = img->h;
      SDL_BlitSurface ( img, NULL, screen, &dest );
      
      img = getImgVImgs ( MMImages, B3_IMG_NORMAL );
      dest.y = Y_BUTTON3; dest.w = img->w; dest.h = img->h;
      SDL_BlitSurface ( img, NULL, screen, &dest );
      
   break;
   case MAIN_MENU_BUTTON2:
       
      img = getImgVImgs ( MMImages, B1_IMG_NORMAL );
      dest.y = Y_BUTTON1; dest.w = img->w; dest.h = img->h;
      SDL_BlitSurface ( img, NULL, screen, &dest ); 
       
      img = getImgVImgs ( MMImages, B2_IMG_SELECTED );
      dest.y = Y_BUTTON2; dest.w = img->w; dest.h = img->h;
      SDL_BlitSurface ( img, NULL, screen, &dest );
      
      img = getImgVImgs ( MMImages, B3_IMG_NORMAL );
      dest.y = Y_BUTTON3; dest.w = img->w; dest.h = img->h;
      SDL_BlitSurface ( img, NULL, screen, &dest );
      
   break;
   case MAIN_MENU_BUTTON3:
       
      img = getImgVImgs ( MMImages, B1_IMG_NORMAL );
      dest.y = Y_BUTTON1; dest.w = img->w; dest.h = img->h;
      SDL_BlitSurface ( img, NULL, screen, &dest ); 
       
      img = getImgVImgs ( MMImages, B2_IMG_NORMAL );
      dest.y = Y_BUTTON2; dest.w = img->w; dest.h = img->h;
      SDL_BlitSurface ( img, NULL, screen, &dest );
      
      img = getImgVImgs ( MMImages, B3_IMG_SELECTED );
      dest.y = Y_BUTTON3; dest.w = img->w; dest.h = img->h;
      SDL_BlitSurface ( img, NULL, screen, &dest );
      
   break;
   
   }

// TEXTO
//SFont_Write (screen, Arial, getXDFighter(DF)-12, getYDFighter(DF) - 20, "Muerto");
/*
   if (img) {
      dest.x = x;
      dest.y = y; 
      dest.w = img->w;
      dest.h = img->h;
                      // SDL_Surface
      SDL_BlitSurface ( img, NULL,   screen, &dest);
      
   } else {
      cerr << "No hay imagen P1\n";
   }
*/
//golpe
/*
    color = SDL_MapRGB (screen->format, 255, 0, 255);
    if (getStatDFighter(DF) == punching || getStatDFighter(DF) == kicking) {
    
       int x1, y1, x2, y2, x3, y3, x4, y4;
       getVertexGenRect (getGRectHit(getHitSFighter(SF,getIdHitDFighter(DF)), idCombination (DF)), x1, y1, x2, y2, x3, y3, x4, y4);
    
       x1 += getXDFighter(DF); x2 += getXDFighter(DF); x3 += getXDFighter(DF); x4 += getXDFighter(DF);
       y1 += getYDFighter(DF); y2 += getYDFighter(DF); y3 += getYDFighter(DF); y4 += getYDFighter(DF);
    
       SDL_drawLine(screen, x1, y1, x2, y2, color);
       SDL_drawLine(screen, x1, y1, x4, y4, color);
       SDL_drawLine(screen, x3, y3, x2, y2, color);
       SDL_drawLine(screen, x3, y3, x4, y4, color);

    }
*/

   SDL_Flip (screen); // Cambia Buffers!

} // Dibujar menu principal //

// ========================================================================== //

static void draw (player P1, player P2) { // Función para dibujar la pelea //

   SDL_Rect rect;
   Uint32 color;
   SDL_Surface * img; // Para guardar la referencia a la imagen que se tiene que dibujar.
   SDL_Rect dest;

   color = SDL_MapRGB (screen->format, 255, 255, 150);
   rect.w = screen->w; rect.h = stageFloor - 50;
   rect.x = 0; rect.y = 0;
   SDL_FillRect (screen, &rect, color);
    
   color = SDL_MapRGB (screen->format, 100, 0, 0);
   rect.w = screen->w; rect.h = screen->h - stageFloor + 50;
   rect.x = 0; rect.y = stageFloor - 50;
   SDL_FillRect (screen, &rect, color);
   //SDL_UpdateRects(screen, 1, &rect); // ACtualiza el rectángulo que pinta todo de negro y tapa lo de atrás.

// ENERGIAS IMG
   rect.x = 10;
   rect.y = 5;
   rect.w = top_img->w;
   rect.h = top_img->h;
   SDL_BlitSurface(top_img, NULL, screen, &rect);

   // Luego hay que poner SF1 y SF2, uno para cada jugador!
   s_fighter SF;
   d_fighter DF;

   getFVectorF (VF, SF, DF, getFighterPlayer (P1));
   
   // Si el luchador 1 se murió //
   int P1muerto = 0;
   if ( getEnergyDFighter (DF) <= 0 ) {
       SFont_Write (screen, Arial, getXDFighter(DF)-12, getYDFighter(DF) - 20, "Muerto");
       P1muerto = 1;
   }    

   
   int y_salto = 0; // Para dibujar posición correcta de la imagen y considerar el caso de estar saltando. 


//cerr << "EMPIEZA P1\n";
// cuerpo
/*
   rectBody = getBodySFighter (SF);
    color = SDL_MapRGB (screen->format, 50, 100, 200);
    rect.w = getWidthRect (rectBody);
    rect.h = getHeightRect (rectBody);
    rect.x = getXRect (rectBody) + getXDFighter (DF); /// Posición absoluta respecto de la posición del luchador.
    rect.y = getYRect (rectBody) + getYDFighter (DF);
    SDL_FillRect (screen, &rect, color);
*/
//cerr << "/cuerpo\n";
    
// energía P1

   if ( !P1muerto ) { // Si P1 no se murió, dibuja la energía //

      color = SDL_MapRGB (screen->format, 255, 255, 255);
      rect.w = int (getEnergyDFighter (DF) * 3/2);
      rect.h = 20;
      rect.x = 50;
      rect.y = 19;
      SDL_FillRect (screen, &rect, color);
    
   }   
   
//cerr << "/energia\n";

/// texto
/*
   switch (getOrientationDFighter(DF)) {
   case lookingLeft:
      SFont_Write (screen, Arial, getXDFighter(DF), getYDFighter(DF) + 10, "<-");
   break;
   case lookingRight:
      SFont_Write (screen, Arial, getXDFighter(DF), getYDFighter(DF) + 10, "->");
   break;
   }
*/  
   /*
   SDL_Surface * img = getImgVF (VF, getFighterPlayer(P1), 0);
   paradoizq 0
   paradoder 1
   saltandoizq 2
   saltandoder 3
   agachadoizq 4
   agachadoder 5
   
   SDL_Rect dest;
   dest.x = getXDFighter(DF);
   dest.y = getYDFighter(DF);
   dest.w = img->w;
   dest.h = img->h;
   SDL_BlitSurface(img, NULL, screen, &dest);
   SDL_UpdateRects(screen, 1, &dest);

   
   */


//cerr << "img\n";

// SOmbra
    if (getOrientationDFighter(DF) == lookingLeft) {
       rect.x = getXDFighter(DF) - 20;
       rect.y = stageFloor - int(shadow_izq->h) + 15;
       rect.w = shadow_izq->w;
       rect.h = shadow_izq->h;
       SDL_BlitSurface(shadow_izq, NULL, screen, &rect);
    } else {
       rect.x = getXDFighter(DF) - 25;
       rect.y = stageFloor - int(shadow_der->h) + 15;
       rect.w = shadow_der->w;
       rect.h = shadow_der->h;
       SDL_BlitSurface(shadow_der, NULL, screen, &rect);
    }



   switch (getVertMoveDFighter (DF)) {
   case Standing:
      
      switch (getStatDFighter(DF)) {
      case punching:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P1), stand_punch_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P1), stand_punch_der);
         }
      break;
      
      case kicking:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P1), stand_kick_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P1), stand_kick_der);
         }
      break;
      
      case notFighting:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P1), parado_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P1), parado_der);
         }
      break;
      
      case beingHited:
         img = NULL;
      break;
      } // getSTat
      
   break;
   
   case Jumping:
   
      // ************************************************************
      // Para saber donde dibujar la imagen.
      //
      y_salto = getYJDFighter (DF);
      //
      // ************************************************************
   
      switch (getStatDFighter(DF)) {
      case punching:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P1), jump_punch_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P1), jump_punch_der);
         }
      break;
      
      case kicking:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P1), jump_kick_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P1), jump_kick_der);
         }
      break;
      
      case notFighting:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P1), saltando_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P1), saltando_der);
         }
      break;
      
      case beingHited:
         img = NULL;
      break;
      } // getSTat
      
   break;
   case Crowched:
      
      switch (getStatDFighter(DF)) {
      case punching:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P1), crowch_punch_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P1), crowch_punch_der);
         }
      break;
      
      case kicking:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P1), crowch_kick_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P1), crowch_kick_der);
         }
      break;
      
      case notFighting:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P1), agachado_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P1), agachado_der);
         }
      break;
      
      case beingHited:
         img = NULL;
      break;
      
      } //getStat
      
   break; // case crowched
   }

   if (img) {
      dest.x = getXDFighter(DF) + int(getWidthRect(getBodySFighter(SF))/2) - int(img->w/2); // para centrar al BMP al rectángulo del cuerpo.
      
      // El y del luchador es el del punto de arriba izq = stageFloor - height(body) (cuando está parado),
      // luego cuando salta, a esto se le va sumando el y del salto, que tiene que ir también aquí.
      // Acá se necesita que sea stageFloor - height(img), y falta el Y de cuando salta que se lo puedo pedir a la
      // función que da el y (el de la parábola), de esta manera, donde aparece la imagen es independiente de el
      // tamaño del cuerpo del tipo, de la manera anterior, el cuerpo tenía que medir de alto lo mismo que la imagen
      // más alta.
      // getYJDFighter (DF) es el y del salto actual.
      // stageFloor - img->h + y_salto
      
      dest.y = stageFloor - img->h + y_salto; // Si no salta, y_salto es 0.
      
      dest.w = img->w;
      dest.h = img->h;

      SDL_BlitSurface(img, NULL, screen, &dest);
      
   } else {
      cerr << "No hay imagen P1\n";
   }
   
//golpe
/*
    color = SDL_MapRGB (screen->format, 255, 0, 255);
    if (getStatDFighter(DF) == punching || getStatDFighter(DF) == kicking) {
    
       int x1, y1, x2, y2, x3, y3, x4, y4;
       getVertexGenRect (getGRectHit(getHitSFighter(SF,getIdHitDFighter(DF)), idCombination (DF)), x1, y1, x2, y2, x3, y3, x4, y4);
    
       x1 += getXDFighter(DF); x2 += getXDFighter(DF); x3 += getXDFighter(DF); x4 += getXDFighter(DF);
       y1 += getYDFighter(DF); y2 += getYDFighter(DF); y3 += getYDFighter(DF); y4 += getYDFighter(DF);
    
       SDL_drawLine(screen, x1, y1, x2, y2, color);
       SDL_drawLine(screen, x1, y1, x4, y4, color);
       SDL_drawLine(screen, x3, y3, x2, y2, color);
       SDL_drawLine(screen, x3, y3, x4, y4, color);

    }
*/

// **************************************************************************************************
// **************************************************************************************************
// **************************                                ****************************************
// ************************** EMPIEZA A DIBUJA AL LUCHADOR 2 ****************************************
// **************************                                ****************************************
// **************************************************************************************************
// **************************************************************************************************

    y_salto = 0; // Para volver a usar esta variable con el otro luchador.

/*   
   switch (getHorMoveDFighter (DF)) {
   case movingNone:
      SFont_Write (screen, Arial, getXDFighter(DF), 20, "none");
   break;
   case movingLeft:
      SFont_Write (screen, Arial, getXDFighter(DF), 20, "left");
   break;
   case movingRight:
      SFont_Write (screen, Arial, getXDFighter(DF), 20, "right");
   break;
   }
   
   switch (getStatDFighter (DF)) {
   case notFighting:
      SFont_Write (screen, Arial, getXDFighter(DF), 40, "none");
   break;
   case punching:
      SFont_Write (screen, Arial, getXDFighter(DF), 40, "punching");
   break;
   case kicking:
      SFont_Write (screen, Arial, getXDFighter(DF), 40, "kicking");
   break;
   case beingHited:
      SFont_Write (screen, Arial, getXDFighter(DF), 40, "hited");
   break;
   }
*/
/// Player2
    
   getFVectorF (VF, SF, DF, getFighterPlayer (P2));


   // Si el luchador 2 se murió //
   int P2muerto = 0;
   if ( getEnergyDFighter (DF) <= 0 ) {
       SFont_Write (screen, Arial, getXDFighter(DF)-12, getYDFighter(DF) - 20, "Muerto");
       P2muerto = 1;
   }  

// CUERPO 2
/*
   rectBody = getBodySFighter (SF);
   color = SDL_MapRGB (screen->format, 0, 255, 0);
   rect.w = getWidthRect (rectBody);
   rect.h = getHeightRect (rectBody);
   rect.x = getXRect (rectBody) + getXDFighter (DF);
   rect.y = getYRect (rectBody) + getYDFighter (DF);
   SDL_FillRect (screen, &rect, color);
*/

// energía P2
   if ( !P2muerto ) { // Si P2 no se murió, dibuja la energía //
   
      color = SDL_MapRGB (screen->format, 255, 255, 255);
      rect.w = int (getEnergyDFighter (DF) * 3/2);
      rect.h = 20;
      rect.x = 285;
      rect.y = 19;
      SDL_FillRect (screen, &rect, color);
      
   }    

// SOmbra
    if (getOrientationDFighter(DF) == lookingLeft) {
       rect.x = getXDFighter(DF) - 10;
       rect.y = stageFloor - int(shadow_izq->h) + 15;
       rect.w = shadow_izq->w;
       rect.h = shadow_izq->h;
       SDL_BlitSurface(shadow_izq, NULL, screen, &rect);
    } else {
       rect.x = getXDFighter(DF) - 20;
       rect.y = stageFloor - int(shadow_der->h) + 15;
       rect.w = shadow_der->w;
       rect.h = shadow_der->h;
       SDL_BlitSurface(shadow_der, NULL, screen, &rect);
    }

   switch (getVertMoveDFighter (DF)) {
       
   case Standing:
      
      switch (getStatDFighter(DF)) {
      case punching:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P2), stand_punch_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P2), stand_punch_der);
         }
      break;
      
      case kicking:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P2), stand_kick_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P2), stand_kick_der);
         }
      break;
      
      case notFighting:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P2), parado_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P2), parado_der);
         }
         
         // Prueba para cambiar colores ( se tiene que ver ByN )
         //SDL_SetPalette (img, SDL_LOGPAL, colors, 0, 256);
         //SDL_SetPalette (img, SDL_LOGPAL|SDL_PHYSPAL, colors, 0, 256);
         //SDL_SetPalette(img, SDL_LOGPAL|SDL_PHYSPAL, colors, 50, 256);

         
         
      break;
      
      case beingHited:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P2), s_hited_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P2), s_hited_der);
         }
      break;
      } // getSTat
      
   break;
   
   case Jumping:
   
      // ************************************************************
      // Para saber donde dibujar la imagen.
      //
      y_salto = getYJDFighter (DF);
      //
      // ************************************************************
   
      switch (getStatDFighter(DF)) {
      case punching:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P2), jump_punch_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P2), jump_punch_der);
         }
      break;
      
      case kicking:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P2), jump_kick_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P2), jump_kick_der);
         }
      break;
      
      case notFighting:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P2), saltando_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P2), saltando_der);
         }
      break;
      
      case beingHited:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P2), j_hited_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P2), j_hited_der);
         }
      break;
      } // getSTat
      
   break;
   case Crowched:
      
      switch (getStatDFighter(DF)) {
      case punching:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P2), crowch_punch_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P2), crowch_punch_der);
         }
      break;
      
      case kicking:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P2), crowch_kick_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P2), crowch_kick_der);
         }
      break;
      
      case notFighting:
         if (getOrientationDFighter(DF) == lookingLeft) {
            img = getImgVF (VF, getFighterPlayer(P2), agachado_izq);
         } else {
            img = getImgVF (VF, getFighterPlayer(P2), agachado_der);
         }
      break;
      
      case beingHited:
         img = NULL;
      break;
      
      } //getStat
      
   break; // case crowched
   }

   if (img) {
       
      dest.x = getXDFighter(DF) + int(getWidthRect(getBodySFighter(SF))/2) - int(img->w/2); // para centrar al BMP al rectángulo del cuerpo.
      dest.y = stageFloor - img->h + y_salto; // Si no salta, y_salto es 0.
      dest.w = img->w;
      dest.h = img->h;
      
      SDL_BlitSurface(img, NULL, screen, &dest);
   
   } else {
      cerr << "no hay img Player 2" << endl;
   }
    
/*
   //golpe
    color = SDL_MapRGB (screen->format, 255, 0, 255);
    if (getStatDFighter(DF) == punching || getStatDFighter(DF) == kicking) {
    
       int x1, y1, x2, y2, x3, y3, x4, y4;
       getVertexGenRect (getGRectHit(getHitSFighter(SF,getIdHitDFighter(DF)), idCombination (DF)), x1, y1, x2, y2, x3, y3, x4, y4);
    
       x1 += getXDFighter(DF); x2 += getXDFighter(DF); x3 += getXDFighter(DF); x4 += getXDFighter(DF);
       y1 += getYDFighter(DF); y2 += getYDFighter(DF); y3 += getYDFighter(DF); y4 += getYDFighter(DF);
    
       SDL_drawLine(screen, x1, y1, x2, y2, color);
       SDL_drawLine(screen, x1, y1, x4, y4, color);
       SDL_drawLine(screen, x3, y3, x2, y2, color);
       SDL_drawLine(screen, x3, y3, x4, y4, color);

    }
*/

/// texto
/*
   switch (getOrientationDFighter(DF)) {
   case lookingLeft:
      SFont_Write (screen, Arial, getXDFighter(DF), getYDFighter(DF), "<-");
   break;
   case lookingRight:
      SFont_Write (screen, Arial, getXDFighter(DF), getYDFighter(DF), "->");
   break;
   }
*/   
/*
   switch (getVertMoveDFighter (DF)) {
   case Standing:
      SFont_Write (screen, Arial, getXDFighter(DF), 60, "stand");
   break;
   case Jumping:
      SFont_Write (screen, Arial, getXDFighter(DF), 60, "jump");
   break;
   case Crowched:
      SFont_Write (screen, Arial, getXDFighter(DF), 60, "crowch");
   break;
   }
   
   switch (getHorMoveDFighter (DF)) {
   case movingNone:
      SFont_Write (screen, Arial, getXDFighter(DF), 80, "none");
   break;
   case movingLeft:
      SFont_Write (screen, Arial, getXDFighter(DF), 80, "left");
   break;
   case movingRight:
      SFont_Write (screen, Arial, getXDFighter(DF), 80, "right");
   break;
   }
   
   switch (getStatDFighter (DF)) {
   case notFighting:
      SFont_Write (screen, Arial, getXDFighter(DF), 100, "none");
   break;
   case punching:
      SFont_Write (screen, Arial, getXDFighter(DF), 100, "punching");
   break;
   case kicking:
      SFont_Write (screen, Arial, getXDFighter(DF), 100, "kicking");
   break;
   case beingHited:
      SFont_Write (screen, Arial, getXDFighter(DF), 100, "hited");
   break;
   }
*/
/// prueba para ver int con Sfont.
/*
char * pepe = new char [3];
char cero = 9 + '0';
char ocho = 8 + '0';
pepe[0] = cero;
pepe[1] = ocho;
pepe[2] = '\0';
//cout << "test: " << pepe << endl;
SFont_Write (screen, Arial, 20, 400, pepe);
*/
/// prueba

/*
    rect.w = screen->w; rect.h = screen->h;
    rect.x = 0; rect.y = 0;
    SDL_UpdateRects(screen, 1, &rect);
*/

    if ( antesPelea ) {
       SFont_Write (screen, Arial, 120, 100, "Preparados para pelear!");
    }    


    //SDL_SetPalette(screen, SDL_LOGPAL|SDL_PHYSPAL, colors, 50, 150);
   
    SDL_Flip (screen);
    
    /*************************************************************************
    /* OBS: las posiciones x,y de los rectángulos están absolutizados por la posición
    /* del luchador, aunque internamente los rectángulos estén en la posición 0,0,
    /* se puede hacer que los rectángulos que representan el cuerpo tengan distinta
    /* posición x,y, es decir que el x,y de los rectángulos no sea 0,0 como es aquí.
    /************************************************************************/

} // Draw


int main (int argc, char *argv[]) {


///// SDL SETUP -....
   char *msg;

   if (SDL_Init (SDL_INIT_VIDEO) < 0) {exit (1);}
   atexit (SDL_Quit);
   //screen = SDL_SetVideoMode (640, 480, 16, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
   //screen = SDL_SetVideoMode (640, 480, 16, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    
//--------------------------------------------------------------------------------------------------------
   int VideoFlags = SDL_HWPALETTE;

   const SDL_VideoInfo * VideoInfo = SDL_GetVideoInfo();

   if(VideoInfo == NULL) {cerr << "Failed getting Video Info : " << SDL_GetError() << endl; exit(0);}

   if(VideoInfo -> hw_available) VideoFlags |= SDL_HWSURFACE;
   else VideoFlags |= SDL_SWSURFACE;
    
   if(VideoInfo -> blit_hw) VideoFlags |= SDL_HWACCEL;

   screen = SDL_SetVideoMode (480, 360, 16, VideoFlags | SDL_DOUBLEBUF);
   //screen = SDL_SetVideoMode (480, 360, 16, VideoFlags | SDL_DOUBLEBUF | SDL_FULLSCREEN);
   //screen = SDL_SetVideoMode (640, 480, 16, VideoFlags | SDL_FULLSCREEN);
   if (screen == NULL) {exit (2);}
//---------------------------------------------------------------------------------------------------

   SDL_WM_SetCaption ("SDL MultiMedia Application", NULL);
   //SDL_ShowCursor(SDL_DISABLE); // saca el cursor (util en fullscreen mode)
    
   //if (SDL_EnableKeyRepeat (1, 10)) {cerr << "NO FUNCA KEY REPEAT.\n";}
   
// SDL SETUP end
// ============================00


// Para prueba de cambiar colores
   for(int i=0;i<256;i++){
      colors[i].r=i;
      colors[i].g=i;
      colors[i].b=i;
   }


   /// misc
   float FPS = 0;


// Main Menu Stuff //
// =============== //
   // Imágenes del menu principal //
   vector_imgs MMImages = newVImgs ( MAIN_MENU_IMG_COUNT );
   
   SDL_Surface * MM_IMG; // Auxiliar para cargar las imágenes del main menu //
   
   MM_IMG = IMG_Load("pics/main/b1_off.png");
   if (!MM_IMG ) { cerr << "NOP1" << endl; }
   addImgVImgs ( MMImages, MM_IMG, B1_IMG_NORMAL );
   
   MM_IMG = IMG_Load("pics/main/b2_off.png");
   if (!MM_IMG ) { cerr << "NOP2" << endl; }
   addImgVImgs ( MMImages, MM_IMG, B2_IMG_NORMAL );
   
   MM_IMG = IMG_Load("pics/main/b3_off.png");
   if (!MM_IMG ) { cerr << "NOP3" << endl; }
   addImgVImgs ( MMImages, MM_IMG, B3_IMG_NORMAL );
   
   MM_IMG = IMG_Load("pics/main/b1_on.png");
   if (!MM_IMG ) { cerr << "NOP4" << endl; }
   addImgVImgs ( MMImages, MM_IMG, B1_IMG_SELECTED );
   
   MM_IMG = IMG_Load("pics/main/b2_on.png");
   if (!MM_IMG ) { cerr << "NOP5" << endl; }
   addImgVImgs ( MMImages, MM_IMG, B2_IMG_SELECTED );
   
   MM_IMG = IMG_Load("pics/main/b3_on.png");
   if (!MM_IMG ) { cerr << "NOP6" << endl; }
   addImgVImgs ( MMImages, MM_IMG, B3_IMG_SELECTED );
// =============== //
// Main Menu Stuff //


   top_img = IMG_Load("pics/top.png"); // imagen para energías.
   shadow_izq = IMG_Load("pics/shadow_izq.png"); // imagen para energías.
   shadow_der = IMG_Load("pics/shadow_der.png"); // imagen para energías.


/// CARGA DE ARCHIVOS

//-------------------------------------------------------------------------------------------
//------------------------------------- CARGA DE TECLAS -------------------------------------
//-------------------------------------------------------------------------------------------

   inputP IP1 = loadInput (FileInputP1);
   if (IP1) {cout << "IP1 cargado con éxito\n";}
   
   /* imprime teclas */ cout << "Teclas Cargadas: ";
   int i = 0;
   while (IP1->vector[i]) {
      cout << IP1->vector[i] << " ";
      i++;
   }
   cout << endl << endl;

   inputP IP2 = loadInput (FileInputP2);
   if (IP2) {cout << "IP2 cargado con éxito\n";}
   
   /* imprime teclas */ cout << "Teclas Cargadas: ";
   i = 0;
   while (IP2->vector[i]) {
      cout << IP2->vector[i] << " ";
      i++;
   }
   cout << endl << endl;
//-------------------------------------------------------------------------------------------
//------------------------------------- CARGA DE TECLAS -------------------------------------
//-------------------------------------------------------------------------------------------

   VF = loadFighters (FileFighters); // Carga Luchadores del archivo de luchadores.
   //// CARGA ...

   /// Configuracion de jugadores.
   player Player1 = newPlayer (IP1);
   player Player2 = newPlayer (IP2);

   /// Seteo de luchadores.
   setFighterPlayer (Player1, 0);
   setFighterPlayer (Player2, 1);

   /// Configuración de los luchadores a usar.

   /// Player 1
   getFVectorF (VF, SF1, DF1, getFighterPlayer (Player1)); /// Luchador que usa el player1 (el de id 0)
   setXDFighter (DF1, P1startX); /// Hay que setear la x a la x predefinida del player1
   
   /// Para la posición y se necesita la altura del luchador.
   setYDFighter (DF1, stageFloor - getHeightFighter(SF1) );

   //cout << "y player 1 " << VF->vector[0].dynamicF->y << "\n";

   //// Player 2
   getFVectorF (VF, SF2, DF2, getFighterPlayer (Player2)); /// Luchador que usa el player2 (el de id 1)
   setXDFighter (DF2, P2startX);
   
   /// Para la posición y se necesita la altura del luchador.
   setYDFighter (DF2, stageFloor - getHeightFighter(SF2) );
   
   //cout << "y player 2 " << VF->vector[1].dynamicF->y << "\n";




   Arial = SFont_InitFont(IMG_Load("font/14P_Arial_Plain_Red.png"));
   if(!Arial) {
      fprintf(stderr, "An error occured while loading the font.");
      exit(1);
   }

   SDL_Event event;
    
   int done = 0;
   int esc;
   while (!done) {

// SEGUN EL ESTADO DEL JUEGO LAS FUNCIONES QUE SE LLAMAN PARA INPUT Y DRAW SON DISTINTAS
// CUANDO UN ROUND TERMINA, uno muere, LOS LUCHADORES SE REPOSICIONAN EN P1startX y P2startX (Ctes. de cte_game.h)

      esc = 0; // Para saber si se quiso ir de la lucha


      if ( GAME_STAT == GAME_STAT_MAIN_MENU ) {
       
         int newActiveButton = 0, optionSelected = 0; // Para ver el nuevo boton activo y si se eligió alguna opcion
       
         drawMainMenu ( MMImages ); // Dibujar de Main Menu
         
         done = inputMainMenu ( event, MAIN_MENU_SELECTED_BUTTON, newActiveButton, optionSelected);
         
         MAIN_MENU_SELECTED_BUTTON = newActiveButton; // Luego de ver el input, setea el nuevo boton seleccionado
         
         if ( optionSelected ) { // Si se seleccionó una opción, hay que ver cual es el boton activo para tomar una desición
         
            switch ( MAIN_MENU_SELECTED_BUTTON ) { // Si Jugar está seleccionado //
            case MAIN_MENU_BUTTON1: // Jugar !
            
               GAME_STAT = GAME_STAT_FIGHT; // Tendría que ir a select Player! 
            
            break;
            case MAIN_MENU_BUTTON2: // Opciones (NA for now!)
            break;
            case MAIN_MENU_BUTTON3: // Salir
               done = 1; // Termina bucle
            break;
            }    
         
         }       
                
      } else if ( GAME_STAT == GAME_STAT_FIGHT ) { // Dentro del Juego //

/*
int startFight = 0; // 1 cuando comienza el round, es para que se denmore un poco en comenzar.
int startFightDelay = 2000;
int startFightTime;
*/
         if ( !startFight ) { // Si no empezó la lucha
            startFightTime = SDL_GetTicks() + startFightDelay;
            startFight=1;
            
            // Para que empiecen bien orientados
            // La dirección del P1 siempre es der y la del P2 izq!
            setOrientationDFighter (DF1, lookingRight);
            setOrientationDFighter (DF2, lookingLeft);
            
         } else {  
            
            if ( SDL_GetTicks() > startFightTime ) { // Empezó la pelea
            
            
               antesPelea = 0; // se acabó el tiempo antes de la pelea
            
               esc = chekInput (event, Player1, Player2, VF, screen);
               // Tiene que estar afuera porque hay que vaciar el buffer de teclas!
                  
               if ( !endRound ) {
               
                  //startFight = 1;
                  
                  if (esc == 1) GAME_STAT = GAME_STAT_MAIN_MENU; // Si se quiere salir de la lucha, va al menu   

                  moveStuff (Player1, Player2, VF, screen);
          
                  if ( getEnergyDFighter(DF1) <= 0 || getEnergyDFighter(DF2) <= 0 ) { // Si alguno se murió
                     endRound = 1;
                     //endRoundTime = SDL_GetTicks();
                  }    
        
               } else { // Si terminó el round
       
                  //if ( SDL_GetTicks() > endRoundTime + endRoundDelay  ) { // Si a pasó el tiempo de fin de ronda
          
                     antesPelea = 1; // Pone el tiempo antes de la pelea
                     endRound = 0;
                     startFight = 0;
                     
                     
                     // Posición y energía iniciales
                     setXDFighter (DF1, P1startX);
                     setXDFighter (DF2, P2startX);
                     setEnergyDFighter (DF1, FullEnergy);
                     setEnergyDFighter (DF2, FullEnergy);
            
                     // Cuando termina, ninguno hace nada ! ! ! //
                     setHorMoveDFighter (DF1, movingNone);
                     setHorMoveDFighter (DF2, movingNone);
                     setVertMoveDFighter (DF1, Standing);
                     setVertMoveDFighter (DF2, Standing);
                     setStatDFighter (DF1, notFighting);
                     setStatDFighter (DF2, notFighting);
                     
                  //}    

               } // Si se terminó el round
         
            } // Si empezó la lucha ( ya luchando )
         
            draw (Player1, Player2); // Dibujar de lucha
         
         } // Si empezó la lucha ( es tiempo antes de lucha, todavía no pelean )    
         
      } // Si el estado del juego es la lucha   
    
    
      FPS++;
    
    
   } // Bucle Principal


   SDL_Quit();
   destroyVImgs ( MMImages ); // Imágenes del menu principal 
   destroyPlayer (Player1);
   destroyPlayer (Player2);
   destroyVectorF (VF);
   
//// misc.
   int secs = SDL_GetTicks(); /// en milisegundos.
   FPS = FPS * 1000 / secs;
   cout << "average FPS: " << FPS << "\n";
   //cout << hor_mov_act_time << endl;
   
   return 0;
}

