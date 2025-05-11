#include "sweeper.h"
#include <iostream>

using namespace std;

int main(void){
    field plot = init_game();
    end_game(plot, game_loop(plot));
    return 0;
}

void end_game(field& plot, bool clear){
    if(!clear) reveal_mines(plot);
    print_field(plot, clear);
    print_result(clear);
}

int input_error(){
    cout << "Wrong format of input" << endl;
    return 1;
}

bool game_loop(field& plot){
    while(plot.remaining>plot.mines){
        pair<int,int> coord;
        char action = 'c';
        // Väliaikainen käyttäjäsyöte, kunnes saadaan graafinen käyttöliittymä
        cout << "Give coordinates and an action [flag(f) or clear( )]: ";
        string line;
        getline(cin >> ws, line);
        if(sscanf(line.c_str(), "%d %d %c", &coord.first, &coord.second, &action) != 3){
            input_error();
            continue;
        };
        // Toimitaan käyttäjän syötteen mukaan
        if(action == 'f') set_flag(plot, coord); // Lipun asettaminen
        else if(action != 'c') cout << KRED << "Invalid input!" << KSTD << endl; // Virheellinen syöte
        else if(reveal_tiles(plot, coord, false)) return false; // Ruudun paljastaminen
        // Tulostus
        print_field(plot, false);
        print_statusbar(plot);
    }
    return true;
}

field init_game(){
    //Käyttäjäsyöte kentän kokoa ja miinoja varten
    pair<int,int> size;
    int mines;
    while (true) {
        cout << "Give height and width of field and amount of mines: ";
        string line;
        getline(cin >> ws, line);
        if (sscanf(line.c_str(), "%d %d %d", &size.first, &size.second, &mines) == 3) {
            break; // Päästään ulos loopista kun syöte onnistuu
        }
        input_error();
    }
    pair<int,int> coord;
    // Väliaikainen käyttäjäsyöte, kunnes saadaan graafinen käyttöliittymä
    while (true) {
        cout << "Give starting coordinates: ";
        string line;
        getline(cin >> ws, line);
        if (sscanf(line.c_str(), "%d %d", &coord.first, &coord.second) == 2) {
            break; // Päästään ulos loopista kun syöte onnistuu
        }
        input_error();
    }
    // Luodaan kenttä
    field plot = create_field(size.first,size.second,mines,coord);
    reveal_tiles(plot, coord, false);
    // Tulostus
    print_field(plot, false);
    print_statusbar(plot);
    return plot;
}

