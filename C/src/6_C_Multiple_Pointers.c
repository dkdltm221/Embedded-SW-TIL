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

#if 1

int main(void){
    int a = 10, b=5;
    int *ap = &a, *bp =&b;
    int** app = &ap, **bpp = &bp;

    
    return 0;
}

#endif