#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

map<string, double(*)(double)> func_map = {
    {"f1", [](double x) { return -pow(x,3) + 10*x + 5; }},
    {"f1P", [](double x) { return -3*pow(x,2) + 10; }},
    {"f2", [](double x) { return 3*pow(x,4) -5*pow(x,2) + 100*x + 10; }},
    {"f2P", [](double x) { return 12*pow(x,3) - 10*x+100; }},
    {"f3", [](double x) { return pow(x,2) - 4; }},
    {"f3P", [](double x) { return 2*x; }},
};

void metodaStycznych(double pktStartowy, double liczbaIteracji, string fun){
    cout << "STYCZNYCH !!" << endl;
    cout<< "Pkt startowy: " << pktStartowy << endl;
    cout<< "Liczba iteracji: " << liczbaIteracji << endl;
    double x = pktStartowy;

    for (int i = 0; i < liczbaIteracji; i++) {
        double fx =  func_map.at(fun)(x);
        double f_derivative_x = func_map.at(fun+"P")(x);

        if (abs(f_derivative_x) < 1e-6) {
            cout << "Pochodna bliska zeru, zakończono iteracje." << std::endl;
            break;
        }
        
        x = x - fx / f_derivative_x;
        cout << "Wartość funckji f(x) dla iteracji " << i+1 << " = " << func_map.at(fun)(x) << endl;
    }
    
    cout << "koncowe x = " << x << endl;
}

double przyblizonaPochodna(double pktStartowy,double pktPrzedStartowy,string fun) {
    return (func_map.at(fun)(pktStartowy) - func_map.at(fun)(pktPrzedStartowy))/(pktStartowy-pktPrzedStartowy);
}

void metodaSiecznych(double pktStartowy,double pktPrzedStartowy,double liczbaIteracji,string fun) {
    cout << "SIECZNYCH !!" << endl;
    cout<< "Pkt startowy: " << pktStartowy << endl;
    cout << "Pkt przed startowy: " << pktPrzedStartowy << endl;
    cout<< "Liczba iteracji: " << liczbaIteracji << endl;
    double x = pktStartowy;
    double przedX = pktPrzedStartowy;

    for (int i = 0; i < liczbaIteracji; i++) {
        double fx =  func_map.at(fun)(x);
        double f_derivative_x = przyblizonaPochodna(x, przedX, fun);

        if (abs(f_derivative_x) < 1e-6) {
            cout << "Pochodna bliska zeru, zakończono iteracje." << std::endl;
            break;
        }
        przedX = x;
        x = x - fx / f_derivative_x;
        cout << "Wartość funckji f(x) dla iteracji " << i+1 << " = " << func_map.at(fun)(x) << endl;
    }
    
    cout << "koncowe x = " << x << endl;
}

int main()
{   
    // F1 - 6, 5.9, 5
    // F2 - 2, 2, 5 / -1, -0.9, 5
    // F3 - 10, ?, 6 / 10, 9, 6 - niedokladnie
    double pktStartowy = 6;
    double pktPrzedStartowy = 5.9;
    double liczbaIteracji= 5;

    metodaStycznych(pktStartowy, liczbaIteracji, "f1");
    cout << endl << endl;
    metodaSiecznych(pktStartowy, pktPrzedStartowy, liczbaIteracji, "f1");

    return 0;
}