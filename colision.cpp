#include <iostream>
#include "colision.h"

using namespace std;

/// Todas las operaciones dan true en el caso de que los objetos se corten.

/* Operaciones en posición absoluta. */

bool RRColision (rect R1, rect R2) { /// Colision entre 2 rects.
   if (!(R1->y + R1->h <= R2->y) && !(R1->x + R1->w <= R2->x) &&
       !(R2->y + R2->h <= R1->y) && !(R2->x + R2->w <= R1->x)) {
      return true;
   } else {
      return false;
   }
}


/// Necesario para GRGRCol.
bool puntoSemiplanoGenRect (genRect GR, int semiplano, int x, int y) {
/* true si el punto x,y está en el semiplano determinado por la recta
#semiplano que no tenga al rectángulo. */

   float m = getMGenRect (GR);
   int x1; int y1;   int x2; int y2;   int x3; int y3;   int x4; int y4;
   getVertexGenRect (GR, x1, y1, x2, y2, x3, y3, x4, y4);

   switch (semiplano) {
   case 1:
          return (y - y1 - (x - x1)*m > 0);
   break;
   case 2:
          if (m >= 0) {
             return (y - y2 + (x - x2)/m > 0);
          } else {
             return (y - y2 + (x - x2)/m < 0);
          }
   break;
   case 3:
          return (y - y3 - (x - x3)*m < 0);
   break;
   case 4:
          if (m >= 0) {
             return (y - y1 + (x - x1)/m < 0);
          } else {
             return (y - y1 + (x - x1)/m > 0);
          }
   break;
   default:
      cout << "Error en puntoEnSemiplano() Módulo: colision\n";
   break;
   }
}

bool GRGRColision (genRect GR1, genRect GR2) { /// Colison entre 2 genRects.

   bool colision = false;

   int x1; int y1; int x2; int y2; int x3; int y3; int x4; int y4;
   getVertexGenRect (GR1, x1, y1, x2, y2, x3, y3, x4, y4);

   int x12; int y12; int x22; int y22; int x32; int y32; int x42; int y42;
   getVertexGenRect (GR2, x12, y12, x22, y22, x32, y32, x42, y42);
   
   if ((
      (puntoSemiplanoGenRect (GR1, 1, x12, y12) && puntoSemiplanoGenRect (GR1, 1, x22, y22) &&
        puntoSemiplanoGenRect (GR1, 1, x32, y32) && puntoSemiplanoGenRect (GR1, 1, x42, y42)) ||
      (puntoSemiplanoGenRect (GR1, 2, x12, y12) && puntoSemiplanoGenRect (GR1, 2, x22, y22) &&
        puntoSemiplanoGenRect (GR1, 2, x32, y32) && puntoSemiplanoGenRect (GR1, 2, x42, y42)) ||
      (puntoSemiplanoGenRect (GR1, 3, x12, y12) && puntoSemiplanoGenRect (GR1, 3, x22, y22) &&
        puntoSemiplanoGenRect (GR1, 3, x32, y32) && puntoSemiplanoGenRect (GR1, 3, x42, y42)) ||
      (puntoSemiplanoGenRect (GR1, 4, x12, y12) && puntoSemiplanoGenRect (GR1, 4, x22, y22) &&
        puntoSemiplanoGenRect (GR1, 4, x32, y32) && puntoSemiplanoGenRect (GR1, 4, x42, y42))
      )
     ||
     (
     (puntoSemiplanoGenRect (GR2, 1, x1, y1) && puntoSemiplanoGenRect (GR2, 1, x2, y2) &&
       puntoSemiplanoGenRect (GR2, 1, x3, y3) && puntoSemiplanoGenRect (GR2, 1, x4, y4)) ||
     (puntoSemiplanoGenRect (GR2, 2, x1, y1) && puntoSemiplanoGenRect (GR2, 2, x2, y2) &&
       puntoSemiplanoGenRect (GR2, 2, x3, y3) && puntoSemiplanoGenRect (GR2, 2, x4, y4)) ||
     (puntoSemiplanoGenRect (GR2, 3, x1, y1) && puntoSemiplanoGenRect (GR2, 3, x2, y2) &&
       puntoSemiplanoGenRect (GR2, 3, x3, y3) && puntoSemiplanoGenRect (GR2, 3, x4, y4)) ||
     (puntoSemiplanoGenRect (GR2, 4, x1, y1) && puntoSemiplanoGenRect (GR2, 4, x2, y2) &&
       puntoSemiplanoGenRect (GR2, 4, x3, y3) && puntoSemiplanoGenRect (GR2, 4, x4, y4))
     ))
   {
      colision = false;
   } else { // Chek de lo mismo pero al revés, vértices de rect1 con semiplanos de rect2.
      colision = true;
   }
   
   return colision;
}

bool RGRColision (rect R, genRect GR) { /// Colision entre un rect y un genRect.
/// Es la misma idea de la colision entre 2 genRects, ver si uno está afuera del otro o si el otro está afuera del uno.

   bool colision = false;

// Vertices del R.
   int Rx1, Ry1, Rx2, Ry2, Rx3, Ry3, Rx4, Ry4;
   Rx1 = getXRect (R); Ry1 = getYRect (R);
   int w = getWidthRect (R); int h = getHeightRect (R);
   Rx2 = Rx1 + w; Ry2 = Ry1;
   Rx3 = Rx2; Ry3 = Ry2 + h;
   Rx4 = Rx1; Ry4 = Ry3;

// Vertices del GR.
   int x1, y1, x2, y2, x3, y3, x4, y4;
   getVertexGenRect (GR, x1, y1, x2, y2, x3, y3, x4, y4);
   
/// 1- Si el GR está afuera del R.
   if (y1<Ry1 && y2<Ry1 && y3<Ry1 && y4<Ry1) { /// GR está arriba.
      colision = false;
   } else if (x1>Rx2 && x2>Rx2 && x3>Rx2 && x4>Rx2) { /// Si GR está todo a la derecha.
      colision = false;
   } else if (y1>Ry3 && y2>Ry3 && y3>Ry3 && y4>Ry3) { /// Si GR está todo abajo.
      colision = false;
   } else if (x1<Rx1 && x2<Rx1 && x3<Rx1 && x4<Rx1) { /// Si GR está todo a la izquierda.
      colision = false;
/// 2- Chekear si R está afuera de GR.
   } else if ((puntoSemiplanoGenRect (GR, 1, Rx1, Ry1) && puntoSemiplanoGenRect (GR, 1, Rx2, Ry2) && puntoSemiplanoGenRect (GR, 1, Rx3, Ry3) && puntoSemiplanoGenRect (GR, 1, Rx4, Ry4)) ||
              (puntoSemiplanoGenRect (GR, 2, Rx1, Ry1) && puntoSemiplanoGenRect (GR, 2, Rx2, Ry2) && puntoSemiplanoGenRect (GR, 2, Rx3, Ry3) && puntoSemiplanoGenRect (GR, 2, Rx4, Ry4)) ||
              (puntoSemiplanoGenRect (GR, 3, Rx1, Ry1) && puntoSemiplanoGenRect (GR, 3, Rx2, Ry2) && puntoSemiplanoGenRect (GR, 3, Rx3, Ry3) && puntoSemiplanoGenRect (GR, 3, Rx4, Ry4)) ||
              (puntoSemiplanoGenRect (GR, 4, Rx1, Ry1) && puntoSemiplanoGenRect (GR, 4, Rx2, Ry2) && puntoSemiplanoGenRect (GR, 4, Rx3, Ry3) && puntoSemiplanoGenRect (GR, 4, Rx4, Ry4)))
   {
      colision = false;
   } else { // Si uno no está todo afuera del otro o el otro no está afuera del uno, se cortan.
      colision = true;
   }

   return colision;
}


/// Ahora operaciones en posición relativa.
bool RRRelColision (rect R1, int xR1, int yR1, rect R2, int xR2, int yR2) {
   if (!(R1->y + R1->h + yR1 <= R2->y + yR2) && !(R1->x + R1->w + xR1 <= R2->x + xR2) &&
       !(R2->y + R2->h + yR2 <= R1->y + yR1) && !(R2->x + R2->w + xR2 <= R1->x + xR1)) {
      return true;
   } else {
      return false;
   }
}



bool puntoSemiplanoRelGenRect (genRect GR, int xGR, int yGR, int semiplano, int x, int y) {
// Idem al otro puntoEn Semiplano, pero con el rectángulo en posición relativa.
/* true si el punto x,y está en el semiplano determinado por la recta
#semiplano que no tenga al rectángulo. */

   float m = getMGenRect (GR);
   int x1, y1, x2, y2, x3, y3, x4, y4;
   getVertexGenRect (GR, x1, y1, x2, y2, x3, y3, x4, y4);
   x1 += xGR; x2 += xGR; x3 += xGR; x4 += xGR; /// aBsolutizando véritces.
   y1 += yGR; y2 += yGR; y3 += yGR; y4 += yGR;

   switch (semiplano) {
   case 1:
          return (y - y1 - (x - x1)*m > 0);
   break;
   case 2:
          if (m >= 0) {
             return (y - y2 + (x - x2)/m > 0);
          } else {
             return (y - y2 + (x - x2)/m < 0);
          }
   break;
   case 3:
          return (y - y3 - (x - x3)*m < 0);
   break;
   case 4:
          if (m >= 0) {
             return (y - y1 + (x - x1)/m < 0);
          } else {
             return (y - y1 + (x - x1)/m > 0);
          }
   break;
   default:
      cout << "Error en puntoEnSemiplanoRel() Módulo: colision\n";
   break;
   }
}



bool GRGRRelColision (genRect GR1, int xGR1, int yGR1, genRect GR2, int xGR2, int yGR2) {

   bool colision = false;

   int x1; int y1; int x2; int y2; int x3; int y3; int x4; int y4;
   getVertexGenRect (GR1, x1, y1, x2, y2, x3, y3, x4, y4);

   x1 += xGR1; x2 += xGR1; x3 += xGR1; x4 += xGR1; /// aBsolutizando véritces.
   y1 += yGR1; y2 += yGR1; y3 += yGR1; y4 += yGR1;

   int x12; int y12; int x22; int y22; int x32; int y32; int x42; int y42;
   getVertexGenRect (GR2, x12, y12, x22, y22, x32, y32, x42, y42);
   
   x12 += xGR2; x22 += xGR2; x32 += xGR2; x42 += xGR2; /// aBsolutizando véritces.
   y12 += yGR2; y22 += yGR2; y32 += yGR2; y42 += yGR2;
   
   
   if ((
      (puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 1, x12, y12) && puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 1, x22, y22) &&
       puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 1, x32, y32) && puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 1, x42, y42)) ||
      (puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 2, x12, y12) && puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 2, x22, y22) &&
       puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 2, x32, y32) && puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 2, x42, y42)) ||
      (puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 3, x12, y12) && puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 3, x22, y22) &&
       puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 3, x32, y32) && puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 3, x42, y42)) ||
      (puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 4, x12, y12) && puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 4, x22, y22) &&
       puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 4, x32, y32) && puntoSemiplanoRelGenRect (GR1, xGR1, yGR1, 4, x42, y42))
      )
     ||
     (
     (puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 1, x1, y1) && puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 1, x2, y2) &&
      puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 1, x3, y3) && puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 1, x4, y4)) ||
     (puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 2, x1, y1) && puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 2, x2, y2) &&
      puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 2, x3, y3) && puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 2, x4, y4)) ||
     (puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 3, x1, y1) && puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 3, x2, y2) &&
      puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 3, x3, y3) && puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 3, x4, y4)) ||
     (puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 4, x1, y1) && puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 4, x2, y2) &&
      puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 4, x3, y3) && puntoSemiplanoRelGenRect (GR2, xGR2, yGR2, 4, x4, y4))
     ))
   {
      colision = false;
   } else { // Chek de lo mismo pero al revés, vértices de rect1 con semiplanos de rect2.
      colision = true;
   }
   
   return colision;

}


bool RGRRelColision (rect R, int xR, int yR, genRect GR, int xGR, int yGR) {

   bool colision = false;

// Vertices del R.
   int Rx1, Ry1, Rx2, Ry2, Rx3, Ry3, Rx4, Ry4;
   int w = getWidthRect (R); int h = getHeightRect (R);
   Rx1 = getXRect (R) + xR; /// Trasladando vertice 1, se traslada todo el rect.
   Ry1 = getYRect (R) + yR;
   Rx2 = Rx1 + w; Ry2 = Ry1;
   Rx3 = Rx2; Ry3 = Ry2 + h;
   Rx4 = Rx1; Ry4 = Ry3;

// Vertices del GR.
   int x1, y1, x2, y2, x3, y3, x4, y4;
   getVertexGenRect (GR, x1, y1, x2, y2, x3, y3, x4, y4);
   x1 += xGR; y1 += yGR; /// Absolutizando coordenadas.
   x2 += xGR; y2 += yGR;
   x3 += xGR; y3 += yGR;
   x4 += xGR; y4 += yGR;
   
/// 1- Si el GR está afuera del R.
   if (y1<Ry1 && y2<Ry1 && y3<Ry1 && y4<Ry1) { /// GR está arriba.
      colision = false;
   } else if (x1>Rx2 && x2>Rx2 && x3>Rx2 && x4>Rx2) { /// Si GR está todo a la derecha.
      colision = false;
   } else if (y1>Ry3 && y2>Ry3 && y3>Ry3 && y4>Ry3) { /// Si GR está todo abajo.
      colision = false;
   } else if (x1<Rx1 && x2<Rx1 && x3<Rx1 && x4<Rx1) { /// Si GR está todo a la izquierda.
      colision = false;
/// 2- Chekear si R está afuera de GR.
   } else if ((puntoSemiplanoRelGenRect (GR, xGR, yGR, 1, Rx1, Ry1) && puntoSemiplanoRelGenRect (GR, xGR, yGR, 1, Rx2, Ry2) && puntoSemiplanoRelGenRect (GR, xGR, yGR, 1, Rx3, Ry3) && puntoSemiplanoRelGenRect (GR, xGR, yGR, 1, Rx4, Ry4)) ||
              (puntoSemiplanoRelGenRect (GR, xGR, yGR, 2, Rx1, Ry1) && puntoSemiplanoRelGenRect (GR, xGR, yGR, 2, Rx2, Ry2) && puntoSemiplanoRelGenRect (GR, xGR, yGR, 2, Rx3, Ry3) && puntoSemiplanoRelGenRect (GR, xGR, yGR, 2, Rx4, Ry4)) ||
              (puntoSemiplanoRelGenRect (GR, xGR, yGR, 3, Rx1, Ry1) && puntoSemiplanoRelGenRect (GR, xGR, yGR, 3, Rx2, Ry2) && puntoSemiplanoRelGenRect (GR, xGR, yGR, 3, Rx3, Ry3) && puntoSemiplanoRelGenRect (GR, xGR, yGR, 3, Rx4, Ry4)) ||
              (puntoSemiplanoRelGenRect (GR, xGR, yGR, 4, Rx1, Ry1) && puntoSemiplanoRelGenRect (GR, xGR, yGR, 4, Rx2, Ry2) && puntoSemiplanoRelGenRect (GR, xGR, yGR, 4, Rx3, Ry3) && puntoSemiplanoRelGenRect (GR, xGR, yGR, 4, Rx4, Ry4)))
   {
      colision = false;
   } else { // Si uno no está todo afuera del otro o el otro no está afuera del uno, se cortan.
      colision = true;
   }

   return colision;

}
