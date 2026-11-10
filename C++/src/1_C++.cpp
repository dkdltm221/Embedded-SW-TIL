#include "lib/Test.h"



int main(){
    Test t1;
    t1.a = 10;
    t1.b = 20;
    t1.printData();

    Test*t2 = new Test; //힙에 객체 생성
    t2->a = 100;
    t2->b = 200;
    t2->printData();
}