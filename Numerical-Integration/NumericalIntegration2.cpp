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

void kwadratura2Wezlowa(string fun, double przedzS, double przedzK) {
    //DANE
    int ilWezlow = 2; 
    double x[ilWezlow] = {-0.57735, 0.57735};
    double A[ilWezlow] = {1,1};
    double t[ilWezlow];

    for (int i = 0; i< ilWezlow; i++ ){
        t[i] =((przedzS+przedzK)/2)+ (((przedzK - przedzS)/2))*x[i];
    } 

    double wynik = 0;

    for( int i = 0; i<ilWezlow; i++) {
        wynik += A[i] * func_map.at(fun)(t[i]);
    }

    wynik *= (przedzK - przedzS)/2;

    cout << "Wartosc dla liczenia calki kwadratura 2 wezlowa dla " << fun << " : " << wynik << endl;
} 

void kwadratura3Wezlowa(string fun, double przedzS, double przedzK) {
    //DANE
    int ilWezlow = 3; 
    double x[ilWezlow] = {-0.774597, 0, 0.774597};
    double A[ilWezlow] = {0.55556, 0.88889, 0.55556};
    double t[ilWezlow];

    for (int i = 0; i< ilWezlow; i++ ){
        t[i] =((przedzS+przedzK)/2)+ (((przedzK - przedzS)/2))*x[i];
    } 

    double wynik = 0;

    for( int i = 0; i<ilWezlow; i++) {
        wynik += A[i] * func_map.at(fun)(t[i]);
    }

    wynik *= (przedzK - przedzS)/2;

    cout << "Wartosc dla liczenia calki kwadratura 3 wezlowa dla " << fun << " : " << wynik << endl;
} 
 

void kwadratura4Wezlowa(string fun, double przedzS, double przedzK) {
    //DANE
    int ilWezlow = 4; 
    double x[ilWezlow] = {-0.861136, -0.339981, 0.339981, 0.861136};
    double A[ilWezlow] = {0.347855,0.652145, 0.652145, 0.347855};
    double t[ilWezlow];

    for (int i = 0; i< ilWezlow; i++ ){
        t[i] =((przedzS+przedzK)/2)+ (((przedzK - przedzS)/2))*x[i];
    } 

    double wynik = 0;

    for( int i = 0; i<ilWezlow; i++) {
        wynik += A[i] * func_map.at(fun)(t[i]);
    }

    wynik *= (przedzK - przedzS)/2;

    cout << "Wartosc dla liczenia calki kwadratura 4 wezlowa dla " << fun << " : " << wynik << endl;
}  

void metodaProstokatow(string fun, double przedzS, double przedzK, int ilPodzialow) {
    double s = (przedzK - przedzS)/ilPodzialow;
    double wartosc = 0;

    for(int i = 0; i <= ilPodzialow - 1; i++) {
        wartosc += func_map.at(fun)((przedzS + i*s) + 0.5*s);
    }
    wartosc *= s;
    cout << "Wartosc dla liczenia calki metoda prostokatow dla " << fun << " : " << wartosc << endl;
}

void metodaTrapezow(string fun, double przedzS, double przedzK, int ilPodzialow) {
    double wartosc = 0;
    double s = (przedzK - przedzS)/ilPodzialow;

    for(int i = 0; i <= ilPodzialow - 1; i++) {
        wartosc += 0.5*(-(przedzS + i*s)+(przedzS + (i+1)*s))*(func_map.at(fun)((przedzS + i*s))+func_map.at(fun)((przedzS + (i+1)*s)));
    }
    cout << "Wartosc dla liczenia calki metoda trapezow dla " << fun << " : " << wartosc << endl;
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
    cout << "Wartosc dla liczenia calki metoda Simpsona dla " << fun << " : " << wartosc << endl;
} 

int main()
{   
    cout<< "METODAPROSTOKATOW" << endl;
    metodaProstokatow("sin", 0.5, 2.5, 20);
    metodaProstokatow("exp", 0.5, 5, 20);
    metodaProstokatow("wielom", 0.5, 5, 20);
    cout<< "METODATRAPEZOW" << endl;
    metodaTrapezow("sin", 0.5, 2.5, 20);
    metodaTrapezow("wielom", 0.5, 5, 20);
    metodaTrapezow("exp", 0.5, 5, 20);
    cout<< "METODASIMPSONA" << endl; 
    metodaSimpsona("sin", 0.5, 2.5, 20);
    metodaSimpsona("wielom", 0.5, 5, 20);
    metodaSimpsona("exp", 0.5, 5, 20);
    cout<< "KWADRATURA2WEZLOWA" << endl;
    kwadratura2Wezlowa("sin", 0.5, 2.5);
    kwadratura2Wezlowa("wielom", 0.5, 5);
    kwadratura2Wezlowa("exp", 0.5, 5);
    cout<< "KWADRATURA3WEZLOWA" << endl;
    kwadratura3Wezlowa("sin", 0.5, 2.5);
    kwadratura3Wezlowa("wielom", 0.5, 5);
    kwadratura3Wezlowa("exp", 0.5, 5);
     cout<< "KWADRATURA4WEZLOWA" << endl;
    kwadratura4Wezlowa("sin", 0.5, 2.5);
    kwadratura4Wezlowa("wielom", 0.5, 5);
    kwadratura4Wezlowa("exp", 0.5, 5);
    cout << "WARTOSCI DOKLADNE: " << endl;
    cout << "Dla sin: 1.67873" << endl;
    cout << "Dla wielom: 88.875" << endl;
    cout << "Dla exp: 146.764" << endl;

    return 0;
}