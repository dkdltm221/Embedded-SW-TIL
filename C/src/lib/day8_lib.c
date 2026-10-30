#include "day8_lib.h"

void free_mem(int **p) {
    if (p == NULL) return; // 아래의 *p 동작이 있어,p가  null인것을 검사
    free(*p);
    *p = NULL;
}