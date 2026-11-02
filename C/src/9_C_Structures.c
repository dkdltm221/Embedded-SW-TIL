#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdint.h>
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))



#if 1
typedef struct _rgb{
    uint32_t blue:8;
    uint32_t green :8;
    uint32_t red : 8;
}rgb_t;

typedef union _pixel{
    uint32_t color ;
    rgb_t rgb;
}pixel_t;

int main(void){
    pixel_t X={0x123456};
    printf("%X %X %X\n",X.rgb.blue,X.rgb.green,X.rgb.red);

    printf("%d %d \n",sizeof(rgb_t),sizeof(pixel_t));
    return 0;
}

#endif


#if 0



typedef struct bit{
    uint32_t a : 3; //uint32_t unsinged int 32 t타입
    uint32_t b : 3;
    uint32_t c : 3;
}bit_t;


int main(void){
    bit_t X ={1,2,3};
    X = (bit_t){4,5,6};
    printf("%d %d %d\n",X.a,X.b,X.c);
}

#endif







//효율적인 코드(성능에 도움이되는)
#if 0

//성능 좋은 프로그램은 메모리를 어느정도 사용하는게 좋다 성능과 메모리는 트레이드 오프관계와 비슷하다
typedef struct bit{
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
}bit_t;

int main(void){
    bit_t x;
    x.a = 1; //1개의 무브
    x.b =2;
    x.c =3;
    printf("%d %d %d\n", x.a,x.b,x.c);
    return 0;
}
#endif


#if 0

//메모리를 절약한다.
typedef struct bit{
    unsigned int a : 3;
    unsigned int b : 3;
    unsigned int c : 3;
}bit_t;

int main(void){
    bit_t x;
    bit_t* p =&x;
    x.a = 1; //MOV,and,or 등의 연산을 실행 - 효율적이지않음
    x.b =2;
    x.c =3;
    // *(char*)*x  부호비트로인해 F앞에다출력 *(unsigned char*)*x  앞에 0이 채워지니 D0만출력
    printf("%X\n",x); // 11010001 ->이놈 출력  즉 *(char*)*x 로읽는거지 c는쓰레기값이고 
    printf("%d %d %d\n", x.a,x.b,x.c);
    return 0;
}

#endif 