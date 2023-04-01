#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;



Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;

	cout << "Posicion: fila " << sensores.posF << " columna " << sensores.posC << " ";
	switch(sensores.sentido){
		case 0: cout << "Norte" << endl; break;
		case 1: cout << "Noreste" << endl; break;
		case 2: cout << "Este" << endl; break;
		case 3: cout << "Sureste" << endl; break;
		case 4: cout << "Sur " << endl; break;
		case 5: cout << "Suroeste" << endl; break;
		case 6: cout << "Oeste" << endl; break;
		case 7: cout << "Noroeste" << endl; break;
	}
	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << endl;

	int a;
	switch(last_action){
		case actFORWARD: //Si me muevo recto
			switch(current_state.brujula){ 
				case norte: current_state.fil--; break; //Si estaba mirando al norte
				case noreste: current_state.fil--; current_state.col++; break;
				case este: current_state.col++; break;
				case sureste: current_state.fil++; current_state.col++; break;
				case sur: current_state.fil++; break;
				case suroeste: current_state.fil++; current_state.col--; break;
				case oeste: current_state.col--; break;
				case noroeste: current_state.fil--; current_state.col--; break;
			}
			break;
		case actTURN_SL:
			a = current_state.brujula;
			a = (a+7) % 8; // Equivalente a (a-1)%8 -> giro 45 left
			current_state.brujula = static_cast<Orientacion>(a);
			break;
		case actTURN_SR:
		a = current_state.brujula;
			a = (a+1) % 8;
			current_state.brujula = static_cast<Orientacion>(a);
			break;
		case actTURN_BL:
		a = current_state.brujula;
			a = (a+5) % 8;
			current_state.brujula = static_cast<Orientacion>(a);
			break;
		case actTURN_BR:
		a = (a+3) % 8;
			current_state.brujula = static_cast<Orientacion>(a);
			break;
	}

	// 4
	if(sensores.posF != -1 and !bien_situado){
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true;
	}

	if (last_action==actFORWARD){
		if (sensores.terreno[0]=='K')
			bikini=true;
		else if (sensores.terreno[0]=='D')
			zapatillas=true;
	}

	if (last_action == actFORWARD or last_action == actIDLE) { //Si he cambiado de casilla, apunto que he visitado la casilla actual. 
		mapaVisitas[current_state.fil][current_state.col]++;
	}

	if(bien_situado){
		//mapaResultado[current_state.fil][current_state.col] = sensores.terreno[0];
		PonerTerrenoEnMatriz(sensores.terreno, current_state, mapaResultado);
	}

	// INTENTO DE ACTUALIZACIÓN DE MOVIMIENTO EN EL MAPA
	/*if((sensores.terreno[2] == 'T' or sensores.terreno[2] == 'S' or sensores.terreno[2] == 'G') and sensores.superficie[2] == '_'){
		accion = actFORWARD;
	}
	else if(!girar_derecha){
		if (!giro_grande) {
			accion = actTURN_SL;
		}
		else {
			accion = actTURN_BL;
		}
		giro_grande = (rand()%2 == 0);
		girar_derecha = (rand()%2 == 0);
	}
	else{
		if (!giro_grande) {
			accion = actTURN_SR;
		}
		else {
			accion = actTURN_BR;
		}
		giro_grande = (rand()%2 == 0);
		girar_derecha = (rand()%2 == 0);
	}

	last_action = accion;
	
	return accion;*/
	/*last_action=GirarMenosVisitada(sensores.terreno, sensores.superficie, current_state, mapaResultado, mapaVisitas);
	return last_action;*/
	
	if ((last_action==actTURN_SL or last_action==actTURN_SR) and (sensores.terreno[1]=='K' or sensores.terreno[1]=='D')){
		last_action=actFORWARD;
		accion=last_action;
		return last_action;
	}
	else {
		last_action=GirarMenosVisitada(sensores.terreno, sensores.superficie, current_state, mapaResultado, mapaVisitas);
		accion=last_action;
		return last_action;
	}
	
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
