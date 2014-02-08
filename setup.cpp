#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "math.h"

#include "vector_SDL_Surf.h"

#include "setup.h"

using namespace std;


inputP loadInput (char * File) {

   inputP IP;

   ifstream iFile (File); // Abre el archivo de luchadores.
   
   string line;
   unsigned short numKeys; /// Número de teclas a leer;
   string keyName; unsigned short action;
   
   if (iFile) {
   
      getline (iFile, line, '='); iFile >> numKeys; getline (iFile, line); //come enter
      IP = newInputPlayer (numKeys + 1); // +1 para terminaro en null y que no halla problemas con basura.
      
      for (int i=0; i<numKeys; i++) {
         getline (iFile, keyName);
         
         cout << "keyName: " << keyName << endl;
         
         addKeyInputPlayer (IP, getSDLKbyName(&keyName[0]), i); /// Guarda en el vector.
      }
      
      addKeyInputPlayer (IP, '\0', numKeys); // NULL al final del vector
   
   } else { /// Si no se abrió el archivo.
      IP = NULL;
   }
   
   iFile.close();
   return IP;
}


vectorFighter loadFighters (char * File) {

   vectorFighter VF; /// Vector para devolver.
   
   string line;
   
   int cantFighters;
   
   string name;
   int id, spd, width, height_s, height_c, height_j; /// Para los datos del luchador (height parado, agachado, saltando).
   float energy;
   
   int numHits;
   char hitType; //// Info de los golpes.
   int hitId, hitDuration, hitDamage;
   int x, y, w, h; float m; /// Para los golpes (gen_rects)
   
   
   vectorHit VHit; /// Vector auxiliar de golpes.
   s_fighter SF; /// Luchador estático auxiliar.
   d_fighter DF; /// luchador dinamico.
   rect bodyC; /// cuerpo agachado
   rect bodyS; /// cuerpo parado.
   rect bodyJ; /// cuerpo saltando.
   hit H; /// Golpe auxiliar.
   genRect hitGRectLL, hitGRectLR; /// Rectángulos para el golpe.
   
   ifstream fFile (File); // Abre el archivo de luchadores.
   
   if (fFile) { /// Si el archivo se pudo abrir.
   
   /// Cuantos luchadores hay.
      getline (fFile, line, '='); fFile >> cantFighters;
      getline (fFile, line); /// Se come el reglon en blanco.
      
      VF = newVectorF (cantFighters);
      
      for (int i=0; i<cantFighters; i++) {
      
         getline (fFile, line); /// Se come el reglon que tiene el titulo.
         getline (fFile, line, '='); fFile >> name; /// Primero el nombre.
         getline (fFile, line, '='); fFile >> id; /// Ahora el id.
         getline (fFile, line, '='); fFile >> spd; /// Velocidad.
         getline (fFile, line, '='); fFile >> width; /// width.
         getline (fFile, line, '='); fFile >> height_s; /// Height del tipo parado.
         getline (fFile, line, '='); fFile >> height_c; /// Height agachado.
         getline (fFile, line, '='); fFile >> height_j; /// Height saltando.
         
         getline (fFile, line, '='); fFile >> energy; /// Energía.
         
         
         /// Ahora a ver los golpes.
         getline (fFile, line, '='); fFile >> numHits; /// Número de golpes.
         VHit = newVHit (numHits);
         
         getline (fFile, line); // siguiente reglón, comienzan los rects de los golpes.
         
         /// Todos los golpes.
         genRect j_izq, j_der, c_izq, c_der, s_izq, s_der;
         
         //for (int j=0; j<numHits; j++) { ///------------------------------------------------------------------------
         
           fFile >> hitType >> hitId >> hitDuration >> hitDamage; getline (fFile, line);
           //cerr << hitType << " " << hitId << " " << hitDuration << " " << hitDamage << line << endl;
           
           fFile >> x >> y >> w >> h >> m; getline (fFile, line);// Golpe parado
           //cerr << x << " " << y << " " << w << " " << h << " " << m << " " << endl;
           
           s_der = newGenRect (x, y, w, h, m);
           //if (sp_der) {cerr << "sp_der OK\n";} else {cerr << "sp_der KO\n";}
           
           if (m != 0) {
              s_izq = newGenRect ( int( -w/sqrt(1 + m*m) - x + width), int((w*m)/sqrt(1 + m*m) + y), w, h, -m); // Golpe mirando a la izquierda.
           } else {
              s_izq = newGenRect ( int( -w/sqrt(1 + m*m) - x + width), int((w*m)/sqrt(1 + m*m) + y), w, h, m); // Golpe mirando a la izq (m=0).
           }
           
           fFile >> x >> y >> w >> h >> m; getline (fFile, line);// Golpe saltando
           //cerr << x << " " << y << " " << w << " " << h << " " << m << " " << endl;
           
           j_der = newGenRect (x, y, w, h, m);
           //if (jp_der) {cerr << "jp_der OK\n";} else {cerr << "jp_der KO\n";}
           
           if (m != 0) {
              j_izq = newGenRect ( int( -w/sqrt(1 + m*m) - x + width), int((w*m)/sqrt(1 + m*m) + y), w, h, -m); // Golpe mirando a la izquierda.
           } else {
              j_izq = newGenRect ( int( -w/sqrt(1 + m*m) - x + width), int((w*m)/sqrt(1 + m*m) + y), w, h, m); // Golpe mirando a la izq (m=0).
           }
           
           fFile >> x >> y >> w >> h >> m; getline (fFile, line);// Golpe agachado
           //cerr << x << " " << y << " " << w << " " << h << " " << m << " " << endl;
           
           c_der = newGenRect (x, y, w, h, m);
           //if (cp_der) {cerr << "cp_der OK\n";} else {cerr << "cp_der KO\n";}
           
           if (m != 0) {
              c_izq = newGenRect ( int( -w/sqrt(1 + m*m) - x + width), int((w*m)/sqrt(1 + m*m) + y), w, h, -m); // Golpe mirando a la izquierda.
           } else {
              c_izq = newGenRect ( int( -w/sqrt(1 + m*m) - x + width), int((w*m)/sqrt(1 + m*m) + y), w, h, m); // Golpe mirando a la izq (m=0).
           }
           
           H = newHit (hitId, hitDuration, hitDamage,
                       j_izq, j_der, c_izq, c_der, s_izq, s_der);
           
           addHitVHit (VHit, H);
           
           
           fFile >> hitType >> hitId >> hitDuration >> hitDamage; getline (fFile, line);
           
           fFile >> x >> y >> w >> h >> m; getline (fFile, line);// patada parado
           s_der = newGenRect (x, y, w, h, m);
           if (m != 0) {
              s_izq = newGenRect ( int( -w/sqrt(1 + m*m) - x + width), int((w*m)/sqrt(1 + m*m) + y), w, h, -m); // Golpe mirando a la izquierda.
           } else {
              s_izq = newGenRect ( int( -w/sqrt(1 + m*m) - x + width), int((w*m)/sqrt(1 + m*m) + y), w, h, m); // Golpe mirando a la izq (m=0).
           }
           
           fFile >> x >> y >> w >> h >> m; getline (fFile, line);// patada saltando
           j_der = newGenRect (x, y, w, h, m);
           if (m != 0) {
              j_izq = newGenRect ( int( -w/sqrt(1 + m*m) - x + width), int((w*m)/sqrt(1 + m*m) + y), w, h, -m); // Golpe mirando a la izquierda.
           } else {
              j_izq = newGenRect ( int( -w/sqrt(1 + m*m) - x + width), int((w*m)/sqrt(1 + m*m) + y), w, h, m); // Golpe mirando a la izq (m=0).
           }
           
           fFile >> x >> y >> w >> h >> m; getline (fFile, line);// patada agachado
           c_der = newGenRect (x, y, w, h, m);
           if (m != 0) {
              c_izq = newGenRect ( int( -w/sqrt(1 + m*m) - x + width), int((w*m)/sqrt(1 + m*m) + y), w, h, -m); // Golpe mirando a la izquierda.
           } else {
              c_izq = newGenRect ( int( -w/sqrt(1 + m*m) - x + width), int((w*m)/sqrt(1 + m*m) + y), w, h, m); // Golpe mirando a la izq (m=0).
           }
           
           
           //hitGRectLR = newGenRect (x, y, w, h, m); // Golpe mirando hacia la derecha
           //**************************************************************************************************
           // Los datos para el rectángulo mirando a la izquierda salen de los datos del mirando a la derecha:
           // Xi = -w/sqrt(1+m^2) - Xd
           // Yi = (w*m)/sqrt(1 + m^2)
           // w y h son los mismos y mi = -md
           // en posicion absoluta a la Xi hay que sumarle X + w/2 (la X del luchador, que es 0) y a Yi: Yd
           //
           // Parece que la Xi funciona bien sin -Xd. ???  Error de cuentas ??? VERIFICAR !!!
           // NO ESTÁ BIEN (sacar -Xd), se acerca pero no es la solución correcta!!!. (?????)
           //**************************************************************************************************
/*
           if (m != 0) {
              hitGRectLL = newGenRect ( int( -w/sqrt(1 + m*m) + width/2), int((w*m)/sqrt(1 + m*m) + y), w, h, -m); // Golpe mirando a la izquierda.
           } else {
              hitGRectLL = newGenRect ( int( -w/sqrt(1 + m*m) + width/2), int((w*m)/sqrt(1 + m*m) + y), w, h, m); // Golpe mirando a la izq (m=0).
           }
*/
           //H = newHit (hitId, hitDuration, hitDamage, hitGRectLL, hitGRectLR); //// crea el golpe
           
           H = newHit (hitId, hitDuration, hitDamage,
                       j_izq, j_der, c_izq, c_der, s_izq, s_der);
           
           addHitVHit (VHit, H); /// agrega el golpe creado.
           
         //} /// For de los golpes ----------------------------------------------------------------------------------
         
         
         /// Para los archivos de imagenes.
         string archivoImgs;
         getline (fFile, archivoImgs);
         //cout << "file: " << line << endl;
         vector_imgs imgs = loadVImgs (&archivoImgs[0]);
         if (!imgs) {cerr << "Error al cargar imágenes: archivo no encontrado: " << archivoImgs << endl;}
         //vector_imgs imgs = loadVImgs ("pics/imgs.txt"); // el archivo de luchadores debe decir donde está el archivo de config de las imgs
         //vector_imgs imgs = NULL;
         //if (imgs) {cerr << "Se creó imgs\n";}
         //else {cerr << "NO se creó imgs\n";}
         
         
         /// Armando a los luchadores.
         bodyS = newRect (0, 0, width, height_s); /// Cuerpo parado.
         bodyC = newRect (0, 0, width, height_c); /// Cuerpo agachado.
         bodyJ = newRect (0, 0, width, height_j); /// Cuerpo saltando.

         
         SF = newSFighter (&name[0], spd, bodyS, bodyC, bodyJ);
         setHitsSFighter (SF, VHit);
         
         DF = newDFighter (0, 0, energy);
         
         addFVectorF (VF, SF, DF, id, imgs); /// Agrega el luchador al vector.
         
         /// Observacion: al principio x,y de los luchadores es 0,0, hasta que no se empiece la pelea,
         /// donde se setearán las posiciones dependiendo de los jugadores. (jugador1 tiene distinta
         /// posicion que el jugador2, y estas son fijas.)
      
         getline (fFile, line); /// Se come el reglon en blanco entre luchadores.
      
      } /// For de los luchadores.
      
   } else { /// Si hubo un error al abrir el archivo.
      VF = NULL;
   }
   
   fFile.close();
   return VF;
}



int getSDLKbyName (char * name) {

/* Teclado numérico. */
        if ( strcmp(name, "[/]") == 0 ) {return 267;}
   else if ( strcmp(name, "[*]") == 0 ) {return 268;}
   else if ( strcmp(name, "[+]") == 0 ) {return 270;}
   else if ( strcmp(name, "[-]") == 0 ) {return 269;}
   else if ( strcmp(name, "numlock") == 0 ) {return 300;}
   else if ( strcmp(name, "[0]") == 0 ) {return 256;}
   else if ( strcmp(name, "[1]") == 0 ) {return 257;}
   else if ( strcmp(name, "[2]") == 0 ) {return 258;}
   else if ( strcmp(name, "[3]") == 0 ) {return 259;}
   else if ( strcmp(name, "[4]") == 0 ) {return 260;}
   else if ( strcmp(name, "[5]") == 0 ) {return 261;}
   else if ( strcmp(name, "[6]") == 0 ) {return 262;}
   else if ( strcmp(name, "[7]") == 0 ) {return 263;}
   else if ( strcmp(name, "[8]") == 0 ) {return 264;}
   else if ( strcmp(name, "[9]") == 0 ) {return 265;}
   else if ( strcmp(name, "[.]") == 0 ) {return 266;}
   else if ( strcmp(name, "up") == 0 ) {return 273;}
   else if ( strcmp(name, "down") == 0 ) {return 274;}
   else if ( strcmp(name, "left") == 0 ) {return 276;}
   else if ( strcmp(name, "right") == 0 ) {return 275;}
   else if ( strcmp(name, "page up") == 0 ) {return 280;}
   else if ( strcmp(name, "page down") == 0 ) {return 281;}
   else if ( strcmp(name, "clear") == 0 ) {return 12;}
   else if ( strcmp(name, "home") == 0 ) {return 278;}
   else if ( strcmp(name, "end") == 0 ) {return 279;}
   else if ( strcmp(name, "insert") == 0 ) {return 277;}
   else if ( strcmp(name, "delete") == 0 ) {return 127;}
/* Teclado numérico. */
/* Arriba */
   else if ( strcmp(name, "return") == 0 ) {return 13;}
   else if ( strcmp(name, "escape") == 0 ) {return 27;}
   else if ( strcmp(name, "f1") == 0 ) {return 282;}
   else if ( strcmp(name, "f2") == 0 ) {return 283;}
   else if ( strcmp(name, "f3") == 0 ) {return 284;}
   else if ( strcmp(name, "f4") == 0 ) {return 285;}
   else if ( strcmp(name, "f5") == 0 ) {return 286;} 
   else if ( strcmp(name, "f6") == 0 ) {return 287;}
   else if ( strcmp(name, "f7") == 0 ) {return 288;}
   else if ( strcmp(name, "f8") == 0 ) {return 289;}
   else if ( strcmp(name, "f9") == 0 ) {return 290;}
   else if ( strcmp(name, "f10") == 0 ) {return 291;}
   else if ( strcmp(name, "f11") == 0 ) {return 292;}
   else if ( strcmp(name, "f12") == 0 ) {return 293;}
/* Arriba */
/* Arrows las flechas están en el teclado numerico cuando bloqnum está activo. */
/* otras teclas como delete o insert también están en el teclado numérico. */
   else if ( strcmp(name, "scroll lock") == 0 ) {return 302;}
   else if ( strcmp(name, "pause") == 0 ) {return 19;}
/* Arrows */

/* simbolos y mods*/
else if ( strcmp(name, "\\") == 0 ) {return 92;} // ojo ver si funca
else if ( strcmp(name, "unknown key") == 0 ) {return 0;} // ojo, no ve tecla "<"
else if ( strcmp(name, "[") == 0 ) {return 91;}
else if ( strcmp(name, "]") == 0 ) {return 93;}
else if ( strcmp(name, ";") == 0 ) {return 59;}
else if ( strcmp(name, "=") == 0 ) {return 61;}
else if ( strcmp(name, "'") == 0 ) {return 39;}
else if ( strcmp(name, "/") == 0 ) {return 47;}
else if ( strcmp(name, "-") == 0 ) {return 45;}
else if ( strcmp(name, ".") == 0 ) {return 46;}
else if ( strcmp(name, ",") == 0 ) {return 44;}
else if ( strcmp(name, "backspace") == 0 ) {return 8;}
else if ( strcmp(name, "tab") == 0 ) {return 9;}
else if ( strcmp(name, "caps lock") == 0 ) {return 301;}
else if ( strcmp(name, "left shift") == 0 ) {return 304;}
else if ( strcmp(name, "left ctrl") == 0 ) {return 306;}
else if ( strcmp(name, "left alt") == 0 ) {return 308;}
else if ( strcmp(name, "left ctrl") == 0 ) {return 306;}
else if ( strcmp(name, "right alt") == 0 ) {return 307;}
else if ( strcmp(name, "right ctrl") == 0 ) {return 305;}
else if ( strcmp(name, "menu") == 0 ) {return 319;}
else if ( strcmp(name, "left shift") == 0 ) {return 304;}
/* simbolos y mods */

/* Numeros */
else if ( strcmp(name, "1") == 0 ) {return 49;}
else if ( strcmp(name, "2") == 0 ) {return 50;}
else if ( strcmp(name, "3") == 0 ) {return 51;}
else if ( strcmp(name, "4") == 0 ) {return 52;}
else if ( strcmp(name, "5") == 0 ) {return 53;}
else if ( strcmp(name, "6") == 0 ) {return 54;}
else if ( strcmp(name, "7") == 0 ) {return 55;}
else if ( strcmp(name, "8") == 0 ) {return 56;}
else if ( strcmp(name, "9") == 0 ) {return 57;}
else if ( strcmp(name, "0") == 0 ) {return 48;}
/* Numeros */

/* letras */
else if ( strcmp(name, "a") == 0 ) {return 97;}
else if ( strcmp(name, "b") == 0 ) {return 98;}
else if ( strcmp(name, "c") == 0 ) {return 99;}
else if ( strcmp(name, "d") == 0 ) {return 100;}
else if ( strcmp(name, "e") == 0 ) {return 101;}
else if ( strcmp(name, "f") == 0 ) {return 102;}
else if ( strcmp(name, "g") == 0 ) {return 103;}
else if ( strcmp(name, "h") == 0 ) {return 104;}
else if ( strcmp(name, "i") == 0 ) {return 105;}
else if ( strcmp(name, "j") == 0 ) {return 106;}
else if ( strcmp(name, "k") == 0 ) {return 107;}
else if ( strcmp(name, "l") == 0 ) {return 108;}
else if ( strcmp(name, "m") == 0 ) {return 109;}
else if ( strcmp(name, "n") == 0 ) {return 110;}
else if ( strcmp(name, "`") == 0 ) {return 96;} // ojo esta es la ñ
else if ( strcmp(name, "o") == 0 ) {return 111;}
else if ( strcmp(name, "p") == 0 ) {return 112;}
else if ( strcmp(name, "q") == 0 ) {return 113;}
else if ( strcmp(name, "r") == 0 ) {return 114;}
else if ( strcmp(name, "s") == 0 ) {return 115;}
else if ( strcmp(name, "t") == 0 ) {return 116;}
else if ( strcmp(name, "u") == 0 ) {return 117;}
else if ( strcmp(name, "v") == 0 ) {return 118;}
else if ( strcmp(name, "w") == 0 ) {return 119;}
else if ( strcmp(name, "x") == 0 ) {return 120;}
else if ( strcmp(name, "y") == 0 ) {return 121;}
else if ( strcmp(name, "z") == 0 ) {return 122;}
/* Letras */

}


char * getNamebySDLK (int Key) {

/* Teclado numérico. */
        if ( Key == 267) {return "[/]";}
   else if ( Key == 268return "[*]") {;}
   else if ( Key == 270return "[+]") 
   else if ( Key == 269return "[-]") 
   else if ( Key == 300return "numlock") 
   else if ( Key == 256return "[0]") 
   else if ( Key == 257return "[1]") 
   else if ( Key == 258return "[2]") 
   else if ( Key == 259return "[3]") 
   else if ( Key == 260return "[4]") 
   else if ( Key == 261return "[5]") 
   else if ( Key == 262return "[6]") 
   else if ( Key == 263return "[7]") 
   else if ( Key == 264return "[8]") 
   else if ( Key == 265return "[9]") 
   else if ( Key == 266return "[.]") 
   else if ( Key == 273return "up") 
   else if ( Key == 274return "down") 
   else if ( Key == 276return "left") 
   else if ( Key == 275return "right") 
   else if ( Key == 280return "page up") 
   else if ( Key == 281return "page down") 
   else if ( Key == 12return "clear") 
   else if ( Key == 278return "home") 
   else if ( Key == 279return "end") 
   else if ( Key == 277return "insert") 
   else if ( Key == 127return "delete") 
/* Teclado numérico. */
/* Arriba */
   else if ( Key == 13return "Key ==") 
   else if ( Key == 27return "escape") 
   else if ( Key == 282return "f1") 
   else if ( Key == 283return "f2") 
   else if ( Key == 284return "f3") 
   else if ( Key == 285return "f4") 
   else if ( Key == 286return "f5")  
   else if ( Key == 287return "f6") 
   else if ( Key == 288return "f7") 
   else if ( Key == 289return "f8") 
   else if ( Key == 290return "f9") 
   else if ( Key == 291return "f10") 
   else if ( Key == 292return "f11") 
   else if ( Key == 293return "f12") 
/* Arriba */
/* Arrows las flechas están en el teclado numerico cuando bloqnum está activo. */
/* otras teclas como delete o insert también están en el teclado numérico. */
   else if ( Key == 302return "scroll lock") 
   else if ( Key == 19return "pause") 
/* Arrows */

/* simbolos y mods*/
else if ( Key == 92return "\\") {;} // ojo ver si funca
else if ( Key == 0return "unknown key") {;} // ojo, no ve tecla "<"
else if ( Key == 91return "[") {;}
else if ( Key == 93return "]") {;}
else if ( Key == 59return ";") {;}
else if ( Key == 61return "=") {;}
else if ( Key == 39return "'") {;}
else if ( Key == 47return "/") {;}
else if ( Key == 45return "-") {;}
else if ( Key == 46return ".") {;}
else if ( Key == 44return ",") {;}
else if ( return "backspace") {Key == 8;}
else if ( return "tab") {Key == 9;}
else if ( return "caps lock") {Key == 301;}
else if ( return "left shift") {Key == 304;}
else if ( return "left ctrl") {Key == 306;}
else if ( return "left alt") {Key == 308;}
else if ( return "left ctrl") {Key == 306;}
else if ( return "right alt") {Key == 307;}
else if ( return "right ctrl") {Key == 305;}
else if ( return "menu") {Key == 319;}
else if ( return "left shift") {Key == 304;}
/* simbolos y mods */

/* Numeros */
else if ( return "1") {Key == 49;}
else if ( return "2") {Key == 50;}
else if ( return "3") {Key == 51;}
else if ( return "4") {Key == 52;}
else if ( return "5") {Key == 53;}
else if ( return "6") {Key == 54;}
else if ( return "7") {Key == 55;}
else if ( return "8") {Key == 56;}
else if ( return "9") {Key == 57;}
else if ( return "0") {Key == 48;}
/* Numeros */

/* letras */
else if ( return "a") {Key == 97;}
else if ( return "b") {Key == 98;}
else if ( return "c") {Key == 99;}
else if ( return "d") {Key == 100;}
else if ( return "e") {Key == 101;}
else if ( return "f") {Key == 102;}
else if ( return "g") {Key == 103;}
else if ( return "h") {Key == 104;}
else if ( return "i") {Key == 105;}
else if ( return "j") {Key == 106;}
else if ( return "k") {Key == 107;}
else if ( return "l") {Key == 108;}
else if ( return "m") {Key == 109;}
else if ( return "n") {Key == 110;}
else if ( return "`") {Key == 96;} // ojo esta es la ñ
else if ( return "o") {Key == 111;}
else if ( return "p") {Key == 112;}
else if ( return "q") {Key == 113;}
else if ( return "r") {Key == 114;}
else if ( return "s") {Key == 115;}
else if ( return "t") {Key == 116;}
else if ( return "u") {Key == 117;}
else if ( return "v") {Key == 118;}
else if ( return "w") {Key == 119;}
else if ( return "x") {Key == 120;}
else if ( return "y") {Key == 121;}
else if ( return "z") {Key == 122;}
/* Letras */

}
