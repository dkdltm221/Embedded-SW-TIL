#include <stdio.h>
#include <limits.h>
#if 0
// 특정 비트를 설정
unsigned int clearBit(unsigned int num, int bitPosition){
    return num & ~(1U << bitPosition);
}
// 특정 비트를 해제
unsigned int setBit(unsigned int num, int bitPosition) {
    return num | (1U << bitPosition);
}
// 특정 비트를 반전
unsigned int toggleBit(unsigned int num, int bitPosition){
    return num ^ (1U << bitPosition);
}

int main(void) {
    unsigned int num = 0b1010;; 
    num = setBit(num, 2); 
    printf("num=%X\n", num); 
    num = clearBit(num, 1);
    printf("num=%X\n", num); 
    num = toggleBit(num, 3);
    printf("num=%X\n", num); 

}
#endif

void printBits(unsigned int num){
    for(int i=sizeof(num)*CHAR_BIT-1U; i>=0;i--){
        printf("%u",(num >> i) & 1U);
    }
    printf("\n");
}

#if 0

//특정 위치부터 특정 개수의 비트를 설정
unsigned int setBits(unsigned int num,int s,int n){
    return num | (((1 << n) - 1) << s);
}

//특정 위치부터 특정 개수의 비트를 해제
unsigned int clearBits(unsigned int num,int s,int n){
    return num & ~(((1 << n) -1) << s);
}

//특정 위치부터 특정 개수의 비트를 반전
unsigned int toggleBits(unsigned int num,int s,int n){
    return num ^ (((1 << n) -1 )<< s);
}

int main(void){
    unsigned int num = 0b10101010;
    num = setBits(num,2,3);
    printf("num=%X\n",num); 
    printBits(num);
    num = clearBits(num,4,2);
    printf("num=%X\n",num); 
    num = toggleBits(num,1,5);
    printf("num=%X\n",num); 

    return 0;
}


#endif

#if 0

static unsigned int isBitSet(unsigned int num,int bitPosition){
    return (num>>bitPosition) & 1U;
}

int main(void){
    unsigned int res = isBitSet(10U,1);

    printf("Bit %d of number %u is %u.\n",1,10U,res);

    return 0;
}
#endif

#if 0
int main(void){
    int a;
    scanf_s("%d",&a);

    int a1 = a/1000;
    int a2 = a/100 % 10;
    int a3 = a/10 %10;
    int a4 = a %10;

    printf("%d %d %d %d",a1,a2,a3,a4);
}

#endif

#if 1

#endif
