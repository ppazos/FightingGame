#include <stdlib.h>
#include <iostream>
//#include "SDL.h"
#include "colision.h"
#include "cte_move.h"
#include "cte_game.h"
#include "game_ops.h"

using namespace std;


int inputMainMenu ( SDL_Event event, int actualButton, int & activeButton, int & optionSelected ) {

   // ============================================================================ //
   //                                                                              //
   // En activeButtton se devuelve el identificador del botón del menu principal   //
   // que quedó seleccionado luego de procesar las teclas.                         //
   //                                                                              //
   // actualButton es el boton que está seleccionado en el momento en que se llama //
   // a esta función.                                                              //
   //                                                                              //
   // ============================================================================ //

   optionSelected = 0;
   activeButton = actualButton; // Si no se hizo nada, queda igual!

   char keyName; // para saber que tecla se apretó.

   while (SDL_PollEvent (&event)) { /* Check for events */

      //keyName = *SDL_GetKeyName(event.key.keysym.sym);

      switch (event.type) {
      
      // Si se levantó una tecla, no me interesa...
      
      // Con las teclas arriba y abajo se navega en el menu
      // Con enter o espacio se selecciona opción
      
      // PUEDO USAR QUE LOS IDS son seguidos! (*)
      // MAIN_MENU_BUTTON1 0
      // MAIN_MENU_BUTTON2 1
      // MAIN_MENU_BUTTON3 2
      
      case SDL_QUIT:
         return 1;
      break;
      
      case SDL_KEYDOWN:
         if ( event.key.keysym.sym == SDLK_DOWN) { // Si se apretó para abajo
         
         // (*)
            activeButton = ( actualButton + 1 ) % MAIN_MENU_BUTTON_COUNT; // Cantidad de botones del Main Menu
         
         } else
         if ( event.key.keysym.sym == SDLK_UP ) { // Si se apretó para arriba
         
         // (*)
            activeButton = ( actualButton - 1 + MAIN_MENU_BUTTON_COUNT ) % MAIN_MENU_BUTTON_COUNT;
         
         } else
         if ( event.key.keysym.sym == SDLK_SPACE  ||
              event.key.keysym.sym == SDLK_KP_ENTER ||
              event.key.keysym.sym == SDLK_RETURN ) { // Si se apretó espacio o cualquier enter
              
         // (*)
              optionSelected = 1;
              
         } else if (event.key.keysym.sym == SDLK_ESCAPE) { // para cerrar el programa.
            return 1;
         }
         // SDLK_KP_ENTER enter de keypad (teclado numérico)
         // SDLK_RETURN enter común
      break;
      } // Switch    
      
   } // while hay teclas en buffer   
   
   return 0;

}


// ========================================================================== //
int idCombination (d_fighter DF) {
// Devuelve el id de combinación de movimientos (definidos en cte_game.h) dependiendo de el mov vertical y la orientación.

   switch (getVertMoveDFighter (DF)) {
   
   case Standing:
   
      switch (getStatDFighter(DF)) {
      case punching: /// parado + piña
         if (getOrientationDFighter(DF) == lookingLeft) {
            return stand_punch_izq;
         } else {
            return stand_punch_der;
         }
      break;
      
      case kicking: /// parado + patada
         if (getOrientationDFighter(DF) == lookingLeft) {
            return stand_kick_izq;
         } else {
            return stand_kick_der;
         }
      break;
      
      case notFighting: /// parado  normal.
         if (getOrientationDFighter(DF) == lookingLeft) {
            return parado_izq;
         } else {
            return parado_der;
         }
      break;
      
      case beingHited:
      break;
      } // switch stat
      
   break;
   
   case Jumping:
      
      switch (getStatDFighter(DF)) {
      case punching: /// salto + piña
         if (getOrientationDFighter(DF) == lookingLeft) {
            return jump_punch_izq;
         } else {
            return jump_punch_der;
         }
      break;
      
      case kicking: /// salto + patada
         if (getOrientationDFighter(DF) == lookingLeft) {
            return jump_kick_izq;
         } else {
            return jump_kick_der;
         }
      break;
      
      case notFighting: /// Salto normal.
         if (getOrientationDFighter(DF) == lookingLeft) {
            return saltando_izq;
         } else {
            return saltando_der;
         }
      break;
      
      case beingHited:
      break;
      } /// switch stat
      
   break; /// caso saltando
   
   case Crowched:
      
      switch (getStatDFighter(DF)) {
      case punching: /// salto + piña
         if (getOrientationDFighter(DF) == lookingLeft) {
            return crowch_punch_izq;
         } else {
            return crowch_punch_der;
         }
      break;
      
      case kicking: /// salto + patada
         if (getOrientationDFighter(DF) == lookingLeft) {
            return crowch_kick_izq;
         } else {
            return crowch_kick_der;
         }
      break;
      
      case notFighting: /// Salto normal.
         if (getOrientationDFighter(DF) == lookingLeft) {
            return agachado_izq;
         } else {
            return agachado_der;
         }
      break;
      
      case beingHited:
      break;
      } /// switch stat
      
   break; // case crowched
   }

}


int chekInput (SDL_Event event, player Player1, player Player2, vectorFighter VF, SDL_Surface * screen) {

   /**** NUEVO, Para poderes. ****/
   #define MAXSTR 128
   // Static para que queden con los mismos valores en cada vuelta

   static char * P1power = new char [MAXSTR]; /* String que guarda el texto que se va formacndo con el input. */

   static int i = 0; /* Lugar del string de poder del jugadro 1 donde se va a guardar la siguiente enrtada. */
   static Uint32 deathTime = 0; /* tiempo de duración del texto del poder */
   static Uint32 iniTime = 0;

   static bool primera = true;
   static bool trucoHecho = false;

   if ( primera ) { // La primera vez, se crea el tiempo y se inicializa el string.
      iniTime = SDL_GetTicks();
      //P1power = new char [512]; // Bastante para no tener problemas.
   
      // for (int k=0;k<MAXSTR;k++) {  P1power[k] = 13;  } // Inicializacion del string NO FUNCA BIEN!
   
      primera = false;
   }


   deathTime =  SDL_GetTicks() - iniTime; // El tiempo actual


   if ( (deathTime > 1000) || (trucoHecho) ) { // Si pasa El tiepmpo de duración o se hace el truco.
   //if ( trucoHecho ) {
   //cout << "Se muere" << endl;

      delete (P1power); // Borra el texto viejo
   
      P1power = new char [MAXSTR]; // Guardo nuevamente memoria, Bastante para no tener problemas.
      //for (int k=0;k<MAXSTR;k++) {  P1power[k] = 13;  } // Inicializacion del string NO FUNCA BIEN!
  
      iniTime = SDL_GetTicks();// De nuevo el tiempo comienza.
      i = 0; // El indice al primer lugar.
      deathTime = 0; // para quitar el valor anterior.
   
      trucoHecho = false;

   }


/**** NUEVO, Para poderes. ****/

   inputP IP1 = getKeysPlayer (Player1);
   inputP IP2 = getKeysPlayer (Player2);
   
   s_fighter SF1; d_fighter DF1;
   getFVectorF (VF, SF1, DF1, getFighterPlayer (Player1)); /// Luchador que usa el player1 (el de id 0)

   s_fighter SF2; d_fighter DF2;
   getFVectorF (VF, SF2, DF2, getFighterPlayer (Player2));

   char keyName; // para saber que tecla se apretó.


   while (SDL_PollEvent (&event)) { /* Check for events */

      //keyName = *SDL_GetKeyName(event.key.keysym.sym);

      switch (event.type) {
      
      case SDL_KEYUP: // SE LEVANTÓ UNA TECLA.
         
         // Player 1.
         if (event.key.keysym.sym == getKeyInputPlayer (IP1, movingRight)) { // Se levanta la tecla de mover derecha
            if (getHorMoveDFighter (DF1) == movingRight) { // Si se estaba moviendo a la derecha.
               setHorMoveDFighter (DF1, movingNone); // Que se quede quieto.
                
/**** NUEVO, Para poderes. ****/
//P1power [i] = ')'; i++;
//P1power [i] = 'F'; i++;
//P1power [i+1] = '\0'; // null al final
// El texto de levantado para la derecha es )F
/**** NUEVO, Para poderes. ****/

            }
         } else
         if (event.key.keysym.sym == getKeyInputPlayer (IP1, movingLeft)) { // Levantó la tecla de mover izquierda
            if (getHorMoveDFighter (DF1) == movingLeft) { // Si se estaba moviendo a la izquierda.
               setHorMoveDFighter (DF1, movingNone); // Que se quede quieto.

/**** NUEVO, Para poderes. ****/
//P1power [i] = ')'; i++;
//P1power [i] = 'B'; i++;
//P1power [i+1] = '\0'; // null al final
// El texto de levantado para la izquierda es )B
/**** NUEVO, Para poderes. ****/

            }
         } else
         if (event.key.keysym.sym == getKeyInputPlayer (IP1, Crowched)) { // Se levantó la tecla de agachado.
            if (getVertMoveDFighter (DF1) == Crowched) { // Si se estaba agachado
               setVertMoveDFighter (DF1, Standing); // Que se quede parado
               setBodySFighter (SF1, Standing); // Cambia a el cuerpo parado
               setYDFighter (DF1, stageFloor - getHeightRect(getBodySFighter(SF1))); // Vuelve a calcular pos. vert. con el nuevo cuerpo

/**** NUEVO, Para poderes. ****/
//P1power [i] = ')'; i++;
//P1power [i] = 'D'; i++;
//P1power [i+1] = '\0'; // null al final
// El texto de levantado para la abajo es )D
/**** NUEVO, Para poderes. ****/

            }
         }

         // Player 2.
         if (event.key.keysym.sym == getKeyInputPlayer (IP2, movingRight)) {
            if (getHorMoveDFighter (DF2) == movingRight) { // Si se estaba moviendo a la derecha.
               setHorMoveDFighter (DF2, movingNone); // Que se quede quieto.
            }
         } else
         if (event.key.keysym.sym == getKeyInputPlayer (IP2, movingLeft)) {
            if (getHorMoveDFighter (DF2) == movingLeft) { // Si se estaba moviendo a la izquierda.
               setHorMoveDFighter (DF2, movingNone); // Que se quede quieto.
            }
         } else
         if (event.key.keysym.sym == getKeyInputPlayer (IP2, Crowched)) {
            if (getVertMoveDFighter (DF2) == Crowched) { // Si se estaba moviendo a la izquierda.
               setVertMoveDFighter (DF2, Standing); // Que se quede quieto.
               setBodySFighter (SF2, Standing); // Cambia a el cuerpo parado.
               setYDFighter (DF2, stageFloor - getHeightRect(getBodySFighter(SF2)));
            }
         }
      break; /// si fue key up.
      
      
      case SDL_KEYDOWN: // OJO, ESTE evento falla si se precionan varias teclas del teclado al mismo tiempo.
      // Se tiene que ver también si se está precionando una tecla pidiendo el estado del teclado!.

         if ( event.key.keysym.sym == getKeyInputPlayer (IP1, actionUP) ) { ///// TECLA ARRIBA P1 //////////////////
            if (getVertMoveDFighter (DF1) != Jumping && getStatDFighter(DF1) == notFighting) { // Si no está saltando y no está peleando
               setBodySFighter (SF1, Jumping); // Cuando salta tiene el cuaerpo parado (por si estaba agachado), luego puede haber un cuerpo saltando.
               setVertMoveDFighter (DF1, Jumping); // Cambia estatus a saltando.
               setJTime1DFighter (DF1, SDL_GetTicks()); // Setea tiempo inicial del salto.
               
/**** NUEVO, Para poderes. ****/
P1power [i] = 'U'; i++;
P1power [i] = '('; i++;
//P1power [i+1] = '\0'; // null al final
// El texto es U(
/**** NUEVO, Para poderes. ****/

            }
            
         } else if ( event.key.keysym.sym == getKeyInputPlayer (IP1, actionDOWN) ) { ///// TECLA ABAJO P1 ///////////
            if (getVertMoveDFighter (DF1) != Jumping) { // No se agacha si está saltando.
               setVertMoveDFighter (DF1, Crowched); // Que se agache.
               setBodySFighter (SF1, Crowched); // Cambia a el cuerpo agachado.
               setYDFighter (DF1, stageFloor - getHeightRect(getBodySFighter(SF1)));
               
/**** NUEVO, Para poderes. ****/
P1power [i] = 'D'; i++;
P1power [i] = '('; i++;
//P1power [i+1] = '\0'; // null al final
// El texto de presionado es D(
/**** NUEVO, Para poderes. ****/

            }
            
         } else if ( event.key.keysym.sym == getKeyInputPlayer (IP1, actionLEFT) ) { ///// IZQUIERDA P1 /////////////
            setHorMoveDFighter (DF1, movingLeft);
            setHorTimeDFighter (DF1, SDL_GetTicks() + hor_mov_act_time); // Tiempo para el movimiento horizontal.

/**** NUEVO, Para poderes. ****/
P1power [i] = 'B'; i++;
P1power [i] = '('; i++;
//P1power [i+1] = '\0'; // null al final

//cout << "ENTRA LEFT" << endl;
//cout << P1power << endl;
// El texto  es B(
/**** NUEVO, Para poderes. ****/
            
         } else if ( event.key.keysym.sym == getKeyInputPlayer (IP1, actionRIGHT) ) { //// DERECHA P1 ///////////////
            setHorMoveDFighter (DF1, movingRight);

            setHorTimeDFighter (DF1, SDL_GetTicks() + hor_mov_act_time); // Tiempo para el movimiento horizontal.

/**** NUEVO, Para poderes. ****/
P1power [i] = 'F'; i++;
P1power [i] = '('; i++;
//P1power [i+1] = '\0'; // null al final
// El texto  es F(
/**** NUEVO, Para poderes. ****/
            
         } else if ( event.key.keysym.sym == getKeyInputPlayer (IP1, actionPUNCH) ) { /////// PIÑA P1 /////////////
           
             if (getStatDFighter (DF1) == notFighting) { // Si no está peleando.
             
               setStatDFighter (DF1, punching);
               
            // la piña tiene id 0. (es el golpe 0 en el archivo de luchadores)
               setIdHitDFighter (DF1, 0);
               
            // setea tiempo de término del golpe.
               setHitTimeDFighter (DF1, getDurationHit(getHitSFighter(SF1, 0)) + SDL_GetTicks());
               
            // Cuando golpea se deja de mover horizontalmente.
               if (getHorMoveDFighter(DF1) != movingNone && getVertMoveDFighter(DF1) != Jumping) { // si se mueve pero no estaba saltando.
                  setHorMoveDFighter(DF1, movingNone);
               }
               
/**** NUEVO, Para poderes. ****/
P1power [i] = 'P'; i++;
P1power [i] = '('; i++;
//P1power [i+1] = '\0'; // null al final
// El texto  es P(
/**** NUEVO, Para poderes. ****/
               
            } // Si no estaba peleando.
            
         } else if ( event.key.keysym.sym == getKeyInputPlayer (IP1, actionKICK) ) { ///// PATADA P1 ///////////////
            
            if (getStatDFighter (DF1) == notFighting) { // Si no está peleando.
            
               setStatDFighter (DF1, kicking);
               
            // la tecla, o estado, kicking, hace referencia al golpe con id = 1.
               setIdHitDFighter (DF1, 1);          
               
            // setea tiempo de término del golpe.
               setHitTimeDFighter (DF1, getDurationHit (getHitSFighter(SF1,1)) + SDL_GetTicks());
               
            // Cuando golpea se daje de mover horizontalmente.
               if (getHorMoveDFighter(DF1) != movingNone && getVertMoveDFighter(DF1) != Jumping) { // si se mueve pero no estaba saltando.
                  setHorMoveDFighter(DF1, movingNone);
               }
               
/**** NUEVO, Para poderes. ****/
P1power [i] = 'K'; i++;
P1power [i] = '('; i++;
//P1power [i+1] = '\0'; // null al final
// El texto  es K(
/**** NUEVO, Para poderes. ****/
               
            } // Si no estaba PELEANDO.
            
 // TECLAS EL JUGADOR 2           
            
         } else // ahora las teclas del player 2.
         if ( event.key.keysym.sym == getKeyInputPlayer (IP2, actionUP) ) { ////////////////////////////////////////
            if (getVertMoveDFighter (DF2) != Jumping && getStatDFighter(DF2) == notFighting) { // Si no está saltando y no está peleando
               setBodySFighter (SF2, Jumping); // Cuando salta tiene el cuaerpo parado (por si estaba agachado), luego puede haber un cuerpo saltando.
               setVertMoveDFighter (DF2, Jumping); // Cambia estatus a saltando.
               setJTime1DFighter (DF2, SDL_GetTicks()); // Setea tiempo inicial del salto.
            }
         } else if ( event.key.keysym.sym == getKeyInputPlayer (IP2, actionDOWN) ) { ///////////////////////////////
            if (getVertMoveDFighter (DF2) != Jumping) { // No se agacha si está saltando.
               setVertMoveDFighter (DF2, Crowched); // Que se agache.
               setBodySFighter (SF2, Crowched); // Cambia a el cuerpo agachado.
               setYDFighter (DF2, stageFloor - getHeightRect(getBodySFighter(SF2)));
            }
         } else if ( event.key.keysym.sym == getKeyInputPlayer (IP2, actionLEFT) ) { ///////////////////////////////
            setHorMoveDFighter (DF2, movingLeft);
            // NUEVO !!!
            setHorTimeDFighter (DF2, SDL_GetTicks() + hor_mov_act_time); // Tiempo para el movimiento horizontal.
            // NUEVO !!!
            
         } else if ( event.key.keysym.sym == getKeyInputPlayer(IP2, actionRIGHT) ) { ///////////////////////////////
            setHorMoveDFighter (DF2, movingRight);
            // NUEVO !!!
            setHorTimeDFighter (DF2, SDL_GetTicks() + hor_mov_act_time); // Tiempo para el movimiento horizontal.
            // NUEVO !!!
            
         } else if ( event.key.keysym.sym == getKeyInputPlayer (IP2, actionPUNCH) ) { //////////////////////////////
            if (getStatDFighter (DF2) == notFighting) { // Si no está peleando.
               setStatDFighter (DF2, punching);
            // la piña tiene id 0. (es el golpe 0 en el archivo de luchadores)
               setIdHitDFighter (DF2, 0);
            // setea tiempo de término del golpe.
               setHitTimeDFighter (DF2, getDurationHit(getHitSFighter(SF2, 0)) + SDL_GetTicks());
            // Cuando golpea se daje de mover horizontalmente.
               if (getHorMoveDFighter(DF2) != movingNone && getVertMoveDFighter(DF2) != Jumping) { // si se mueve pero no estaba saltando.
                  setHorMoveDFighter(DF2, movingNone);
               }
            } // si no estaba peleando.
         } else if ( event.key.keysym.sym == getKeyInputPlayer (IP2, actionKICK) ) { ///////////////////////////////
            if (getStatDFighter (DF2) == notFighting) { // Si no está peleando.
               setStatDFighter (DF2, kicking);
            // la tecla, o estado, kicking, hace referencia al golpe con id = 1.
               setIdHitDFighter (DF2, 1);          
            // setea tiempo de término del golpe.
               setHitTimeDFighter (DF2, getDurationHit (getHitSFighter(SF2, 1)) + SDL_GetTicks());
            // Cuando golpea se daje de mover horizontalmente.
               if (getHorMoveDFighter(DF2) != movingNone && getVertMoveDFighter(DF2) != Jumping) { // si se mueve pero no estaba saltando.
                  setHorMoveDFighter(DF2, movingNone);
               }
            } // Si no estaba peleando.
         } 
         else if (event.key.keysym.sym == SDLK_ESCAPE) { // para cerrar el programa.
            return 1;
         }
         
      break; /// caso key down
      
      case SDL_QUIT:
         return 1;
      break;
   
      case SDL_VIDEORESIZE :                     // if there is a resize event
      screen = SDL_SetVideoMode( event.resize.w, event.resize.h, 16, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
      if (screen == NULL) {
         cerr << " Failed resizing SDL window : " << SDL_GetError() << endl;   // report error
         return 1;
      }
      break; // video resize
   
      } /// switch event.type


   } /// while sdl poll
   
   //P1power [i+1] = '\0';
   
   
   
   //cout << "POWER: " << P1power << endl; // Para ver que texto de poder se ingresó.
   
   
   
   //char * Buff = new char[MAXSTR];
   //strcpy(Buff,P1power);
   //cout << "buff" << Buff << endl;
   
   // Esto es más exacto que el compare
   /*
   if ( strstr( P1power, "B(D(F(" ) != NULL ) {// Si el substring B(D(F( está en el string P1power
      trucoHecho = true; // poeque se hace el truco.
      cout << "Abuken Rapido" << endl;
   }
   */
   /*
   if ( strcmp ( P1power, "B(D(F(" ) == 0 ) {
   //if ( strcmp ( Buff, "B(D(F(" ) == 0 ) {
      trucoHecho = true; // poeque se hace el truco.
      cout << "Abuken Rapido" << endl;
   }
   */
   return 0; 
       
}


void moveStuff (player Player1, player Player2, vectorFighter VF, SDL_Surface * screen) {

   inputP IP1 = getKeysPlayer (Player1);
   inputP IP2 = getKeysPlayer (Player2);
   
   s_fighter SF1; d_fighter DF1;
   getFVectorF (VF, SF1, DF1, getFighterPlayer (Player1)); /// Luchador que usa el player1 (el de id 0)

   s_fighter SF2; d_fighter DF2;
   getFVectorF (VF, SF2, DF2, getFighterPlayer (Player2));
   
   Uint8 *keystate = SDL_GetKeyState(NULL);


// HAY QUE VER QUE SI LOS 2 están pegando, si ambos golpes llegan, que se peguen los 2.
// para que no sea ventajoso para el que se chekea primero.

//***************************************************
// Chekeo para término de "siendo golpeado"
//********************************************************************************************

   if (getStatDFighter (DF1) == beingHited) {
         
         if (getStatDFighter (DF2) == beingHited) { // Si los 2 se pegaron.
         
            if (getOuchTimeDFighter (DF1) <= SDL_GetTicks()) { // terminó de ser golpeado 1.
               setStatDFighter (DF1, notFighting);
            }
            if (getOuchTimeDFighter (DF2) <= SDL_GetTicks()) { // terminó de ser golpeado 2.
               setStatDFighter (DF2, notFighting);
            }
         
         } else { // P1 siendo golpeado.
         
            if (getOuchTimeDFighter (DF1) <= SDL_GetTicks()) { // terminó de ser golpeado 1.
               setStatDFighter (DF1, notFighting);
            }
         }
         
   } else {
   
      if (getStatDFighter (DF2) == beingHited) { // P2 siendo golpeado.
         if (getOuchTimeDFighter (DF2) <= SDL_GetTicks()) { // terminó de ser golpeado 1.
            setStatDFighter (DF2, notFighting);
         }
      }
   }

//********************************************************************************************
// Chekeo para término de "siendo golpeado"
//***************************************************
//***************************************************
// Movimiento
//********************************************************************************************

//////////////////////////////////////////////////////////////////////////
// REGLA: cuando termina de saltar, se termina el golpe dado en el aire. (*)
// Hay que tener cuidado porque también se termina el siendo golpeado si lo
// golpean en el aire, si lo golpean en el aire, debería caer al piso y luego
// de la duración del siendo golpeado, que se levante.
//////////////////////////////////////////////////////////////////////////


// Plyer 1
/// Ver por salto.
   if (getVertMoveDFighter (DF1) == Jumping) {

      setJTime2DFighter (DF1, SDL_GetTicks()); /// Setea tiempo actual del salto.
      int y_Salto1 = getYJDFighter (DF1); /// pide y actual del salto.

      if (y_Salto1 <= 0) { // Si está saltando.
         setYDFighter (DF1, stageFloor - getHeightRect(getBodySFighter(SF1)) + y_Salto1);
      } else { // Se termina el salto.
      
         if ( keystate [getKeyInputPlayer(IP1, actionDOWN)] ) {// si está apretada la tecla abajo del P1
            setStatDFighter(DF1, notFighting); // termina golpe del aire. (*)
            setBodySFighter (SF1, Crowched);
            setVertMoveDFighter (DF1, Crowched);
         } else {
            setStatDFighter(DF1, notFighting); // termina golpe del aire. (*)
            setBodySFighter (SF1, Standing);
            setVertMoveDFighter (DF1, Standing);
         }
         setYDFighter (DF1, stageFloor - getHeightRect(getBodySFighter(SF1)) );
         
      }
   } /// if salta
   
   
   /// Movimiento horizontal.
   if (getStatDFighter (DF1) == notFighting || getVertMoveDFighter(DF1) == Jumping) { // si no pelea se mueve o si está saltando
   
      if (getVertMoveDFighter(DF1) != Crowched) { // Si no está agachado, se mueve.
         switch (getHorMoveDFighter (DF1)) {
         case movingRight:
         
            // NUEVO !!! -------------------------------------------------------------------------------------------
            // Funca bien aunque está medio trancado, se tendría que hacer un movimiento relativo al tiempo que pasa
            // ya que si pasa todo el intervalo se mueve una unidad de velocidad, si pasa medio intervalo que se
            /// mueva la mitad de la unidad de velocidad, sino tiene que esperar hasta el próximo bucle para poder
            // moverse. Por lo tanto no es tan importante si pasa el intervalo, sino cuanto del intervalo pasa. !!!
            
            if (getHorTimeDFighter(DF1) < SDL_GetTicks()) { // Movimiento por tiempo para evitar movimiento rápido en máquinas rápidas.
               setXDFighter (DF1, getXDFighter(DF1) + getSpdSFighter(SF1));
               if (getXDFighter(DF1) + getWidthRect(getBodySFighter(SF1)) > screen->w) {
                  setXDFighter(DF1, screen->w - getWidthRect(getBodySFighter(SF1))); // Pone al tipo contra el borde derecho.
               }

               setHorTimeDFighter (DF1, SDL_GetTicks() + hor_mov_act_time); // Tiempo para el movimiento horizontal.
            }
            // NUEVO !!! -------------------------------------------------------------------------------------------
            
         break;
         case movingLeft:
            if (getHorTimeDFighter(DF1) < SDL_GetTicks()) {
               setXDFighter (DF1, getXDFighter(DF1) - getSpdSFighter(SF1));
               if (getXDFighter(DF1) < 0) {
                  setXDFighter (DF1, 0); // pone al tipo contra el borde izquierdo.
               }
               setHorTimeDFighter (DF1, SDL_GetTicks() + hor_mov_act_time);
            }
         break;
         } /// switch mov. hor.
      } /// si no está agachado.
      
   }

// Plyer 2
/// Ver por salto.
   if (getVertMoveDFighter (DF2) == Jumping) {

      setJTime2DFighter (DF2, SDL_GetTicks()); /// Setea tiempo actual del salto.
      int y_Salto2 = getYJDFighter (DF2); /// pide y actual del salto.

      if (y_Salto2 <= 0) { // Si está saltando.
         setYDFighter (DF2, stageFloor - getHeightRect(getBodySFighter(SF2)) + y_Salto2);
      } else { // Se termina el salto.
      
      if ( keystate[getKeyInputPlayer(IP2,actionDOWN)] ) {// si está apretada la tecla abajo del P1
            setStatDFighter(DF2, notFighting); // termina golpe del aire. (*)
            setBodySFighter (SF2, Crowched);
            setVertMoveDFighter (DF2, Crowched);
         } else {
            setStatDFighter(DF2, notFighting); // termina golpe del aire. (*)
            setBodySFighter (SF2, Standing);
            setVertMoveDFighter (DF2, Standing);
         }
         setYDFighter (DF2, stageFloor - getHeightRect(getBodySFighter(SF2)) );
      }

   } /// if salta p2
   
   
   /// Movimiento horizontal.
   if (getStatDFighter (DF2) == notFighting || getVertMoveDFighter(DF2) == Jumping) { // si no pelea se mueve o si está saltando
   //cerr << "se MUEVE ---------------------------------" << endl;
      if (getVertMoveDFighter(DF2) != Crowched) { // Si no está agachado, se mueve.
      
         switch (getHorMoveDFighter (DF2)) {
         case movingRight:
            if (getHorTimeDFighter(DF2) < SDL_GetTicks()) {
               setXDFighter (DF2, getXDFighter(DF2) + getSpdSFighter(SF2));
               if (getXDFighter(DF2) + getWidthRect(getBodySFighter(SF2)) > screen->w) {
                  setXDFighter(DF2, screen->w - getWidthRect(getBodySFighter(SF2))); // Pone al tipo contra el borde derecho.
               }
               setHorTimeDFighter (DF2, SDL_GetTicks() + hor_mov_act_time);
            }
         break;
         case movingLeft:
            if (getHorTimeDFighter(DF2) < SDL_GetTicks()) {
               setXDFighter (DF2, getXDFighter(DF2) - getSpdSFighter(SF2));
               if (getXDFighter(DF2) < 0) {
                  setXDFighter (DF2, 0); // pone al tipo contra el borde izquierdo.
               }
            setHorTimeDFighter (DF2, SDL_GetTicks() + hor_mov_act_time);
            }
         break;
         } /// switch mov. hor.
         
      } /// si no está agachado
   } // si no está peleando.
   
//********************************************************************************************
// Movimiento.
//***************************************************

//***************************************************
// Colision
//******************************************************************************************** 
// Chek colisiones. (Si P1 y P2 se cortan, chocan, intersectan, etc, etc.)

   // Si se chocan los cuerpos, se deshace el movimiento //
   if (RRRelColision(getBodySFighter(SF1), getXDFighter(DF1), getYDFighter(DF1), getBodySFighter(SF2), getXDFighter(DF2), getYDFighter(DF2))) {

      switch (getHorMoveDFighter (DF1)) { // Si el P1 se movió, que desahga el movimiento.
      case movingRight:
         setXDFighter(DF1, getXDFighter(DF1) - getSpdSFighter(SF1));
      break;
      case movingLeft:
         setXDFighter(DF1, getXDFighter(DF1) + getSpdSFighter(SF1));
      break;
      } // switch hor mov p1

      switch (getHorMoveDFighter (DF2)) { // Si el P2 se movió, que desahga el movimiento.
      case movingRight:
         setXDFighter(DF2, getXDFighter(DF2) - getSpdSFighter(SF2));
      break;
      case movingLeft:
         setXDFighter(DF2, getXDFighter(DF2) + getSpdSFighter(SF2));
      break;
      } // switch hor mov p2
   
   
   //***************************************************
   // Cuando uno cae encima del otro.
   //********************************************************************************************
   
      // Ver si el luchador 2 cae sobre el 1
      if (getVertMoveDFighter(DF2) == Jumping && getVertMoveDFighter(DF1) != Jumping) {
          
            
         int x1 = getXDFighter(DF1);                        // x del luchador 1
         int x1w = x1 + getWidthRect(getBodySFighter(SF1)); // x + width del luchador 1
         int x2 = getXDFighter(DF2);                        // x del luchador 2
         int x2w = x2 + getWidthRect(getBodySFighter(SF2)); // x + width del luchador 2


         if ( (x1<=x2 && x2<=x1w) && x2w >= x1w ) { // x2 adentro y x2w no.
         
            setXDFighter (DF1, getXDFighter(DF2) - getWidthRect(getBodySFighter(SF1))); // mueve 1 izq.
            
         } else if ( x2<=x1 && (x1<=x2w && x2w<=x1w)) { // x2w adentro y x2 no.
         
            setXDFighter (DF1, getXDFighter(DF2) + getWidthRect(getBodySFighter(SF2))); // mueve 1 der.
            
         } else if ( (x1<=x2 && x2<=x1w) && (x1<=x2w && x2w<=x1w)) { // Si P2 está todo dentro de P1 porque P1 es mas ancho
         
            if ( abs(x2-x1) > abs(x2w-x1w) ) { /// si ac > bd
               setXDFighter (DF1, getXDFighter(DF2) - getWidthRect(getBodySFighter(SF1))); /// mueve izq
            } else {
               setXDFighter (DF1, getXDFighter(DF2) + getWidthRect(getBodySFighter(SF2))); /// mueve der
            }
            
         } else if ( (x2<=x1 && x1<=x2w) && (x2<=x1w && x1w<=x2w) ) { // OBS si x2 < x1 => x2 < x1w CAMBIAR!
         // Si P1 está todo dentro de P2 porque P2 es más ancho:
             
            if ( abs(x2-x1) > abs(x2w-x1w) ) { /// si ac > bd
               setXDFighter (DF1, getXDFighter(DF2) + getWidthRect(getBodySFighter(SF2))); /// mueve der
            } else {
               setXDFighter (DF1, getXDFighter(DF2) - getWidthRect(getBodySFighter(SF1))); /// mueve izq
            }
            
         }
         
         // =========================================================================== //
         // =========================================================================== //
         // SI P2 cayó sobre P1 y lo sacó de la pantalla, P1 debe entrar a la pantalla  //
         // y P2 correrse para atrás, para que cuando entre P1 no se superpongan        //
         // =========================================================================== //
         // =========================================================================== //
         
         // Se movieron => actualiza variables
         x1 = getXDFighter(DF1);                        // x del luchador 1
         x1w = x1 + getWidthRect(getBodySFighter(SF1));
         x2 = getXDFighter(DF2);                        // x del luchador 2
         x2w = x2 + getWidthRect(getBodySFighter(SF2)); // x + width del luchador 2

         if ( screen->w < x1w ) {                       // Si P1 se fue por la derecha                        //
         
            int diferencia = x1w - screen->w;           // Cuanto se fue para afuera, se podría poner algo de margen //
            
            setXDFighter (DF1, x1 - diferencia);        // mueve izq, P1 para adentro de la pantalla //
            setXDFighter (DF2, x2 - diferencia);        // mueve izq, P2 para que no corte a P1, si no aprarece uno superpuesto al otro  //
            
         } else if ( x1 < 0 ) {                         // Si P1 se fue por la izquierda
         
            int diferencia = -x1;                       // Cuanto se fue para afuera, se podría poner algo de margen //
            
            setXDFighter (DF1, x1 + diferencia);        // mueve izq, P1 para adentro de la pantalla //
            setXDFighter (DF2, x2 + diferencia);        // mueve izq, P2 para que no corte a P1, si no aprarece uno superpuesto al otro //
         
         }    
         
         // =========================================================================== //
         // =========================================================================== //
         // =========================================================================== //
         // =========================================================================== //
         
         
         
      // Ver si el luchador 1 cae sobre el 2
      } else if (getVertMoveDFighter(DF1) == Jumping && getVertMoveDFighter(DF2) != Jumping) {
          
          
         int x1 = getXDFighter(DF1);                        // x del luchador 1
         int x1w = x1 + getWidthRect(getBodySFighter(SF1)); // x + width del luchador 1
         int x2 = getXDFighter(DF2);                        // x del luchador 2
         int x2w = x2 + getWidthRect(getBodySFighter(SF2)); // x + width del luchador 2


         if ( (x2<=x1 && x1<=x2w) && x1w>=x2w ) { // a adentro y b no.
         
            setXDFighter (DF2, getXDFighter(DF1) - getWidthRect(getBodySFighter(SF2))); // mueve 2 izq.
            
         } else if ( x1<=x2 && (x2<=x1w && x1w<=x2w)) { // b adentro y a no.
         
            setXDFighter (DF2, getXDFighter(DF1) + getWidthRect(getBodySFighter(SF1))); // mueve 2 der.
            
         } else if ( (x2<=x1 && x1<=x2w) && (x2<=x1w && x1w<=x2w)) { // a adentro y b también.
         
            if ( abs(x1-x2) > abs(x1w-x2w) ) { /// si ac > bd
               setXDFighter (DF2, getXDFighter(DF1) - getWidthRect(getBodySFighter(SF2))); /// mueve izq
            } else {
               setXDFighter (DF2, getXDFighter(DF1) + getWidthRect(getBodySFighter(SF1))); /// mueve der
            }
            
         } else if ( (x1<=x2 && x2<=x1w) && (x1<=x2w && x2w<=x1w) ) {
             
            if ( abs(x1-x2) > abs(x1w-x2w) ) { /// si ac > bd
               setXDFighter (DF2, getXDFighter(DF1) + getWidthRect(getBodySFighter(SF1))); /// mueve der
            } else {
               setXDFighter (DF2, getXDFighter(DF1) - getWidthRect(getBodySFighter(SF2))); /// mueve izq
            }
            
         }
         
         // =========================================================================== //
         // =========================================================================== //
         // SI P1 cayó sobre P2 y lo sacó de la pantalla, P2 debe entrar a la pantalla  //
         // y P1 correrse para atrás, para que cuando entre P2 no se superpongan        //
         // =========================================================================== //
         // =========================================================================== //
         
         // Se movieron => actualiza variables
         x1 = getXDFighter(DF1);                        // x del luchador 1
         x1w = x1 + getWidthRect(getBodySFighter(SF1));
         x2 = getXDFighter(DF2);                        // x del luchador 2
         x2w = x2 + getWidthRect(getBodySFighter(SF2)); // x + width del luchador 2

         if ( screen->w < x2w ) {                       // Si P2 se fue por la derecha                        //
         
            int diferencia = x2w - screen->w;           // Cuanto se fue para afuera, se podría poner algo de margen //
            
            setXDFighter (DF1, x1 - diferencia);        // mueve izq, P1 para que no corte a P1, si no aprarece uno superpuesto al otro  //
            setXDFighter (DF2, x2 - diferencia);        // mueve izq, P2 para adentro de la pantalla //
            
         } else if ( x2 < 0 ) {                         // Si P2 se fue por la izquierda
         
            int diferencia = -x2;                       // Cuanto se fue para afuera, se podría poner algo de margen //
            
            setXDFighter (DF1, x1 + diferencia);        // mueve izq, P1 para que no corte a P1, si no aprarece uno superpuesto al otro //
            setXDFighter (DF2, x2 + diferencia);        // mueve izq, P2 para adentro de la pantalla //
         
         }
         // =========================================================================== //
         // =========================================================================== //
         // =========================================================================== //
         // =========================================================================== //
         
      }
      
   // VER  ABAJO DEL TODO, hay un buggie. (/***/)
   //********************************************************************************************
   // Cuando uno cae encima del otro
   //***************************************************  
   
   
   } // Si hay colision entre los cuerpos.
//********************************************************************************************
// Colision.
//*************************************************** 

//***************************************************
// Chekeo para intersecciones de "golpeando"
//********************************************************************************************

//---------------------------------------------------------------------------------------------

   int fight_meter = 0;
   // 0 si ningubno pega
   // 1 solo el player 1 pega
   // 2 solo player 2 pega
   // 3 los 2 players pegan

   if (getStatDFighter (DF1) == punching || getStatDFighter (DF1) == kicking) { // Si el luchador 1 está pegando //

      if (getHitTimeDFighter (DF1) <= SDL_GetTicks()) {                         // Si terminó de golpear.
         setStatDFighter (DF1, notFighting);
         
                                                                                // Si cuando termina de golpear está apretando
                                                                                // para izquierda o derecha, que se mueva.
      
         if ( keystate[getKeyInputPlayer(IP1,actionLEFT)] ) {
            setHorMoveDFighter(DF1, movingLeft);
         } else if ( keystate[getKeyInputPlayer(IP1,actionRIGHT)] ) {
            setHorMoveDFighter(DF1, movingRight);
         }
         
      } else {                                                                  // caso Si sigue pegando.

         if (getStatDFighter(DF2) != beingHited) {                              // Si el luchador 2 no está siendo golpeado, puede ser golpeado.
      
            //genRect golpe = getGRectHit(getHitSFighter(SF1,getIdHitDFighter(DF1)), idCombination (DF1));
            
            // Si el luchador 1 le pega al luchador 2
            if (RGRRelColision (getBodySFighter(SF2), getXDFighter(DF2), getYDFighter(DF2), getGRectHit(getHitSFighter(SF1,getIdHitDFighter(DF1)), idCombination (DF1)), getXDFighter(DF1), getYDFighter(DF1))) {
               
               // no cambia el estatus porque falta chekear si p2 le pega a p1.
               fight_meter++; // vale 1 si p1 le pega a p2.
               
               // La duracion de el "siendo golpeado" es igual a la duración del golpe recibido!
               setOuchTimeDFighter (DF2, SDL_GetTicks() + getDurationHit(getHitSFighter(SF1, getIdHitDFighter(DF1))));
               
               
               // Acá se chekea cuando el luchador pierde, se muere, etc. (si la energía llega a 0 o menos.)
               float dmg = getDmgHit(getHitSFighter(SF1, getIdHitDFighter(DF1)));
               setEnergyDFighter (DF2, getEnergyDFighter(DF2) - dmg);
               
               
               // Acción física sobre el luchador que recibe el golpe, se puede mejorar!.
               if (getOrientationDFighter(DF2) == lookingRight) {    // Si el luchador 2 mira a la derecha
                   setXDFighter(DF2, getXDFighter(DF2) - int(dmg));  // el golpe lo corre hacia la izquierda
               } else {                                              // Si no
                   setXDFighter(DF2, getXDFighter(DF2) + int(dmg));  // Lo corre a la derecha
               }
               
               // Al final se puede chekear todo, y ver si el tipo está dentro de la pantalla !!!! //
               // Luego de ser corrido hay que fijarse que no se halla ido de la pantalla
               // Si el luchador 1 le pega al 2, y el 2 se va de la pantalla, corre al 2
               // dentro de la pantalla, y corre al 1 para atrás lo que correría al 2 ese golpe
                  
                  
            } // si hay colision.

         } // si p2 puede ser golpeado.

      } // si P1 sigue pegando
   } // si P1 pegando
   
   if (getStatDFighter (DF2) == punching || getStatDFighter (DF2) == kicking) {
   
      if (getHitTimeDFighter (DF2) <= SDL_GetTicks()) { // terminó de golpear.
         setStatDFighter (DF2, notFighting);
      // Si cuando termina de golpear está apretando para izquierda o derecha, que se mueva.
         if ( keystate[getKeyInputPlayer(IP2,actionLEFT)] ) {
            setHorMoveDFighter(DF2, movingLeft);
         } else if ( keystate[getKeyInputPlayer(IP2,actionRIGHT)] ) {
            setHorMoveDFighter(DF2, movingRight);
         }   
      } else { // caso Si sigue pegando.
      
         if (getStatDFighter(DF1) != beingHited) { // si no está siendo golpeado, puede ser golpeado.
      
            //genRect golpe = getGRectHit(getHitSFighter(SF1,getIdHitDFighter(DF1)), idCombination (DF1));
            // Si hay colisión entre el golpe y el luchador del player 2.
            if (RGRRelColision (getBodySFighter(SF1), getXDFighter(DF1), getYDFighter(DF1), getGRectHit(getHitSFighter(SF2,getIdHitDFighter(DF2)), idCombination (DF2)), getXDFighter(DF2), getYDFighter(DF2))) {
               
               // no cambia el estatus porque falta chekear si p1 le pegó a p2.
               fight_meter += 2; // vale 2 si p1 no le pegó a p2 ó 3 si p1 le pegó.
               
               // La duracion de el "siendo golpeado" es igual a la duración del golpe recibido!
               setOuchTimeDFighter (DF1, SDL_GetTicks() + getDurationHit(getHitSFighter(SF2, getIdHitDFighter(DF2))));
               
               // Acá se chekea cuando el luchador pierde, se muere, etc. (si la energía llega a 0 o menos.)
               float dmg = getDmgHit(getHitSFighter(SF2, getIdHitDFighter(DF2)));
               setEnergyDFighter (DF1, getEnergyDFighter(DF1) - dmg);
               
               // Acción física sobre el luchador que recibe el golpe, se puede mejorar!.
               if (getOrientationDFighter(DF1) == lookingRight) {setXDFighter(DF1, getXDFighter(DF1) - int(dmg));
               } else {setXDFighter(DF1, getXDFighter(DF1) + int(dmg));}
                  
            } // si hay colision.

         } // si p2 puede ser golpeado.

      } // si P1 sigue pegando
   } // si P1 pegando
   
   //cout << "caso: " << fight_meter << endl;
   switch (fight_meter) {
   case 0: // si ninguno pega
   break;
   case 1: // si p1 le pegó a p2
      setStatDFighter(DF2, beingHited);
   break;
   case 2: // si p2 le pegó a p1
      setStatDFighter(DF1, beingHited);
   break;
   case 3: // si ambos se pegaron
      setStatDFighter(DF1, beingHited);
      setStatDFighter(DF2, beingHited);
   break;
   }

//---------------------------------------------------------------------------------------------

//********************************************************************************************
// Chekeo para intersecciones de "golpeando"
//***************************************************
//***************************************************
// Orientación de luchadores.
//********************************************************************************************

   // Chekeo de orientacion, un jugador que está pegando o saltando no se da vuelta hasta llegar al piso.
   if (getXDFighter(DF1) > getXDFighter (DF2)) {
   // El player1 mira a la izquierda y el 2 a la derecha (si no están saltando o pegando.)
      if (getVertMoveDFighter(DF1) != Jumping && getStatDFighter(DF1) == notFighting) {
         setOrientationDFighter (DF1, lookingLeft);
      }
      if (getVertMoveDFighter (DF2) != Jumping && getStatDFighter (DF2) == notFighting) {
         setOrientationDFighter (DF2, lookingRight);
      }
   } else {
      if (getVertMoveDFighter(DF1) != Jumping && getStatDFighter(DF1) == notFighting) {
         setOrientationDFighter(DF1, lookingRight);
      }
      if (getVertMoveDFighter(DF2) != Jumping && getStatDFighter(DF2) == notFighting) {
         setOrientationDFighter (DF2, lookingLeft);
      }
   }
   
//********************************************************************************************
// Orientación de luchadores.
//***************************************************   

// (/***/)
// HAY UN BUGGIE CUANDO UNO CAE ARRIBA DEL OTRO Y ESTÁ EN EL BORDE DE LA PANTALLA, EL dE ABAJO SE VA DE LA PANTALLA,
// este se tendría que quedar quieto y el otro resvalarse por arriba para que no se intersecten.

// TAM BIEN CUANDO LE PEGA Y ESTÄ CONTRA EL BORDE, EL GOLPEADO SE VA DE LA PANTALLA.

   int x1 = getXDFighter(DF1);                        // x del luchador 1
   int x1w = x1 + getWidthRect(getBodySFighter(SF1)); // x + width del luchador 1
   int x2 = getXDFighter(DF2);                        // x del luchador 2
   int x2w = x2 + getWidthRect(getBodySFighter(SF2)); // x + width del luchador 2

   // Si al final hay algún tipo de intersección
   if (RRRelColision(getBodySFighter(SF1), x1, getYDFighter(DF1), getBodySFighter(SF2), x2, getYDFighter(DF2))) {

      // Hay que ver "cuanto" están intersectados //
      
      // Si el P1 está a la izquerda del P2
      if ( x1 < x2 ) {
      
         int diferencia = x1w - x2; // Lo que P1 está dentro de P2, el lado derecho de P1 está dentro del izq de P2
                                 // deja 1 de margen
         setXDFighter( DF1, x1 - (diferencia+1/2) ); // Corre a P1 a la izq la mitad de la intersección
         setXDFighter( DF2, x2 + (diferencia+1/2) ); // Corre a P2 a la der la mitad de la intersección
         
      } else { // Si P2 está a la izquierda de P1
      
         int diferencia = x2w - x1; // Lo que P1 está dentro de P2, el lado derecho de P1 está dentro del izq de P2
                                 // deja 1 de margen
         setXDFighter( DF1, x1 + (diferencia+1/2) );
         setXDFighter( DF2, x2 - (diferencia+1/2) );
         
      }    
             
   }  

/*
   int x1 = getXDFighter(DF1);                        // x del luchador 1
   int x1w = x1 + getWidthRect(getBodySFighter(SF1)); // x + width del luchador 1
   int x2 = getXDFighter(DF2);                        // x del luchador 2
   int x2w = x2 + getWidthRect(getBodySFighter(SF2)); // x + width del luchador 2
   
   // Si el luchador 1 se fue a la derecha //
   if ( x1w > screen->w ) {
    
       int diferencia = x1w - screen->w;    // Cuanto es lo que el luchador está paar afuera //
       setXDFighter(DF1, x1 - (diferencia+1)); // Lo pone dentro de la pantalla, deja 1 de margen! //    
       
       // Ahora hay que ver si el luchador 1, que fue corrido para adentro de la pantalla, no esté sobre el otro //
       // Si se chocan los cuerpos, se deshace el movimiento //
       //if (RRRelColision(getBodySFighter(SF1), x1, getYDFighter(DF1), getBodySFighter(SF2), x2, getYDFighter(DF2))) {
           
          if (getStatDFighter (DF2) == punching || getStatDFighter (DF2) == kicking) { // Si es que P1 se fue xq 2 le pegaba, P2 se corre lo que se correría P1 por causa del golpe 
          
             float dmg = getDmgHit(getHitSFighter(SF2, getIdHitDFighter(DF2)));
             setXDFighter(DF2, getXDFighter(DF2) - int(dmg));
          }    
          //setXDFighter(DF2, x2 - diferencia); // Corre al jugador 2 para atrás lo mismo que se corrió el 1 para adentro de la pantalla
       //}    
         
   }    
   */
   //setXDFighter(DF1, getXDFighter(DF1) + int(dmg));


   // Luego de ser corrido hay que fijarse que no se halla ido de la pantalla
   // Si el luchador 1 le pega al 2, y el 2 se va de la pantalla, corre al 2
   // dentro de la pantalla, y corre al 1 para atrás lo que correría al 2 ese golpe
                  

} // move stuff



void drawOptions ( SDL_Surface *screen, int selKey, bool changeKey ) {  // Dibujar Opciones //

// selKey tiene en número de tecla que está seleccionada en configurar teclado
// changeKey es true si la tecla está actiavada para ser cambiada


// Se van a dibujar 2 columnas de teclas
// En la primer columna se ponen las teclas del jugador 1, en la segunda del 2.
#define X_COL1 50
#define X_COL2 150

// Desde donde se empiezan a dibujar las cosas
#define Y_TOP 100


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
 
 
   SFont_Write ( screen, Arial, X_COL1, Y_TOP, "Jugador 1");
   SFont_Write ( screen, Arial, X_COL2, Y_TOP, "Jugador 2");
   
   SFont_Write ( screen, Arial, X_COL1, Y_TOP, "Jugador 1");
   SFont_Write ( screen, Arial, X_COL2, Y_TOP, "Jugador 2");
   
   switch ( selKey ) { // ver que tecla está seleccionada //
   
   case P1_UP:
   break;
   case P1_DOWN:
   break;
   case P1_LEFT:
   break;
   case P1_RIGHT:
   break;
   case P1_PUNCH:
   break;
   case P1_KICK:
   break;
   
   case P2_UP:
   break;
   case P2_DOWN:
   break;
   case P2_LEFT:
   break;
   case P2_RIGHT:
   break;
   case P2_PUNCH:
   break;
   case P2_KICK:
   break;
   
   }

   SDL_Flip (screen); // Cambia Buffers!

} // Dibujar menu principal //


