
#include "day3_lib.h"

#if 0
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))
//x가 연산식으로 들어올수도있기에 x를 감싸준다.



int main(void){
    int score[5] = {0};
    input_data(score,SIZE(score));
    print_data(score,SIZE(score));
    printf("total = %d\n",sum_data(score,SIZE(score)));
    printf("average = %.2f\n",avg_data(score,SIZE(score)));
    return 0;
}

#endif

#if 0
int main(void){
    char str1[80] = "cat";
    char str2[80];

    strcpy(str1,"tiger");
    strcpy(str2,str1);
    printf("%s, %s\n",str1,str2);
    //I am a boy [Enter]
    char str[80] = {0};
    // %s -> char *
    // str -> char *,&str -> char(*)[80]
    scanf_s("%s",str); // "I"-> 'I','\0'
    printf("Enter: %s\n",str); // I출력
    gets(str); // " am a boy \0 , 입력내용을 모두 읽어 Buffer에는 내용이 없음, [Enter]대신 \0가 str에 저장됨"
    char ch;
    scanf("%c",&ch); // 'a'
    printf("%s, %c\n",str,ch);
    scanf("%c",&ch); // '[Enter]'을 가져감
    printf("-%c-",ch); 
    return 0;
}
#endif

#if 0

int main(void){
    char str[80] = "apple";
    char* p1 = str;
    char* p2 = "banana";

    // 포인터 상수 : str,apple,banana -> 보이는 것은 배열 이름, 문자열 이지만 해석시 '주소'로 할것
    // 포인터 변수 : p1,p2
    // p1 - 참조연산을 사옹해 char 읽고 쓰기 가능 
    // p2 - 참조연산을 사용해 char 읽기만 가능 (쓰기 동작을 하면 오류 발생)
    printf("%s\n","apple"+2); //이런것도 가능
    
    printf("%c\n","banana"[3]);
    
    p2[0] = 'k'; // RUN TIME ERROR - read only 메모리에 쓰기 동작을 해서 오류
    return 0;
}

#endif

#if 1

void swap(int *pa,int *pb){
    int temp = *pa; 
    *pa = *pb;
    *pb = temp;
    
}

int main(void){
    int a=10,b=12;
    swap(&a,&b);
    printf("a=%d, b=%d\n",a,b);
}
#endif