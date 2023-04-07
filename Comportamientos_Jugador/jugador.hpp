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

      ultima.fil=-2;
      ultima.col=-2;
      actual.fil=-1;
      actual.col=-1;
      zapatillas=false;
      bikini=false;
      posicionamiento=false;
      /*girar_derecha = false;
      giro_grande = false;*/
      bien_situado = false;
      stuck=false;

      vector<unsigned int> aux;
      for (unsigned int i = 0; i < 100; i++)
      {
        for (unsigned int j=0; j<100; j++){
          aux.push_back(0);
        }
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
  bool zapatillas; 
  bool bikini;
  bool posicionamiento;
  bool stuck;
  casilla ultima;
  casilla actual;


  // INTENTO DE ACTUALIZACIÓN DE MAPA CUANDO LLEGUEMOS A LA CASILLA G 
    vector< vector< unsigned int> > mapaVisitas;
  Action proximaAccion;

  void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st, vector<vector<unsigned char>> &matriz){
    int count=0;

    switch(current_state.brujula){ 
      case norte:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.fil-i][st.col-i+j]=terreno[count];
              count++;
            }
            /*if (terreno[count]=='P') 
              parar=true;*/
          }
        break; //Si estaba mirando al norte
      case este:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.fil-i+j][st.col+i]=terreno[count];
              count++;
            }
            /*if (terreno[count]=='P') 
              parar=true;*/
          }
        break;
      case sur:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.fil+i][st.col-j+i]=terreno[count];
              count++;
            }
            /*if (terreno[count]=='P') 
              parar=true;*/
          }
        break;
      case oeste:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.fil+i-j][st.col-i]=terreno[count];
              count++;
            }
            /*if (terreno[count]=='P') 
              parar=true;*/
          }
        break;
      case noroeste:
        matriz[st.fil][st.col]=terreno[0];
        matriz[st.fil][st.col-1]=terreno[1];
        matriz[st.fil-1][st.col-1]=terreno[2];
        matriz[st.fil-1][st.col]=terreno[3];
        matriz[st.fil][st.col-2]=terreno[4];
        matriz[st.fil-1][st.col-2]=terreno[5];
        matriz[st.fil-2][st.col-2]=terreno[6];
        matriz[st.fil-2][st.col-1]=terreno[7];
        matriz[st.fil-2][st.col]=terreno[8];
        matriz[st.fil][st.col-3]=terreno[9];
        matriz[st.fil-1][st.col-3]=terreno[10];
        matriz[st.fil-2][st.col-3]=terreno[11];
        matriz[st.fil-3][st.col-3]=terreno[12];
        matriz[st.fil-3][st.col-2]=terreno[13];
        matriz[st.fil-3][st.col-1]=terreno[14];
        matriz[st.fil-3][st.col]=terreno[15];
        break;
      case noreste:
        matriz[st.fil][st.col]=terreno[0];
        matriz[st.fil-1][st.col]=terreno[1];
        matriz[st.fil-1][st.col+1]=terreno[2];
        matriz[st.fil][st.col+1]=terreno[3];
        matriz[st.fil-2][st.col]=terreno[4];
        matriz[st.fil-2][st.col+1]=terreno[5];
        matriz[st.fil-2][st.col+2]=terreno[6];
        matriz[st.fil-1][st.col+2]=terreno[7];
        matriz[st.fil][st.col+2]=terreno[8];
        matriz[st.fil-3][st.col]=terreno[9];
        matriz[st.fil-3][st.col+1]=terreno[10];
        matriz[st.fil-3][st.col+2]=terreno[11];
        matriz[st.fil-3][st.col+3]=terreno[12];
        matriz[st.fil-2][st.col+3]=terreno[13];
        matriz[st.fil-1][st.col+3]=terreno[14];
        matriz[st.fil][st.col+3]=terreno[15];
        break;
      case suroeste:
        matriz[st.fil][st.col]=terreno[0];
        matriz[st.fil+1][st.col]=terreno[1];
        matriz[st.fil+1][st.col-1]=terreno[2];
        matriz[st.fil][st.col-1]=terreno[3];
        matriz[st.fil+2][st.col]=terreno[4];
        matriz[st.fil+2][st.col-1]=terreno[5];
        matriz[st.fil+2][st.col-2]=terreno[6];
        matriz[st.fil+1][st.col-2]=terreno[7];
        matriz[st.fil][st.col-2]=terreno[8];
        matriz[st.fil+3][st.col]=terreno[9];
        matriz[st.fil+3][st.col-1]=terreno[10];
        matriz[st.fil+3][st.col-2]=terreno[11];
        matriz[st.fil+3][st.col-3]=terreno[12];
        matriz[st.fil+2][st.col-3]=terreno[13];
        matriz[st.fil+1][st.col-3]=terreno[14];
        matriz[st.fil][st.col-3]=terreno[15];
      break;
      case sureste:
        matriz[st.fil][st.col]=terreno[0];
        matriz[st.fil][st.col+1]=terreno[1];
        matriz[st.fil+1][st.col+1]=terreno[2];
        matriz[st.fil+1][st.col]=terreno[3];
        matriz[st.fil][st.col+2]=terreno[4];
        matriz[st.fil+1][st.col+2]=terreno[5];
        matriz[st.fil+2][st.col+2]=terreno[6];
        matriz[st.fil+2][st.col+1]=terreno[7];
        matriz[st.fil+2][st.col]=terreno[8];
        matriz[st.fil][st.col+3]=terreno[9];
        matriz[st.fil+1][st.col+3]=terreno[10];
        matriz[st.fil+2][st.col+3]=terreno[11];
        matriz[st.fil+3][st.col+3]=terreno[12];
        matriz[st.fil+3][st.col+2]=terreno[13];
        matriz[st.fil+3][st.col+1]=terreno[14];
        matriz[st.fil+3][st.col]=terreno[15];
        break;
	  }
  }

  Action GirarMenosVisitada(const vector<unsigned char> &terreno, const vector<unsigned char> &superficie, const int &bateria, const state &st, vector<vector<unsigned char>> &matriz, vector<vector<unsigned int>> &matriz2){

    /*if (terreno[2]=='M'){
      if (terreno[3]=='M'){
        if (terreno[1]=='M'){
          proximaAccion=actTURN_BL;
          return proximaAccion;
        }
        else if (terreno[1]=='P'){
          proximaAccion=actTURN_BR;
          return proximaAccion;
        }
        proximaAccion=actTURN_SL;
        return proximaAccion;
      }
      if (terreno[1]=='M'){
        if (terreno[3]=='P'){
          proximaAccion=actTURN_BL;
          return proximaAccion;
        }
        proximaAccion=actTURN_SR;
        return proximaAccion;
      }
      proximaAccion=actTURN_SR;
      return proximaAccion;
    }
    else if (terreno[1]=='M'){
      if (terreno[2]!='P'){
        proximaAccion=actFORWARD;
        return proximaAccion;
      }
      else {
        proximaAccion=actTURN_BR;
      }
    }
    else if (terreno[3]=='M'){
      if (terreno[2]!='P'){
        proximaAccion=actFORWARD;
        return proximaAccion;
      }
      else {
        proximaAccion=actTURN_BL;
      }
    }*/

    /*if (terreno[0]=='X' and bateria<5000){
      proximaAccion=actIDLE;
      return proximaAccion;
    }*/

    if (!zapatillas and terreno[2]=='D'){
      proximaAccion=actFORWARD;
    }
    else if (!zapatillas and terreno[1]=='D'){
      proximaAccion=actTURN_SL;
    }
    else if (!zapatillas and terreno[3]=='D'){
      proximaAccion=actTURN_SR;
    }
    else if (!bikini and terreno[2]=='K'){
      proximaAccion=actFORWARD;
    }
    else if (!bikini and terreno[1]=='K'){
      proximaAccion=actTURN_SL;
    }
    else if (!bikini and terreno[3]=='K'){
      proximaAccion=actTURN_SR;
    }

    else if (terreno[2]=='M'){
      if (terreno[1]!='M'){
        proximaAccion=actTURN_SL;
        return proximaAccion;
      }
      else {
        proximaAccion=actTURN_SR;
        return proximaAccion;
      }
    }
    else if (terreno[1]=='M' and terreno[3]=='M'){
      if (terreno[2]!='P'){
        proximaAccion=actFORWARD;
        return proximaAccion;
      }
    }
    else if (terreno[1]=='M'){
      proximaAccion=actTURN_SL;
      return proximaAccion;
    }
    else if (terreno[3]=='M'){
      proximaAccion=actTURN_SR;
      return proximaAccion;
    }

    else if (terreno[2]!='P'){
    switch (current_state.brujula){
      case norte:
        // SUELO PEDREGOSO
        if (terreno[2]=='S'){
          if (terreno[1]=='S'){
            // Si las tres casillas coinciden
            if (terreno[3]=='S'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='S'){
          if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='S'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA BIKINI
        if (!bikini and terreno[2]=='K'){
          if (terreno[1]=='K'){
            // Si las tres casillas coinciden
            if (terreno[3]=='K'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!bikini and terreno[1]=='K'){
          if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!bikini and terreno[3]=='K'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA ZAPATILLAS
        else if (!zapatillas and terreno[2]=='D'){
          if (terreno[1]=='D'){
            // Si las tres casillas coinciden
            if (terreno[3]=='D'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!zapatillas and terreno[1]=='D'){
          if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!zapatillas and terreno[3]=='D'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA POSICIONAMIENTO
        else if (terreno[2]=='G' and !posicionamiento){
          if (terreno[1]=='G'){
            // Si las tres casillas coinciden
            if (terreno[3]=='G'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='G' and !posicionamiento){
          if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='G' and !posicionamiento){
          proximaAccion=actTURN_SR;
        }

        // SUELO ARENOSO
        else if (terreno[2]=='T'){
          if (terreno[1]=='T'){
            // Si las tres casillas coinciden
            if (terreno[3]=='T'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='T'){
          if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='T'){
          proximaAccion=actTURN_SR;
        }

        // AGUA CON BIKINI
        else if (bikini){
          if (terreno[2]=='A'){
            if (terreno[1]=='A'){
              // Si las tres casillas coinciden
              if (terreno[3]=='A'){
                // Si la 2 es la menos visitada
                if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1] and
                  mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                  proximaAccion=actFORWARD;
                }
                // Si la 1 es la menos visitada
                else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 3 es la menos visitada
                else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                  proximaAccion=actTURN_SR;
                }
                else {
                  proximaAccion=actFORWARD;
                }
              }
              // Si sólo coinciden la 1 y la 2
              else {
                // Si la 1 es la menos visitada
                if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 2 es la menos visitada
                else {
                  proximaAccion=actFORWARD;
                }
              }
            }
            // Si sólo coinciden la 2 y la 3
            else if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo lo es la 2
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si coinciden la 1 y la 3
          else if (terreno[1]=='A'){
            if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              // Si la 1 es la menos visitada
              else {
                proximaAccion=actTURN_SL;
              }
            }
            // Si sólo lo es la 1
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 3
          else if (terreno[3]=='A'){
            proximaAccion=actTURN_SR;
          }
        }

        // BOSQUE (CON O SIN ZAPATILLAS)
        else if (terreno[2]=='B'){
          if (terreno[1]=='B'){
            // Si las tres casillas coinciden
            if (terreno[3]=='B'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='B'){
          if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='B'){
          proximaAccion=actTURN_SR;
        }
        
        // AGUA SIN BIKINI
        /*else if (terreno[2]=='A'){
          if (terreno[1]=='A'){
            // Si las tres casillas coinciden
            if (terreno[3]=='A'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else {
                proximaAccion=actTURN_SR;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='A'){
          if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='A'){
          proximaAccion=actTURN_SR;
        }*/
        else {
          proximaAccion=actTURN_SL;
        }
      break;
      case noreste:
        // SUELO PEDREGOSO
        if (terreno[2]=='S'){
          if (terreno[1]=='S'){
            // Si las tres casillas coinciden
            if (terreno[3]=='S'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='S'){
          if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='S'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA BIKINI
        if (!bikini and terreno[2]=='K'){
          if (terreno[1]=='K'){
            // Si las tres casillas coinciden
            if (terreno[3]=='K'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!bikini and terreno[1]=='K'){
          if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!bikini and terreno[3]=='K'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA ZAPATILLAS
        else if (!zapatillas and terreno[2]=='D'){
          if (terreno[1]=='D'){
            // Si las tres casillas coinciden
            if (terreno[3]=='D'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!zapatillas and terreno[1]=='D'){
          if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!zapatillas and terreno[3]=='D'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA POSICIONAMIENTO
        else if (terreno[2]=='G' and !posicionamiento){
          if (terreno[1]=='G'){
            // Si las tres casillas coinciden
            if (terreno[3]=='G'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='G' and !posicionamiento){
          if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='G' and !posicionamiento){
          proximaAccion=actTURN_SR;
        }

        // SUELO ARENOSO
        else if (terreno[2]=='T'){
          if (terreno[1]=='T'){
            // Si las tres casillas coinciden
            if (terreno[3]=='T'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='T'){
          if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='T'){
          proximaAccion=actTURN_SR;
        }

        // AGUA CON BIKINI
        else if (bikini){
          if (terreno[2]=='A'){
            if (terreno[1]=='A'){
              // Si las tres casillas coinciden
              if (terreno[3]=='A'){
                // Si la 2 es la menos visitada
                if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)] and
                  mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                  proximaAccion=actFORWARD;
                }
                // Si la 1 es la menos visitada
                else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 3 es la menos visitada
                else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                  proximaAccion=actTURN_SR;
                }
                else {
                  proximaAccion=actFORWARD;
                }
              }
              // Si sólo coinciden la 1 y la 2
              else {
                // Si la 1 es la menos visitada
                if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 2 es la menos visitada
                else {
                  proximaAccion=actFORWARD;
                }
              }
            }
            // Si sólo coinciden la 2 y la 3
            else if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo lo es la 2
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si coinciden la 1 y la 3
          else if (terreno[1]=='A'){
            if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              // Si la 1 es la menos visitada
              else {
                proximaAccion=actTURN_SL;
              }
            }
            // Si sólo lo es la 1
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 3
          else if (terreno[3]=='A'){
            proximaAccion=actTURN_SR;
          }
        }

        // BOSQUE (CON O SIN ZAPATILLAS)
        else if (terreno[2]=='B'){
          if (terreno[1]=='B'){
            // Si las tres casillas coinciden
            if (terreno[3]=='B'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='B'){
          if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='B'){
          proximaAccion=actTURN_SR;
        }
        
        // AGUA SIN BIKINI
        /*else if (terreno[2]=='A'){
          if (terreno[1]=='A'){
            // Si las tres casillas coinciden
            if (terreno[3]=='A'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='A'){
          if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='A'){
          proximaAccion=actTURN_SR;
        }*/
        else {
          proximaAccion=actTURN_SL;
        }
      break;
      case este:
        // SUELO PEDREGOSO
        if (terreno[2]=='S'){
          if (terreno[1]=='S'){
            // Si las tres casillas coinciden
            if (terreno[3]=='S'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil-1)][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='S'){
          if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='S'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA BIKINI
        if (!bikini and terreno[2]=='K'){
          if (terreno[1]=='K'){
            // Si las tres casillas coinciden
            if (terreno[3]=='K'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!bikini and terreno[1]=='K'){
          if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!bikini and terreno[3]=='K'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA ZAPATILLAS
        else if (!zapatillas and terreno[2]=='D'){
          if (terreno[1]=='D'){
            // Si las tres casillas coinciden
            if (terreno[3]=='D'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!zapatillas and terreno[1]=='D'){
          if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!zapatillas and terreno[3]=='D'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA POSICIONAMIENTO
        else if (terreno[2]=='G' and !posicionamiento){
          if (terreno[1]=='G'){
            // Si las tres casillas coinciden
            if (terreno[3]=='G'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='G' and !posicionamiento){
          if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='G' and !posicionamiento){
          proximaAccion=actTURN_SR;
        }

        // SUELO ARENOSO
        else if (terreno[2]=='T'){
          if (terreno[1]=='T'){
            // Si las tres casillas coinciden
            if (terreno[3]=='T'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='T'){
          if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='T'){
          proximaAccion=actTURN_SR;
        }

        // AGUA CON BIKINI
        else if (bikini){
          if (terreno[2]=='A'){
            if (terreno[1]=='A'){
              // Si las tres casillas coinciden
              if (terreno[3]=='A'){
                // Si la 2 es la menos visitada
                if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1] and
                  mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                  proximaAccion=actFORWARD;
                }
                // Si la 1 es la menos visitada
                else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 3 es la menos visitada
                else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                  proximaAccion=actTURN_SR;
                }
                else{
                  proximaAccion=actFORWARD;
                }
              }
              // Si sólo coinciden la 1 y la 2
              else {
                // Si la 1 es la menos visitada
                if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 2 es la menos visitada
                else {
                  proximaAccion=actFORWARD;
                }
              }
            }
            // Si sólo coinciden la 2 y la 3
            else if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo lo es la 2
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si coinciden la 1 y la 3
          else if (terreno[1]=='A'){
            if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              // Si la 1 es la menos visitada
              else {
                proximaAccion=actTURN_SL;
              }
            }
            // Si sólo lo es la 1
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 3
          else if (terreno[3]=='A'){
            proximaAccion=actTURN_SR;
          }
        }

        // BOSQUE (CON O SIN ZAPATILLAS)
        else if (terreno[2]=='B'){
          if (terreno[1]=='B'){
            // Si las tres casillas coinciden
            if (terreno[3]=='B'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='B'){
          if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='B'){
          proximaAccion=actTURN_SR;
        }
        
        // AGUA SIN BIKINI
        /*else if (terreno[2]=='A'){
          if (terreno[1]=='A'){
            // Si las tres casillas coinciden
            if (terreno[3]=='A'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='A'){
          if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='A'){
          proximaAccion=actTURN_SR;
        }*/
        else {
          proximaAccion=actTURN_SL;
        }
      break;
      case sureste:
        // SUELO PEDREGOSO
        if (terreno[2]=='S'){
          if (terreno[1]=='S'){
            // Si las tres casillas coinciden
            if (terreno[3]=='S'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='S'){
          if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='S'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA BIKINI
        if (!bikini and terreno[2]=='K'){
          if (terreno[1]=='K'){
            // Si las tres casillas coinciden
            if (terreno[3]=='K'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!bikini and terreno[1]=='K'){
          if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!bikini and terreno[3]=='K'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA ZAPATILLAS
        else if (!zapatillas and terreno[2]=='D'){
          if (terreno[1]=='D'){
            // Si las tres casillas coinciden
            if (terreno[3]=='D'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!zapatillas and terreno[1]=='D'){
          if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!zapatillas and terreno[3]=='D'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA POSICIONAMIENTO
        else if (terreno[2]=='G' and !posicionamiento){
          if (terreno[1]=='G'){
            // Si las tres casillas coinciden
            if (terreno[3]=='G'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='G' and !posicionamiento){
          if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='G' and !posicionamiento){
          proximaAccion=actTURN_SR;
        }

        // SUELO ARENOSO
        else if (terreno[2]=='T'){
          if (terreno[1]=='T'){
            // Si las tres casillas coinciden
            if (terreno[3]=='T'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='T'){
          if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='T'){
          proximaAccion=actTURN_SR;
        }

        // AGUA CON BIKINI
        else if (bikini){
          if (terreno[2]=='A'){
            if (terreno[1]=='A'){
              // Si las tres casillas coinciden
              if (terreno[3]=='A'){
                // Si la 2 es la menos visitada
                if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1] and
                  mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                  proximaAccion=actFORWARD;
                }
                // Si la 1 es la menos visitada
                else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 3 es la menos visitada
                else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                  proximaAccion=actTURN_SR;
                }
                else{
                  proximaAccion=actFORWARD;
                }
              }
              // Si sólo coinciden la 1 y la 2
              else {
                // Si la 1 es la menos visitada
                if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 2 es la menos visitada
                else {
                  proximaAccion=actFORWARD;
                }
              }
            }
            // Si sólo coinciden la 2 y la 3
            else if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo lo es la 2
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si coinciden la 1 y la 3
          else if (terreno[1]=='A'){
            if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              // Si la 1 es la menos visitada
              else {
                proximaAccion=actTURN_SL;
              }
            }
            // Si sólo lo es la 1
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 3
          else if (terreno[3]=='A'){
            proximaAccion=actTURN_SR;
          }
        }

        // BOSQUE (CON O SIN ZAPATILLAS)
        else if (terreno[2]=='B'){
          if (terreno[1]=='B'){
            // Si las tres casillas coinciden
            if (terreno[3]=='B'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='B'){
          if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='B'){
          proximaAccion=actTURN_SR;
        }
        
        // AGUA SIN BIKINI
        /*else if (terreno[2]=='A'){
          if (terreno[1]=='A'){
            // Si las tres casillas coinciden
            if (terreno[3]=='A'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='A'){
          if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='A'){
          proximaAccion=actTURN_SR;
        }*/
        else {
          proximaAccion=actTURN_SL;
        }
      break;
      case sur:
        // SUELO PEDREGOSO
        if (terreno[2]=='S'){
          if (terreno[1]=='S'){
            // Si las tres casillas coinciden
            if (terreno[3]=='S'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='S'){
          if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='S'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA BIKINI
        if (!bikini and terreno[2]=='K'){
          if (terreno[1]=='K'){
            // Si las tres casillas coinciden
            if (terreno[3]=='K'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!bikini and terreno[1]=='K'){
          if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!bikini and terreno[3]=='K'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA ZAPATILLAS
        else if (!zapatillas and terreno[2]=='D'){
          if (terreno[1]=='D'){
            // Si las tres casillas coinciden
            if (terreno[3]=='D'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!zapatillas and terreno[1]=='D'){
          if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!zapatillas and terreno[3]=='D'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA POSICIONAMIENTO
        else if (terreno[2]=='G' and !posicionamiento){
          if (terreno[1]=='G'){
            // Si las tres casillas coinciden
            if (terreno[3]=='G'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='G' and !posicionamiento){
          if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='G' and !posicionamiento){
          proximaAccion=actTURN_SR;
        }

        // SUELO ARENOSO
        else if (terreno[2]=='T'){
          if (terreno[1]=='T'){
            // Si las tres casillas coinciden
            if (terreno[3]=='T'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='T'){
          if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='T'){
          proximaAccion=actTURN_SR;
        }

        // AGUA CON BIKINI
        else if (bikini){
          if (terreno[2]=='A'){
            if (terreno[1]=='A'){
              // Si las tres casillas coinciden
              if (terreno[3]=='A'){
                // Si la 2 es la menos visitada
                if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1] and
                  mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                  proximaAccion=actFORWARD;
                }
                // Si la 1 es la menos visitada
                else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 3 es la menos visitada
                else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                  proximaAccion=actTURN_SR;
                }
                else{
                  proximaAccion=actFORWARD;
                }
              }
              // Si sólo coinciden la 1 y la 2
              else {
                // Si la 1 es la menos visitada
                if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 2 es la menos visitada
                else {
                  proximaAccion=actFORWARD;
                }
              }
            }
            // Si sólo coinciden la 2 y la 3
            else if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo lo es la 2
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si coinciden la 1 y la 3
          else if (terreno[1]=='A'){
            if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              // Si la 1 es la menos visitada
              else {
                proximaAccion=actTURN_SL;
              }
            }
            // Si sólo lo es la 1
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 3
          else if (terreno[3]=='A'){
            proximaAccion=actTURN_SR;
          }
        }

        // BOSQUE (CON O SIN ZAPATILLAS)
        else if (terreno[2]=='B'){
          if (terreno[1]=='B'){
            // Si las tres casillas coinciden
            if (terreno[3]=='B'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='B'){
          if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='B'){
          proximaAccion=actTURN_SR;
        }
        
        // AGUA SIN BIKINI
        /*else if (terreno[2]=='A'){
          if (terreno[1]=='A'){
            // Si las tres casillas coinciden
            if (terreno[3]=='A'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)+1] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='A'){
          if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)+1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='A'){
          proximaAccion=actTURN_SR;
        }*/
        else {
          proximaAccion=actTURN_SL;
        }
      break;
      case suroeste:
        // SUELO PEDREGOSO
        if (terreno[2]=='S'){
          if (terreno[1]=='S'){
            // Si las tres casillas coinciden
            if (terreno[3]=='S'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='S'){
          if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='S'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA BIKINI
        if (!bikini and terreno[2]=='K'){
          if (terreno[1]=='K'){
            // Si las tres casillas coinciden
            if (terreno[3]=='K'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!bikini and terreno[1]=='K'){
          if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!bikini and terreno[3]=='K'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA ZAPATILLAS
        else if (!zapatillas and terreno[2]=='D'){
          if (terreno[1]=='D'){
            // Si las tres casillas coinciden
            if (terreno[3]=='D'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!zapatillas and terreno[1]=='D'){
          if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!zapatillas and terreno[3]=='D'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA POSICIONAMIENTO
        else if (terreno[2]=='G' and !posicionamiento){
          if (terreno[1]=='G'){
            // Si las tres casillas coinciden
            if (terreno[3]=='G'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='G' and !posicionamiento){
          if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='G' and !posicionamiento){
          proximaAccion=actTURN_SR;
        }

        // SUELO ARENOSO
        else if (terreno[2]=='T'){
          if (terreno[1]=='T'){
            // Si las tres casillas coinciden
            if (terreno[3]=='T'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='T'){
          if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='T'){
          proximaAccion=actTURN_SR;
        }

        // AGUA CON BIKINI
        else if (bikini){
          if (terreno[2]=='A'){
            if (terreno[1]=='A'){
              // Si las tres casillas coinciden
              if (terreno[3]=='A'){
                // Si la 2 es la menos visitada
                if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)] and
                  mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                  proximaAccion=actFORWARD;
                }
                // Si la 1 es la menos visitada
                else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 3 es la menos visitada
                else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                  proximaAccion=actTURN_SR;
                }
                else{
                  proximaAccion=actFORWARD;
                }
              }
              // Si sólo coinciden la 1 y la 2
              else {
                // Si la 1 es la menos visitada
                if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 2 es la menos visitada
                else {
                  proximaAccion=actFORWARD;
                }
              }
            }
            // Si sólo coinciden la 2 y la 3
            else if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo lo es la 2
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si coinciden la 1 y la 3
          else if (terreno[1]=='A'){
            if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              // Si la 1 es la menos visitada
              else {
                proximaAccion=actTURN_SL;
              }
            }
            // Si sólo lo es la 1
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 3
          else if (terreno[3]=='A'){
            proximaAccion=actTURN_SR;
          }
        }

        // BOSQUE (CON O SIN ZAPATILLAS)
        else if (terreno[2]=='B'){
          if (terreno[1]=='B'){
            // Si las tres casillas coinciden
            if (terreno[3]=='B'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='B'){
          if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='B'){
          proximaAccion=actTURN_SR;
        }
        
        // AGUA SIN BIKINI
        /*else if (terreno[2]=='A'){
          if (terreno[1]=='A'){
            // Si las tres casillas coinciden
            if (terreno[3]=='A'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)] and
                mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]<mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='A'){
          if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='A'){
          proximaAccion=actTURN_SR;
        }*/
        else {
          proximaAccion=actTURN_SL;
        }
      break;
      case oeste:
        // SUELO PEDREGOSO
        if (terreno[2]=='S'){
          if (terreno[1]=='S'){
            // Si las tres casillas coinciden
            if (terreno[3]=='S'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil+1)][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='S'){
          if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='S'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA BIKINI
        if (!bikini and terreno[2]=='K'){
          if (terreno[1]=='K'){
            // Si las tres casillas coinciden
            if (terreno[3]=='K'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!bikini and terreno[1]=='K'){
          if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!bikini and terreno[3]=='K'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA ZAPATILLAS
        else if (!zapatillas and terreno[2]=='D'){
          if (terreno[1]=='D'){
            // Si las tres casillas coinciden
            if (terreno[3]=='D'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!zapatillas and terreno[1]=='D'){
          if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!zapatillas and terreno[3]=='D'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA POSICIONAMIENTO
        else if (terreno[2]=='G' and !posicionamiento){
          if (terreno[1]=='G'){
            // Si las tres casillas coinciden
            if (terreno[3]=='G'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='G' and !posicionamiento){
          if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='G' and !posicionamiento){
          proximaAccion=actTURN_SR;
        }

        // SUELO ARENOSO
        else if (terreno[2]=='T'){
          if (terreno[1]=='T'){
            // Si las tres casillas coinciden
            if (terreno[3]=='T'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='T'){
          if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='T'){
          proximaAccion=actTURN_SR;
        }

        // AGUA CON BIKINI
        else if (bikini){
          if (terreno[2]=='A'){
            if (terreno[1]=='A'){
              // Si las tres casillas coinciden
              if (terreno[3]=='A'){
                // Si la 2 es la menos visitada
                if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1] and
                  mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                  proximaAccion=actFORWARD;
                }
                // Si la 1 es la menos visitada
                else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 3 es la menos visitada
                else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                  proximaAccion=actTURN_SR;
                }
                else{
                  proximaAccion=actFORWARD;
                }
              }
              // Si sólo coinciden la 1 y la 2
              else {
                // Si la 1 es la menos visitada
                if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 2 es la menos visitada
                else {
                  proximaAccion=actFORWARD;
                }
              }
            }
            // Si sólo coinciden la 2 y la 3
            else if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo lo es la 2
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si coinciden la 1 y la 3
          else if (terreno[1]=='A'){
            if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              // Si la 1 es la menos visitada
              else {
                proximaAccion=actTURN_SL;
              }
            }
            // Si sólo lo es la 1
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 3
          else if (terreno[3]=='A'){
            proximaAccion=actTURN_SR;
          }
        }

        // BOSQUE (CON O SIN ZAPATILLAS)
        else if (terreno[2]=='B'){
          if (terreno[1]=='B'){
            // Si las tres casillas coinciden
            if (terreno[3]=='B'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='B'){
          if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='B'){
          proximaAccion=actTURN_SR;
        }
        
        // AGUA SIN BIKINI
        /*else if (terreno[2]=='A'){
          if (terreno[1]=='A'){
            // Si las tres casillas coinciden
            if (terreno[3]=='A'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)+1][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='A'){
          if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)+1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='A'){
          proximaAccion=actTURN_SR;
        }*/
        else {
          proximaAccion=actTURN_SL;
        }
      break;
      case noroeste:
        // SUELO PEDREGOSO
        if (terreno[2]=='S'){
          if (terreno[1]=='S'){
            // Si las tres casillas coinciden
            if (terreno[3]=='S'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='S'){
          if (terreno[3]=='S'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='S'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA BIKINI
        if (!bikini and terreno[2]=='K'){
          if (terreno[1]=='K'){
            // Si las tres casillas coinciden
            if (terreno[3]=='K'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!bikini and terreno[1]=='K'){
          if (terreno[3]=='K'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!bikini and terreno[3]=='K'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA ZAPATILLAS
        else if (!zapatillas and terreno[2]=='D'){
          if (terreno[1]=='D'){
            // Si las tres casillas coinciden
            if (terreno[3]=='D'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (!zapatillas and terreno[1]=='D'){
          if (terreno[3]=='D'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (!zapatillas and terreno[3]=='D'){
          proximaAccion=actTURN_SR;
        }

        // CASILLA POSICIONAMIENTO
        else if (terreno[2]=='G' and !posicionamiento){
          if (terreno[1]=='G'){
            // Si las tres casillas coinciden
            if (terreno[3]=='G'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='G' and !posicionamiento){
          if (terreno[3]=='G'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='G' and !posicionamiento){
          proximaAccion=actTURN_SR;
        }

        // SUELO ARENOSO
        else if (terreno[2]=='T'){
          if (terreno[1]=='T'){
            // Si las tres casillas coinciden
            if (terreno[3]=='T'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='T'){
          if (terreno[3]=='T'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='T'){
          proximaAccion=actTURN_SR;
        }

        // AGUA CON BIKINI
        else if (bikini){
          if (terreno[2]=='A'){
            if (terreno[1]=='A'){
              // Si las tres casillas coinciden
              if (terreno[3]=='A'){
                // Si la 2 es la menos visitada
                if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1] and
                  mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                  proximaAccion=actFORWARD;
                }
                // Si la 1 es la menos visitada
                else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 3 es la menos visitada
                else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                  proximaAccion=actTURN_SR;
                }
                else{
                  proximaAccion=actFORWARD;
                }
              }
              // Si sólo coinciden la 1 y la 2
              else {
                // Si la 1 es la menos visitada
                if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                  proximaAccion=actTURN_SL;
                }
                // Si la 2 es la menos visitada
                else {
                  proximaAccion=actFORWARD;
                }
              }
            }
            // Si sólo coinciden la 2 y la 3
            else if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo lo es la 2
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si coinciden la 1 y la 3
          else if (terreno[1]=='A'){
            if (terreno[3]=='A'){
              // Si la 3 es la menos visitada
              if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              // Si la 1 es la menos visitada
              else {
                proximaAccion=actTURN_SL;
              }
            }
            // Si sólo lo es la 1
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 3
          else if (terreno[3]=='A'){
            proximaAccion=actTURN_SR;
          }
        }

        // BOSQUE (CON O SIN ZAPATILLAS)
        else if (terreno[2]=='B'){
          if (terreno[1]=='B'){
            // Si las tres casillas coinciden
            if (terreno[3]=='B'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='B'){
          if (terreno[3]=='B'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='B'){
          proximaAccion=actTURN_SR;
        }
        
        // AGUA SIN BIKINI
        /*else if (terreno[2]=='A'){
          if (terreno[1]=='A'){
            // Si las tres casillas coinciden
            if (terreno[3]=='A'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actFORWARD;
              }
              // Si la 1 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]<mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SL;
              }
              // Si la 3 es la menos visitada
              else if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                proximaAccion=actTURN_SR;
              }
              else{
                proximaAccion=actFORWARD;
              }
            }
            // Si sólo coinciden la 1 y la 2
            else {
              // Si la 1 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                proximaAccion=actTURN_SL;
              }
              // Si la 2 es la menos visitada
              else {
                proximaAccion=actFORWARD;
              }
            }
          }
          // Si sólo coinciden la 2 y la 3
          else if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)-1][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 2 es la menos visitada
            else {
              proximaAccion=actFORWARD;
            }
          }
          // Si sólo lo es la 2
          else {
            proximaAccion=actFORWARD;
          }
        }
        // Si coinciden la 1 y la 3
        else if (terreno[1]=='A'){
          if (terreno[3]=='A'){
            // Si la 3 es la menos visitada
            if (mapaVisitas[(current_state.fil)][(current_state.col)-1]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
              proximaAccion=actTURN_SR;
            }
            // Si la 1 es la menos visitada
            else {
              proximaAccion=actTURN_SL;
            }
          }
          // Si sólo lo es la 1
          else {
            proximaAccion=actTURN_SL;
          }
        }
        // Si sólo lo es la 3
        else if (terreno[3]=='A'){
          proximaAccion=actTURN_SR;
        }*/
        else {
          proximaAccion=actTURN_SL;
        }
      break;
    }
    }
    else if (terreno[1]!='P'){
      proximaAccion=actTURN_SL;
    }
    else if (terreno[3]!='P'){
      proximaAccion=actTURN_SR;
    }
    else {
      proximaAccion=actTURN_BL;
    }

    return proximaAccion;
  }
};

#endif
