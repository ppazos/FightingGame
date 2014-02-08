#ifndef _colision_h
#define _colision_h

#include "rectangle.h"
#include "gen_rectangle.h"

/// Todas las operaciones dan true en el caso de que los objetos se corten.

/// En posición absoluta.
bool RRColision (rect R1, rect R2); /// Colision entre 2 rects.
bool GRGRColision (genRect GR1, genRect GR2); /// Colison entre 2 genRects.
bool RGRColision (rect R, genRect GR); /// Colision entre un rect y un genRect.

/// En posición relativa.
bool RRRelColision (rect R1, int xR1, int yR1, rect R2, int xR2, int yR2); /// Colision entre 2 rects.
bool GRGRRelColision (genRect GR1, int xGR1, int yGR1, genRect GR2, int xGR2, int yGR2); /// Colison entre 2 genRects.
bool RGRRelColision (rect R, int xR, int yR, genRect GR, int xGR, int yGR); /// Colision entre un rect y un genRect.

#endif
