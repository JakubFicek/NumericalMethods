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

void rozkladLU(double** macierz, int size) {
    for (int i = 0; i < size; i++) {
        if(macierz[i][i] == 0) {
            throw new invalid_argument("MACIERZ MA 0 na przekatnej - nie da sie jej rozwiazac!");
        }
    }

    //TWORZENIE MACIERZY U
    double **U = new double*[size];
    for (int i = 0; i < size; i++) {
        U[i] = new double[size];
        for(int j = 0; j < size; j++){
            U[i][j] = 0; 
        }
    }

    //TWORZENIE MACIERZY L
    double **L = new double*[size];
    for (int i = 0; i < size; i++) {
        L[i] = new double[size];
        for(int j = 0; j < size; j++){
            if(i == j) {
                L[i][j] = 1;
            } else {
                L[i][j] = 0; 
            }
        }
    }

    //Doolittle
    for (int i = 0; i < size; i++)
    {   
        //U
        for (int k = i; k < size; k++)
        {
            double suma = 0;
            for (int j = 0; j < i; j++){
                suma += (L[i][j] * U[j][k]);
            }
            U[i][k] = macierz[i][k] - suma;
        }
 
        //L
        for (int k = i; k < size; k++)
        {   
            double suma = 0;
            for (int j = 0; j < i; j++){
                suma += (L[k][j] * U[j][i]);
            }
            L[k][i] = (macierz[k][i] - suma) / U[i][i];
        }
    }
	
    cout << "Macierz A: " << endl;
	printMatrix(size, size, macierz);
    cout << "\nMacierz U: " <<endl;;
    printMatrix(size, size, U);
	cout << "\nMacierz L: " << endl;
	printMatrix(size, size, L);

    //WEKTOR Y
    double *Y = new double[size];
    Y[0] = macierz[0][size];

    for (int i = 1; i < size; i++) {
        double suma = 0;
        for(int j = 0; j < i; j++) {
            suma += L[i][j]*Y[j];
        }
        Y[i] = macierz[i][size] - suma;
    }

    cout << endl << "Wektor Y: " ; 
    for (int i = 0; i < size; i++) {
        cout << Y[i] << " ";
    }
    cout << endl;

    //WYNIK
    double *X = new double[size];
    X[size-1] = Y[size-1]/U[size-1][size-1];
    for (int i = size - 2; i >=0; i--){
        double suma = 0;
        for (int j = i+1; j < size; j++){
            suma+= U[i][j]*X[j];
        }
        X[i] = (Y[i] - suma)/U[i][i];
    }
    
    cout << "WYNIK: " << endl;
    for(int i = 0; i<size; i++){
        cout << "x" << i << " = " << X[i] << endl;
    }
}

int main()
{   
    //ODCZYTYWANIE WARTOSCI Z PLIKU DO ZMIENNYCH
    string filename("RURL_dane1.txt");
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

    try {
        rozkladLU(wiersze, il_wierszy);
    } catch (invalid_argument& e) {
        cout << "MACIERZ MA 0 na przekatnej - nie da sie jej rozwiazac!" << endl;
        cerr << e.what() << endl;
        return -1;
    }

    input_file.close();

    for (int k = 0; k < il_wierszy; k++){
        delete[] wiersze[k];
    }
    delete [] wiersze;
    return 0;
}