#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>

using namespace std;

map<string, double(*)(double)> func_map = {
        {"sin", [](double x) { return sin(x); }},
        {"exp", [](double x) { return exp(x); }},
        {"wielom", [](double x) { return pow(x,2) + 2*x+5; }},
    };

void metodaProstokatow(string fun, double przedzS, double przedzK, int ilPodzialow) {
    double s = (przedzK - przedzS)/ilPodzialow;
    double wartosc = 0;

    for(int i = 0; i <= ilPodzialow - 1; i++) {
        wartosc += func_map.at(fun)((przedzS + i*s) + 0.5*s);
    }
    wartosc *= s;
    cout << "Wartosc dla liczenia calki metoda prostokatow: " << wartosc << endl;
}

void metodaTrapezow(string fun, double przedzS, double przedzK, int ilPodzialow) {
    double wartosc = 0;
    double s = (przedzK - przedzS)/ilPodzialow;

    for(int i = 0; i <= ilPodzialow - 1; i++) {
        wartosc += 0.5*(-(przedzS + i*s)+(przedzS + (i+1)*s))*(func_map.at(fun)((przedzS + i*s))+func_map.at(fun)((przedzS + (i+1)*s)));
    }
    cout << "Wartosc dla liczenia calki metoda trapezow: " << wartosc << endl;
}

void metodaSimpsona(string fun, double przedzS, double przedzK, int ilPodzialow) {
    double wartosc;
    double wartosc1 = 0;
    double wartosc2 = 0;
    double wartosc3 = 0;

    double s = (przedzK - przedzS)/ilPodzialow;

    for(int i = 1; i <= ilPodzialow; i++) {
        wartosc1 += func_map.at(fun)((przedzS + (i-1)*s));
        wartosc2 += func_map.at(fun)((przedzS + i*s));
        wartosc3 += func_map.at(fun)(((przedzS + i*s) + (przedzS + (i-1)*s))/2);
    }
    wartosc = s/6*(wartosc1 + wartosc2+ 4*wartosc3);
    cout << "Wartosc dla liczenia calki metoda Simpsona: " << wartosc << endl;
} 

int main()
{   
    cout<< "SIN" << endl;
    metodaProstokatow("sin", 0.5, 2.5, 54);
    metodaTrapezow("sin", 0.5, 2.5, 54);
    metodaSimpsona("sin", 0.5, 2.5, 54);
    cout<< "EXP" << endl;
    metodaProstokatow("exp", 0.5, 5, 54);
    metodaTrapezow("exp", 0.5, 5, 54);
    metodaSimpsona("exp", 0.5, 5, 54);
    cout<< "WIELOMIAN" << endl;
    metodaProstokatow("wielom", 0.5, 5, 54);
    metodaTrapezow("wielom", 0.5, 5, 54);
    metodaSimpsona("wielom", 0.5, 5, 54);

    return 0;
}