#include "day7_lib.h"
#include "day3_lib.h"







#if 0
int main(void){
    void* vp;
    int a= 10;
    double b = 3.14;
    vp = &a;
    printf("%d\n",*(int*)vp);
    vp = &b;
    printf("%.f\n",*(double*)vp);
    vp = sum;
    printf("%d",(*(int(*)(int,int))vp)(10,20));
    return 0;
}

#endif






#if 0

typedef int (*FP1)(int);
typedef int (*FP2)(int,int);
typedef FP2(*FP3)(int,int);

//int (* (*act(int x, FP1))(int, int))(int, int);


int (*get_function(int no))(int,int){
    static int (*fp[])(int,int) = {sum,sub,mul,divi};
    return fp[no];
}

int main(void){
    int(*function)(int,int);
    function = get_function(1);

    return 0;
}

#endif



#if 0

typedef struct _score_t {
    int kor;
    int eng;
    int mat;
}score_t;
void print_score(score_t* arr, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d %d %d\n", arr[i].kor, arr[i].eng, arr[i].mat);
    }
    printf("\n");
}
int compScore(const void* a, const void* b) {
    score_t* s = (score_t*)a;
    score_t* c = (score_t*)b;
    return s->mat - c->mat;
}
int main(void){
    int ary[] = {8,5,2,12,7,9,4,6,10,3};
    double dary[] = {3.1456,3.1466 , 4.56 , 8.12, 1.34, 5.89, 3.135 , 2.44};
    char* sary[] = {"kiwi","banana","melon","apple","orange"};
    int arr[][3] = { {1,3,5},{3 , 1, 2},{ 2, 4, 1}};
    print_2Darr(arr,SIZE(arr),SIZE(arr[0]));
    qsort(arr,SIZE(arr),sizeof(arr[0]),comp2D);
    print_2Darr(arr,SIZE(arr),SIZE(arr[0]));

    score_t stu[5]={{80,90,85}, { 100,80,70}, { 90,95,100},{88,77,50},{60,30,20}};
 
    qsort(stu,SIZE(stu),sizeof(stu[0]),compScore);
    print_score(stu,SIZE(stu));
    // print_strdata(sary,SIZE(sary));
    // qsort(sary,SIZE(sary),sizeof(sary[0]),compStr);
    // print_strdata(sary,SIZE(sary));

    // print_data(ary,SIZE(ary));
    // sort_data2(ary, SIZE(ary),comp_desc);
    // print_data(ary,SIZE(ary));
    // qsort(ary,SIZE(ary),sizeof(ary[0]),compInt);
    // print_data(ary,SIZE(ary));

    // print_doubledata(dary, SIZE(dary));

    // qsort(dary, SIZE(dary), sizeof(dary[0]), compDouble);
    // print_doubledata(dary, SIZE(dary));

    

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
