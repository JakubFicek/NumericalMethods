#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

void metodaEliminacjiGaussa(double **macierz, double* result, int il_wierszy) {
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

    result[il_wierszy-1] = macierz[il_wierszy-1][il_wierszy] / macierz[il_wierszy-1][il_wierszy-1];
    for (int i = il_wierszy-1; i >= 0; i--) {
        result[i] = macierz[i][il_wierszy];
        for (int j = i + 1; j <= il_wierszy-1; j++) {
            result[i] = result[i] - macierz[i][j] * result[j];
		}
		result[i] = result[i] / macierz[i][i];
    }
}

void aproksymacjaSredwJednomianach(vector<double> waga, vector<pair<double,double>> points, int degree, int il_wezlow){
    //TWORZYMY MACIERZ G
    vector<vector<double>> matrix(degree+1, vector<double>(degree+1, 0.0));
    vector<double> F(degree+1, 0.0);

    //OBLICZANIE MACIERZY G
    for(int k = 0; k < degree+1; k++) {
        for(int j = 0; j < degree+1; j++){
            for(int i = 0; i < il_wezlow; i++){
                matrix[k][j] += (waga[i]*pow(points[i].first, k)*pow(points[i].first, j));
            }
        }
    }

    //OBLICZANIE F
    for(int k = 0; k < degree+1; k++) {
        for(int i = 0; i < il_wezlow; i++){
            F[k] += (waga[i]*pow(points[i].first, k)*points[i].second);
        }
    }

    //TABELA DO METODY GAUSSA ABY OTRZYMAC WYNIK
    double** macierz = new double*[degree+1];
    double* a = new double[degree+1];
     for (int i = 0; i < degree+1; i++) {
        macierz[i] = new double[degree+2];
        a[i] = 0;
        for (int j = 0; j < degree+2; j++) {
            if(j == degree+1) {
                macierz[i][j] = F[i];
            } else {
                macierz[i][j] = matrix[i][j];
            }
        }
    }

    metodaEliminacjiGaussa(macierz, a, degree+1);

    vector<double> noweY(il_wezlow, 0.0);
    for(int i = 0; i<il_wezlow; i++) {
        for(int j = 0; j<degree+1; j++) {
            noweY[i] += a[j] * pow(points[i].first,j);
        }
    } 

    // //WYPISYWANIE
    // //Macierz G
    // for (int i = 0; i < degree+1; i++) {
    //     for (int j = 0; j < degree+1; j++) {
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // //VECTOR F
    // for (int i = 0; i < degree+1; i++) {
    //     cout << F[i] << " ";
    // }   

    cout << "Liczba wezlow: " << il_wezlow << endl;
    cout << "Wspolczynniki wielomianu aproksymujacego: " << endl;
    for (int i = 0; i < degree+1; i++) {
        cout << "a[" << i <<"]: " << a[i] << endl;
    }
    cout << "Podane wezly aproksymacji i ich obliczone wartosci z funckji aproksymujacej (x, y): " << endl;
    for(int i = 0; i < il_wezlow; i++) {
        cout << "(" << points[i].first << ", " << noweY[i] << ")" << endl;
    }
    cout << endl;

    double dla25, dla65;
    for(int j = 0; j<degree+1; j++) {
            dla25 += a[j] * pow(2.5, j);
            dla65 += a[j] * pow(6.5, j);
        }

    cout << "WArtosc dla wezla 2.5 oraz dla 6.5 to : " << endl;
    cout << dla25 << "       " << dla65 << endl;
}

int main()
{   
    const int degree = 1;  // Stopień wielomianu
    const vector<pair<double, double>> points = {{1.0, 2.0}, {2.0, 4.0}, {3.0, 3.0}, {4.0, 5.0}, {5.0, 6.0}, {6.0, 9.0}, {7.0, 11.0}, {8.0, 11.0}};
    const vector<double> waga = {1,1,1,1,1,1,1,1};
    int il_wezlow = points.size();



    aproksymacjaSredwJednomianach(waga, points, degree, il_wezlow);

    return 0;
}