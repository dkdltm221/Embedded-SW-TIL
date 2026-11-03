#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define printINT(x) printf(#x" is %d\n",x)//문자열화 연산자
#define printCHAR(x) printf("%c is %c\n",#@x,x) // 문자화연산자
#define cocnat(x,i) printf("%s is %d\n",#i,x##i)


#if 1








#endif

#if 0

#include <assert.h>
#define NDEBUG
int main() {
    int x;
    printf("\nEnter an integer value: ");
    (void)scanf("%d", &x);
    assert(x >= 0);
    printf("You entered %d.", x);
    return(0);
}

#endif

#if 0

#define printINT(x) printf(#x" is %d\n",x)//문자열화 연산자
#define printCHAR(x) printf("%c is %c\n",#@x,x) // 문자화연산자
#define cocnat(x,i) printf("%s is %d\n",#i,x##i)

int main(void){
    int s =10, c = 97 , ca = 7, cb =9;
    printf("hello world\n");
    printINT(s);
    printCHAR(c);
    printINT(c);
    cocnat(c,a); 
    cocnat(c,b);
    return 0;
}


#endif


#if 0

#define ABS(x)(x)>=0 ? x:-(x)
#define MIN(x,y)(x)>(y) ? (y) : (x)
#define MAX(x,y)(x)>(y) ? (x):(y)
#define SWAP(x,y){x = x^y; y=x^y;x= x^y;};

int main(void) {
    int a = 10, b = 20;
    printf("ABS = %d\n", ABS(-10));
    printf("MIN = %d\n", MIN(a, b));
    printf("MAX = %d\n", MAX(a, b));
    SWAP(a, b);
    printf("a = %d, b = %d\n", a, b);
    return 0;
}



#endif