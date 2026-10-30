#ifndef DAY8_LIB_H
#define DAY8_LIB_H

#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))



void free_mem(void **p);
void free_mem2(void ***p,int n);
#endif
