#include <utility>
#include <vector>
#include <iostream>
using namespace std;

//juez online http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=11&page=show_problem&problem=930

// Varios typedefs
typedef vector<int> Vec;
typedef vector<Vec> Tablero;
typedef pair<int, int> Coord;

// Prototipado de funciones
bool resolver(Tablero& p, int nsubs);
void mostrar(const Tablero& m);
int check(const Tablero& c, int n);
bool algunRepetido(const Vec &v);

/**
 * La funci�n main toma el tablero por std input:
 * recibe primero el tama�o de bloque (si se le pasa n se
 * asume un bloque de n*n, con lo cual la matriz final ser�
 * de (n*n)*(n*n)). Luego recibe un numero por cada casillero
 * del tablero. Un cero indica casilla vacia.
 * Finalmente, llama al m�todo resolver(...) y al finalizar �ste
 * se muestra el resultado (de haberlo).
 */
int main()
{
	int n;

	while(true) {
		cin >> n;
		if(cin.eof()){
			break;
		}
		int n2 = n*n;
		Tablero p(n2, Vec(n2, 0));
		for(int i = 0; i < n2; ++i)
			for(int j = 0; j < n2; ++j)
				cin >> p[i][j];

		bool sol = resolver(p,n);
		if(!sol){
			cout << "El tablero no tene solucion...";
		} else {
			mostrar(p);
		}
		cout << endl;
	}

	return 0;
}

/**
 * Recibe el tablero inicial y el tama�o de bloque.
 * Sugerencia: preparar los datos que sean necesarios
 * para la resoluci�n y luego llamar a un m�todo que se
 * encargue de realizar el algoritmo de backtracking.
 * La sugerencia es para poder elegir los par�metros
 * adecuados sobre los cuales se har� la recurrencia.
 */
bool resolver(Tablero& p, int n)
{
    // To do: resolver el sudoku!
	int termine = check(p, n);
	if (termine == 1)
		return true;
	if (termine == 0)
		
		resolver(p, n);
	return false;
}

/**
 * Recibe un tablero y lo muestra por pantalla
 */
void mostrar(const Tablero& m)
{
	cout << endl;
	int n = m.size();
	for(int i = 0; i < n; ++i)
	{
		cout << m[i][0];
		for (int j = 1; j < n; j++)
		{
			cout << " " << m[i][j];
		}
		cout << endl;
	}
}


/**
 * La siguiente funci�n devuelve:
 *    2 --> Si el tablero tiene repetidos en alguna fila, columna o cuadrante
 *    1 --> Si no tiene repetidos y es una solucion de Sudoku
 *    0 --> Si no tiene repetidos pero le faltan casillas por llenar
 */
int check(const Tablero& p, int n)
{
	int n2 = p.size();
	bool ceros = false;
	for (int i = 0; i < n2; i++)
	{
		// verifico la fila i
		Vec flag_fila (n2, 0);
		for (int j = 0; j < n2; j++)
		{
			if (p[i][j] == 0)
				ceros = true;
			else
				flag_fila[p[i][j]-1]++;
		}

		if (algunRepetido(flag_fila))
			return 2;

		// verifico la columna i
		Vec flag_col (n2, 0);
		for (int j = 0; j < n2; j++)
		{
			if (p[j][i] == 0)
				ceros = true;
			else
				flag_col[p[j][i]-1]++;
		}

		if (algunRepetido(flag_col))
			return 2;

		// verifico el cuadrante i
		Vec flag_cuad(n2, 0);
		int f = (i/n)*n; // fila donde empieza el cuadrante
		int c = (i % n)*n; // col donde empieza el cuadrante
		for (int j = 0; j < n; j++)
		for (int k = 0; k < n; k++)
		{
			if (p[f+j][c+k] == 0)
				ceros = true;
			else
				flag_cuad[p[f+j][c+k]-1]++;
		}

		if (algunRepetido(flag_cuad))
			return 2;
	}

	return ceros? 0 : 1;
}

/**
 * M�todo auxiliar del m�todo check
 */
bool algunRepetido(const Vec& v)
{
	int k = v.size();
	for (int i = 0; i < k; i++)
		if (v[i] > 1)
			return true;

	return false;
}

