#ifndef _input_player_h
#define _input_player_h

//#include "cte_game.h"

typedef struct _inputP {
   //char * vector; /// Solo para guardar los nombres de las teclas.
   int * vector; // guarda las teclas.
   int size;
} * inputP; /// Es un puntero a un array de chars.

inputP newInputPlayer (unsigned short numKeys);
/// Crea un array de tama�o numKeys.

//void addKeyInputPlayer (inputP & IP, char keyName, unsigned short action);
void addKeyInputPlayer (inputP & IP, int key, int index);
/// Agrega el nombre de una tecla al vector, action es la acci�n de esa tecla, cada acci�n tiene su lugar en el vector.
/// Acciones arriba, abajo, pi�a1, ptada2, etc., las constantes van a ser definidas en cte_game.h

int getKeyInputPlayer (inputP IP, int index);
//char getKeyInputPlayer (inputP IP, unsigned short action);
/// Devuelve el nombre de la tecla especificada por la acci�n.


void destroyInputPlayer (inputP & IP);
/// Libera memoria.

#endif
