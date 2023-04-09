#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;



Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;

	cout << "Posicion: fila ciega " << state_ciego.fil << " columna ciega " << state_ciego.col << " ";
	switch(state_ciego.brujula){
		case norte: cout << "Norte" << endl; break;
		case noreste: cout << "Noreste" << endl; break;
		case este: cout << "Este" << endl; break;
		case sureste: cout << "Sureste" << endl; break;
		case sur: cout << "Sur " << endl; break;
		case suroeste: cout << "Suroeste" << endl; break;
		case oeste: cout << "Oeste" << endl; break;
		case noroeste: cout << "Noroeste" << endl; break;
	}
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
		a = current_state.brujula;
		a = (a+3) % 8;
			current_state.brujula = static_cast<Orientacion>(a);
			break;
	}

	// Si no estamos en el nivel 0 y aún no estamos bien situados, actualizamos el estado de nuestra propia brújula
	if (!bien_situado){
		switch(state_ciego.brujula){
			case norte:
				switch(last_action){
					case actFORWARD:
						state_ciego.fil--;
					break;
					case actTURN_BL:
						state_ciego.brujula=suroeste;
					break;
					case actTURN_BR:
						state_ciego.brujula=sureste;
					break;
					case actTURN_SL:
						state_ciego.brujula=noroeste;
					break;
					case actTURN_SR:
						state_ciego.brujula=noreste;
					break;
				}
			break;
			case noreste:
				switch(last_action){
					case actFORWARD:
						state_ciego.fil--;
						state_ciego.col++;
					break;
					case actTURN_BL:
						state_ciego.brujula=oeste;
					break;
					case actTURN_BR:
						state_ciego.brujula=sur;
					break;
					case actTURN_SL:
						state_ciego.brujula=norte;
					break;
					case actTURN_SR:
						state_ciego.brujula=este;
					break;
				}
			break;
			case este:
				switch(last_action){
					case actFORWARD:
						state_ciego.col++;
					break;
					case actTURN_BL:
						state_ciego.brujula=noroeste;
					break;
					case actTURN_BR:
						state_ciego.brujula=suroeste;
					break;
					case actTURN_SL:
						state_ciego.brujula=noreste;
					break;
					case actTURN_SR:
						state_ciego.brujula=sureste;
					break;
				}
			break;
			case sureste:
				switch(last_action){
					case actFORWARD:
						state_ciego.fil++;
						state_ciego.col++;
					break;
					case actTURN_BL:
						state_ciego.brujula=norte;
					break;
					case actTURN_BR:
						state_ciego.brujula=oeste;
					break;
					case actTURN_SL:
						state_ciego.brujula=este;
					break;
					case actTURN_SR:
						state_ciego.brujula=sur;
					break;
				}
			break;
			case sur:
				switch(last_action){
					case actFORWARD:
						state_ciego.fil++;
					break;
					case actTURN_BL:
						state_ciego.brujula=noreste;
					break;
					case actTURN_BR:
						state_ciego.brujula=noroeste;
					break;
					case actTURN_SL:
						state_ciego.brujula=sureste;
					break;
					case actTURN_SR:
						state_ciego.brujula=suroeste;
					break;
				}
			break;
			case suroeste:
				switch(last_action){
					case actFORWARD:
						state_ciego.fil++;
						state_ciego.col--;
					break;
					case actTURN_BL:
						state_ciego.brujula=este;
					break;
					case actTURN_BR:
						state_ciego.brujula=norte;
					break;
					case actTURN_SL:
						state_ciego.brujula=sur;
					break;
					case actTURN_SR:
						state_ciego.brujula=oeste;
					break;
				}
			break;
			case oeste:
				switch(last_action){
					case actFORWARD:
						state_ciego.col--;
					break;
					case actTURN_BL:
						state_ciego.brujula=sureste;
					break;
					case actTURN_BR:
						state_ciego.brujula=noreste;
					break;
					case actTURN_SL:
						state_ciego.brujula=suroeste;
					break;
					case actTURN_SR:
						state_ciego.brujula=noroeste;
					break;
				}
			break;
			case noroeste:
				switch(last_action){
					case actFORWARD:
						state_ciego.fil--;
						state_ciego.col--;
					break;
					case actTURN_BL:
						state_ciego.brujula=sur;
					break;
					case actTURN_BR:
						state_ciego.brujula=este;
					break;
					case actTURN_SL:
						state_ciego.brujula=oeste;
					break;
					case actTURN_SR:
						state_ciego.brujula=norte;
					break;
				}
			break;
		}
	}

	if (sensores.reset){
		if (!bien_situado){
			PintarCasillasVistas(mapaResultado, mapaCiego, state_ciego, sensores);
		}
		bien_situado=false;
		nivel_cero=false;
		bikini=false;
		zapatillas=false;
		posicionamiento=false;

		vector<unsigned char> aux2;
		for (unsigned int i = 0; i < 199; i++){
        	for (unsigned int j=0; j<199; j++){
          		aux2.push_back('?');
        	}
        	mapaCiego.push_back(aux2);
       	}
		
      	state_ciego.fil = state_ciego.col = 99;
      	state_ciego.brujula = norte;	
	}

	// Si no estamos en el nivel 0 y encontramos una casilla de posicionamiento, copiamos las casillas que hemos visto hasta ahora
	if (sensores.terreno[0]=='G' and !nivel_cero){
		PintarCasillasVistas(mapaResultado, mapaCiego, state_ciego, sensores);
		PintarPrecipiciosBordes(current_state, mapaResultado);
		nivel_cero=true;
	}

	if(sensores.posF != -1 and !bien_situado){
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true;
		PintarPrecipiciosBordes(current_state, mapaResultado);
	}

	// Actualizamos los datos de los objetos que tenemos 
	if (last_action==actFORWARD){
		if (sensores.terreno[0]=='K')
			bikini=true;
		else if (sensores.terreno[0]=='D')
			zapatillas=true;
		else if (sensores.terreno[0]=='G')
			posicionamiento=true;
	}
	
	// Si estoy en el NIVEL 0 (o en los demás pero bien situado)
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
		else if (sensores.terreno[2]=='X' and sensores.bateria<4500 and sensores.superficie[2]=='_'){
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
				if (sensores.terreno[2]!='P' and sensores.terreno[2]!='M' and sensores.superficie[2]=='_') {
					last_action=actFORWARD;
				}
				else {
					last_action=actTURN_BL;
				}
			}
			// PARA EVITAR QUE ENTRE EN UN CICLO DE VARIAS CASILLAS
			else if (mapaVisitas[current_state.fil][current_state.col]>5 and last_action!=actFORWARD){
				if (sensores.terreno[2]!='P' and sensores.terreno[2]!='M' and sensores.superficie[2]=='_') {
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
	// Si estoy en el NIVEL 1-3 y no estoy bien situado
	else{
		// Sé que no estoy en el nivel 0
		nivel_cero=false;

		// Pinto el terreno que veo en mi matriz ciega
		PonerTerrenoEnMatriz(sensores.terreno, state_ciego, mapaCiego);
		
		last_action=GirarCiego(sensores.terreno, sensores.superficie, state_ciego, mapaResultado, mapaCiego);

	}

	return last_action;
	
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
