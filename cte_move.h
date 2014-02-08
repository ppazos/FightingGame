#ifndef _cte_move_h
#define _cte_move_h

#define hor_mov_act_time 20 // Tiempo en el que se actualiza el movimiento horizontal. (en mili-segundos)

// Movimiento Vertical.
#define Standing 6 // Identificador de que el luchador está parado. (Se puede estar moviendo o no)
#define Crowched 1 // Identificador de que el luchador está agachado.
#define Jumping 0 // Identificador de que el luchador está saltando.

// Movimiento Horizontal.
#define movingNone 7 // Id. de que no se está moviendo. (Puede estar saltando o agachado, etc)
#define movingLeft 2 // Id. de que se está moviendo a la izquierda.
#define movingRight 3 // Id. de que se está moviendo a la derecha.

// Identificadores de orientación de luchadores (hacia donde miran).
#define lookingRight 0 // Id. de que está mirandi hacia la derecha.
#define lookingLeft 1 // Id. de que está mirando a la izquierda.

// Pelea.
#define punching 4 // Pegando.
#define kicking 5
#define beingHited 8 // Siendo golpeado.
#define notFighting 9 // Ni pegando ni siendo golpeado.

/* Oservar: los ids
/* jumping (arriba) 0
/* crowched (abajo) 1
/* movingleft (izq) 2
/* movingright (der) 3
/* punch 4
/* kick 5
/* tienen que ser seguidos, e iguales a las teclas del archivo input.
   (igual que las acciones de cte_game.h)
/****************************/

#endif
