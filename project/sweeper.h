#ifndef SWEEPER_H
#define SWEEPER_H
#include <vector>
#include <utility>

// Värien lisäys syötteeseen
#define KSTD  "\x1B[0m"  // Normaali väri
#define KRED  "\x1B[31m" // Punainen väri
#define KGRN  "\x1B[32m" // Vihreä väri 
#define KYEL  "\x1B[33m" // Keltainen väri
#define KBLU  "\x1B[34m" // Sininen väri 
#define KGRY  "\x1B[90m" // Harmaa väri

struct field {
    int rows; // rivien lkm
    int cols; // sarakkeiden lkm
    int mines; // miinojen lkm
    int remaining; // piilotettujen ruutujen lkm
    int flags; // lippujen lkm
    std::vector<std::vector<int>> realsquare; // Oikea ruudukko
    std::vector<std::vector<int>> vissquare; // Näkyvä ruudukko
};

field init_game(int rows, int cols, int mines);
field create_field(int row, int col, int mine, std::pair<int,int> coord);
bool game_loop(field& plot);
bool reveal_tiles(field& plot, std::pair<int,int> coord, bool recursive);
void set_flag(field& plot, std::pair<int,int> coord);
void reveal_mines(field& plot);
void end_game(field& plot, bool clear);
void setFirstClickCoord(int row, int col);
std::pair<int, int> getFirstClickCoord();

#endif