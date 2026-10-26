// #if 01
#include <stdio.h>

// int main() {
//     float a= 1.2345678901234567890f;
//     double b = 1.2345678901234567890;
//     printf("float a = %.20f\n", a);
//     printf("double b = %.20lf\n", b);
    
//     // const double tax_rate = 0.08;
//     // double* price = &tax_rate; 
//     return 0;
// }
// #endif

// #if 2
// int mystrlen(const char *str)
// {
//   const char *s;

//   if (str == 0)
//     return 0;
//   for (s = str; *s; ++s);
//   return s-str;
// }


// int main(void){
//     int a = mystrlen("apple");
//     printf("a=%d\n", a);
    
//     return 0;
// }
// #endif 2

// #if 1
// int main(void){
//     int a =10,b=20;
//     int res;
//     res = (a>b) ? a : b;
//     if(a>b){
//         res =a;
//     }
//     else{
//         res = b;
//     }
//     printf("res=%d\n", res);
//     return 0;
// }
#if 0
unsigned int setBit(unsigned int num, int bitPosition) {
    return num | (1U << bitPosition);
}
unsigned int setBit(unsigned int num, int bitPosition) {
    return num | (1U << bitPosition);
}

int main(void) {
    unsigned int num = 0xAU; // 2진수 1010

    printf("num=%X\n", setBit(num, 2)); // 1110 → 16진수 E
    return 0;
}
#endif