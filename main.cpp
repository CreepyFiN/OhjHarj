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
        // Väliaikainen käyttäjäsyöte, kunnes saadaan graafinen käyttöliittymä (ei sisällä virheen tarkistusta)
        cout << "Give coordinates and an action [flag(f) or clear( )]: ";
        string line;
        getline(cin >> ws, line);
        sscanf(line.c_str(), "%d %d %c", &coord.first, &coord.second, &action);
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
    /* LISÄÄ KÄYTTÄJÄSYÖTE KENTÄN KOKOA JA MIINOJA VARTEN */
    cout << "Give height and width of field and amount of mines: " >>;
    if(scanf("%d %d %d", &field.rows, &field.cols, &field.mines) != 3){
        cout << "Wrong format of input!" >>;
        init_game();
    }
    pair<int,int> coord;
    // Väliaikainen käyttäjäsyöte, kunnes saadaan graafinen käyttöliittymä (ei sisällä virheen tarkistusta)
    cout << "Give starting coordinates: ";
    scanf("%d %d", &coord.first, &coord.second);
    // Luodaan kenttä
    field plot = create_field(10,10,5,coord);
    reveal_tiles(plot, coord, false);
    // Tulostus
    print_field(plot, false);
    print_statusbar(plot);
    return plot;
}