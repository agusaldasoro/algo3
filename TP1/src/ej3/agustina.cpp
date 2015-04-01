/*
Tomo todas las posiciones libres que estan en el tablero que me dan como parametro.
Guardo todas esas coordenadas, en orden, en un vector (PosLibresInicio)
Entonces, lo que voy a querer hacer es por ej:
	tengo el vector<coordenadas> PosLibresInicio = [a, b]
	las cuatro posibilidades que pueden tomar con esto serian:
		1) [0, 0]		--no haya ningun caballo
		2) [0, b]		--haya un solo caballo en la segunda posicion libre
		3) [a, 0]		--haya un solo caballo en la primer posicion libre
		4) [a, b]		--haya dos caballos ocupando todos los lugares libres

	A estos cuatro casos los voy a traducir como:
		1) [0, 0]
		2) [0, 1]
		3) [1, 0]
		4} [1, 1]
	Pues, es innecesario poner que en la posicion 0 del vector va a estar a y en la 1 se va a encontrar b. 
	(Ver que ya guardamos todas las coordenadas en el vector PosLibresInicio)
	Por lo tanto vamos a trabajar con dos vector<bool>: uno que se llama ACUM y otro ESTADO_ACTUAL

*/


/*
 0 = 0 0 0 0		no hay ningun caballo
 1 = 0 0 0 1 +	hay uno solo en la ultima posicion
 2 = 0 0 1 0 	hay uno solo en la anteultima
 3 = 0 0 1 1 +
 4 = 0 1 0 0
 5 = 0 1 0 1 +
 6 = 0 1 1 0
 7 = 0 1 1 1
 8 = 1 0 0 0
 9 = 1 0 0 1
10 = 1 0 1 0
11 = 1 0 1 1
12 = 1 1 0 0
13 = 1 1 0 1
14 = 1 1 1 0
15 = 1 1 1 1
*/

/*
Nos vamos a ir movimiendo de modo "backtrace" dentro del vector<bool> estadoActual.
Vamos a usar dos contadores:
posicionEnVector : Nos indica en que posicion del vector estadoActual estamos trabajando ahora.
contadorDePasadas: Va a contar las veces que llegamos a una hoja
*/



list<caballos> senorCaballosAgus(Tablero& t,int n){
	vector<coordenadas> PosLibresInicio = calcularPosLibres(t, ); //esto no lo voy a querer modificar nunca
	vector<bool> estadoActual(PosLibresInicio); //este vector tiene el mismo tamanio que el de arriba y guarda un 1 si hay caballo en esa coordenada, 0 cc.
	vector<bool> acum(PosLibresInicio); //idem estadoActual, pero este funciona de acumulador de mejor solucion 
	bool retrocedo = false;
	if (t.chequeo == true){
		return pasarALista(PosLibresInicio, acum); //sin nada wacho ganamos de toque roque;
	}
	int contadorDePasadas = 1;
	int posicionEnVector = 0;
	while(contadorDePasadas <= 2**PosLibresInicio.size){ //no termine: contadorDePasadas <= cantidadTotalDeHojasDelArbol
		//Decidir si avanzar o retroceder o es hoja...
		if (posicionEnVector == estadoActual.size-1){//es Hoja
			if (t.chequeo == 0){ //si es solucion debo fijarme de renovar el acum cuando necesario
					if (acum.size == 0 || acum.size > estadoActual.size)
						acum = copiar(estadoActual);//Armar esta funcion
				}				
				contadorDePasadas++;
				//ver que onda estos dos renglones
				t[i][j].esCaballo = !t[i][j].esCaballo; //fijarse que siempre la hoja va a cambiar de valor cuando tengamos que retroceder
				retrocedo = fijarmeSiRetrocedo(); //en el proximo tengo que retroceder.
		}else if (retrocedo){
				posicionEnVector--;
				retrocedo = ponerOsacarCaballo(t, PosLibresInicio, estadoActual, contadorDePasadas, posicionEnVector);
				retrocedo = fijarmeSiRetrocedo();
			}else{ //debo avanzar
				posicionEnVector++;
				ponerOsacarCaballo(t, PosLibresInicio, estadoActual, contadorDePasadas, posicionEnVector);
				retrocedo = false; //nunca debo retroceder una vez que avance, porque solo freno en las hojas
			}
	}
	return pasarALista(PosLibresInicio, acum);
}



//devuelve true si debo seguir retrocediendo, false si debo avanzar
bool ponerOsacarCaballo(Tablero& t, vector<coordenadas> PosLibresInicio, vector<bool>& estadoActual, int contadorDePasadas, int posicionEnVector){
	// Quiero que el vector estadoActual quede igual a binario(contadorDePasadas) 
	vector<bool> comoDebeQuedar(PosLibresInicio.size);
	//armo el binario (FIJARSE QUE ESTO ANDE!)
	for (int i = PosLibresInicio.size-1; i >= 0; --i){
		contadorDePasadas = ceil(comoDebeQuedar/2);
		comoDebeQuedar[i] = contadorDePasadas;
	}
	if (estadoActual[posicionEnVector] != comoDebeQuedar[posicionEnVector]){
		coordenadas actual = PosLibresInicio[posicionEnVector];
		estadoActual[posicionEnVector] = !estadoActual[posicionEnVector];
		if (t[actual.fil][actual.col].esCaballo == false){
			t[actual.fil][actual.col].esCaballo = true;
			atacame(t, actual.fil, actual.col);
		}else{
			t[actual.fil][actual.col].esCaballo = false;
			desataca(t, actual.fil, actual.col);
		}
		return difierenAntes(estadoActual, comoDebeQuedar, posicionEnVector);
	}	
	return true;
}

bool difierenAntes(vector<bool> v, vector<bool>w, int pos){
	for (int i = 0; i < pos; ++i){
		if (v[i]!=w[i])
			return true;
	}
	false
}

copiar();