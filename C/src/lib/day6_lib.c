#include "day6_lib.h"

void print_2D(int(*p)[3][4]){
    int r = SIZE(*p);
    int c = SIZE(**p);
    for(int i=0; i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d ",(*p)[i][j]);
        }
    }
}