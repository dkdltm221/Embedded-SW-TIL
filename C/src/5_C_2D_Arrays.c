#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <string.h>
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))
#include "day3_lib.h"
#if 0

void func(char(*p)[10]){
    printf("%d %d\n",sizeof(p),sizeof(*p));
}

void func2(char (*p)[5][10]){
    printf("%d %d\n",sizeof(p),sizeof(*p));
}

void func3(char* p[5][10]){ //이건 무엇이나올것인가
    printf("%d %d\n",sizeof(p),sizeof(*p));
}
void func4(char** p){
    printf("%d %d %d\n",sizeof(p),sizeof(*p),sizeof(**p));
}
char (*func5(void)){
    static char str[5][10] = {"apple","banana","kiwi","melon","orange"};
    return str; // char(*)[10];
}
int main(void){
    char str[5][10] = {0};
    char* str2[5][10] = {0};
    char* str[5] = {"apple","banana","kiwi"};
    printf("%d %d %d\n",sizeof(str[0]),sizeof(*str),sizeof(*(str+2)));
    func(str);
    func2(&str);
    func3(str2);
    char (*p)[10] = func5(); // 문제점 몇개있는지를 모름
    
    return 0;
}

#endif

#if 0

// a,b 값이 copy
void func1(int a, int b){
    a = 20;
}
// int가 저장된 메모리의 주소 2개를 copy -> 주소에 접근해서 int값을 읽거나 쓰기 할 수 있음
void func2(int* ap,int* bp){
    int temp = *ap;
    *ap = *bp;
    *bp = temp;
}

void func3(int (*p1)[5],int *p2){
    for(int i=0;i<5;i++){
        p2[i]+= 5;
    }
}
//p[0][1] = (*p)[1],*((*p)+1),*(p[0]+1)
//p[1][2] = *(*(p+1)+2), *(p[1]+2), (*(p+1))[2]
//p[1][2][3] = *(*(*(p+1)+2)+3),(*(p[1]+2))[3],(*(p+1))[2][3],  *((*(p+1))[2]+3) , *(*(p[1]+2)+3),*(p[1][2]+3)
//p[3][0] = **(p+3),(*(p+3))[0], *(p[3])

void func4(int (*p1)[5]){
    for(int i=0;i<SIZE(*p1);i++) (*p1)[i]+= 5;
}

int main(void){
    int a = 10, b= 20;
    printf("%d %d\n",a,b);
    func2(&a,&b); // func2에게 a,b변수에 접근해서 R/W를 할 수 있도록 허용
    printf("%d %d\n",a,b);

    int arr[5] = {1,2,3,4,5};
    printf("%p %p %p\n",&arr,arr,&arr[0]);
    print_data(arr,SIZE(arr));
    func3(&arr,arr);
    print_data(arr,SIZE(arr));
    func4(&arr);
    print_data(arr,SIZE(arr));
    return 0;
}

#endif

#if 1

void func1(int(*p)[4],int r){
    int c = sizeof(*p)/sizeof((*p)[0]);
    
    for(int i=0;i<r*c;i++) printf("%d ",*(*p+i));
    printf("\n");
}
// 개수만 유지된다면 형변환을 자유롭게 할수있다.
void func2(int(*p)[4],int r){
    int c = SIZE(*p);
    int n = r*c;
    int (*p2)[6] = (int(*)[6]) p;
    c = 6; r = n/c;
    //3차원
    int (*p3)[2][3] = (int(*)[2][3])p;
}

void func3(int(*p)[3][4]){
    int r = SIZE(*p);
    int c = SIZE((*p)[0]);
    printf("%d %d\n",r,c);
}

void func4(int(*p)[2][3][4]){
    int k = sizeof(*p)/sizeof(**p);
    int r = sizeof(**p)/sizeof(***p);
    int c = sizeof(***p)/sizeof(****p);
    printf("%d %d %d\n",k,r,c);

}

int main(void){
    int arr[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
    int b[2][3][4] = {0};
    //func1(arr, 3);
    //func2((int*)arr,12);
    func3(&arr);
    func4(&b);
    return 0;
}

#endif