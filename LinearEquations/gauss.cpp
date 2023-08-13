#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void printMatrix (int n, int m, double **matrix) {
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void gauss(double **macierz, double* result, int il_wierszy) {
	for (int i = 0; i < il_wierszy; i++)
	{
		double pom = 0;

		for (int j = i+1; j <= il_wierszy - 1; j++)
		{   
            if(macierz[i][i] == 0) {
                throw new invalid_argument("MACIERZ MA 0 na przekatnej - nie da sie jej rozwiazac!");
            }
			pom = macierz[j][i] / macierz[i][i];

			for (int k = 0; k < il_wierszy+1; k++)
			{
				macierz[j][k] = macierz[j][k] - pom * macierz[i][k];
			}
		}
	}
    cout << "Macierz po postepowaniu prostym: " << endl;
    printMatrix(il_wierszy, il_wierszy+1, macierz);

    result[il_wierszy-1] = macierz[il_wierszy-1][il_wierszy] / macierz[il_wierszy-1][il_wierszy-1];

    for (int i = il_wierszy-1; i >= 0; i--) {
        result[i] = macierz[i][il_wierszy];
        for (int j = i + 1; j <= il_wierszy-1; j++) {
            result[i] = result[i] - macierz[i][j] * result[j];
		}
		result[i] = result[i] / macierz[i][i];
    }

    for (int i = 0; i <il_wierszy ; i++) {
        cout << "Wynik dla x"<< i <<"= " << result[i] << endl;
    }

}

int main()
{   
    //ODCZYTYWANIE WARTOSCI Z PLIKU DO ZMIENNYCH
    string filename("MN-8.txt");
    int number;
    double number1, number2;
    
    ifstream input_file(filename);

    //SPRAWDZENIE CZY PLIK SIE OTWIERA
    if (!input_file.is_open()) {
        cerr << "Plik sie nie otwiera '"<< filename << "'" << endl;
        return -1;
    }
    //PIERWSZA LICZBA W PLIKU TEKSTOWYM OZNACZA ILOSC WEZLOW
    int il_wierszy;
    input_file >> il_wierszy;

    //ZAPISUJE WEZLY I WARTOSCI FUNKCJI W DWOCH OSOBNYCH TABELACH
    double **wiersze = new double*[il_wierszy];
    for (int i = 0; i < il_wierszy; i++) {
        wiersze[i] = new double[il_wierszy+1];
        for(int j = 0; j < il_wierszy+1; j++){
            wiersze[i][j] = 0; 
        }
    }

    for(int i = 0; i < il_wierszy; i++) {
        for (int j = 0; j < il_wierszy+1; j++){
            input_file >> wiersze[i][j];
        }
    }

    input_file.close();

    printMatrix(il_wierszy, il_wierszy+1, wiersze);

    double* result = new double[il_wierszy];
    try {
        gauss(wiersze, result, il_wierszy);
    } catch (invalid_argument& e) {
        cerr << e.what() << endl;
        return -1;
    }

    for (int k = 0; k < il_wierszy; k++){
        delete[] wiersze[k];
    }
    delete [] wiersze;
    return 0;
}