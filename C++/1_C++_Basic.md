# C++ 핵심 문법

> 2026-11-10 · Day 01 · 기본 연산자와 함수 설명은 생략

## 1. 직접 작성한 코드: 객체와 객체 포인터

```cpp
#include <iostream>
using namespace std;

class Test {
public:  // 외부에서 a, b, printData에 접근 가능
    int a;
    int b;

    void printData() {
        cout << a << "," << b << endl;
    }
};  // 클래스 정의 끝에는 ; 필요

int main() {
    Test t1;  // 지역 객체 생성
    t1.a = 10;
    t1.b = 20;
    t1.printData();

    Test* t2 = new Test;  // 객체를 동적 생성하고, 그 주소를 t2에 저장
    t2->a = 100;
    t2->b = 200;
    t2->printData();

    delete t2;  // 원본 코드에 추가: new로 만든 객체 해제
}
```

출력:

```text
10,20
100,200
```

| 코드 | 핵심 |
| --- | --- |
| `Test t1;` | t1 자체가 객체. 범위를 벗어나면 자동 소멸 |
| `Test* t2 = new Test;` | t2는 포인터, new로 만든 객체는 별도로 존재. 직접 delete 필요 |
| `t1.a` | 객체의 멤버는 `.`으로 접근 |
| `t2->a` | 포인터가 가리키는 객체의 멤버는 `->`로 접근 |

- `Test*t2`, `Test* t2`, `Test *t2`는 같은 선언이다.
- `t2->a`는 `(*t2).a`와 같다.
- **포인터라고 반드시 new가 필요한 것은 아니다.** 기존 객체의 주소를 가리킬 수도 있다.

```cpp
Test* p = &t1;
p->a = 30;  // t1.a가 30으로 바뀜
// delete p;  // 금지: t1은 new로 만든 객체가 아님
```

원본 코드의 a, b는 생성 직후 값이 초기화되어 있지 않다. 지금처럼 값을 넣은 뒤 읽거나, 선언할 때 `int a = 0;`처럼 초기화한다.

## 2. 참조 &: 복사하지 않고 원본 사용

```cpp
int a = 10;
int b = a;    // 복사본
int& r = a;   // a의 별명

b = 20;      // a는 10
r = 30;      // a가 30
```

참조는 처음 연결한 대상을 바꿀 수 없다. `r = b;`는 참조 대상 변경이 아니라 a에 b의 값을 대입하는 것이다.

```cpp
void change(int& x) { x = 100; }  // 원본 수정
// int x로 받으면 복사본만 수정
```

## 3. Test::와 this->: 소속과 현재 객체

```cpp
class Test {
private:
    int x = 0;  // 외부에서 t.x로 직접 접근 불가
public:
    void setX(int x);  // 선언
};

void Test::setX(int x) {  // 클래스 밖에서 정의 → Test 소속 표시
    this->x = x;         // 현재 객체의 x = 매개변수 x
}
```

- `Test::setX`는 함수를 **정의**할 때 소속을 표시한다.
- `t.setX(10)`은 객체 t의 함수를 **호출**한다.
- 클래스 안에서 바로 함수 내용을 작성하면 Test::는 생략한다.
- `this`는 현재 함수를 호출한 객체의 주소다.
- `.h`에 클래스와 함수 선언, `.cpp`에 함수 정의를 나눠 작성할 수 있다.
- `std::cout`의 `::`도 같은 범위 지정 문법이다. std에 속한 cout이라는 뜻이다.

### 실습: Test.h / Test.cpp로 나누기

```text
src/
├─ 1_C++.cpp
└─ lib/
   ├─ Test.h
   └─ Test.cpp
```

**Test.h — 클래스 구성과 함수 선언**

```cpp
#pragma once

class Test {
public:
    int a;
    int b;
    void printData();  // 여기서는 선언만
};
```

**Test.cpp — 함수의 실제 동작 정의**

```cpp
#include "Test.h"
#include <iostream>

void Test::printData() {
    std::cout << a << "," << b << std::endl;
}
```

**1_C++.cpp — 헤더를 포함하고 객체 사용**

```cpp
#include "lib/Test.h"

int main() {
    Test t;
    t.a = 10;
    t.b = 20;
    t.printData();
}
```

- `lib`는 문법이 아니라 **폴더 이름**이다. cpp와 헤더가 같은 폴더면 `#include "Test.h"`로 쓴다.
- `#pragma once`는 같은 헤더의 중복 포함을 막는다.
- 정의 순서는 **`반환형 클래스명::함수명()`** → `void Test::printData()`.
- `TEST :: void printData()`는 오류다. 순서와 대소문자를 맞춰야 한다.
- 헤더를 include하는 것과 cpp를 함께 컴파일하는 것은 별개다. **두 cpp를 함께 빌드한다.**

```powershell
# 저장소 루트에서 실행
g++ C++/src/1_C++.cpp C++/src/lib/Test.cpp -o main.exe
.\main.exe
```

## 4. 생성자와 : x(x)

```cpp
class Test {
    int x;
    int y;
public:
    Test() : x(0), y(0) {}
    Test(int x, int y) : x(x), y(y) {}
};

// 사용
// Test t1;        → x=0, y=0
// Test t2(4, 5);  → x=4, y=5
```

- 생성자는 객체를 만들 때 실행된다. **클래스와 이름이 같고 반환형이 없다.**
- `: x(x)`는 **멤버 x를 매개변수 x로 초기화**한다는 뜻이다.
- 초기화 목록은 처음 값을 정하고, 본문의 `this->x = x;`는 대입한다.

### 멤버 변수와 매개변수 이름이 같아도 되는 이유

멤버 변수와 생성자의 매개변수는 **서로 다른 범위(scope)에 선언된 별개의 변수**이므로 이름이 같아도 된다. 저장 위치가 달라서 이름 충돌이 허용되는 것이 아니라, 이름의 유효 범위가 다르기 때문이다.

```cpp
class Test {
    int x;  // 객체의 멤버 변수
public:
    Test(int x) {     // 생성자의 매개변수
        this->x = x; // 객체의 멤버 x = 매개변수 x
    }
};
```

- 생성자 본문에서 그냥 `x`라고 쓰면 매개변수 x를 뜻한다. 매개변수가 같은 이름의 멤버를 **가린다(shadowing)**.
- `x = x;`는 매개변수를 자기 자신에게 대입하므로 멤버 x에는 값이 들어가지 않는다.
- `this->x`는 현재 객체의 멤버를 명확하게 지정한다. 위 대입은 자기 자신에게 하는 대입이 아니다.
- 초기화 목록의 `Test(int x) : x(x) {}`는 왼쪽이 멤버, 괄호 안이 매개변수로 구분되므로 this 없이도 올바르게 초기화된다.

## 5. 함수 뒤 const와 오버로딩

```cpp
int getX() const { return x; }  // 객체의 일반 멤버를 수정하지 않는 함수
```

- const 함수 안에서는 같은 객체의 일반 멤버를 수정하거나 비const 멤버 함수를 호출할 수 없다.
- **const 객체는 const 멤버 함수만 호출 가능.** 일반 객체는 둘 다 가능하다.

```cpp
void print();
void print() const;
```

위 두 함수가 모두 있으면 일반 객체는 일반 버전, const 객체는 const 버전을 호출한다. const 버전만 있으면 일반 객체도 호출할 수 있다.

```cpp
void show(const Test& t);  // 객체를 복사하지 않고, 읽기용 참조로 받기
```

**오버로딩**은 같은 이름에 다른 매개변수를 두는 것이다. 반환형만 달라서는 안 된다.

```cpp
void f();
void f(int a);
void f(double a);
```

멤버 함수는 위 print처럼 뒤의 const 유무로도 구분할 수 있다.
