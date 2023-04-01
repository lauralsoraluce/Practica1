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

      zapatillas=false;
      bikini=false;
      /*girar_derecha = false;
      giro_grande = false;*/
      bien_situado = false;

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


  // INTENTO DE ACTUALIZACIÓN DE MAPA CUANDO LLEGUEMOS A LA CASILLA G 
    vector< vector< unsigned int> > mapaVisitas;
  casilla menosVisitada;
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

  Action GirarMenosVisitada(const vector<unsigned char> &terreno, const vector<unsigned char> &superficie, const state &st, vector<vector<unsigned char>> &matriz, vector<vector<unsigned int>> &matriz2){
    menosVisitada.fil=0;
    menosVisitada.col=0;
    bool picked=false;

    switch(current_state.brujula){
      case norte:
        for (int i=1; i<4; i++){
          if (terreno[i]!='P'){
            if (terreno[i]=='X'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!zapatillas and terreno[i]=='D'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!bikini and terreno[i]=='K'){
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              break;
            }
            else if (terreno[i]=='S' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)-2+i] or !picked)){
              menosVisitada.fil=(current_state.fil)-1;
              menosVisitada.col=(current_state.col)-2+i;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            else if (terreno[i]=='T' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)-2+i] or !picked)) {
              menosVisitada.fil=(current_state.fil)-1;
              menosVisitada.col=(current_state.col)-2+i;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            else if (bikini and terreno[i]=='A' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)-2+i] or !picked)){
              menosVisitada.fil=(current_state.fil)-1;
              menosVisitada.col=(current_state.col)-2+i;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            /*else if (zapatillas and terreno[i]=='B' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)-2+i] or !picked)){
              menosVisitada.fil=(current_state.fil)-1;
              menosVisitada.col=(current_state.col)-2+i;
              switch(i){
              case 1:
                proximaAccion=actFORWARD;
                break;
              case 2:
                proximaAccion=actTURN_SL;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }*/
            else if (terreno[i]=='B' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)-2+i] or !picked)){
              menosVisitada.fil=(current_state.fil)-1;
              menosVisitada.col=(current_state.col)-2+i;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            else if (terreno[i]=='A' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)-2+i] or !picked)){
              menosVisitada.fil=(current_state.fil)-1;
              menosVisitada.col=(current_state.col)-2+i;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            if (!picked){
              menosVisitada.fil=(current_state.fil)-1;
              menosVisitada.col=(current_state.col)-2+i;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
          }
          else {
            proximaAccion=actFORWARD;
            break;
          }
        }
      break;
      case sur:
        for (int i=1; i<4; i++){
          if (terreno[i]!='P'){
            if (terreno[i]=='X'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!zapatillas and terreno[i]=='D'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!bikini and terreno[i]=='K'){
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              break;
            }
            else if (terreno[i]=='S' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)+2-i] or !picked)){
              menosVisitada.fil=(current_state.fil)+1;
              menosVisitada.col=(current_state.col)-i+2;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            else if (terreno[i]=='T' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)+2-i] or !picked)){
              menosVisitada.fil=(current_state.fil)+1;
              menosVisitada.col=(current_state.col)-i+2;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            else if (bikini and terreno[i]=='A' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)+2-i] or !picked)){
              menosVisitada.fil=(current_state.fil)+1;
              menosVisitada.col=(current_state.col)-i+2;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            /*else if (zapatillas and terreno[i]=='B' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)+2-i] or !picked)){
              menosVisitada.fil=(current_state.fil)+1;
              menosVisitada.col=(current_state.col)-i+2;
              switch(i){
              case 1:
                proximaAccion=actFORWARD;
                break;
              case 2:
                proximaAccion=actTURN_SL;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }*/
            else if (terreno[i]=='B' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)+2-i] or !picked)){
              menosVisitada.fil=(current_state.fil)+1;
              menosVisitada.col=(current_state.col)-i+2;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            else if (terreno[i]=='A' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)+2-i] or !picked)){
              menosVisitada.fil=(current_state.fil)+1;
              menosVisitada.col=(current_state.col)-i+2;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            if (!picked){
              menosVisitada.fil=(current_state.fil)+1;
              menosVisitada.col=(current_state.col)-i+2;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
          }
          else {
            proximaAccion=actFORWARD;
            break;
          }
        }
      break;
      case este:
        for (int i=1; i<4; i++){
          if (terreno[i]!='P'){
            if (terreno[i]=='X'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!zapatillas and terreno[i]=='D'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!bikini and terreno[i]=='K'){
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              break;
            }
            else if (terreno[i]=='S' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-2+i][(current_state.col)+1] or !picked)){
              menosVisitada.fil=(current_state.fil)-2+i;
              menosVisitada.col=(current_state.col)+1;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            else if (terreno[i]=='T' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-2+i][(current_state.col)+1] or !picked)){
              menosVisitada.fil=(current_state.fil)-2+i;
              menosVisitada.col=(current_state.col)+1;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            else if (bikini and terreno[i]=='A' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-2+i][(current_state.col)+1] or !picked)){
              menosVisitada.fil=(current_state.fil)-2+i;
              menosVisitada.col=(current_state.col)+1;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            /*else if (zapatillas and terreno[i]=='B' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-2+i][(current_state.col)+1] or !picked)){
              menosVisitada.fil=(current_state.fil)-2+i;
              menosVisitada.col=(current_state.col)+1;
              switch(i){
              case 1:
                proximaAccion=actFORWARD;
                break;
              case 2:
                proximaAccion=actTURN_SL;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }*/
            else if (terreno[i]=='B' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-2+i][(current_state.col)+1] or !picked)){
              menosVisitada.fil=(current_state.fil)-2+i;
              menosVisitada.col=(current_state.col)+1;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            else if (terreno[i]=='A' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-2+i][(current_state.col)+1] or !picked)){
              menosVisitada.fil=(current_state.fil)-2+i;
              menosVisitada.col=(current_state.col)+1;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            if (!picked){
              menosVisitada.fil=(current_state.fil)-2+i;
              menosVisitada.col=(current_state.col)+1;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
          }
          else {
            proximaAccion=actFORWARD;
            break;
          }
        }
      break;
      case oeste:
        for (int i=1; i<4; i++){
          if (terreno[i]!='P'){
            if (terreno[i]=='X'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!zapatillas and terreno[i]=='D'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!bikini and terreno[i]=='K'){
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              break;
            }
            else if (terreno[i]=='S' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+2-i][(current_state.col)-1] or !picked)){
              menosVisitada.fil=(current_state.fil)+2-i;
              menosVisitada.col=(current_state.col)-1;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            else if (terreno[i]=='T' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+2-i][(current_state.col)-1] or !picked)){
              menosVisitada.fil=(current_state.fil)+2-i;
              menosVisitada.col=(current_state.col)-1;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            else if (bikini and terreno[i]=='A' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+2-i][(current_state.col)-1] or !picked)){
              menosVisitada.fil=(current_state.fil)+2-i;
              menosVisitada.col=(current_state.col)-1;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            /*else if (zapatillas and terreno[i]=='B' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+2-i][(current_state.col)-1] or !picked)){
              menosVisitada.fil=(current_state.fil)+2-i;
              menosVisitada.col=(current_state.col)-1;
              switch(i){
              case 1:
                proximaAccion=actFORWARD;
                break;
              case 2:
                proximaAccion=actTURN_SL;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }*/
            else if (terreno[i]=='B' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+2-i][(current_state.col)-1] or !picked)){
              menosVisitada.fil=(current_state.fil)+2-i;
              menosVisitada.col=(current_state.col)-1;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            else if (terreno[i]=='A' and (mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+2-i][(current_state.col)-1] or !picked)){
              menosVisitada.fil=(current_state.fil)+2-i;
              menosVisitada.col=(current_state.col)-1;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
            if (!picked){
              menosVisitada.fil=(current_state.fil)+2-i;
              menosVisitada.col=(current_state.col)-1;
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
          }
          else {
            proximaAccion=actTURN_SL;
            break;
          }
        }
      break;
      case noroeste:
        for (int i=1; i<4; i++){
          if (terreno[i]!='P'){
            if (terreno[i]=='X'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!zapatillas and terreno[i]=='D'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!bikini and terreno[i]=='K'){
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              break;
            }
            else if (terreno[i]=='S'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            else if (terreno[i]=='T') {
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            else if (bikini and terreno[i]=='A'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            /*else if (zapatillas and terreno[i]=='B'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }*/
            else if (terreno[i]=='B'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            else if (terreno[i]=='A'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)-1]){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)-1]){
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)]){
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            if (!picked){
              switch(i){
              case 1:
                menosVisitada.fil=(current_state.fil);
                menosVisitada.col=(current_state.col)-1;
                proximaAccion=actTURN_SL;
                break;
              case 2:
                menosVisitada.fil=(current_state.fil)-1;
                menosVisitada.col=(current_state.col)-1;
                proximaAccion=actFORWARD;
                break;
              case 3:
                menosVisitada.fil=(current_state.fil)-1;
                menosVisitada.col=(current_state.col);
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
          }
          else {
            proximaAccion=actFORWARD;
            break;
          }
        }
      break;
      case noreste:
        for (int i=1; i<4; i++){
          if (terreno[i]!='P'){
            if (terreno[i]=='X'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!zapatillas and terreno[i]=='D'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!bikini and terreno[i]=='K'){
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              break;
            }
            else if (terreno[i]=='S'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)]) {
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]) {
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)+1]) {
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            else if (terreno[i]=='T') {
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)]) {
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]) {
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)+1]) {
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            else if (bikini and terreno[i]=='A'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)]) {
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]) {
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)+1]) {
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            /*else if (zapatillas and terreno[i]=='B'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)]) {
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]) {
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)+1]) {
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }*/
            else if (terreno[i]=='B'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)]) {
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]) {
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)+1]) {
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            else if (terreno[i]=='A'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)]) {
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)-1][(current_state.col)+1]) {
                  menosVisitada.fil=(current_state.fil)-1;
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)+1]) {
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            if (!picked){
              switch(i){
              case 1:
                menosVisitada.fil=(current_state.fil)-1;
                menosVisitada.col=(current_state.col);
                proximaAccion=actTURN_SL;
                break;
              case 2:
                menosVisitada.fil=(current_state.fil)-1;
                menosVisitada.col=(current_state.col)+1;
                proximaAccion=actFORWARD;
                break;
              case 3:
                menosVisitada.fil=(current_state.fil);
                menosVisitada.col=(current_state.col)+1;
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
          }
          else {
            proximaAccion=actFORWARD;
            break;
          }
        }
      break;
      case sureste:
        for (int i=1; i<4; i++){
          if (terreno[i]!='P'){
            if (terreno[i]=='X'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!zapatillas and terreno[i]=='D'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!bikini and terreno[i]=='K'){
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              break;
            }
            else if (terreno[i]=='S'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            else if (terreno[i]=='T') {
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            else if (bikini and terreno[i]=='A'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            /*else if (zapatillas and terreno[i]=='B'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }*/
            else if (terreno[i]=='B'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            else if (terreno[i]=='A'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][(current_state.col)+1]){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)+1]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col)+1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][(current_state.col)]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            if (!picked){
              switch(i){
              case 1:
                menosVisitada.fil=(current_state.fil);
                menosVisitada.col=(current_state.col)+1;
                proximaAccion=actTURN_SL;
                break;
              case 2:
                menosVisitada.fil=(current_state.fil)+1;
                menosVisitada.col=(current_state.col)+1;
                proximaAccion=actFORWARD;
                break;
              case 3:
                menosVisitada.fil=(current_state.fil)+1;
                menosVisitada.col=(current_state.col);
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
          }
          else {
            proximaAccion=actFORWARD;
            break;
          }
        }
      break;
      case suroeste:
        for (int i=1; i<4; i++){
          if (terreno[i]!='P'){
            if (terreno[i]=='X'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!zapatillas and terreno[i]=='D'){
              switch(i){
                case 1:
                  proximaAccion=actTURN_SL;
                  break;
                case 2:
                  proximaAccion=actFORWARD;
                  break;
                case 3:
                  proximaAccion=actTURN_SR;
                  break;
              }
              break;
            }
            else if (!bikini and terreno[i]=='K'){
              switch(i){
              case 1:
                proximaAccion=actTURN_SL;
                break;
              case 2:
                proximaAccion=actFORWARD;
                break;
              case 3:
                proximaAccion=actTURN_SR;
                break;
              }
              break;
            }
            else if (terreno[i]=='S'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][current_state.col]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][current_state.col]-1){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][current_state.col]-1){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            else if (terreno[i]=='T') {
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][current_state.col]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][current_state.col]-1){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][current_state.col]-1){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            else if (bikini and terreno[i]=='A'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][current_state.col]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][current_state.col]-1){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][current_state.col]-1){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            /*else if (zapatillas and terreno[i]=='B'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][current_state.col]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][current_state.col]-1){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][current_state.col]-1){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }*/
            else if (terreno[i]=='B'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][current_state.col]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][current_state.col]-1){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][current_state.col]-1){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            else if (terreno[i]=='A'){
              switch(i){
              case 1:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][current_state.col]){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col);
                  proximaAccion=actTURN_SL;
                  picked=true;
                }
                break;
              case 2:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)+1][current_state.col]-1){
                  menosVisitada.fil=(current_state.fil)+1;
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actFORWARD;
                  picked=true;
                }
                break;
              case 3:
                if (!picked or mapaVisitas[menosVisitada.fil][menosVisitada.col]>mapaVisitas[(current_state.fil)][current_state.col]-1){
                  menosVisitada.fil=(current_state.fil);
                  menosVisitada.col=(current_state.col)-1;
                  proximaAccion=actTURN_SR;
                  picked=true;
                }
                break;
              }
            }
            if (!picked){
              switch(i){
              case 1:
                menosVisitada.fil=(current_state.fil)+1;
                menosVisitada.col=(current_state.col);
                proximaAccion=actTURN_SL;
                break;
              case 2:
                menosVisitada.fil=(current_state.fil)+1;
                menosVisitada.col=(current_state.col)-1;
                proximaAccion=actFORWARD;
                break;
              case 3:
                menosVisitada.fil=(current_state.fil);
                menosVisitada.col=(current_state.col)-1;
                proximaAccion=actTURN_SR;
                break;
              }
              picked=true;
            }
          }
          else {
            proximaAccion=actFORWARD;
            break;
          }
        }
      break;
    }

    return proximaAccion;
  }
};

#endif
