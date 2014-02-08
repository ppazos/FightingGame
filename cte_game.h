#ifndef _cte_game_h
#define _cte_game_h

#define stageFloor 320
// Coordenada Y que indica a que altura se encuentra el piso (es donde están parados los luchadores.)
// Sirve para saber cuando terminan de saltar los luchadores.

// Posiciones iniciales de los luchadores.
#define P1startX 100
#define P2startX 350

#define FullEnergy 100.0 // Energía con la que comienzan a luchar los tipos
                         // Obs: en el archivo de luchadores, los luchadores tienen
                         // una energía asignada, la idea es que todos comienecen con
                         // la misma energía, entonces que quede como cte aquí y no en el archivo.

/// Posibles acciones dentro del juego. (para saber teclas definidas)
/// Los valores van a ser los índices de las teclas en el input_player.
#define actionUP 0
#define actionDOWN 1
#define actionLEFT 2
#define actionRIGHT 3
#define actionPUNCH 4
#define actionKICK 5

/// Nombres de archivos.
#define FileFighters "fighters.txt"
#define FileInputP1 "p1input.txt"
#define FileInputP2 "p2input.txt"


// Todas las teclas
#define P1_UP     0
#define P1_DOWN   1
#define P1_LEFT   2
#define P1_RIGHT  3
#define P1_PUNCH  4
#define P1_KICK   5

#define P2_UP     6
#define P2_DOWN   7
#define P2_LEFT   8
#define P2_RIGHT  9
#define P2_PUNCH  10
#define P2_KICK   11


// Identificadores de estados del juego
#define GAME_STAT_MAIN_MENU 0       // Juego en menu principal
#define GAME_STAT_SELECT_FIGHTER 1  // Juego en elección de luchador
#define GAME_STAT_FIGHT 2           // Juego en la pelea

#define MAIN_MENU_IMG_COUNT 6       // Cantidad de imágenes que se usan en el menu principal //
#define MAIN_MENU_BUTTON_COUNT 3    // 3 botones, 6 graficos (por ahora)

// DEntro del menu principal, los estados son la selección de botones.
#define MAIN_MENU_BUTTON1 0
#define MAIN_MENU_BUTTON2 1
#define MAIN_MENU_BUTTON3 2

// Identificadores de las imágenes del menu principal
#define B1_IMG_NORMAL 0
#define B2_IMG_NORMAL 1
#define B3_IMG_NORMAL 2
#define B1_IMG_SELECTED 3
#define B2_IMG_SELECTED 4
#define B3_IMG_SELECTED 5
#define TITLE_IMG 6 // Por ahora no se usa, no hay logo ni nada... hay que hacer!

// =========== //

/// Para las imágenes
#define parado_izq 0
#define parado_der 1
#define saltando_izq 2
#define saltando_der 3
#define agachado_izq 4
#define agachado_der 5
#define jump_punch_izq 6
#define jump_punch_der 7
#define jump_kick_izq 8
#define jump_kick_der 9
#define crowch_punch_izq 10
#define crowch_punch_der 11
#define crowch_kick_izq 12
#define crowch_kick_der 13
#define stand_punch_izq 14
#define stand_punch_der 15
#define stand_kick_izq 16
#define stand_kick_der 17
#define j_hited_izq 18
#define j_hited_der 19
#define s_hited_izq 20
#define s_hited_der 21

#endif
