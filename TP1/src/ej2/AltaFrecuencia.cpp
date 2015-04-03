//Hay que compilarlo con el flag -std=c++11
//#include "AltaFrecuencia.h"

int main(int argc, char const *argv[]){
	chrono::time_point<chrono::system_clock> start, end; //LINEA NUEVA
	long int cantFrec;
	vector<frecuencia> frecuencias;
	cin >> cantFrec;
	for (int i = 0; i < cantFrec; ++i){
		frecuencia actual;
		actual.id = i;
		cin >> actual.costo;
		cin >> actual.principio;
		cin >> actual.fin;
		if(actual.fin > actual.principio)
			frecuencias.push_back(actual);
	}
	start = chrono::system_clock::now(); //LINEA NUEVA
	vector<frecuencia> optimas = altaFrecuencia(frecuencias);
	vector<frecuencia>::iterator iter;
	long int costoTotal = 0;
	for (iter = optimas.begin(); iter != optimas.end(); iter++){
		costoTotal += (iter->fin - iter->principio) * iter->costo;
	}
	//MOVI EL CHRONO DE LUGAR, ES PARTE DEL EJERCICIO HACER ESTE CALCULO :p
	end = chrono::system_clock::now(); //LINEA NUEVA
	cout << costoTotal << endl;
	for (iter = optimas.begin(); iter != optimas.end(); iter++){
		cout << iter->principio << " " << iter->fin << " " << iter->id + 1 << endl;
	}
	cout << "-1" << endl;
	chrono::duration<double> elapsed_seconds = end-start; //LINEA NUEVA
	cout << "Tiempo: " << elapsed_seconds.count() << endl; //LINEA NUEVA
	return 0;
}

vector<frecuencia> altaFrecuencia(vector<frecuencia>& frecuencias){
	sort(frecuencias.begin(), frecuencias.end());
	return divideAndConquer(frecuencias, 0, frecuencias.size()-1);
}

vector<frecuencia> divideAndConquer(vector<frecuencia>& frecuencias, long int comienzo, long int final){
	if(final - comienzo > 0){
		vector<frecuencia> barata = divideAndConquer(frecuencias, comienzo, (final+comienzo)/2);
		vector<frecuencia> cara = divideAndConquer(frecuencias, ((final+comienzo)/2)+1, final);
		return conquer(barata, cara);
	}
	else{
		vector<frecuencia> res;
		res.push_back(frecuencias[comienzo]);
			return res;
	}
}

vector<frecuencia> conquer(vector<frecuencia> barata, vector<frecuencia> cara){
	vector<frecuencia>::iterator iterCara = cara.begin(), iterBarata = barata.begin();
	vector<frecuencia> res;
	while(iterCara != cara.end()){
		if(iterBarata != barata.end()){
			if(iterCara->principio < iterBarata->principio){ //la cara empieza antes
				if(iterCara->fin <= iterBarata->principio){ //la cara termina antes de que empiece la barata
					res.push_back(*iterCara);				//meto la cara entera
					iterCara++;
				}
				else{ //la cara empieza antes y termina despues del principio de la barata
					frecuencia antes;
					antes.id = iterCara->id;
					antes.costo = iterCara->costo;
					antes.principio = iterCara->principio;
					antes.fin = iterBarata->principio;
					res.push_back(antes);
					iterCara->principio = iterBarata->fin;
				}
			}
			else{ //la barata empieza antes (o igual) que la cara
				if(iterCara->fin > iterBarata->fin){ //la cara termina despues que la barata
					if (iterCara->principio < iterBarata->fin) //este if es nuevo
						iterCara->principio = iterBarata->fin;
					res.push_back(*iterBarata);
					iterBarata++;
				}
				else
					iterCara++;
			}
		}
		else{
			if(iterCara->principio < iterCara->fin)
				res.push_back(*iterCara);
			iterCara++;
		}
	}
	while(iterBarata != barata.end()){
		res.push_back(*iterBarata);
		iterBarata++;
	}
	return res;
}
