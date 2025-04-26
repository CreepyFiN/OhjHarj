#include "sweeper.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;

// Tulostus
void print_field(const field& plot, int clear){
    // Oikea ruudukko
    if(!clear){
        for(int i = 0; i < plot.rows; i++){
            for (int j = 0; j < plot.cols; j++){
                if(plot.realsquare[i][j] == -10) cout << "\033[31m" << setw(3) << "X" <<"\033[0m"; // Räjähtänyt pommi
                else if(plot.realsquare[i][j] == -1) cout << "\033[31m" << setw(3) << "M" <<"\033[0m"; // Muut pommit
                else cout << setw(3) << plot.realsquare[i][j]; // Tavallinen ruutu
            }
            cout << endl;
        }
    }
    // Näennäinen ruudukko
    else{
        for(int i = 0; i < plot.rows; i++){
            for (int j = 0; j < plot.cols; j++){
                if(plot.vissquare[i][j] == -2) cout << "\x1B[32m" << setw(3) << "F" <<"\033[0m"; // Lippu
                else if(clear == 1 && plot.vissquare[i][j] == 9) cout << "\033[32m" << setw(3) << "M" <<"\033[0m"; // Purettu miina
                else if(plot.vissquare[i][j] == 9) cout << "\033[90m" << setw(3) << "H" <<"\033[0m"; // Piilotettu ruutu
                else cout << setw(3) << plot.vissquare[i][j]; // Tavallinen ruutu
            }
            cout << endl;
        }
    }
}