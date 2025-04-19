#include "sweeper.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;

// Kentän luonti
field create_field(int row, int col, int bomb){
    field plot;
    plot.rows = row;
    plot.cols = col;
    plot.bombs = bomb;
    plot.realsquare.resize(row, vector<int>(col, 0));
    plot.vissquare.resize(row, vector<int>(col, 9));
    // Pommien satunnaistaminen
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1,10000);
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            plot.realsquare[i][j] = dist(gen);
        }
    }
    // Alkioiden järjestely satunnaisnumeron mukaan
    vector<int> vec;
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            vec.push_back(plot.realsquare[i][j]);
            }
        }
    sort(vec.begin(), vec.end(), greater<int>());
    // Tarkistetaan raja-tapausten varalta
    if(vec[plot.bombs-1] == vec[plot.bombs]){
        int h = 2, b2 = 0;
        while(true){
            if(vec[plot.bombs-h] != vec[plot.bombs-1]  || (plot.bombs-h) < 0) break;
            h++, b2--;
        }
        for(int i = 0; i < plot.rows; i++){
            for (int j = 0; j < plot.cols; j++){
                if(plot.realsquare[i][j] == vec[plot.bombs-1]){
                    if(b2 > 0) plot.realsquare[i][j] = 0;
                    else b2++;
                }
            }
        }
    }
    // Asetetaan oikea määrä pommeja
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            if(plot.realsquare[i][j] >= vec[plot.bombs-1]){
                plot.realsquare[i][j] = -1;
            }
            else plot.realsquare[i][j] = 0;
        }
    }
    // Päivitetään ympäröivät ruudut    
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (plot.realsquare[i][j] == -1) {
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        int ni = i + dx;
                        int nj = j + dy;
                        if (dx == 0 && dy == 0) continue;
                        if (ni >= 0 && ni < row && nj >= 0 && nj < col && plot.realsquare[ni][nj] != -1) {
                            plot.realsquare[ni][nj]++;
                        }
                    }
                }
            }
        }
    }
    return plot;
}