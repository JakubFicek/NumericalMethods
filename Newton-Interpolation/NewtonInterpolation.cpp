#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void oblInterNewt (int il_wezlow, double* wezly, double* wartosci) {
    //POBIERANIE PKT Z KLAWIATURY
    double pkt;
    cout << "Podaj pkt w ktorym chcesz obliczyc wartosc wielomianu: ";
    cin >> pkt;

    double *tabP = new double[il_wezlow];
    tabP[0] = 1;
    for (int i = 1; i < il_wezlow; i++) {
        tabP[i] = tabP[i-1]*(pkt - wezly[i-1]);
    }

    double *tabB = new double[il_wezlow];
    tabB[0] = wartosci[0];
    for (int i = 1; i < il_wezlow; i++) {
        double wartPomocnicza = 1;
        
        for(int j = 0; j < i+1 ; j++){
            
            for(int k = 0; k < i+1; k++){
                if(k != j ) {
                    wartPomocnicza *= (wezly[j]-wezly[k]); 
                }
            }
            
            tabB[i] += wartosci[j]/wartPomocnicza;
            wartPomocnicza = 1;
        }
    }

    double wynik = 0;
    //OBLICZANIE KONKRETNEJ WARTOSCI WIELOMIANU W PKT X
    for (int i = 0; i < il_wezlow; i++) {
        wynik += tabB[i]*tabP[i];
    }

    cout << "Liczba wezlow: " << il_wezlow << endl;
    cout << "Wezly - Wartosci: " << endl;
    for(int i = 0; i < il_wezlow; i++){
        cout<< wezly[i]<< " ____ " << wartosci[i] << endl;
    }
    cout << endl << "Punkt w ktorym liczymy wartosc wielomianu: " << pkt << endl;
    cout << "Wartosc wielomianiu Newtona w danym punkcie: " << wynik << endl;
    cout << "Wartosci wspolczynnikow wielomianu Newtona(b): " <<endl;
    for(int i = 0; i < il_wezlow; i++){
        cout<< "b"<< i << " = " << tabB[i] << endl;
    }
}

int main()
{   
    //ODCZYTYWANIE WARTOSCI Z PLIKU DO ZMIENNYCH
    string filename("MN-2-p2.txt");
    int number;
    double number1, number2;
    
    ifstream input_file(filename);

    //SPRAWDZENIE CZY PLIK SIE OTWIERA
    if (!input_file.is_open()) {
        cerr << "Plik sie nie otwiera '"<< filename << "'" << endl;
        return -1;
    }
    //PIERWSZA LICZBA W PLIKU TEKSTOWYM OZNACZA ILOSC WEZLOW
    int il_wezlow;
    input_file >> il_wezlow;

    //ZAPISUJE WEZLY I WARTOSCI FUNKCJI W DWOCH OSOBNYCH TABELACH
    double *wezly = new double[il_wezlow];
    double *wartosci = new double[il_wezlow];

    int i = 0;
    while (input_file >> number1 && input_file >> number2 && i < il_wezlow) {
        wezly[i] = number1;
        wartosci[i] = number2;
        i++;
    }
    input_file.close();

    oblInterNewt(il_wezlow, wezly, wartosci);


    delete [] wezly;
    delete [] wartosci;
    return 0;
}