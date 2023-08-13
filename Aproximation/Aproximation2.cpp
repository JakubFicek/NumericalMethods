#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

double dwumianNewtona(double n, double k) {
    double wynik = 1.0;
    if (k > n - k) {
        k = n - k;
    }
    for (int i = 0; i < k; i++) {
        wynik *= (n - i) / (i + 1);
    }
    return wynik;
}

double wielomianCzynnikowy(int n, double x) {
    if(n == 0) {
        return 1.0;
    }
    double wynik = 1.0;
    for (int i = 1; i < n; i++) {
        wynik *= (x - i);
    }
    return wynik * x;
}

vector<double> wielomianyGrama(int n, double q, int degree) {
    vector<double> wynik;
    for (int k = 0; k <= degree; k++) {
        double suma = 0.0;
        if(k == 0) {
            wynik.push_back(1.0);
        }else if (q == 0) {
            wynik.push_back(1.0);
        } else {
            for (int i = 0; i <= k; i++) {
                suma += pow(-1, i)*dwumianNewtona(k, i) * dwumianNewtona(k+i, i) * (wielomianCzynnikowy(i,q)/wielomianCzynnikowy(i,n));
            }
            wynik.push_back(suma);
        }
        
    }
    return wynik;
}

vector<double> policzC(int n, int degree){
    vector<double> wynik;
    for (int k = 0; k <= degree; k++) {
        double suma = 0.0;
        for (int i = 0; i < n; i++) {
            vector<double> wielomianyG = wielomianyGrama(n-1, i, degree);
            suma += pow(wielomianyG[k], 2);
        }
        wynik.push_back(suma);
    }
    return wynik;
}

vector<double> policzS(int n, vector<double> wartosciY, int degree){
    vector<double> wynik;
    for (int k = 0; k <= degree; k++) {
        double suma = 0.0;
        for (int i = 0; i <= n; i++) {
            double q = i;
            vector<double> wielomianyG = wielomianyGrama(n-1, i, degree);
            suma += wartosciY[i]*wielomianyG[k];
        }
        if (abs(suma) < 0.1e-16) {
            suma = 0.0;
        }
        wynik.push_back(suma);
    }
    return wynik;
}

void aproksymacjaWielomianowaGrahama(vector<double> waga, vector<pair<double,double>> points, int degree, int il_wezlow) {
    vector<double> wartosciY;
    for (auto point : points) {
        wartosciY.push_back(point.second);
    }
    double h = points[1].first - points[0].first;
    vector<double> C = policzS(il_wezlow, wartosciY, degree);
    vector<double> S = policzC(il_wezlow, degree);
    vector<double> wynikY;
    for(int m = 0; m < il_wezlow; m++){
        double suma = 0.0;
        for(int k = 0; k <= degree; k++) {
            double q = (points[m].first - points[0].first)/h;
            vector<double> wielomianyG = wielomianyGrama(il_wezlow-1, q, degree);
            suma += (C[k]/S[k]) * wielomianyG[k];
        }
        if (abs(suma) < 0.1e-16) {
            suma = 0.0;
        }
        wynikY.push_back(suma);
    }

    cout << "Liczba wezlow: " << il_wezlow << endl;
    cout << "Wspolczynniki: " << endl;
    for (int i = 0; i <= degree; i++) {
        cout << "C[" << i <<"]: " << C[i] << "   S[" << i << "]: " << S[i] << endl;
    }
    cout << "Podane wezly aproksymacji i ich obliczone wartosci z funckji aproksymujacej (x, y) , ym =  " << endl;
    for(int i = 0; i < il_wezlow; i++) {
        cout << "(" << points[i].first << ", " << points[i].second << ") , ym = "<< wynikY[i] << endl;
    }
    double wezel;
    cout << endl << "Podaj wezel dla ktorego tez chcesz policzyc apro: ";
    cin >> wezel;

    double suma = 0.0;

    for(int k = 0; k <= degree; k++) {
        double q = (wezel - points[0].first)/h;
        vector<double> wielomianyG = wielomianyGrama(il_wezlow-1, q, degree);
        suma += (C[k]/S[k]) * wielomianyG[k];
    }
    cout << endl;
    cout << "Wartosc funkcji dla x = " << wezel << " to: " << suma << endl;
}

int main()
{   
    const int degree = 2;  // Stopień wielomianu
    // const vector<pair<double, double>> points = {{1.0, 3.0}, {1.5, 4.75}, {2.0, 7}, {2.5, 9.75}, {3.0, 13.0}};
    // const vector<double> waga = {1,1,1,1,1};
    const vector<pair<double, double>> points = {{1.0, 2.0}, {2.0, 4.0}, {3.0, 3.0}, {4.0, 5.0}, {5.0, 6.0}, {6.0, 9.0}, {7.0, 11.0}, {8.0, 11.0}};
    const vector<double> waga = {1,1,1,1,1,1,1,1};
    int il_wezlow = points.size();

    // vector<double> aa = wielomianyGrama(il_wezlow-1, 4, degree);
    // for (auto a: aa) {
    //     cout << a << endl;
    // }

    aproksymacjaWielomianowaGrahama(waga, points, degree, il_wezlow);

    return 0;
}