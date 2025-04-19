#include "minesweeper.h"

int main(void){
    field plot = create_field(15,15,50);
    print_field(plot);
    return 0;
}