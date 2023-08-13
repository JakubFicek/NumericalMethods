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

bool checkMatrixIfWeak(double** matrix, int size) {
    bool oneGreatherThan = false;

    for (int i = 0; i < size; i++){
        double sum = 0;
        for(int j = 0; j < size; j++){
            if(i!=j) {
                sum += abs(matrix[i][j]);
            }
        }
        if(abs(matrix[i][i]) > sum){
            oneGreatherThan = true;
        } 
        if(abs(matrix[i][i]) < sum){
            return false;
        }
    }

    return oneGreatherThan;
}

void jacobi(double **matrix, int size, int ilIteracji, double epsilon) {
    cout<< "MACIERZ ROZSZERZONA: " << endl;
    printMatrix(size,size+1,matrix);

    if(!checkMatrixIfWeak(matrix, size)) {
        cout << "MACIERZ NIE JEST DIAGONALNIE SLABO DOMINUJACA!" << endl;
        exit(0);
    }

    // Inicjalizacja macierzy L, U i D i LU
    double **U = new double*[size];
    double **L = new double*[size];
    double **D = new double*[size];
    double **LU = new double*[size];
    for (int i = 0; i < size; i++) {
        U[i] = new double[size];
        L[i] = new double[size];
        D[i] = new double[size];
        LU[i] = new double[size];
        for (int j = 0; j < size; j++) {
            L[i][j] = 0;
            U[i][j] = 0;
            D[i][j] = 0;
            LU[i][j] = 0;
        }
    }

    // Podzielenie macierz na L, U i D
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                D[i][j] = matrix[i][j];
            } else if (i < j) {
                U[i][j] = matrix[i][j];
            } else {
                L[i][j] = matrix[i][j];
            }
        }
    }

    //ODWROCENIE MACIERZY D
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j && D[i][j] != 0) {
                D[i][j] = 1.0 / D[i][j];
            }
        }
    }

    //STWORZENIE MACIERZY L+U
    for (int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            LU[i][j] = L[i][j] + U[i][j];
        }
    }

    cout << "MACIERZ L+U: " << endl;
    printMatrix(size,size,LU);
    cout << "MACIERZ D^(-1): " << endl;
    printMatrix(size,size,D);

    //ROZWIAZANIE
    double **DLU = new double*[size];
    double *Db = new double[size];
    for(int i=0; i < size; i++) {
        DLU[i] = new double[size];
        Db[i] = 0; 
        for(int j = 0; j < size; j++) {
            DLU[i][j] = 0;
        }
    }

    // Mnożenie macierzy -D-1 i L+U
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                DLU[i][j] += -D[i][k] * LU[k][j];
            }
        }
    }

    // Mnożenie macierzy D-1 i wektora b
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Db[i] += D[i][j] * matrix[j][size];
        }
    }

    //ROZWIĄZANIE DLA PODANEJ ILOŚCI ITERACJI I DOKLADNOSCI
    int iter = 0;
    bool przezDokladnosc = false;
    if(ilIteracji != 0) {
        //X DLA NADADEJ ILITERACJI;
        double **x = new double*[ilIteracji+1];
        for(int i = 0; i < ilIteracji+1; i++) {
            x[i] = new double[size];
            for(int j = 0; j < size; j++) {
                x[i][j] = 0;
            }
        }
        for(int i = 0; i < ilIteracji; i++) {
            for(int j=0; j<size; j++) {
                for (int k = 0; k < size; k++) {
                    x[i+1][j] += DLU[j][k] * x[i][k];
                }
                x[i+1][j] += Db[j];
            }
            for (int j = 0; j < size; j++) {
                double diff = abs(x[i+1][j] - x[i][j]);
                if(diff < epsilon) {
                    przezDokladnosc = true;
                } else {
                    przezDokladnosc = false;
                    break;
                }
            }
            iter++;
            if (przezDokladnosc) {
                cout<< "Rozwiazanie przez dokladnosc po " << iter << " iteracjach, dokladnosc wynosi "<< epsilon << ": " << endl;
                for(int i = 0; i< size; i++) {
                    cout << "x[" << i << "] = " << x[iter][i] << endl;
                }
                break;
            }
        }
        if(!przezDokladnosc){
            cout<< "Rozwiazanie po " << iter << " iteracjach: " << endl;
            for(int i = 0; i< size; i++) {
                cout << "x[" << i << "] = " << x[iter][i] << endl;
            }
        }
    } else {
        //ROZWIAZANIE BEZ PODANEJ ILOSCI ITERACJI
        //MAX IL ITERACJI 1000
        double *x = new double[size];
        double *newX = new double[size];
        for (int i = 0; i<size; i++) {
            x[i] = 0;
            newX[i] = 0;
        }
        for(int i = 0; i < 1000; i++) {
            for(int j=0; j<size; j++) {
                for (int k = 0; k < size; k++) {
                    newX[j] += DLU[j][k] * x[k];
                }
                newX[j] += Db[j];
            }
            //SPRAWDZANIE
            for(int j = 0; j<size; j++) {
                double diff = abs(newX[j] - x[j]);
                if(diff < epsilon) {
                    przezDokladnosc = true;
                } else {
                    przezDokladnosc = false;
                    break;
                }
            }
            //NOWE WARTOSCI DLA x i newX zerowanie
            for (int j = 0; j < size; j++) {
                x[j] = newX[j];
                newX[j] = 0;
            }
            iter++;
            if (przezDokladnosc) {
                cout<< "Rozwiazanie przez dokladnosc po " << iter << " iteracjach, dokladnosc wynosi "<< epsilon << ": " << endl;
                for(int i = 0; i< size; i++) {
                    cout << "x[" << i << "] = " << x[i] << endl;
                }
                break;
            }
        }
        if(!przezDokladnosc){
            cout<< "Rozwiazanie po max ilosci iteracji: " << iter << ": " << endl;
            for(int i = 0; i< size; i++) {
                cout << "x[" << i << "] = " << x[i] << endl;
            }
        }
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

    jacobi(wiersze, il_wierszy, 0, 0.000001);

    input_file.close();

    for (int k = 0; k < il_wierszy; k++){
        delete[] wiersze[k];
    }
    delete [] wiersze;
    return 0;
}