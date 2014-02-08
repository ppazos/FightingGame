#ifndef _player_h
#define _player_h

#include "vector_fighter.h"
#include "input_player.h"

typedef struct _player {

   unsigned short fighterId; /// Id del luchador que está usando el jugador.
   inputP keys; /// Controles con teclado del luchador.
   
   /// Aquí pueden haber varias cosas: score, nombre, nivel alcanzado, peleas ganadas, etc, etc.
   /// Todas las cosas del jugador.

} * player;


player newPlayer (inputP keys);
/// Crea un Jugador con los datos especificados, todo viene creado desde afuera.
/// Al principio no tiene un luchador asociado, tiene que elegirlo primero.

void setFighterPlayer (player & P, unsigned short fighterId);
/// Asocia un luchador al jugador.

unsigned short getFighterPlayer (player P);
/// Devuelve el id del luchador asociado al jugador P.

char getKeyPlayer (player P, unsigned short action);
/// Devuelve el nombre de la tecla asociada a la acción.
/// No hay set, las teclas se pueden cambiar con las operaciones de abajo.


inputP getKeysPlayer (player P);
/// Devuelve todo el vector de teclas del jugador, puede servir para cambiar teclas.
/// Ojo, si se retorna directamente el input, los cambios afectarán a las teclas del jugador.
/// Y si se retorna una copia, para que los cambios tengan efecto, debe hacerse el setKeysPlayer.

void setKeysPlayer (player & P, inputP keys);
/// El nuevo input debe estar desvinculado del viejo (no compartir memoria), ya que antes de
/// asignar el nuevo input se borrará el viejo.


void destroyPlayer (player & P);

#endif
