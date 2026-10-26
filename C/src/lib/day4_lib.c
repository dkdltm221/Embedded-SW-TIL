#include "day4_lib.h"

void my_gets(char*str,int n){
    int i=0;
    for(;i<n-1;i++){
        int c = getchar();
        if(c=='\n') break;
        *(str+i)=(char)c;
    }
    str[i]='\0';
}