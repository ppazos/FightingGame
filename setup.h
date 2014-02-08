#ifndef _setup_h
#define _setup_h

#include "input_player.h"
#include "vector_fighter.h"

inputP loadInput (char * File);
vectorFighter loadFighters (char * File);

int getSDLKbyName (char * name);

#endif
