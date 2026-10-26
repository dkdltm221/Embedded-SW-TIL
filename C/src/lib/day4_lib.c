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
#if 0

void my_gets1(char* p, int n) {
    for (int i = 0; i < n -1; i++) {
        *p = getchar();
        if (*p == '\n') break;
        p++;
        
    }
         *p = '\0';
}


void my_gets2(char * str, int n) {
    int i = 0;
    for(i = 0; i < n - 1; i++) {
        str[i] = getchar();

        if(str[i] == '\n') break;
    }

    str[i] = 0;
}

#endif

#if 1

char* to_upper(char* str){
    char* start = str;
    while(*str!='\0'){
        if(*str >='a' && *str<='z'){
            *str = (*str -'a')+'A';
        }
        str++;
    }
    return start;
}

char * my_strcpy(char *to,const char* from){
    char *save = to;

    for(;(*to = *from); ++from,++to);
    return save;
}


#endif
