#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void printMatrix (int n, int m, long double **matrix) {
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            if (abs(matrix[i][j]) < 0.1e-16) {
                matrix[i][j] = 0.0;
            }
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void metodaEliminacjiGaussa(long double **macierz, long double* result, int il_wierszy) {
	for (int i = 0; i < il_wierszy; i++)
	{
		long double pom = 0;
        
        // Szukanie wiersza z wieksza wartoscia od przekatnej i zapisywanie go w maxRow
        int maxRow = i;
        for (int j = i+1; j < il_wierszy; j++)
        {
            if (abs(macierz[j][i]) > abs(macierz[maxRow][i]))
            {
                maxRow = j;
            }
        }

        // Zamiana wierszy, od i, zeby nie sprawdzac wierszy nad
        for (int k = i; k <= il_wierszy; k++)
        {
            long double temp = macierz[i][k];
            macierz[i][k] = macierz[maxRow][k];
            macierz[maxRow][k] = temp;
        }

		for (int j = i+1; j <= il_wierszy - 1; j++){   
			pom = macierz[j][i] / macierz[i][i];
			for (int k = 0; k < il_wierszy+1; k++){
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

void metodaEliminacjiGaussaCrouta(long double **macierz, long double* result, int il_wierszy) {
    vector<int> kolumny;
    for(int i = 0; i < il_wierszy; i++) {
        kolumny.push_back(i);
    }

    for (int i = 0; i < il_wierszy; i++)
    {
        long double pivot = abs(macierz[i][i]);
        int maxIndex = i;

        // szukanie wiersza z maksymalną wartością bezwzględną w kolumnie i-tej
        for (int j = i + 1; j < il_wierszy; j++) {
            if (abs(macierz[i][j]) > pivot) {
                pivot = abs(macierz[i][j]);
                maxIndex = j;
            }
        }

        // zamiana kolumn i-tej i maxIndex, tylko jezeli potrzeba
        if (maxIndex != i) {
            for (int j = 0; j < il_wierszy; j++) {
                long double temp = macierz[j][i];
                macierz[j][i] = macierz[j][maxIndex];
                macierz[j][maxIndex] = temp;
            }
            swap(kolumny[i], kolumny[maxIndex]);
        }

        for (int j = i + 1; j < il_wierszy; j++) {
            long double multiplier = macierz[j][i] / macierz[i][i];
            for (int k = i; k < il_wierszy + 1; k++) {
                macierz[j][k] -= multiplier * macierz[i][k];
            }
        }
    }

    // Wyliczanie wyników
    cout << "Macierz po postepowaniu prostym: " << endl;
    printMatrix(il_wierszy, il_wierszy+1, macierz);

    result[il_wierszy-1] = macierz[il_wierszy-1][il_wierszy] / macierz[il_wierszy-1][il_wierszy-1];

    for (int i = il_wierszy-2; i >= 0; i--)
    {
        result[i] = macierz[i][il_wierszy];
        for (int j = i+1; j < il_wierszy; j++)
        {
            result[i] = result[i] - macierz[i][j] * result[j];
        }
        result[i] = result[i] / macierz[i][i];
    }

    cout << "WEKTOR z numerami kolumn: ";
    for (int i =0; i< il_wierszy; i++) {
        cout << kolumny[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < il_wierszy; i++)
    {
        cout << "Wynik dla x" << kolumny[i] << "= " << result[i] << endl;
    }
}

int main()
{   
    //ODCZYTYWANIE WARTOSCI Z PLIKU DO ZMIENNYCH
    string filename("MN-6-1.txt");
    int number;
    long double number1, number2;
    
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
    long double **wiersze = new long double*[il_wierszy];
    long double **wiersze2 = new long double*[il_wierszy];
    for (int i = 0; i < il_wierszy; i++) {
        wiersze[i] = new long double[il_wierszy+1];
        wiersze2[i] = new long double[il_wierszy+1];
        for(int j = 0; j < il_wierszy+1; j++){
            wiersze[i][j] = 0; 
            wiersze2[i][j] = 0;
        }
    }

    for(int i = 0; i < il_wierszy; i++) {
        for (int j = 0; j < il_wierszy+1; j++){
            input_file >> wiersze[i][j];
            wiersze2[i][j] = wiersze[i][j];
        }
    }

    input_file.close();

    long double* result = new long double[il_wierszy];
    
    cout<< "METODA ELIMINACJI GAUSSA!!" <<endl;
    cout << "Macierz przed: " << endl;
    printMatrix(il_wierszy, il_wierszy+1, wiersze);
    metodaEliminacjiGaussa(wiersze, result, il_wierszy);

    cout<< "METODA ELIMINACJI GAUSSA-CROUTA!!" <<endl;
    cout << "Macierz przed: " << endl;
    printMatrix(il_wierszy, il_wierszy+1, wiersze2);
    metodaEliminacjiGaussaCrouta(wiersze2, result, il_wierszy);

    for (int k = 0; k < il_wierszy; k++){
        delete[] wiersze[k];
    }
    delete [] wiersze;
    return 0;
}