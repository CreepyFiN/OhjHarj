#include "sweeper.h"
#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;

// Virheellisen syötteen tulostus
void input_error(){
    cout << KRED << "Wrong format of input" << KSTD << endl;
}

// Loppuviestin tulostus
void print_result(bool clear){
    // Viestin asettaminen
    string end_msg = clear ? KGRN " GAME CLEAR! YOU WON! " : KRED " GAME OVER! YOU LOST! ";
    string frame_long = KYEL "==================================" KSTD;
    string frame_short = KYEL "======" KSTD;
    // Tulostaminen
    cout << endl << frame_long << endl;
    cout << frame_short << end_msg << frame_short;
    cout << endl << frame_long << endl;
}

// Ruutujen ja lippujen lkm tulostus
void print_statusbar(const field& plot){
    cout << "Remaining tiles: " << KGRY << plot.remaining << KSTD << endl;
    cout << "Tiles flagged: " << KGRY << plot.flags << KSTD << endl;
}

// Kentän Tulostus
void print_field(const field& plot, bool clear){
    cout << setw(3) << " ";
    for(int i = 0; i < plot.cols; i++) cout << KBLU << setw(3) << i << KSTD; // Kentän koordinaatit (sarake)
    cout << endl;
    for(int i = 0; i < plot.rows; i++){
        cout << KBLU << setw(3) << i << KSTD; // kentän koordinaatit (rivi)
        for (int j = 0; j < plot.cols; j++){
            if(plot.vissquare[i][j] == 19) cout << KGRN << setw(3) << "F" << KSTD; // Lippu piilotetulla ruudulla
            else if(plot.vissquare[i][j] >= 10) cout << KYEL << setw(3) << "F" << KSTD; // Lippu jo paljastetulla ruudulla
            else if(plot.vissquare[i][j] == -2) cout << KRED << setw(3) << "X" << KSTD; // Räjähtänyt miina
            else if(plot.vissquare[i][j] == -1) cout << KRED << setw(3) << "M" << KSTD; // Muut miinat
            else if(clear && plot.vissquare[i][j] == 9) cout << KGRN << setw(3) << "M" << KSTD; // Purettu miina
            else if(plot.vissquare[i][j] == 9) cout << KGRY << setw(3) << "H" << KSTD; // Piilotettu ruutu
            else cout << setw(3) << plot.vissquare[i][j]; // Tavallinen ruutu
        }
        cout << endl;
    }
}