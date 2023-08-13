#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

map<string, double(*)(double, double)> func_map = {
    {"f1", [](double x, double y) { return pow(x,2) + y; }},
    {"f2", [](double x, double y) { return x + y; }},
};

void metodaEulera(string fun, double x, double N, double xWarPoczatkowego, double wartoscWarPoczatkowy, double h) {
    vector<double> wynikY;
    vector<double> kolejnoscX;
    wynikY.push_back(wartoscWarPoczatkowy);
    kolejnoscX.push_back(xWarPoczatkowego);

    for(int i = 0; i < N; i++){
        kolejnoscX.push_back(kolejnoscX[i] + h);
        wynikY.push_back(wynikY[i] + h*(func_map.at(fun)(kolejnoscX[i], wynikY[i])));
    }

    cout << "Metoda Eulera: y(" << kolejnoscX[N] << ") = " << wynikY[N] << endl;
}

void metodaRK2(string fun, double x, double N, double xWarPoczatkowego, double wartoscWarPoczatkowy, double h) {
    double y = wartoscWarPoczatkowy;
    double k1, k2;
    int i = 0;
    double x0 = xWarPoczatkowego;

    while(i < N){
        k1 = h*func_map.at(fun)(x0, y);
        k2 = h*func_map.at(fun)(x0+h, y+k1);
        y = y + 0.5 * (k1 + k2);
        x0 = x0 + h;
        i++;
    }
    cout << "Metoda RK2: y(" << x << ") = " << y << endl;
}

void metodaRK4(string fun, double x, double N, double xWarPoczatkowego, double wartoscWarPoczatkowy, double h){
    double y = wartoscWarPoczatkowy;
    double k1, k2, k3, k4;
    double x0 = xWarPoczatkowego;
    int i = 0;
    while ( i < N) {
        k1 = h * func_map.at(fun)(x0, y);
        k2 = h * func_map.at(fun)(x0 + 0.5 * h, y + 0.5 * k1);
        k3 = h * func_map.at(fun)(x0 + 0.5 * h, y + 0.5 * k2);
        k4 = h * func_map.at(fun)(x0 + h, y + k3);
        y = y + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
        x0 = x0 + h;
        i++;
    }
    cout << "Metoda RK4: y(" << x << ") = " << y << endl;
}


int main()
{   
    double x = 1;
    double N = 10;
    double xWarPoczatkowego = 0;
    double wartoscWarPoczatkowy = 0.1;

    cout << "War poczatkowy: y("<< xWarPoczatkowego <<") = " << wartoscWarPoczatkowy << endl;
    cout << "Punkt koncowy: x" << N << " = " << x << endl;
    
    double h = (x-xWarPoczatkowego)/N;
    cout << "Krok czasowy: h = " << h << endl;

    cout << endl << "F1 = x^2 + y: " << endl;
    metodaEulera("f1", x, N, xWarPoczatkowego, wartoscWarPoczatkowy, h);
    metodaRK2("f1", x, N, xWarPoczatkowego, wartoscWarPoczatkowy, h);
    metodaRK4("f1", x, N, xWarPoczatkowego, wartoscWarPoczatkowy, h);
    
    cout << endl << "F2 = x + y: " << endl;
    metodaEulera("f2", x, N, xWarPoczatkowego, wartoscWarPoczatkowy, h);
    metodaRK2("f2", x, N, xWarPoczatkowego, wartoscWarPoczatkowy, h);
    metodaRK4("f2", x, N, xWarPoczatkowego, wartoscWarPoczatkowy, h);


    return 0;
}