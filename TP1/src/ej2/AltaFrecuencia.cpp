#include "AltaFrecuencia.h"

int main(int argc, char const *argv[])
{
	while(true){
		if(cin.eof())
			break;
		int cantFrec;
		vector<frecuencia> frecuencias;
		cin >> cantFrec;
		for (int i = 0; i < cantFrec; ++i)
		{
			frecuencia actual;
			actual.id = i;
			cin >> actual.costo;
			cin >> actual.principio;
			cin >> actual.fin;
			frecuencias.push_back(actual);
		}
		vector<frecuencia> optimas = altaFrecuencia(frecuencias);
		vector<frecuencia>::iterator iter;
		int costoTotal = 0;
		for (iter = optimas.begin(); iter != optimas.end(); iter++)
		{
			costoTotal += (iter->fin - iter->principio) * iter->costo;
		}
		cout << costoTotal << endl;
		for (iter = optimas.begin(); iter != optimas.end(); iter++){
			cout << iter->principio << " " << iter->fin << " " << iter->id << endl;
		}
		cout << "-1" << endl;
	}
	return 0;
}

vector<frecuencia> altaFrecuencia(vector<frecuencia>& frecuencias){
	sort_heap(frecuencias.begin(), frecuencias.end());
	return divideAndConquer(frecuencias, 0, frecuencias.size()-1);
}

vector<frecuencia> divideAndConquer(vector<frecuencia>& frecuencias, int comienzo, int final){
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
			if(iterCara->principio < iterBarata->principio){
				if(iterCara->fin <= iterBarata->principio){
					res.push_back(*iterCara);
					iterCara++;
				}
				else{
					frecuencia antes;
					antes.id = iterCara->id;
					antes.costo = iterCara->costo;
					antes.principio = iterCara->principio;
					antes.fin = iterBarata->principio;
					res.push_back(antes);
					iterCara->principio = iterBarata->fin;
					res.push_back(*iterBarata);
					iterBarata++;
				}
			}
			else{
				if(iterCara->fin > iterBarata->fin){
					iterCara->principio = iterBarata->fin;
					res.push_back(*iterBarata);
					iterBarata++;
				}
				else
					iterCara++;
			}
		}
		else{
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



/*#include "AltaFrecuencia.h"

int main(int argc, char const *argv[])
{
	while(true){
		if(cin.eof())
			break;
		int cantFrec;
		vector<frecuencia> frecuencias;
		cin >> cantFrec;
		for (int i = 0; i < cantFrec; ++i)
		{
			frecuencia actual;
			actual.id = i;
			cin >> actual.costo;
			cin >> actual.principio;
			cin >> actual.fin;
			frecuencias.push_back(actual);
		}
		vector<frecuencia> optimas = altaFrecuencia(frecuencias);
		vector<frecuencia>::iterator iter;
		int costoTotal = 0;
		for (iter = optimas.begin(); iter != optimas.end(); iter++)
		{
			costoTotal += (iter->fin - iter->principio) * iter->costo;
		}
		cout << costoTotal << endl;
		for (iter = optimas.begin(); iter != optimas.end(); iter++){
			cout << iter->principio << " " << iter->fin << " " << iter->id << endl;
		}
		cout << "-1" << endl;
	}
	return 0;
}

vector<frecuencia> altaFrecuencia(vector<frecuencia>& frecuencias){
	sort_heap(frecuencias.begin(), frecuencias.end());
	vector<frecuencia> optima;
	for (int i = 0; i < frecuencias.size(); ++i)
	{
		optima.push_back(frecuencias[i]);
	}
	return divideAndConquer(optima);
}

vector<frecuencia> divideAndConquer(vector<frecuencia> frecuencias){
	if (frecuencias.size() > 1)
	{
		vector<frecuencia> barata, cara;
		int sizeF = frecuencias.size()/2;
		for (int i = 0; i < sizeF; ++i)
		{
			barata.push_back(frecuencias.front());
			frecuencias.pop_front();
		}
		sizeF = frecuencias.size();
		for (int i = 0; i < sizeF; ++i)
		{
			cara.push_back(frecuencias.front());
			frecuencias.pop_front();
		}
		barata = divideAndConquer(barata);
		cara = divideAndConquer(cara);
		return conquer(barata, cara);
	}
	else{
		return frecuencias;
	}
}

vector<frecuencia> conquer(vector<frecuencia> barata, vector<frecuencia> cara){
	vector<frecuencia>::iterator iterCara = cara.begin(), iterBarata = barata.begin();
	vector<frecuencia> res;
	while(iterCara != cara.end()){
		if(iterBarata != barata.end()){
			if(iterCara->principio < iterBarata->principio){
				if(iterCara->fin <= iterBarata->principio){
					res.push_back(*iterCara);
					iterCara++;
				}
				else{
					frecuencia antes;
					antes.id = iterCara->id;
					antes.costo = iterCara->costo;
					antes.principio = iterCara->principio;
					antes.fin = iterBarata->principio;
					res.push_back(antes);
					iterCara->principio = iterBarata->fin;
					res.push_back(*iterBarata);
					iterBarata++;
				}
			}
			else{
				if(iterCara->fin > iterBarata->fin){
					iterCara->principio = iterBarata->fin;
					res.push_back(*iterBarata);
					iterBarata++;
				}
				else
					iterCara++;
			}
		}
		else{
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
*/