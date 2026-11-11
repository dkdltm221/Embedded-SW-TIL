#include "lib/Test.h"


#if 0
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
#endif

//과제
#if 01
#include "lib/Person.h"

int main()
{
    PersonService service;
    service.add();
    service.add();
    service.add();
    service.get();
    service.printAll();
    service.edit();
    service.printAll();
    service.del();
    service.del();
    service.printAll();
}


#endif