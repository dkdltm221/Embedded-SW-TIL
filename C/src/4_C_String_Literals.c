#include "day4_lib.h"

#if 0

int main(void){
    char str[30] = {0};
    my_gets(str,SIZE(str));
    printf("%s\n",str);
    return 0;
}

#endif

#if 0

int main(void){
    char str[40] = "Tom & Jerry!!";
    printf("%s\n",to_upper(str));
    return 0;
}

#endif

#if 1

int main(void){
    //함수
    printf("num : %d\n", GetNum());
    Increment();
    printf("num : %d\n",GetNum());
    Increment();
    printf("num :  %d\n",GetNum());

    return 0;
}

#endif