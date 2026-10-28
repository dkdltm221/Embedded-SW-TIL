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

// a,b를 사용해 main에 있는 a,b의 값을 교환한다.
void exchange0(int* a,int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//ap,bp를 변수의 주소를 전달 받아 main에 있는 a,b의 값을 교환한다.
void exchange1(int** a,int** b){
    int temp = **a;
    **a = **b;
    **b=temp;
}

//app,bpp를 변수의 주소를 전달 받아 main에 있는 a,b의 값을 교환한다.
void exchange2(int*** a,int*** b){
    int temp = ***a;
    ***a = ***b;
    ***b=temp;
}


//ap,bp를 변수의 주소를 전달 받아 ap,bp의 값을 교환하는 함수
void exchange3(int** a,int** b){
    int* temp = *a;
    *a = *b;
    *b  = temp;
}


//app,bpp를 변수의 주소를 전달 받아 ap,bp의 값을 교환하는 함수
void exchange4(int*** a,int*** b){
    int *temp = **a;
    **a = **b;
    **b = temp;
}

//app,bpp를 변수의 주소를 전달 받아 app,bpp의 값을 교환하는 함수
void exchange5(int*** a,int*** b){
    int** temp = *a;
    *a = *b;
    *b = temp;
}

