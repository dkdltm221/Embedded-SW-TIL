#include "day7_lib.h"
#include "day3_lib.h"

#if 1
int main(void){
    int ary[] = {8,5,2,12,7,9,4,6,10,3};
    print_data(ary,SIZE(ary));
    sort_data2(ary, SIZE(ary),comp_desc);
    print_data(ary,SIZE(ary));

    return 0;
}
#endif

//화면에 메뉴 출력 1. sum 2. sub .. 0. exit
// 메뉴 항목을 의미하는 숫자를 입력 받아 동작하고, 다시 메뉴를 출력하는 동작을 반복
// 사용자가 0을 입려갛면 프로그램 종료

#if 0

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
    my_t* p = funcs;
    

    
    return 0;
}

#endif