#include "sweeper.h"
#include <iostream>

using namespace std;

int main(void){
    field plot = init_game();
    end_game(plot, game_loop(plot));
    return 0;
}

void end_game(field plot, int over){
    print_field(plot, 1);
    if(over) cout << "HAVISIT PELIN!" << endl;
    else cout << "VOITIT PELIN!"<< endl;
}

int game_loop(field& plot){
    while(plot.remaining>plot.bombs){
        pair<int,int> coord;
        // Väliaikainen käyttäjäsyöte, kunnes saadaan graafinen käyttöliittymä (ei sisällä virheen tarkista)
        cout << "Anna koordinaatti:";
        scanf("%d %d", &coord.first, &coord.second);
        //
        if(reveal_tiles(plot, coord)) return 1;
        print_field(plot, 0);
        cout << "remaining tiles: " << plot.remaining << endl;
    }
    return 0;
}

field init_game(){
    pair<int,int> coord;
    // Väliaikainen käyttäjäsyöte, kunnes saadaan graafinen käyttöliittymä (ei sisällä virheen tarkista)
    cout << "Anna koordinaatti:";
    scanf("%d %d", &coord.first, &coord.second);
    //
    field plot = create_field(8,8,5,coord);
    reveal_tiles(plot, coord);
    print_field(plot, 0);
    cout << "remaining tiles: " << plot.remaining << endl;
    return plot;
}