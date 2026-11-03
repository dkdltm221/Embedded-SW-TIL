#include "day7_lib.h"
#include <stdint.h>

// 형재정의를 해보세요.
typedef char C10[10];


#if 1
int printAry(char (*ary)[10], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%s ", ary[i]);
    }
    printf("\n");
}

int main(void) {
    C10 fruit[] = { "apple", "melon", "cherry" };
    int (*fn) (char (*ary)[10], int size);
    fn = printAry;
    fn(fruit, sizeof(fruit) / sizeof(fruit[0]));
    return 0;
}

#endif

#if 0
typedef int* IP;
typedef char C10[10];
typedef C10 C10_5[5];

#endif



#if 0
typedef struct _my_t {
    int (*fp)(int, int);
    char* name;
    char op;
}my_t;

int get_command_no(my_t *p, int n) {
    int no;
    printf("*-+-+-+-+-+-+-*\n");
    for (int i = 1; i < n; ++i) {
        printf("|  %d. %s     |\n",i, p[i].name);
    }
    printf("|  0. EXIT    |\n");
    printf("*-+-+-+-+-+-+-*\n");
    scanf("%d", &no);
    return no;
}
int main(void) {
    int a = 25, b = 6;
    my_t funcs[] = {
        {0},
        { sum, "SUM", '+'},
        { sub, "SUB", '-'},
        { mul, "MUL", '*'},
        { divi, "DIV", '/'},
        { mod, "MOD", '%'},
    }; // 구조체 배열

    //  아래의 동작을 반복하다가 cmd_no가 0이면 종료하는 프로그램
    // while(1){
    //     int cmd_no = get_command_no(funcs, SIZE(funcs));  // 1 ~ 5
    //     if(cmd_no<=0 || cmd_no >5)
    //         break;
    //     int result = funcs[cmd_no].fp(a, b);
    //     printf("%d %c %d = %d\n", a,funcs[cmd_no].op,funcs[cmd_no].fp(a, b));
    // }
    
    // printf("%d %c %d = %d\n", result);

    // enum, switch~case를 이용한 프로그램 작성
    enum  {SUM = 1,SUB,MUL,DIV,MOD};

    int cmd_no;
    while(cmd_no =  get_command_no(funcs, SIZE(funcs)) ){
        if(cmd_no >5)
            break;
        switch (cmd_no){
            case SUM:  
            case SUB:
            case MUL:
            case DIV:
            case MOD:
                printf("%d %c %d = %d\n", a,funcs[cmd_no].op,b,funcs[cmd_no].fp(a, b));
                break;
        }

    }

    return 0;
}

#endif

#if 0
enum {KOR = 1,ENG,MAT}; //eng =2 mat=3으로 자동갱신


int main(void){
    int scores[4] = {0,90,100,80};
    printf("%d\n",scores[KOR]);
    printf("%d\n",scores[KOR] + scores[MAT]); 

    return 0;
}

#endif

#if 0
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
    printf("%X %X %X %X\n",X.rgb.blue,X.rgb.green,X.rgb.red,X.rgb);
    X.color = 0X7722DD;
    //한번의 입력으로 전체 구조체의 주소값을 변경할수있다는 아주 좋은 장점이있다.
    printf("%X %X %X %X\n",X.rgb.blue,X.rgb.green,X.rgb.red,X.rgb);
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