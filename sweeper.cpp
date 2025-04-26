#include "sweeper.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;

// Miinojen paljastaminen hävittäessä
void reveal_mines(field& plot){
    for(int i = 0; i < plot.rows; ++i) {
        for(int j = 0; j < plot.cols; ++j) {
            if(plot.realsquare[i][j] < 0){
                plot.vissquare[i][j] = plot.realsquare[i][j];
            }
        }
    }
}

// Lippujen asettaminen
void set_flag(field& plot, pair<int,int> coord){
    // Jos on jo olemassa lippu, poistetaan se
    if(plot.vissquare[coord.first][coord.second] >= 10){
        plot.vissquare[coord.first][coord.second] -= 10;
        plot.flags--;
    }
    else{ // Uuden lipun asettaminen
        plot.vissquare[coord.first][coord.second] += 10;
        plot.flags++;
    }
}

// Ruutujen paljastus
bool reveal_tiles(field& plot, pair<int,int> coord, bool recursive){
    int x = coord.first;
    int y = coord.second;
    /* LISÄÄ TÄHÄN TARKISTUS SIITÄ, JOS PAINETTU RUUTU ON JO PALJASTETTU JA SEN YMPÄRILLÄ ON OIKEA MÄÄRÄ LIPPUJA
        --> TÄLLÖIN PALJASTETAAN YMPÄRÖIVÄT RUUDUT JA TARKISTETAAN MIINOILTA
            --> JOS MIINA EI LIPUTETUSSA RUUDUSSA, LOPETETAAN PELI */

    // Jos ruudussa lippu, ohitetaan
    if(!recursive && plot.vissquare[x][y] >= 10) return false;
    // Poistetaan liput rekursiivisessa kutsussa
    else if(recursive && plot.vissquare[x][y] >= 10){
        plot.vissquare[x][y] -= 10;
        plot.flags--;
    }
    // Jos ruutu on jo paljastettu, palataan takaisin
    if(plot.vissquare[x][y] < 9) return false; 
    // Jos painettu ruutu on miina, lopetetaan peli
    else if(plot.realsquare[x][y] == -1){
        plot.realsquare[x][y] = -2;
        return true;
    }
    // Jos painettu ruutu on tyhjä(0)
    else if(plot.realsquare[x][y] == 0){
        plot.vissquare[x][y] = plot.realsquare[x][y];
        plot.remaining--; // päivitetään piilotettujen ruutujen määrä
        // Kun painettu ruutu on tyhjä(0), niin päivitetään rekursiivisesti ympäröivät ruudut
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int ni = x + dx;
                int nj = y + dy;
                if(dx == 0 && dy == 0) continue;
                if(ni >= 0 && ni < plot.rows && nj >= 0 && nj < plot.cols && plot.realsquare[ni][nj] != -1) {
                    pair<int,int> coord2 = {ni,nj};
                    reveal_tiles(plot, coord2, true);
                    }
                }
            }
        }
    // Jos painettu ruutu on miinan vieressä
    else{
        plot.vissquare[x][y] = plot.realsquare[x][y];
        plot.remaining--; // päivitetään piilotettujen ruutujen määrä
    }
    return false;
}

// Kentän luonti
field create_field(int row, int col, int mine, pair<int,int> coord){
    field plot;
    plot.rows = row;
    plot.cols = col;
    plot.mines = mine;
    plot.flags = 0;
    plot.remaining = row * col;
    plot.realsquare.resize(row, vector<int>(col, 0));
    plot.vissquare.resize(row, vector<int>(col, 9));
    // Miinojen satunnaistaminen
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1,10000);
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            plot.realsquare[i][j] = dist(gen);
        }
    }
    // Asetetaan käyttäjän syöte nollaksi
    plot.realsquare[coord.first][coord.second] = 0;
    // Alkioiden järjestely satunnaisnumeron mukaan
    vector<int> vec;
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            vec.push_back(plot.realsquare[i][j]);
            }
        }
    sort(vec.begin(), vec.end(), greater<int>());
    // Tarkistetaan raja-tapausten varalta
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
    // Asetetaan oikea määrä miinoja
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            if(plot.realsquare[i][j] >= vec[plot.mines-1]){
                plot.realsquare[i][j] = -1;
            }
            else plot.realsquare[i][j] = 0;
        }
    }
    // Päivitetään ympäröivät ruudut    
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