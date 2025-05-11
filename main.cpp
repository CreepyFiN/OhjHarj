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

bool game_loop(field& plot){
    while(plot.remaining>plot.mines){
        pair<int,int> coord;
        char action = 'c';
        bool breakloop = false;
        // Väliaikainen käyttäjäsyöte, kunnes saadaan graafinen käyttöliittymä
        while(!breakloop){
            cout << "Give coordinates and an action [flag(f) or clear( )]: ";
            string line;
            getline(cin >> ws, line);
            switch (sscanf(line.c_str(), "%d %d %c", &coord.first, &coord.second, &action))
            {
            case 2:
                if(action == 'c') breakloop = true;
                break;
            case 3:
                if(action == 'c' || action == 'f') breakloop = true;
                break;
            default:
                break;
            }
            if(!breakloop) input_error();
        }
        // Toimitaan käyttäjän syötteen mukaan
        if(action == 'f') set_flag(plot, coord); // Lipun asettaminen
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
    while(true){
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
    while(true){
        cout << "Give starting coordinates: ";
        string line;
        getline(cin >> ws, line);
        if (sscanf(line.c_str(), "%d %d", &coord.first, &coord.second) == 2) {
            break; // Päästään ulos loopista kun syöte onnistuu
        }
        input_error();
    }
    // Luodaan kenttä
    field plot = create_field(size.first, size.second, mines, coord);
    reveal_tiles(plot, coord, false);
    // Tulostus
    print_field(plot, false);
    print_statusbar(plot);
    return plot;
}

