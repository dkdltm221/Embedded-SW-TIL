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

#if 0

int check(int n){
    if(n % 2 == 0) return 2;
    if(n % 3 == 0) return 3;
    if(n % 5 == 0) return 5;
    return 0;
}

int main(void){
    int n;
    scanf_s("%d",&n);
    //홀짝 조건문
    if(n%2==0){
        printf("even.\n");
    }else{
        printf("odd.\n");
    }
    //홀짝 비트연산

    if (n & 1U) {
        printf("odd.\n");
    } else {
        printf("even.\n");
    }
    //삼중 머시기
    printf(n & 1U ? "odd" : "even");

    //2,3,5 배수 검사
    printf(check(n));


}

#endif

#if 0

int check(int n){
    if(n % 2 == 0) return 2;
    if(n % 3 == 0) return 3;
    if(n % 5 == 0) return 5;

    return 0;
}

int main(void){
    int n;
    scanf_s("%d",&n);
    
    printf("result: %d",check(n));
}


#endif

#if 0

int check(int s){
    if(s>=70) return 0;
    if(s>=60) return 1;
    return 2;
}

int main(void){
    char* result[] = {"합격입니다.","재시험보세요","불합격입니다."};
    int score;

    printf("점수(0~100)입력해주세요:");
    scanf_s("%d",&score);

    printf("%s \n감사합니다.",result[check(score)]);


    return 0;
}

#endif

#if 0

int main(void){
    int score;
    scanf_s("%d",&score);
    char* c;
    switch (score/10){
        case 10:
        case 9:
            c="A";
            break;
        case 8:
            c="B";
            break;
        case 7:
            c="C";
            break;
        case 6:
            c="D";
            break;
        default:
            c="F";
            break;
    }
    printf("%s",c);
}

#endif

#if 0

int main(void){
    int a1,a2;

    while(scanf_s("%d",&a1) && (a1 > 10));

    do{
        scanf_s("%d",&a2);
    }while(a2>10);
    printf("%d %d",a1,a2);
}

#endif

#if 1
int sumPositiveNumbers(){
    int sum=0,n;

    do{
        scanf_s("%d",&n);

        if(n>0)
            sum+=n;
    }while(n!=0);

    return sum;
}

void verifyPassword(){
    int num=0,pw;

    do{
        scanf_s("%d",&pw);
        if(pw==1357){
            printf("로그인 성공!\n");
            return;
        }
        num++;
    }while(num<3);

    printf("관리자에게 문의하세요\n");
}

int countDigits(){
    int num=0,inputN;

    scanf_s("%d",&inputN);

    while(inputN>0){
        inputN/=10;
        num++;
    }

    return num;
}

//숫자 뒤집기
int reverseInt(){
    int num,reverse=0;

    scanf_s("%d",&num);

    while(num>0){
        reverse = reverse*10 + num%10;
        num/=10;
    }
    return reverse;
}


int main(void){
    printf("%d\n",sumPositiveNumbers());
    verifyPassword();
    printf("%d\n",countDigits());
    printf("%d",reverseInt());

}
#endif

