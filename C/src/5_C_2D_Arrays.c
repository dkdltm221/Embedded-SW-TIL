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

int main(void){
    char str[5][10] = {0};
    char* str2[5][10] = {0};
    printf("%d %d %d\n",sizeof(str[0]),sizeof(*str),sizeof(*(str+2)));
    func(str);
    func2(&str);
    func3(str2);
    return 0;
}

#endif