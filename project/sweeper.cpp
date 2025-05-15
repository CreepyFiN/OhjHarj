#include "sweeper.h"
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

std::pair<int, int> g_leftClickCoord = {-1, -1};

// Setting coordinates from click
void setLeftClickCoord(int row, int col) {
    g_leftClickCoord = {row, col};
}

// Getting coordinates from click
std::pair<int, int> getLeftClickCoord() {
    return g_leftClickCoord;
}

// Game initiation
field init_game(int rows, int cols, int mines) {
    pair<int,int> coord = getLeftClickCoord();  // Taking the coordinate of the clicked tile
    if (coord.first == -1 || coord.second == -1) {
        std::cerr << "Virhe: ei ensimmäistä klikkausta annettu." << std::endl;
        exit(1); // tai muuta virheenkäsittelyä
    }
    field plot = create_field(rows, cols, mines, coord);
    reveal_tiles(plot, coord, false);
    return plot;
}


// Revealing mines upon losing
void reveal_mines(field& plot) {
    for(int i = 0; i < plot.rows; ++i) {
        for(int j = 0; j < plot.cols; ++j) {
            if(plot.realsquare[i][j] < 0){
                plot.vissquare[i][j] = plot.realsquare[i][j];
            }
        }
    }
}

// Setting flags
void set_flag(field& plot, pair<int,int> coord) {
    // Removing old flags
    if(plot.vissquare[coord.first][coord.second] >= 10){
        plot.vissquare[coord.first][coord.second] -= 10;
        plot.flags--;
    }
    // Adding new flags
    else{
        plot.vissquare[coord.first][coord.second] += 10;
        plot.flags++;
    }
}

// Revealing the tiles
bool reveal_tiles(field& plot, pair<int,int> coord, bool recursive) {
    int x = coord.first;
    int y = coord.second;
    // Checking if a visible tile has right number of flags
    if(!recursive && plot.vissquare[x][y] == plot.realsquare[x][y]){
        int flag_count = 0;
        // Checking the number of flags around square
        for(int dx = -1; dx <= 1; ++dx){
            for(int dy = -1; dy <= 1; ++dy){
                int nx = x + dx;
                int ny = y + dy;
                if(dx == 0 && dy == 0) continue;
                if(nx >= 0 && nx < plot.rows && ny >= 0 && ny < plot.cols){
                    if(plot.vissquare[nx][ny] >= 10) flag_count++;
                }
            }
        }
        if(flag_count == plot.realsquare[x][y]){
            // Checking if flags set in right place with recursion
            for(int dx = -1; dx <= 1; ++dx){
                for(int dy = -1; dy <= 1; ++dy){
                    int nx = x + dx;
                    int ny = y + dy;
                    if(dx == 0 && dy == 0) continue;
                    if(nx >= 0 && nx < plot.rows && ny >= 0 && ny < plot.cols){
                        if(plot.vissquare[nx][ny] >= 10) continue; // If the square has a flag, continue
                        if(plot.realsquare[nx][ny] == -1){
                            // Ending game if unflagged mine is hit
                            plot.realsquare[nx][ny] = -2;
                            return true;
                        }
                        if(plot.vissquare[nx][ny] == 9) {
                            if(reveal_tiles(plot, {nx, ny}, true) == true) return true;
                        }
                    }
                }
            }
        }
    }
    // If the tile has a flag, return back
    if(!recursive && plot.vissquare[x][y] >= 10) return false;
    // Removing flags in recursive call
    else if(recursive && plot.vissquare[x][y] >= 10){
        plot.vissquare[x][y] -= 10;
        plot.flags--;
    }
    // If square already visible, return back
    if(plot.vissquare[x][y] < 9) return false; 
    // If mine hit, end game
    else if(plot.realsquare[x][y] == -1){
        plot.realsquare[x][y] = -2;
        return true;
    }
    // If the tile is empty(0)
    else if(plot.realsquare[x][y] == 0){
        plot.vissquare[x][y] = plot.realsquare[x][y];
        plot.remaining--; // Updating the number of hidden tiles
        // Updating the surrounding tiles recursively, if the tile is empty(0)
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int ni = x + dx;
                int nj = y + dy;
                if(dx == 0 && dy == 0) continue;
                if(ni >= 0 && ni < plot.rows && nj >= 0 && nj < plot.cols && plot.realsquare[ni][nj] != -1) {
                    if(reveal_tiles(plot, {ni, nj}, true) == true) return true;
                    }
                }
            }
        }
    // If pressed tile is adjacent to a mine
    else{
        plot.vissquare[x][y] = plot.realsquare[x][y];
        plot.remaining--; // Updating the number of hidden tiles
    }
    return false;
}

// Creating the gamefield
field create_field(int row, int col, int mine, pair<int,int> coord) {
    field plot;
    plot.rows = row;
    plot.cols = col;
    plot.mines = mine;
    plot.flags = 0;
    plot.remaining = row * col;
    plot.realsquare.resize(row, vector<int>(col, 0));
    plot.vissquare.resize(row, vector<int>(col, 9));
    // Randomizing mines
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1,10000);
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            plot.realsquare[i][j] = dist(gen);
        }
    }
    // Setting first click to zero
    plot.realsquare[coord.first][coord.second] = 0;
    // Sorting elements by size
    vector<int> vec;
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            vec.push_back(plot.realsquare[i][j]);
            }
        }
    sort(vec.begin(), vec.end(), greater<int>());
    // Checking for edge-cases
    if(vec[plot.mines-1] == vec[plot.mines]){
        int h = 2, b2 = 0;
        while(true){
            if(vec[plot.mines-h] != vec[plot.mines-1]  || (plot.mines-h) < 0) break;
            h++, b2--;
        }
        for(int i = 0; i < plot.rows; i++){
            for (int j = 0; j < plot.cols; j++){
                if(plot.realsquare[i][j] == vec[plot.mines-1]){
                    if(b2 > 0) plot.realsquare[i][j] = 0;
                    else b2++;
                }
            }
        }
    }
    // Setting the right amount of mines
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            if(plot.realsquare[i][j] >= vec[plot.mines-1]){
                plot.realsquare[i][j] = -1;
            }
            else plot.realsquare[i][j] = 0;
        }
    }
    // Updating surrounding tiles    
    for(int i = 0; i < plot.rows; ++i) {
        for(int j = 0; j < plot.cols; ++j) {
            if(plot.realsquare[i][j] == -1) {
                for(int dx = -1; dx <= 1; ++dx) {
                    for(int dy = -1; dy <= 1; ++dy) {
                        int ni = i + dx;
                        int nj = j + dy;
                        if(dx == 0 && dy == 0) continue;
                        if(ni >= 0 && ni < plot.rows && nj >= 0 && nj < plot.cols && plot.realsquare[ni][nj] != -1) {
                            plot.realsquare[ni][nj]++;
                        }
                    }
                }
            }
        }
    }
    return plot;
}