#include "sweeper.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;

// Tulostus
void print_field(const field& plot){
    // Oikea kenttä
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            cout << setw(3);
            if(plot.realsquare[i][j] == -1) cout << "M";
            else cout << plot.realsquare[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
    // Näennäinen kenttä
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            cout << setw(3);
            if(plot.vissquare[i][j] == -1) cout << "M";
            else if(plot.vissquare[i][j] == 9) cout << "H";
            else cout << plot.vissquare[i][j];
        }
        cout << "\n";
    }
}