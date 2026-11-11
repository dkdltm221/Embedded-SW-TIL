#define _CRT_SECURE_NO_WARINGS
#include <iostream>
using namespace std;
#if 0
class Point{
    //접근제한자 private,public,protected;
    private :
        //자식한테 해당 private 멤버를 보여주고싶으면 protected사용해라 흠
        // 개인적으로 private으로하고 수정과 조회는 따로 처리하는게 좋을듯
        // 애초에 수정도 맘에안들긴함 
        int x,y;
        char* name;
    public:
        //생성자: 반환타입 없고 이름이 클래스와 동일함. 오버로딩 가능 객체 초기화 용도
        //객체 생성잇에만 자동 호출됨
        Point():x(0),y(0){
            cout << "디폴트 생성자" << endl;
            name = new char[5]; //문자열 주소한개 문자열을 저장할 메모리 할당필요
            strcpy(name,"abc");
        }
        Point(int x,int y){
            cout << "defalut +create" << endl;
            this ->x =x;
            this ->y =y;
            name = new char[5];
            strcpy(name,"abc");
        }

        void printXY(){
            cout << "(" << x <<", "<<y <<")" << endl;
        }
        Point(const Point& p):x(p.x),y(p.y){
            int len = strlen(p.name)+1;
            name = new char[len];
            strcpy(name,p.name);
            
        }

        //소멸자: 객체 소멸 전 자동 호출. 파람 없음. 오버로딩도 안되고 하나만 존재해야함
        //객체가 사용한 자원 반환
        ~Point(){
            cout << "delete "<< endl;
            delete[] name;
        }

        // setter: 멤버 클래스 밖에서 값 변경,해당함수가...
        // set은 서비스에서는 특정목적에맞는 함수로 변경해야한다.
        void setX(int x){
            this -> x = x; //현재 객체주소를 담은 this이기때문에 ->사용
        }
        int getX() const{ //함수 내에서 맴버 변수 변경불가 
            return x;
        }

        void setY(int y){
            this -> y=y;
        }
        int gety() const{
            return y;
        }
};

int main(void){
    cout << "Hello World!\n";
    {
        Point p1(1,2);
        p1.printXY();
    }
    Point* p2 = new Point(3,4); //이건 힙메모리에 지정 생성
    p2 ->printXY();
    delete p2;

    Point arr[2]; //방이 2개 각 방에 디폴트 생성자가 만들어진다.
    //아니 근데 이걸 방이라부르넹

    for(int i=0;i<2;i++){
        arr[i].printXY();
    }


    Point arr2[] = {{4,5},{6,7}};
    for(int i=0;i<2;i++){
        arr2[i].printXY();
    } 

    Point* arr3[] = {new Point(7,8), new Point(9,10)};
    for(int i=0;i<2;i++){
        arr3[i]->printXY(); //주소가 들어가있어 ->연산자 사용 주소 괜찮을지도
    }

    Point p3(10,20);
    cout << &p3 << endl;
    p3.printXY();

    

    //Point p4 =p3; //객체 복사 생성 객체내에 포인터가있기에 에러가 떠야정상 난 왜 안뜨노..?
    //컴파일러가 얕으복사를해서그럼
    //스택 p3에있다치고 name에저장된 문자열은 heap영역에 저장되어 해당 주소를 name에 저장한다
    //그러나 p4는 말그대로 복사하기때문에 p3가 해제하면서 name안에 문자열 주소를 해제함으로써
    //p4에 오류가남 또한 문자열을 변경하면 p3에서 애기치못한 수정이 생기기때문에 주의가 필요함
    //cout << &p4 << endl;
    //p4.printXY();
    Point p4(p3); //이놈이 생성자를 이용해서 깊은 복사
    cout << &p4 << endl;
    p4.printXY();
}

#endif

#if 0

#include <iostream>
#include <string>
using namespace std;

//객체를 함수의 반환값으로 전달하는 방법들
class Person {
public:
    int num;
    string name;
    Person() {}
    Person(int num, string name) :num(num), name(name) {}

    //현재 객체 반환. 
    Person getThis1() {
        return *this;  //this: 현재 객체의 주소. *this는 현재 객체의미
        //반환 타입을 Person으로 하면 현재 객체를 복사해서 전달
    }

    Person& getThis2() {
        return *this;
        //반환 타입을 Person&으로 하면 현재 객체를 복사하지 밖에서 부를 이름만 하나 더 추가
    }

    Person* getThis3() {
        return this;  //현재 객체의 주소 반환. 함수 반환 타입은 Person*(포인터)
    }
};

class TestPerson {
public:
    //call by value. 객체를 복사해서 전달. 제일 나쁨.
    void printPerson(Person p) {
        cout << "num:" << p.num << ", name:" << p.name << endl;
    }

    //call by value. 객체의 주소값을 복사해서 전달. 중간
    void printPerson(Person* p) {
        cout << "num:" << p->num << ", name:" << p->name << endl;
    }

    //call by reference. 파라메터 타입이 참조형 이어야 함. 제일 좋음
    void printPerson2(Person& p) {
        cout << "num:" << p.num << ", name:" << p.name << endl;
    }

};
int main()
{
    Person p1(1,"aaa");
    cout << &p1 << endl;
    Person p2= p1.getThis1();
    Person &p3 = p1.getThis2();
    cout << "객체 주소: " << &p2 << endl;
    cout << "객체 주소: " << &p3 << endl;
    cout << "객체 주소: " << p1.getThis3() << endl;
    
    Person p5(2,"bbb");
    TestPerson tp;
    tp.printPerson(p5); //p5를 함수 지역변수로 복사하여 사용
    tp.printPerson(&p5); //main의 p5를 그대로 사용. 객체 주소로 한번더 이동
    tp.printPerson2(p5); //main의 p5를 그대로 사용
}


#endif

#if 01

//성적처리 프로그램
//학생 3 ,학생:번호,이름,국,영,수, 총점
//기능 : 멤버 초기화 => 총점계산,정보 출력

#include <string>

class Score {
private:
    int kor, eng, math, total;

public:
    Score() : kor(0), eng(0), math(0), total(0) {}
    Score(int k, int e, int m)
        : kor(k), eng(e), math(m), total(k + e + m) {}

    int getTotal() const {
        return total;
    }

    void print() const {
        cout << "국어: " << kor << ", 영어: " << eng
             << ", 수학: " << math << ", 총점: " << getTotal();
    }
};

class Student {
private:
    int num;
    string name;
    Score scor;  // Student가 Score 객체를 멤버로 포함

public:
    Student() : num(0), name(""), scor() {}
    Student(const Score& s, int num, string name)
        : num(num), name(name), scor(s) {} // s를 멤버 scor로 복사

    
    void printInfo() const {
        cout << "번호: " << num << ", 이름: " << name << ", ";
        scor.print();
        cout << endl;
    }
};

int main() {
    Student students[3] = {
        Student(Score(90, 80, 70), 1, "Kim"),
        Student(Score(100, 95, 90), 2, "Lee"),
        Student(Score(70, 75, 80), 3, "Park")
    };

    for (int i = 0; i < 3; i++) {
        students[i].printInfo();
    }
}


#endif
