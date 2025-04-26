#include "sweeper.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;

// Tulostus
void print_field(const field& plot, bool clear){
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            if(plot.vissquare[i][j] == 19) cout << "\x1B[32m" << setw(3) << "F" <<"\033[0m"; // Lippu piilotetulla ruudulla
            else if(plot.vissquare[i][j] >= 10) cout << "\x1B[33m" << setw(3) << "F" <<"\033[0m"; // Lippu jo paljastetulla ruudulla
            else if(plot.vissquare[i][j] == -2) cout << "\033[31m" << setw(3) << "X" <<"\033[0m"; // Räjähtänyt miina
            else if(plot.vissquare[i][j] == -1) cout << "\033[31m" << setw(3) << "M" <<"\033[0m"; // Muut miinat
            else if(clear && plot.vissquare[i][j] == 9) cout << "\033[32m" << setw(3) << "M" <<"\033[0m"; // Purettu miina
            else if(plot.vissquare[i][j] == 9) cout << "\033[90m" << setw(3) << "H" <<"\033[0m"; // Piilotettu ruutu
            else cout << setw(3) << plot.vissquare[i][j]; // Tavallinen ruutu
        }
        cout << endl;
    }
}