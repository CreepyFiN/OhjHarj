#include <cstdlib>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct{
    int rows;
    int cols;
    int bombs;
    vector<vector<int>> square;
} field;


field createfield(int, int, int);
void printfield(field);

int main(void){
    field plot = createfield(20,30,60);
    printfield(plot);
    return 0;
}

// Tulostus
void printfield(field plot){
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            printf("%2d ", plot.square[i][j]);
        }
        printf("\n");
    }
}

// Kentän luonti
field createfield(int row, int col, int bomb){
    field plot;
    plot.rows = row;
    plot.cols = col;
    plot.bombs = bomb;
    plot.square.resize(row, vector<int>(col, 0));
    // Pommien satunnaistaminen
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1,10000);
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            plot.square[i][j] = dist(gen);
        }
    }
    // Alkioiden järjestely satunnaisnumeron mukaan
    vector<int> vec;
    int z = 0;
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            vec.push_back(plot.square[i][j]);
            }
        }
    sort(vec.begin(), vec.end(), greater<int>());
    // Tarkistetaan raja-tapausten varalta
    if(vec[plot.bombs-1] == vec[plot.bombs]){
        int h = 2;
        int b2 = 0;
        while(true){
            if(vec[plot.bombs-h] != vec[plot.bombs-1]  || (plot.bombs-h) < 0) break;
            h++, b2--;
        }
        for(int i = 0; i < plot.rows; i++){
            for (int j = 0; j < plot.cols; j++){
                if(plot.square[i][j] == vec[plot.bombs-1]){
                    if(b2 > 0) plot.square[i][j] = 0;
                    else b2++;
                }
            }
        }
    }
    // Asetetaan oikea määrä pommeja
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            if(plot.square[i][j] >= vec[plot.bombs-1]){
                plot.square[i][j] = -1;
            }
            else plot.square[i][j] = 0;
        }
    }
    // Päivitetään ympäröivät ruudut
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (plot.square[i][j] == -1) {
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        int ni = i + dx;
                        int nj = j + dy;
                        if (dx == 0 && dy == 0) continue;
                        if (ni >= 0 && ni < row && nj >= 0 && nj < col && plot.square[ni][nj] != -1) {
                            plot.square[ni][nj]++;
                        }
                    }
                }
            }
        }
    }
    return plot;
}