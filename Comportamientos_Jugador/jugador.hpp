#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

struct state{
  int fil;
  int col;
  Orientacion brujula;
};

struct casilla{
  int fil;
  int col;
};


class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
      last_action = actIDLE; //No se hizo nada en el instante anterior a empezar la simulación
      //Orientacion = norte;
      current_state.fil = current_state.col = 99;
      current_state.brujula = norte;

      girar_derecha = false;
      giro_grande = false;
      bien_situado = false;

      vector<unsigned int> aux(100, 0);
      for (unsigned int i = 0; i < 100; i++)
      {
        mapaVisitas.push_back(aux);
      }
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);

  private:
  
  // Declarar aquí las variables de estado
  Action last_action; 
  // Orientacion brujula;

  state current_state; 
  /* Importante para los niveles del juego en los que no se dispone de sensores de orientación 
  y es el propio jugador el que tiene que guardar esta información */

  bool girar_derecha;
  bool giro_grande; // Para que también se puedan hacer los giros de 135 al moverse por el terreno
  bool bien_situado;


  // INTENTO DE ACTUALIZACIÓN DE MAPA CUANDO LLEGUEMOS A LA CASILLA G 
    vector< vector< unsigned int> > mapaVisitas;
  casilla menosVisitada;
  Action proximaAccion;

};

#endif
