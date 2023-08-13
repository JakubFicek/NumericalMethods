#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void calcPolynInter(int no_of_nodes, float* nodes, float* values) {
    float pkt;
    cout << "Point to calculate value of polynomial: ";
    cin >> pkt;
    float *tabL = new float[no_of_nodes];
    for (int i = 0; i < no_of_nodes; i++) {
        tabL[i] = 1;
    }

    for (int i = 0; i < no_of_nodes; i++) {
        for(int j = 0; j < no_of_nodes; j++){
            if(i != j ) {
                tabL[i] *= (pkt - nodes[j])/(nodes[i] - nodes[j]);
            }
        }
    }

    float wynik = 0;
    for (int i = 0; i < no_of_nodes; i++) {
        wynik += tabL[i]*values[i];
    }

    cout << "No. Nodes: " << no_of_nodes << endl;
    cout << "Node - Value: " << endl;
    for(int i = 0; i < no_of_nodes; i++){
        cout<< nodes[i]<< " ____ " << values[i] << endl;
    }
    cout << endl << "Node to calculate: " << pkt << endl;
    cout << "Value in this node: " << wynik << endl << endl << endl;
}

int main()
{   
    string filename("data2.txt");
    int number;
    float number1, number2;
    
    ifstream input_file(filename);

    if (!input_file.is_open()) {
        cerr << "File is not opening '"<< filename << "'" << endl;
        return -1;
    }
    int no_of_nodes;
    input_file >> no_of_nodes;

    float *nodes = new float[no_of_nodes];
    float *values = new float[no_of_nodes];

    int i = 0;
    while (input_file >> number1 && input_file >> number2 && i < no_of_nodes) {
        nodes[i] = number1;
        values[i] = number2;
        i++;
    }
    input_file.close();

    calcPolynInter(no_of_nodes, nodes, values);

    delete [] nodes;
    delete [] values;
    return 0;
}