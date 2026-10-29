#include "day7_lib.h"




typedef struct _my_t{
    int (*fp)(int,int);
    char* name;
    int res;
}my_t;



int main(void){
     
    my_t funcs[] = {
        {sum,"sum"},
        {sub,"sub"},
        {mul,"mul"},
        {divi,"divi"},
        {mod,"mod"}
    }; //구조체 배열

    int a= 25,b=6;

    int totalSum =0;
    for(int i=0;i<SIZE(funcs);i++){
        funcs[i].res = funcs[i].fp(a,b);
        totalSum+=funcs[i].res;
        printf("%s(%d,%d) = %d\n", funcs[i].name,a,b,funcs[i].res);
    }
    
    return 0;
}