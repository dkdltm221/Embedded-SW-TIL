#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <string.h>
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))
#include "day3_lib.h"

#if 1

int main(void){
    int a[3][4] = {0};
    printf("%d\n",sizeof(a[-1]));
}

#endif