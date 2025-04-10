#include <cstdlib>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct{
    int rows;
    int cols;
    vector<vector<int>> square;
} field;

int main(void){
    field plot;
    plot.rows = 15;
    plot.cols = 15;
    plot.square.resize(plot.rows, vector<int>(plot.cols, 0));
    int bombs = 50;

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
    if(vec[bombs-1] == vec[bombs]){
        int h = 2;
        int b2 = 0;
        while(true){
            if(vec[bombs-h] != vec[bombs-1] || (bombs-h) < 0) break;
            h++, b2--;
        }
        for(int i = 0; i < plot.rows; i++){
            for (int j = 0; j < plot.cols; j++){
                if(plot.square[i][j] == vec[bombs-1]){
                    if(b2 > 0) plot.square[i][j] = 0;
                    else b2++;
                }
            }
        }
    }

    // Asetetaan oikea määrä pommeja
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            if(plot.square[i][j] >= vec[bombs-1]){
                plot.square[i][j] = -1;
            }
            else plot.square[i][j] = 0;
        }
    }
    
    // Päivitetään ympäröivät ruudut
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            if(plot.square[i][j] == -1){
                if(i != 0 && j != 0){
                    if(plot.square[i-1][j-1] != -1) plot.square[i-1][j-1]++;
                }
                if(j != 0){
                    if(plot.square[i][j-1] != -1) plot.square[i][j-1]++;
                }
                if(i != (plot.rows-1) && j != 0){
                    if(plot.square[i+1][j-1] != -1) plot.square[i+1][j-1]++;
                }
                if(i != 0) {
                    if(plot.square[i-1][j] != -1) plot.square[i-1][j]++;
                }
                if(i != (plot.rows-1)) {
                    if(plot.square[i+1][j] != -1) plot.square[i+1][j]++;
                }
                if(i != 0 && j != (plot.cols-1)) {
                    if(plot.square[i-1][j+1] != -1) plot.square[i-1][j+1]++;
                }
                if(j != (plot.cols-1)) {
                    if(plot.square[i][j+1] != -1) plot.square[i][j+1]++;
                }
                if(i != (plot.rows-1) && j != (plot.cols-1)) {
                    if(plot.square[i+1][j+1] != -1) plot.square[i+1][j+1]++;
                }
            }
        }
    }

    // Tulostus
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            printf("%2d ", plot.square[i][j]);
        }
        printf("\n");
    }

    return 0;
}