#ifndef _game_ops_h
#define _game_ops_h

#include "vector_fighter.h"
#include "player.h"
#include "SDL.h"

int idCombination (d_fighter DF);

int chekInput (SDL_Event event, player Player1, player Player2, vectorFighter VF, SDL_Surface * screen);
/// tira 1 cuando el boton es esc (que salga del programa)

void moveStuff (player Player1, player Player2, vectorFighter VF, SDL_Surface * screen);

int inputMainMenu ( SDL_Event event, int actualButton, int & activeButton, int & optionSelected );
// Chekea input en estado Main Menu

#endif
