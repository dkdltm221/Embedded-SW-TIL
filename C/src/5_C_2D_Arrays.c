#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <string.h>
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

#if 1

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