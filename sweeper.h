#ifndef SWEEPER_H
#define SWEEPER_H
#include <vector>

using namespace std;

typedef struct{
    int rows; // rivien määrä
    int cols; // sarakkeiden määrä
    int bombs; // pommien määrä
    int remaining; // piilotettujen ruutujen määrä
    vector<vector<int>> realsquare; // Oikea ruudukko
    vector<vector<int>> vissquare; // Näkyvä ruudukko
} field;

void end_game(field, int);
field init_game();
int game_loop(field&);
int reveal_tiles(field&, pair<int,int>);
field create_field(int, int, int, pair<int,int>);
void print_field(const field&, int);

#endif