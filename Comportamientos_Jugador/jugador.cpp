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

	int a, b; //CAMBIOS
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
			switch(state_ciego.brujula){
				case norte: state_ciego.fil--; break; //Si estaba mirando al norte
				case noreste: state_ciego.fil--; state_ciego.col++; break;
				case este: state_ciego.col++; break;
				case sureste: state_ciego.fil++; state_ciego.col++; break;
				case sur: state_ciego.fil++; break;
				case suroeste: state_ciego.fil++; state_ciego.col--; break;
				case oeste: state_ciego.col--; break;
				case noroeste: state_ciego.fil--; state_ciego.col--; break;
			}
			break;
		case actTURN_SL:
			a = current_state.brujula;
			b = state_ciego.brujula;
			a = (a+7) % 8; // Equivalente a (a-1)%8 -> giro 45 left
			b = (b+7) % 8;
			current_state.brujula = static_cast<Orientacion>(a);
			state_ciego.brujula = static_cast<Orientacion>(b);
			break;
		case actTURN_SR:
		a = current_state.brujula;
			b=state_ciego.brujula;
			a = (a+1) % 8;
			b= (b+1) % 8;
			current_state.brujula = static_cast<Orientacion>(a);
			state_ciego.brujula = static_cast<Orientacion>(b);
			break;
		case actTURN_BL:
		a = current_state.brujula;
			b = state_ciego.brujula;
			a = (a+5) % 8;
			b = (b+5) % 8;
			current_state.brujula = static_cast<Orientacion>(a);
			state_ciego.brujula = static_cast<Orientacion>(b);
			break;
		case actTURN_BR:
		a = current_state.brujula;
			b = state_ciego.brujula;
		a = (a+3) % 8;
			b = (b+3) % 8;
			current_state.brujula = static_cast<Orientacion>(a);
			state_ciego.brujula = static_cast<Orientacion>(b);
			break;
	}

	if (primeraVez){
		PintarPrecipiciosBordes(current_state, mapaResultado);
		// Me sitúo en mi propia brújula y fila y columna por si estoy en los niveles 1-3
		/*state_ciego.brujula=norte;
		state_ciego.fil=99;
		state_ciego.col=99;*/
		primeraVez=false;
	}

	// PARA NIVEL 1-3
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
		else if (sensores.terreno[0]=='G')
			posicionamiento=true;
	}

	// Si estamos en un nivel que no es el cero y estamos bien situados (hemos encontrado la casilla de posicionamiento)
	/*if (sensores.terreno[0]=='G'){
		PintarCasillasVistas(mapaResultado, mapaCiego, current_state);
	}*/
	
	// Si estoy en el NIVEL 0
	if (bien_situado){
		if (last_action == actFORWARD) { //Si he cambiado de casilla, apunto que he visitado la casilla actual. 
			mapaVisitas[current_state.fil][current_state.col]++;
		}

		PonerTerrenoEnMatriz(sensores.terreno, current_state, mapaResultado);

		// SI HAY CASILLA DE RECARGA A LA VISTA VOY HACIA ELLA
		if (sensores.terreno[0]=='X' and sensores.bateria<4980){
			last_action=actIDLE;
			ultima=actual;
			actual.fil=current_state.fil;
			actual.col=current_state.col;
			accion=last_action;
		}
		else if (sensores.terreno[2]=='X' and sensores.bateria<4500){
			last_action=actFORWARD;
			ultima=actual;
			actual.fil=current_state.fil;
			actual.col=current_state.col;
			accion=last_action;
		}
		else if (sensores.terreno[1]=='X' and sensores.bateria <4500){
			last_action=actTURN_SL;
			ultima=actual;
			actual.fil=current_state.fil;
			actual.col=current_state.col;
			accion=last_action;
		}
		else if (sensores.terreno[3]=='X' and sensores.bateria<4500){
			last_action=actTURN_SR;
			ultima=actual;
			actual.fil=current_state.fil;
			actual.col=current_state.col;
			accion=last_action;
		}
		// SI NO HAY CASILLA DE RECARGA A LA VISTA UTILIZO EL MÉTODO
		else {
			last_action=GirarMenosVisitada(sensores.terreno, sensores.superficie, current_state, mapaResultado, mapaVisitas);
			
			// PARA EVITAR QUE SE QUEDE ATASCADO GIRANDO EN UNA CASILLA
			if (ultima.fil==actual.fil and ultima.col==actual.col and last_action!=actFORWARD){
				if (sensores.terreno[2]!='P' and sensores.terreno[2]!='M') {
					last_action=actFORWARD;
				}
				else {
					last_action=actTURN_BL;
				}
			}
			// PARA EVITAR QUE ENTRE EN UN CICLO DE VARIAS CASILLAS
			else if (mapaVisitas[current_state.fil][current_state.col]>5 and last_action!=actFORWARD){
				if (sensores.terreno[2]!='P' and sensores.terreno[2]!='M') {
					last_action=actFORWARD;
				}
				else {
					last_action=actTURN_BL;
				}
			}
			ultima=actual;
			actual.fil=current_state.fil;
			actual.col=current_state.col;
			accion=last_action;
		}
	}
	// Si estoy en el NIVEL 1-3
	else{
		nivel_cero=false;
		PonerTerrenoEnMatriz(sensores.terreno, state_ciego, mapaCiego);
		last_action=GirarCiego(sensores.terreno, sensores.superficie, state_ciego, mapaResultado, mapaCiego);
	}

	return last_action;
	
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
