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
   char keyName; unsigned short action;
   
   if (iFile) {
   
      getline (iFile, line, '='); iFile >> numKeys; 
      IP = newInputPlayer (numKeys);
      
      for (int i=0; i<numKeys; i++) {
         iFile >> action >> keyName; /// Lee info del archivo.
         addKeyInputPlayer (IP, keyName, action); /// Guarda en el vector.
      }
   
   } else { /// Si no se abrió el archivo.
      IP = NULL;
   }
   
   return IP;
}


vectorFighter loadFighters (char * File) {

   vectorFighter VF; /// Vector para devolver.
   
   string line;
   
   int cantFighters;
   
   string name; char * nameCP; /// La funcion crear luchador usa char *.
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
         
         for (int j=0; j<numHits; j++) { ///------------------------------------------------------------------------
         
           fFile >> hitType >> hitId >> hitDuration >> hitDamage >> x >> y >> w >> h >> m; /// Entrada.
           
           hitGRectLR = newGenRect (x, y, w, h, m); // Golpe mirando hacia la derecha
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
           if (m != 0) {
              hitGRectLL = newGenRect ( int( -w/sqrt(1 + m*m) + width/2), int((w*m)/sqrt(1 + m*m) + y), w, h, -m); // Golpe mirando a la izquierda.
           } else {
              hitGRectLL = newGenRect ( int( -w/sqrt(1 + m*m) + width/2), int((w*m)/sqrt(1 + m*m) + y), w, h, m); // Golpe mirando a la izq (m=0).
           }
           //newHit (unsigned short Hid, unsigned short Hdur, float Hdmg, genRect GRectLL, genRect GRectLR)
           H = newHit (hitId, hitDuration, hitDamage, hitGRectLL, hitGRectLR); //// crea el golpe
           
           addHitVHit (VHit, H); /// agrega el golpe creado.
           
         } /// For de los golpes ----------------------------------------------------------------------------------
         
         
         /// Armando a los luchadores.
         bodyS = newRect (0, 0, width, height_s); /// Cuerpo parado.
         bodyC = newRect (0, 0, width, height_c); /// Cuerpo agachado.
         bodyJ = newRect (0, 0, width, height_j); /// Cuerpo saltando.
         
         /*************************************************************
         /* Necesito que name sea char* no string para el newSFighter
         /************************************************************/
         
         nameCP = &name[0]; /// Apunta al primer char del string.
         ///cout << "El nombre del tipo " << id << " es: " << nameCP << endl;
         
         /*************************************************************
         /* OJO! chekear que nameCP tenga exactamente el nombre del tipo!, -> FUNCIONA BIEN!
         /************************************************************/
         
         SF = newSFighter (nameCP, spd, bodyS, bodyC, bodyJ);
         setHitsSFighter (SF, VHit);
         
         DF = newDFighter (0, 0, energy);
         
         vector_imgs imgs = loadVImgs ("pics/imgs.txt"); // el archivo de luchadores debe decir donde está el archivo de config de las imgs
         //vector_imgs imgs = NULL;
         //if (imgs) {cerr << "Se creó imgs\n";}
         //else {cerr << "NO se creó imgs\n";}
         
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



