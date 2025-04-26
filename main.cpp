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
    if(!clear) cout << "GAME OVER!" << endl;
    else cout << "GAME CLEARED!"<< endl;
}

bool game_loop(field& plot){
    while(plot.remaining>plot.mines){
        pair<int,int> coord;
        char action;
        // Väliaikainen käyttäjäsyöte, kunnes saadaan graafinen käyttöliittymä (ei sisällä virheen tarkistusta)
        cout << "Give coordinates and an action [flag(f) or clear(c)]:";
        scanf("%d %d %c", &coord.first, &coord.second, &action);
        // Toimitaan käyttäjän syötteen mukaan
        if(action == 'f') set_flag(plot, coord);
        else if(action != 'c') cout << "\033[31m" << "Invalid input!" << "\033[0m" << endl;
        else if(reveal_tiles(plot, coord, false)) return false;
        print_field(plot, 0);
        cout << "Remaining tiles: " << plot.remaining << endl;
        cout << "Tiles flagged: " << plot.flags << endl;
    }
    return true;
}

field init_game(){
    pair<int,int> coord;
    // Väliaikainen käyttäjäsyöte, kunnes saadaan graafinen käyttöliittymä (ei sisällä virheen tarkistusta)
    cout << "Give starting coordinates:";
    scanf("%d %d", &coord.first, &coord.second);
    // Luodaan kenttä
    field plot = create_field(8,8,5,coord);
    reveal_tiles(plot, coord, false);
    print_field(plot, 0);
    cout << "Remaining tiles: " << plot.remaining << endl;
    cout << "Tiles flagged: " << plot.flags << endl;
    return plot;
}