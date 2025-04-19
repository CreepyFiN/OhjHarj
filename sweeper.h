#ifndef SWEEPER_H
#define SWEEPER_H
#include <vector>

using namespace std;

typedef struct{
    int rows;
    int cols;
    int bombs;
    vector<vector<int>> realsquare;
    vector<vector<int>> vissquare;
} field;

field create_field(int, int, int);
void print_field(const field&);

#endif