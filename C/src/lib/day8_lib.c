#include "day8_lib.h"

void free_mem(void **p) {
    if (p == NULL) return; // 아래의 *p 동작이 있어,p가  null인것을 검사
    free(*p);
    *p = NULL;
}

void free_mem2(void ***p,int n) {
    if (p == NULL || *p == NULL) return;
    
    for(int i=0;i<n;i++){
        free_mem(&(*p)[i]);
    }
    free(*p);
    *p = NULL;
}
