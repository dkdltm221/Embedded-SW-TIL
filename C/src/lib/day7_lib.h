#ifndef __DAY7_LIB_H__
#define __DAY7_LIB_H__

#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

int sum(int x, int y);
int sub(int x,int y);
int mul(int x,int y);
int divi(int x,int y);
int mod(int x,int y);
int comp2D(const void* a,const void* b);
void print_2Darr(int (*arr)[3], int r,int c);
int compStr(const void*a,const void* b);
void print_strdata(char** c,int n);
void print_doubledata(double* arr, int n);
int compDouble(const void*a,const void*b);
#endif
