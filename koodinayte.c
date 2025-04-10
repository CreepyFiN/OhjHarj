#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int rows;
    int cols;
    int** square;

} field;

int main(void){
    field plot;
    plot.rows = 20;
    plot.cols = 30;

    // Musitin varaaminen
    plot.square = calloc(plot.rows, sizeof(int*));
    for(int i = 0; i < plot.rows; i++){
        plot.square[i] = calloc(plot.cols, sizeof(int));
    }



    // Tulostus
    for(int i = 0; i < plot.rows; i++){
        for (int j = 0; j < plot.cols; j++){
            printf("%d ", plot.square[i][j]);
        }
        printf("\n");
    }

    // Muistin vapautus
    for(int i = 0; i < plot.rows; i++){
        free(plot.square[i]);
    }
    free(plot.square);
    return 0;
}