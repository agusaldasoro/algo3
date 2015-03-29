#include "SenorCaballos.h"

typedef std::vector<bool> Vec;
typedef std::vector<Vec> Tablero;

int main(int argc, char const *argv[])
{
	while(true){
		if(std::cin.eof())
			break;	int dimension, cantCaballos;
		std::cin >> dimension;
		std::cin >> cantCaballos;
		Tablero tablero(dimension, Vec(dimension, 0));
		for (int i = 0; i < dimension; ++i)
		{
			for (int j = 0; j < dimension; ++j)
			{
				tablero[i][j] = false;
			}
		}
		int fila;
		int col;
		for (int i = 0; i < cantCaballos; ++i)
		{
			std::cin >> fila;
			std::cin >> col;
			tablero[fila-1][col-1] = true;
		}
///////////////////////////////////////////MOSTRAR UN TABLERO//////////////////////////////
		for (int i = 0; i < dimension; ++i)
		{
			for (int j = 0; j < dimension; ++j)
			{
				std::cout << tablero[i][j] << " ";
			}
			std::cout << std::endl;
		}
//////////////////////////////////////////////////////////////////////////////////////////
	}
	return 0;
}
