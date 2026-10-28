#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <string.h>
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))
#include "day6_lib.h"

#if 0

int main(void){
    int a[3][4] = {0};
    printf("%d\n",sizeof(a[-1]));
}

#endif

#if 0

int main(void){
    int a[3][4] = {100,2,3,4,5,6,7,8,9,10,11,12};
    print_2D(&a);

}


#endif

#if 0

int main(void){
    int a = 10, b=5;
    int *ap = &a, *bp =&b;
    int** app = &ap, **bpp = &bp;

    
    return 0;
}

#endif

#if 1

int add(int a,int b){
    return a+b;
}

void func1(int (*p)(int,int)){
    printf("%d\n",p(10,20));
}

void func2(int (**pa)(int,int)){
    printf("%d\n",(*pa)(10,20));
}

int main(void){

    int arr[10] = {0};
    int a = 10,b=20;
    int (*p)(int,int);
    int (*pa[5])(int,int) = {add,};
    p = add;
    printf("%d + %d  = %d\n",a,b,p(a,b));

    func1(p);
    func2(pa);
    //함수는 상수이다.
    printf("%p %p %p\n",add,*add,**add);
    //이친구는 상수이지만 *을 붙이는순가 참조해버림 그래서안댜
    //printf("%p %p %p\n",arr,*arr,**arr);
    
    return 0;
}

#endif