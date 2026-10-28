#ifndef __DAY6_LIB_H__
#define __DAY6_LIB_H__

#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))


void print_2D(int(*p)[3][4]);
void exchange0(int* a,int* b);
void exchange1(int** a,int** b);
void exchange2(int*** a,int*** b);
void exchange3(int** a,int** b);
void exchange4(int*** a,int*** b);
#endif
