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
      state_ciego.fil = state_ciego.col = 99;
      state_ciego.brujula = norte;

      ultima.fil=-2;
      ultima.col=-2;
      actual.fil=-1;
      actual.col=-1;
      zapatillas=false;
      bikini=false;
      posicionamiento=false;
      bien_situado = false;
      contador_agua=0;
      contador_bosque=0;
      contador_pos=0;
      nivel_cero=true;

      vector<unsigned int> aux;
      for (unsigned int i = 0; i < 100; i++)
      {
        for (unsigned int j=0; j<100; j++){
          aux.push_back(0);
        }
        mapaVisitas.push_back(aux);
      }

      vector<unsigned char> aux2;
      for (unsigned int i = 0; i < 199; i++)
      {
        for (unsigned int j=0; j<199; j++){
          aux2.push_back('?');
        }
        mapaCiego.push_back(aux2);
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

  bool bien_situado;
  bool zapatillas; 
  bool bikini;
  bool posicionamiento;
  casilla ultima;
  casilla actual;
  int contador_agua, contador_bosque, contador_pos;

  //PARA EL NIVEL 1-3
  state state_ciego;
  bool nivel_cero;


  // INTENTO DE ACTUALIZACIÓN DE MAPA CUANDO LLEGUEMOS A LA CASILLA G 
    vector< vector< unsigned int> > mapaVisitas;
    vector< vector< unsigned char> > mapaCiego;
  Action proximaAccion;

  // DEVUELVE TRUE SI HAY ALGUNA CASILLA DE POSICIONAMIENTO A LA VISTA
  bool RodeadoPosicionamiento(const vector<unsigned char> &terreno){
    bool hay_pos = false;

    for (int i=0; i<16; i++){
      if (terreno[i]=='G'){
        hay_pos=true;
      }
    }

    return hay_pos;
  }

  // DEVUELVE TRUE SI ESTAMOS RODEADOS DE AGUA O SI SE DESCONOCE ALGUNA PARTE DEL TERRENO ALREDEDOR NUESTRA
  bool RodeadoLobo(const vector<unsigned char> &superf){
    bool hay_lobo = false;

    for (int i=0; i<16; i++){
      if (superf[i]=='l'){
        hay_lobo=true;
      }
    }

    return hay_lobo;
  }

  // DEVUELVE TRUE SI ESTAMOS RODEADOS DE AGUA O SI SE DESCONOCE ALGUNA PARTE DEL TERRENO ALREDEDOR NUESTRA
  bool RodeadoAgua(const vector<unsigned char> &terreno, const state &st, vector<vector<unsigned char>> &matriz){

    for (int i=-1; i<2; i++){
      for (int j=-1; j<2; j++){
        if (!(i==0 and j==0) and matriz[(current_state.fil)+i][(current_state.col)+j]!='A'){
          return false;
        }
      }
    }
    return true;
  }

  bool RodeadoBosque(const vector<unsigned char> &terreno, const state &st, vector<vector<unsigned char>> &matriz){

    for (int i=-1; i<2; i++){
      for (int j=-1; j<2; j++){
        if (!(i==0 and j==0) and matriz[(current_state.fil)+i][(current_state.col)+j]!='B'){
          if (matriz[(current_state.fil)+i][(current_state.col)+j]!='A' or (matriz[(current_state.fil)+i][(current_state.col)+j]=='A' and bikini)){
            return false;
          }
        }
      }
    }
    return true;
  }

  void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st, vector<vector<unsigned char>> &matriz){
    int count=0;

    switch(st.brujula){ 
      case norte:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.fil-i][st.col-i+j]=terreno[count];
              count++;
            }
          }
        break; //Si estaba mirando al norte
      case este:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.fil-i+j][st.col+i]=terreno[count];
              count++;
            }
          }
        break;
      case sur:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.fil+i][st.col-j+i]=terreno[count];
              count++;
            }
          }
        break;
      case oeste:
          for (int i=0; i<4; i++){
            for (int j=0; j<1+2*i; j++){
              matriz[st.fil+i-j][st.col-i]=terreno[count];
              count++;
            }
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

  // PARA PONER LAS CASILLAS QUE HEMOS VISTO MIENTRAS TENÍAMOS LOS SENSORES APAGADOS
  void PintarCasillasVistas(vector<vector<unsigned char>> &matriz, vector<vector<unsigned char>> &matriz2, const state &state_ciego, const Sensores &sensor){
    
    for (int i=0; i<matriz.size(); i++){
      for (int j=0; j<matriz.size(); j++){
        if (matriz[i][j]=='?'){
          matriz[i][j]=matriz2[(state_ciego.fil)-(sensor.posF)+i][(state_ciego.col)-(sensor.posC)+j];
        }
      }
    }
  }

  // PARA PINTAR LOS PRECIPICIOS DE LOS BORDES DESDE EL PRINCIPIO
  void PintarPrecipiciosBordes(const state &st, vector<vector<unsigned char>> &matriz){
    for (int i=0; i<3; i++){
      for (int j=0; j<matriz.size(); j++){
        matriz[i][j]='P';
      }
    }
    for (int i=0; i<matriz.size(); i++) {
      for (int j=0; j<3; j++){
        matriz[i][j]='P';
      }
    }
    for (int i=matriz.size()-3; i<matriz.size(); i++){
      for (int j=0; j<matriz.size(); j++){
        matriz[i][j]='P';
      }
    }
    for (int i=0; i<matriz.size(); i++){
      for (int j=matriz.size()-3; j<matriz.size(); j++){
        matriz[i][j]='P';
      }
    }
  }

  // PARA SABER HACIA DÓNDE MOVERNOS CUANDO NO ESTAMOS BUSCANDO CASILLA DE POSICIONAMIENTO
  Action GirarMenosVisitada(const vector<unsigned char> &terreno, const vector<unsigned char> &superficie, const state &current_state, vector<vector<unsigned char>> &matriz, vector<vector<unsigned int>> &mapaVisitas){
    
    if (RodeadoLobo(superficie)){
      if (superficie[1]=='l' or superficie[4]=='l' or superficie[9]=='l' or superficie[5]=='l' or superficie[10]=='l'){
        if (terreno[2]!='A' or bikini){
          proximaAccion=actTURN_SR;
        }
        else {
          proximaAccion=actTURN_BR;
        }
      }
      else if (superficie[3]=='l' or superficie[8]=='l' or superficie[15]=='l' or superficie[7]=='l' or superficie[14]=='l'){
        if (terreno[2]!='A' or bikini){
          proximaAccion=actTURN_SL;
        }
        else {
          proximaAccion=actTURN_SR;
        }
      }
      else if (superficie[2]=='l' or superficie[6]=='l' or superficie[12]=='l'){
        proximaAccion=actTURN_BL;
      }
    }

    else if (!zapatillas and terreno[2]=='D' and superficie[2]=='_'){
      proximaAccion=actFORWARD;
    }
    else if (!zapatillas and terreno[1]=='D'){
      proximaAccion=actTURN_SL;
    }
    else if (!zapatillas and terreno[3]=='D'){
      proximaAccion=actTURN_SR;
    }
    else if (!bikini and terreno[2]=='K' and superficie[2]=='_'){
      proximaAccion=actFORWARD;
    }
    else if (!bikini and terreno[1]=='K'){
      proximaAccion=actTURN_SL;
    }
    else if (!bikini and terreno[3]=='K'){
      proximaAccion=actTURN_SR;
    }

    else if (terreno[2]=='M'){
      if (terreno[1]!='M' and terreno[3]!='M'){
        if (terreno[5]=='M'){
          proximaAccion=actTURN_SR;
          return proximaAccion;
        }
        else if (terreno[7]=='M'){
          proximaAccion=actTURN_SL;
          return proximaAccion;
        }
      }
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
      if (terreno[2]!='P' and superficie[2]=='_'){
        proximaAccion=actFORWARD;
        return proximaAccion;
      }
      else {
        proximaAccion=actTURN_BL;
        return proximaAccion;
      }
    }
    else if (terreno[1]=='M' and terreno[2]!='P' ){
      if (terreno[7]=='M' and superficie[2]=='_'){
        proximaAccion=actFORWARD;
        return proximaAccion;
      }
      proximaAccion=actTURN_SL;
      return proximaAccion;
    }
    else if (terreno[3]=='M' and terreno[2]!='P'){
      if (terreno[5]=='M' and superficie[2]=='_'){
        proximaAccion=actFORWARD;
        return proximaAccion;
      }
      proximaAccion=actTURN_SR;
      return proximaAccion;
    }

    else if (terreno[2]!='P' and superficie[2]=='_'){
    switch (current_state.brujula){
      case norte:
        // SUELO PEDREGOSO
        if (terreno[2]=='S'){
          if (terreno[1]=='S'){
            // Si las tres casillas coinciden
            if (terreno[3]=='S'){
              // Si la 2 es la menos visitada
              if (mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)-1] and
                mapaVisitas[(current_state.fil)-1][(current_state.col)]<mapaVisitas[(current_state.fil)-1][(current_state.col)+1] ){
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
        /*else if (!bikini and terreno[2]=='K'){
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
        }*/

        // CASILLA ZAPATILLAS
        /*else if (!zapatillas and terreno[2]=='D'){
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
        }*/

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

        // BOSQUE CON ZAPATILLAS
        else if (terreno[2]=='B' and zapatillas){
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
        else if (terreno[1]=='B' and zapatillas){
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
        else if (terreno[3]=='B' and zapatillas){
          proximaAccion=actTURN_SR;
        }

        // BOSQUE SIN ZAPATILLAS
        // Si estamos rodeados de bosque nos movemos hacia delante
        else if (RodeadoBosque(terreno,current_state,matriz) and terreno[2]=='B'){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (terreno[2]=='B' and contador_bosque<1){
          proximaAccion=actTURN_BL;
          contador_bosque++;
        }
        else if (terreno[2]=='B' and contador_bosque>=1){
          proximaAccion=actTURN_SL;
          contador_bosque=0;
        }
        
        // AGUA SIN BIKINI -- LO ESTOY PROBANDO
        // Si estamos rodeados de agua nos movemos hacia delante
        else if (RodeadoAgua(terreno,current_state,matriz)){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (contador_agua<1){
          proximaAccion=actTURN_BL;
          contador_agua++;
        }
        else {
          proximaAccion=actTURN_SL;
          contador_agua=0;
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
        /*else if (!bikini and terreno[2]=='K'){
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
        }*/

        // CASILLA ZAPATILLAS
        /*else if (!zapatillas and terreno[2]=='D'){
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
        }*/

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

        // BOSQUE CON ZAPATILLAS
        else if (terreno[2]=='B' and zapatillas){
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
        else if (terreno[1]=='B' and zapatillas){
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
        else if (terreno[3]=='B' and zapatillas){
          proximaAccion=actTURN_SR;
        }
        
        // BOSQUE SIN ZAPATILLAS
        // Si estamos rodeados de bosque nos movemos hacia delante
        else if (RodeadoBosque(terreno,current_state,matriz) and terreno[2]=='B'){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (terreno[2]=='B' and contador_bosque<1){
          proximaAccion=actTURN_BL;
          contador_bosque++;
        }
        else if (terreno[2]=='B' and contador_bosque>=1){
          proximaAccion=actTURN_SL;
          contador_bosque=0;
        }
        
        // AGUA SIN BIKINI -- LO ESTOY PROBANDO
        // Si estamos rodeados de agua nos movemos hacia delante
        else if (RodeadoAgua(terreno,current_state,matriz)){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (contador_agua<1){
          proximaAccion=actTURN_BL;
          contador_agua++;
        }
        else {
          proximaAccion=actTURN_SL;
          contador_agua=0;
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
        /*else if (!bikini and terreno[2]=='K'){
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
        }*/

        // CASILLA ZAPATILLAS
        /*else if (!zapatillas and terreno[2]=='D'){
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
        }*/

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

        // BOSQUE CON ZAPATILLAS
        else if (terreno[2]=='B' and zapatillas){
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
        else if (terreno[1]=='B' and zapatillas){
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
        else if (terreno[3]=='B' and zapatillas){
          proximaAccion=actTURN_SR;
        }
        
        // BOSQUE SIN ZAPATILLAS
        // Si estamos rodeados de bosque nos movemos hacia delante
        else if (RodeadoBosque(terreno,current_state,matriz) and terreno[2]=='B'){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (terreno[2]=='B' and contador_bosque<1){
          proximaAccion=actTURN_BL;
          contador_bosque++;
        }
        else if (terreno[2]=='B' and contador_bosque>=1){
          proximaAccion=actTURN_SL;
          contador_bosque=0;
        }
        
        // AGUA SIN BIKINI -- LO ESTOY PROBANDO
        // Si estamos rodeados de agua nos movemos hacia delante
        else if (RodeadoAgua(terreno,current_state,matriz)){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (contador_agua<1){
          proximaAccion=actTURN_BL;
          contador_agua++;
        }
        else {
          proximaAccion=actTURN_SL;
          contador_agua=0;
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
        /*else if (!bikini and terreno[2]=='K'){
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
        }*/

        // CASILLA ZAPATILLAS
        /*else if (!zapatillas and terreno[2]=='D'){
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
        }*/

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

        // BOSQUE CON ZAPATILLAS
        else if (terreno[2]=='B' and zapatillas){
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
        else if (terreno[1]=='B' and zapatillas){
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
        else if (terreno[3]=='B' and zapatillas){
          proximaAccion=actTURN_SR;
        }
        
        // BOSQUE SIN ZAPATILLAS
        // Si estamos rodeados de bosque nos movemos hacia delante
        else if (RodeadoBosque(terreno,current_state,matriz) and terreno[2]=='B'){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (terreno[2]=='B' and contador_bosque<1){
          proximaAccion=actTURN_BL;
          contador_bosque++;
        }
        else if (terreno[2]=='B' and contador_bosque>=1){
          proximaAccion=actTURN_SL;
          contador_bosque=0;
        }
        
        // AGUA SIN BIKINI -- LO ESTOY PROBANDO
        // Si estamos rodeados de agua nos movemos hacia delante
        else if (RodeadoAgua(terreno,current_state,matriz)){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (contador_agua<1){
          proximaAccion=actTURN_BL;
          contador_agua++;
        }
        else {
          proximaAccion=actTURN_SL;
          contador_agua=0;
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
        else if (terreno[1]=='S' and zapatillas){
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
        else if (terreno[3]=='S' and zapatillas){
          proximaAccion=actTURN_SR;
        }

        // CASILLA BIKINI
        /*else if (!bikini and terreno[2]=='K'){
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
        }*/

        // CASILLA ZAPATILLAS
        /*else if (!zapatillas and terreno[2]=='D'){
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
        }*/

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

        // BOSQUE CON ZAPATILLAS
        else if (terreno[2]=='B' and zapatillas){
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
        else if (terreno[1]=='B' and zapatillas){
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
        else if (terreno[3]=='B' and zapatillas){
          proximaAccion=actTURN_SR;
        }
        
        // BOSQUE SIN ZAPATILLAS
        // Si estamos rodeados de bosque nos movemos hacia delante
        else if (RodeadoBosque(terreno,current_state,matriz) and terreno[2]=='B'){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (terreno[2]=='B' and contador_bosque<1){
          proximaAccion=actTURN_BL;
          contador_bosque++;
        }
        else if (terreno[2]=='B' and contador_bosque>=1){
          proximaAccion=actTURN_SL;
          contador_bosque=0;
        }
        
        // AGUA SIN BIKINI -- LO ESTOY PROBANDO
        // Si estamos rodeados de agua nos movemos hacia delante
        else if (RodeadoAgua(terreno,current_state,matriz)){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (contador_agua<1){
          proximaAccion=actTURN_BL;
          contador_agua++;
        }
        else {
          proximaAccion=actTURN_SL;
          contador_agua=0;
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
        /*else if (!bikini and terreno[2]=='K'){
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
        }*/

        // CASILLA ZAPATILLAS
        /*else if (!zapatillas and terreno[2]=='D'){
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
        }*/

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

        // BOSQUE CON ZAPATILLAS
        else if (terreno[2]=='B' and zapatillas){
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
        else if (terreno[1]=='B' and zapatillas){
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
        else if (terreno[3]=='B' and zapatillas){
          proximaAccion=actTURN_SR;
        }
        
        // BOSQUE SIN ZAPATILLAS
        // Si estamos rodeados de bosque nos movemos hacia delante
        else if (RodeadoBosque(terreno,current_state,matriz) and terreno[2]=='B'){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (terreno[2]=='B' and contador_bosque<1){
          proximaAccion=actTURN_BL;
          contador_bosque++;
        }
        else if (terreno[2]=='B' and contador_bosque>=1){
          proximaAccion=actTURN_SL;
          contador_bosque=0;
        }
        
        // AGUA SIN BIKINI -- LO ESTOY PROBANDO
        // Si estamos rodeados de agua nos movemos hacia delante
        else if (RodeadoAgua(terreno,current_state,matriz)){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (contador_agua<1){
          proximaAccion=actTURN_BL;
          contador_agua++;
        }
        else {
          proximaAccion=actTURN_SL;
          contador_agua=0;
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
        /*else if (!bikini and terreno[2]=='K'){
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
        }*/

        // CASILLA ZAPATILLAS
        /*else if (!zapatillas and terreno[2]=='D'){
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
        }*/

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

        // BOSQUE CON ZAPATILLAS
        else if (terreno[2]=='B' and zapatillas){
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
        else if (terreno[1]=='B' and zapatillas){
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
        else if (terreno[3]=='B' and zapatillas){
          proximaAccion=actTURN_SR;
        }
        
        // BOSQUE SIN ZAPATILLAS
        // Si estamos rodeados de bosque nos movemos hacia delante
        else if (RodeadoBosque(terreno,current_state,matriz) and terreno[2]=='B'){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (terreno[2]=='B' and contador_bosque<1){
          proximaAccion=actTURN_BL;
          contador_bosque++;
        }
        else if (terreno[2]=='B' and contador_bosque>=1){
          proximaAccion=actTURN_SL;
          contador_bosque=0;
        }
        
        // AGUA SIN BIKINI -- LO ESTOY PROBANDO
        // Si estamos rodeados de agua nos movemos hacia delante
        else if (RodeadoAgua(terreno,current_state,matriz)){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (contador_agua<1){
          proximaAccion=actTURN_BL;
          contador_agua++;
        }
        else {
          proximaAccion=actTURN_SL;
          contador_agua=0;
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
        /*else if (!bikini and terreno[2]=='K'){
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
        }*/

        // CASILLA ZAPATILLAS
        /*else if (!zapatillas and terreno[2]=='D'){
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
        }*/

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

        // BOSQUE CON ZAPATILLAS
        else if (terreno[2]=='B' and zapatillas){
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
        else if (terreno[1]=='B' and zapatillas){
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
        else if (terreno[3]=='B' and zapatillas){
          proximaAccion=actTURN_SR;
        }
        
        // BOSQUE SIN ZAPATILLAS
        // Si estamos rodeados de bosque nos movemos hacia delante
        else if (RodeadoBosque(terreno,current_state,matriz) and terreno[2]=='B'){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (terreno[2]=='B' and contador_bosque<1){
          proximaAccion=actTURN_BL;
          contador_bosque++;
        }
        else if (terreno[2]=='B' and contador_bosque>=1){
          proximaAccion=actTURN_SL;
          contador_bosque=0;
        }
        
        // AGUA SIN BIKINI -- LO ESTOY PROBANDO
        // Si estamos rodeados de agua nos movemos hacia delante
        else if (RodeadoAgua(terreno,current_state,matriz)){
          proximaAccion=actFORWARD;
        }
        // Si no lo estamos, giramos hasta que encontremos la casilla que no es agua
        else if (contador_agua<1){
          proximaAccion=actTURN_BL;
          contador_agua++;
        }
        else {
          proximaAccion=actTURN_SL;
          contador_agua=0;
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

  // PARA SABER HACIA DÓNDE MOVERNOS SI ESTAMOS BUSCANDO CASILLA DE POSICIONAMIENTO
  Action GirarCiego(const vector<unsigned char> &terreno, const vector<unsigned char> &superficie, const state &state_ciego, vector<vector<unsigned char>> &matriz, vector<vector<unsigned char>> &mapaCiego){
    
    // Si tenemos un lobo a la vista, nos piramos
    if (RodeadoLobo(superficie)){
      if (superficie[1]=='l' or superficie[4]=='l' or superficie[9]=='l' or superficie[5]=='l' or superficie[10]=='l'){
        if (terreno[2]!='A' or bikini){
          proximaAccion=actTURN_SR;
        }
        else {
          proximaAccion=actTURN_BR;
        }
      }
      else if (superficie[3]=='l' or superficie[8]=='l' or superficie[15]=='l' or superficie[7]=='l' or superficie[14]=='l'){
        if (terreno[2]!='A' or bikini){
          proximaAccion=actTURN_SL;
        }
        else {
          proximaAccion=actTURN_SR;
        }
      }
      else if (superficie[2]=='l' or superficie[6]=='l' or superficie[12]=='l'){
        proximaAccion=actTURN_BL;
      }
    }

    // Si hay casilla de posicionamiento a la vista, vamos hacia ella
    else if (RodeadoPosicionamiento(terreno)){
      if (terreno[2]!='M' and terreno[2]!='P' and (terreno[2]=='G' or terreno[6]=='G' or terreno[12]=='G' or terreno[5]=='G'
        or terreno[7]=='G' or terreno[10]=='G' or terreno[11]=='G' or terreno[13]=='G' or terreno[14]=='G') and superficie[2]=='_'){
        proximaAccion=actFORWARD;
      }
      else if (terreno[1]=='G' or terreno[4]=='G' or terreno[9]=='G'){
        proximaAccion=actTURN_SL;
      }
      else if (terreno[3]=='G' or terreno[8]=='G' or terreno[15]=='G'){
        proximaAccion=actTURN_SR;
      }
    }
    // Si no hay casilla de posicionamiento a la vista nos movemos hacia lo que más nos interese
    else{
      if (terreno[2]=='P' or terreno[2]=='M'){
        proximaAccion=actTURN_SR;
        contador_pos++;
      }
      /*else if (contador_pos==2){
        proximaAccion=actTURN_SR;
        contador_pos++;
      }*/
      //else {
        if (((terreno[2]=='K' and !bikini) or (terreno[2]=='D' and !zapatillas) or (terreno[2]=='S') or terreno[2]=='T' or (terreno[2]=='A' and bikini)
          or (terreno[2]=='B' and zapatillas)) and superficie[2]=='_'){
          proximaAccion=actFORWARD;
        }
        else if (terreno[1]=='K' and !bikini){
          proximaAccion=actTURN_SL;
        }
        else if (terreno[3]=='K' and !bikini){
          proximaAccion=actTURN_SR;
        }
        /*else if (terreno[2]=='D' and !zapatillas and superficie[2]=='_'){
          proximaAccion=actFORWARD;
        }*/
        else if (terreno[1]=='D' and !zapatillas){
          proximaAccion=actTURN_SL;
        }
        else if (terreno[3]=='D' and !zapatillas){
          proximaAccion=actTURN_SR;
        }
        /*else if (terreno[2]=='S' and superficie[2]=='_'){
          proximaAccion=actFORWARD;
        }*/
        else if (terreno[1]=='S'){
          proximaAccion=actTURN_SL;
        }
        else if (terreno[3]=='S'){
          proximaAccion=actTURN_SR;
        }
        /*else if (terreno[2]=='T' and superficie[2]=='_'){
          proximaAccion=actFORWARD;
        }*/
        else if (terreno[1]=='T'){
          proximaAccion=actTURN_SL;
        }
        else if (terreno[3]=='T'){
          proximaAccion=actTURN_SR;
        }
        /*else if (terreno[2]=='A' and bikini and superficie[2]=='_'){
          proximaAccion=actFORWARD;
        }*/
        else if (terreno[1]=='A' and bikini){
          proximaAccion=actTURN_SL;
        }
        else if (terreno[3]=='A' and bikini){
          proximaAccion=actTURN_SR;
        }
        else if (terreno[2]=='B' and superficie[2]=='_'){
          proximaAccion=actFORWARD;
        }
        else if (terreno[1]=='B'){
          proximaAccion=actTURN_SL;
        }
        else if (terreno[3]=='B'){
          proximaAccion=actTURN_SR;
        }
        else if (terreno[2]=='A' and !bikini and superficie[2]=='_'){
          proximaAccion=actFORWARD;
        }
        else if (terreno[1]=='A' and !bikini){
          proximaAccion=actTURN_SL;
        }
        else if (terreno[3]=='A' and !bikini){
          proximaAccion=actTURN_SR;
        }

        if (proximaAccion==actFORWARD){
          contador_pos=0;
        }
      //}

    }
        
    return proximaAccion;
  }
};

#endif
