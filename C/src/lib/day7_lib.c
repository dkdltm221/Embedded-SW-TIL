#include "day7_lib.h"

int sum(int x, int y){
    return x+y;
}
int sub(int x,int y){
    return x-y;
}
int mul(int x,int y){
    return x*y;
}
int divi(int x,int y){
    return x / y;
}
int mod(int x,int y){
    return x % y;
}

//day3_lib 사용
// a>b : 양수
// a == 0
// a< b :음수
// 자료형과 상관없이 어떤 타입이 오던지 해당 로직을 정상적으로 수행해야한다..

int compDouble(const void*a,const void*b){
    if(*(double*)a == *(double*)b ) return 0;
    return *(double*)a > *(double*)b ? 1 : -1 ; 
}

void print_doubledata(double* arr, int n){
    for(int i=0;i<n;i++){
        printf("%.2lf ",arr[i]);
    }
    printf("\n");
}

void print_strdata(char** c,int n){
    for(int i=0;i<n;i++){
        printf("%s ",c[i]);
    }
    printf("\n");
}
int compStr(const void*a,const void* b){
    return strcmp(*(char *const *)a, *(char *const *)b);
}

void print_2Darr(int (*arr)[3], int r,int c){
    for(int i=0;i<r;i++){
        for(int j =0;j<c;j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int comp2D(const void* a,const void* b){
    int* arr = *(int(*)[3])a  ;
    int* arrb = *(int(*)[3])b;
    return arr[1]-arrb[1];
    
}
