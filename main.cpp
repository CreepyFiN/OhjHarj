#include "sweeper.h"
#include <iostream>

using namespace std;

int main(void){
    field plot = init_game();
    end_game(plot, game_loop(plot));
    return 0;
}

void end_game(const field& plot, int clear){
    print_field(plot, clear);
    if(!clear) cout << "YOU LOST!" << endl;
    else cout << "VICTORY!"<< endl;
}

int game_loop(field& plot){
    while(plot.remaining>plot.bombs){
        pair<int,int> coord;
        // Väliaikainen käyttäjäsyöte, kunnes saadaan graafinen käyttöliittymä (ei sisällä virheen tarkista)
        cout << "Give a coordinate:";
        scanf("%d %d", &coord.first, &coord.second);
        //
        if(reveal_tiles(plot, coord)) return 0;
        print_field(plot, 2);
        cout << "remaining tiles: " << plot.remaining << endl;
    }
    return 1;
}

field init_game(){
    pair<int,int> coord;
    // Väliaikainen käyttäjäsyöte, kunnes saadaan graafinen käyttöliittymä (ei sisällä virheen tarkista)
    cout << "Give a coordinate:";
    scanf("%d %d", &coord.first, &coord.second);
    //
    field plot = create_field(8,8,5,coord);
    reveal_tiles(plot, coord);
    print_field(plot, 2);
    cout << "Remaining tiles: " << plot.remaining << endl;
    return plot;
}