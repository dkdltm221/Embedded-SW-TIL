
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

#if 1
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