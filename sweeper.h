#ifndef SWEEPER_H
#define SWEEPER_H
#include <vector>

using namespace std;

typedef struct{
    int rows; // rivien lkm
    int cols; // sarakkeiden lkm
    int mines; // miinojen lkm
    int remaining; // piilotettujen ruutujen lkm
    int flags; // lippujen lkm
    vector<vector<int>> realsquare; // Oikea ruudukko
    vector<vector<int>> vissquare; // Näkyvä ruudukko
} field;

field init_game();
field create_field(int, int, int, pair<int,int>);
bool game_loop(field&);
bool reveal_tiles(field&, pair<int,int>, bool);
void print_field(const field&, bool);
void set_flag(field&, pair<int,int>);
void reveal_mines(field&);
void end_game(field&, bool);

#endif