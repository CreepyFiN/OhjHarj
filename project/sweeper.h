#ifndef SWEEPER_H
#define SWEEPER_H
#include <vector>
#include <utility>

struct field {
    int rows; // Number of rows
    int cols; // Number of columns
    int mines; // Number of mines
    int remaining; // Hidden tiles remaining
    int flags; // Number of flags
    std::vector<std::vector<int>> realsquare; // Actual minefield
    std::vector<std::vector<int>> vissquare; // Visible minefield
};

field init_game(int rows, int cols, int mines);
field create_field(int row, int col, int mine, std::pair<int,int> coord);
bool reveal_tiles(field& plot, std::pair<int,int> coord, bool recursive);
void set_flag(field& plot, std::pair<int,int> coord);
void reveal_mines(field& plot);
void setLeftClickCoord(int row, int col);
std::pair<int, int> getLeftClickCoord();

#endif