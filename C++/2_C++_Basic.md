# C++ 객체지향 — 생성·복사·static·상속

> 2026-11-11 · Day 02 · [실습 코드](src/2_C++.cpp)

## 1. private은 객체가 아니라 클래스 기준

Point의 멤버 함수는 **다른 Point 객체의 private 멤버에도 접근 가능**하다.

```cpp
Point(const Point& p) : x(p.x), y(p.y) {
    // Point 생성자 안이므로 p.x, p.y, p.name 접근 가능
}
```

반면 main에서는 `p.x`로 접근할 수 없다. 공개된 `p.getX()` 등을 사용해야 한다.

- private: 외부의 직접 접근 제한. 같은 클래스의 멤버는 접근 가능.
- public: 외부에 공개.
- protected: 파생 클래스에서도 접근 가능. 상속한다고 private에 직접 접근할 수 있는 것은 아니다.

## 2. this가 포인터라서 this->x

```cpp
void setX(int x) {
    this->x = x;  // 현재 객체의 멤버 x = 매개변수 x
}
```

- this는 현재 함수를 호출한 객체의 주소를 가리키는 포인터다.
- 객체는 `.`, 객체 포인터는 `->`로 멤버에 접근한다.
- `this->x`와 `(*this).x`는 같다.
- 이름이 같아도 멤버와 매개변수의 범위가 달라 선언 가능하다. 본문의 `x = x;`는 매개변수를 자기 자신에게 대입한다.

setter를 전부 열어두기보다는 필요한 변경 동작과 검증을 제공한다. 이름만 바꾸는 것이 아니라 객체의 상태를 지키는 규칙이 중요하다.

## 3. getX() 뒤 const는 함수 내부의 수정을 제한

```cpp
int getX() const {
    // x = 100;  // 오류
    return x;
}
```

**반환값의 복사와 함수 뒤 const는 별개다.**

- int를 반환하면 복사되므로, 받은 값을 바꿔도 원본 x는 그대로다.
- 함수 뒤 const는 함수 안에서 현재 객체의 일반 멤버를 수정하지 못하게 한다.
- 같은 객체의 비const 멤버 함수도 호출할 수 없다.
- const 객체나 const 참조를 통해 호출하려면 const 멤버 함수여야 한다.

컴파일러는 get이라는 이름만 보고 읽기 전용이라고 판단하지 않는다.

## 4. 생성자·소멸자와 객체 수명

```cpp
Point() : x(0), y(0) { /* 기본 생성자 */ }
Point(int x, int y) : x(x), y(y) { /* 인자 있는 생성자 */ }
~Point() { delete[] name; }
```

- 생성자: 클래스와 이름이 같고 반환형이 없다. 객체 생성 시 호출되며 오버로딩 가능.
- `: x(x)`는 멤버 x를 매개변수 x로 초기화한다.
- 소멸자: `~클래스명()`. 현재 실습에서는 매개변수 없이 하나를 정의하고 자원을 정리한다.

```cpp
{
    Point p1(1, 2);
}  // 범위를 벗어나면 p1 소멸자 자동 호출

Point* p2 = new Point(3, 4);
delete p2;  // 소멸자 호출 후 객체 메모리 해제
```

name은 포인터이므로 가리키는 메모리를 자동 해제하지 않는다. 소멸자의 `delete[] name`이 필요하다. **new는 delete, new[]는 delete[]와 짝을 맞춘다.**

## 5. 객체 배열과 포인터 배열

```cpp
Point arr[2];                     // 각 원소에 기본 생성자 호출
Point arr2[] = {{4, 5}, {6, 7}};    // 각 원소에 인자 있는 생성자 호출
Point* arr3[] = {new Point(7, 8), new Point(9, 10)};

arr[0].printXY();     // 원소가 객체
arr3[0]->printXY();   // 원소가 객체의 주소
```

arr, arr2는 범위를 벗어나면 원소들이 자동 소멸한다. arr3는 **포인터 배열만 사라지므로 따로 만든 객체를 각각 해제**해야 한다.

```cpp
for (int i = 0; i < 2; i++) {
    delete arr3[i];  // 현재 실습 코드에 필요한 정리
}
```

## 6. 얕은 복사와 깊은 복사

Point의 name은 문자열 자체가 아니라 **별도로 할당한 문자열의 주소**를 저장한다.

| 복사 방식 | name 처리 | 결과 |
| --- | --- | --- |
| 얕은 복사 | 주소값 복사 | 두 객체가 같은 메모리를 가리킴 |
| 깊은 복사 | 새 메모리를 할당하고 내용 복사 | 각 객체가 별도의 메모리를 가짐 |

얕은 복사 자체가 컴파일 오류는 아니다. 하지만 이 클래스처럼 각 소멸자가 같은 주소를 해제하면 이중 해제가 발생한다. 한 객체를 통해 문자열을 바꾸면 다른 객체에도 영향을 준다.

### 작성한 복사 생성자

```cpp
Point(const Point& p) : x(p.x), y(p.y) {
    int len = strlen(p.name) + 1;  // 문자열 끝의 '\0'까지 공간 확보
    name = new char[len];
    strcpy(name, p.name);         // 새 공간에 내용 복사
}
```

- `const Point& p`: 원본을 참조로 받고, 이 참조로 원본을 수정하지 않는다.
- 새 메모리를 만들었으므로 각 객체의 소멸자가 자기 메모리를 해제할 수 있다.
- `&p3`, `&p4`가 다르다는 것만으로 깊은 복사가 증명되지는 않는다. 핵심은 두 name이 가리키는 메모리도 별개라는 점이다.

### = 모양이어도 새 객체 선언이면 복사 생성

```cpp
Point p4 = p3;  // 복사 생성자 호출
// 또는
Point p4(p3);   // 같은 복사 생성자 호출
```

**지금 작성한 복사 생성자가 있으면 둘 다 깊은 복사한다.** 문법 모양이 아니라 복사 생성자의 구현이 복사 방식을 결정한다.

반면 이미 만들어진 객체에 대입하면 다른 동작이다.

```cpp
Point p4;
p4 = p3;  // 복사 생성자가 아니라 복사 대입 연산자 호출
```

현재 코드는 복사 대입 연산자를 직접 작성하지 않았다. 기본 대입은 name의 주소만 복사하므로, 지금 상태에서 위 대입은 피해야 한다. 직접 메모리를 소유하는 클래스는 **소멸자·복사 생성자·복사 대입 연산자**를 함께 고려한다(Rule of Three).

## 실습 코드에서 주의할 것

- strcpy, strlen 사용에는 `<cstring>`을 포함한다.
- MSVC 경고 억제 매크로의 올바른 이름은 `_CRT_SECURE_NO_WARNINGS`다. 현재 코드의 WARINGS는 오타이며, 이 매크로가 헤더를 대신하지는 않는다.
- arr3의 new 객체 2개는 각각 delete가 필요하다.
- 현재 `Point p4(p3)`는 깊은 복사다. 주석 처리한 `Point p4 = p3`도 동일하다.

## 7. 현재 객체 반환: 값 / 참조 / 포인터

```cpp
Person getThis1() { return *this; }   // 객체를 복사해 반환
Person& getThis2() { return *this; }  // 현재 객체의 참조 반환
Person* getThis3() { return this; }   // 현재 객체의 주소 반환
```

**this는 포인터, *this는 현재 객체다. 반환형에 따라 복사 여부가 달라진다.**

```cpp
Person p1(1, "aaa");
Person p2 = p1.getThis1();
Person& p3 = p1.getThis2();
Person* p4 = p1.getThis3();
```

| 변수 | 정체 | 주소 관계 | 변경하면 |
| --- | --- | --- | --- |
| p2 | 별도의 복사 객체 | `&p2 != &p1` | p1에 영향 없음 |
| p3 | p1의 별명 | `&p3 == &p1` | p1 변경 |
| p4 | p1을 가리키는 포인터 | `p4 == &p1` | 가리키는 p1 변경 |

```cpp
p2.name = "bbb";   // p1.name은 그대로
p3.name = "ccc";   // p1.name도 ccc
p4->name = "ddd";  // p1.name도 ddd
```

참조 반환이어도 **받는 변수에 &가 없으면 복사**한다.

```cpp
Person p5 = p1.getThis2();  // p5는 별도 객체
```

반환한 참조나 포인터는 원본 p1이 살아 있는 동안만 사용한다. p4는 new로 만든 객체를 가리키는 것이 아니므로 delete하면 안 된다.

## 8. 함수에 객체 전달: 값 / 포인터 / 참조

```cpp
void byValue(Person p);          // 객체 복사, p 수정은 원본에 영향 없음
void byPointer(Person* p);       // 주소값 복사, 가리키는 원본 수정 가능
void byReference(Person& p);     // 원본의 별명, 원본 수정 가능
void readOnly(const Person& p);  // 객체 복사 없이 읽기

// 호출
// byValue(p1);
// byPointer(&p1);
// byReference(p1);
// readOnly(p1);
```

- 포인터 전달도 **주소값을 값으로 전달**한다. 포인터 자체를 재대입하는 것과 가리키는 원본을 수정하는 것은 다르다.
- 값 전달이 무조건 나쁘고 참조가 무조건 좋은 것은 아니다. 독립된 복사본이 필요하면 값, 원본 수정이 필요하면 참조 등을 선택한다.
- 현재 printPerson처럼 조회만 하면 `const Person&`로 받는 방식이 적합하다.
- 포인터는 nullptr일 수 있으므로 역참조 전에 유효한지 확인해야 한다.

### 현재 오버로딩에서 주의할 점

```cpp
void printPerson(Person p);
void printPerson(Person& p);
```

위 두 함수를 함께 선언하면 **일반 객체로 printPerson(p1)을 호출할 때 어느 쪽을 선택할지 모호해서 컴파일 오류**가 난다. 현재 실습 코드에서는 참조 버전을 printPerson2로 분리해 이 문제를 피했다. 비교 실습은 함수 이름을 나누거나 하나씩 활성화해서 진행한다.

## 9. 성적처리: Student가 Score를 포함

```cpp
class Student {
    int num;
    string name;
    Score scor;
public:
    Student(const Score& s, int num, string name)
        : num(num), name(name), scor(s) {}
};
```

- Student는 Score를 **가지고 있다(has-a)**. Student가 Score의 한 종류인 것은 아니므로 상속 관계가 아니다.
- s는 참조로 받지만 멤버 scor는 별도 객체로 복사해서 저장한다.
- 생성자에서 국·영·수와 총점을 초기화하고, 출력 함수는 const로 둔다.
- `Score scor`는 Student와 함께 자동 소멸한다. string도 내부 자원을 정리하므로 직접 delete할 것이 없다.
- `Score*`에 new로 만든 객체를 저장하면 소유자가 해제해야 한다. 현재처럼 점수 객체 하나가 항상 함께 존재하면 값 멤버가 단순하다.

## 10. static: 공유 카운터와 객체별 번호

현재 Product 코드의 핵심:

```cpp
class Product {
    int num;          // 객체마다 자기 번호 보관
    string name;
    int price;
    static int cnt;   // 모든 객체가 공유하는 카운터
public:
    Product() : num(cnt++), name(""), price(0) {}
    Product(const string& name, int price)
        : num(cnt++), name(name), price(price) {}

    void printInfo() const {
        cout << num << ", " << name << ", " << price << endl;
    }
};

int Product::cnt = 0;  // 클래스 밖에서 한 번 정의·초기화
```

- cnt의 **선언은 클래스 안**, 정의와 초기화는 클래스 밖이다. 밖에 적어도 Product 소속이며 private 접근 제한도 유지된다.
- 생성자에서는 cnt를 초기화하지 않고 증가시킨다. 매번 0을 대입하면 카운터가 리셋된다.
- cnt++로 생성한 세 객체의 num은 0, 1, 2이고, 공유 cnt는 3이다.
- num까지 static으로 바꾸면 각자의 번호를 보관하지 못하고 모두 같은 값을 보게 된다.
- 이 cnt는 누적 번호 발급용이다. 객체가 소멸해도 줄이지 않으므로 현재 살아 있는 객체 수와는 다르다.
- 기본 복사 생성자는 num도 그대로 복사한다. 복사 생성에도 새 번호를 주려면 별도로 설계해야 한다.
- C++17부터는 `inline static int cnt = 0;`으로 클래스 안에서 정의할 수도 있다. 이 경우 밖의 정의는 제거한다.

### static 멤버 함수

`StaticTest::f2()`처럼 객체 없이 호출할 수 있고 this가 없다. 따라서 일반 멤버 x나 f1을 **객체 지정 없이** 사용할 수 없다. 단, 전달받거나 직접 만든 객체를 통해 일반 멤버에 접근하는 것은 가능하다.

### 오늘 적용한 const

- `printInfo() const`: 현재 객체를 읽기만 하는 함수.
- `const string& name`: 원본 문자열을 수정하지 않고 참조로 받기. 멤버 name에 저장할 때는 복사한다.
- cnt는 증가해야 하므로 const로 만들 수 없다.

## 11. 상속: 부모의 한 종류를 만들기

```cpp
class Child : public Parent {
    int ch1;
public:
    Child(int x, int y, int z, int ch1)
        : Parent(x, y, z), ch1(ch1) {}
};
```

- public 상속은 **Child가 Parent의 한 종류(is-a)**라는 관계를 표현한다. 예: SmartPhone은 Phone의 한 종류.
- `Parent(x, y, z)`는 객체 안의 부모 부분을 초기화한다. ch1은 자식의 멤버다.
- 부모 생성자를 명시하지 않으면 부모의 기본 생성자를 호출하려 한다. 기본 생성자가 없다면 사용할 부모 생성자에 인자를 전달해야 한다.
- 부모의 private 데이터도 부모 부분에 존재한다. 자식이 직접 접근할 수 없을 뿐이며, 부모의 공개 함수로 사용할 수 있다.

### 자료의 Parent / Child1·2·3 코드 읽기

Parent에는 private x, protected y, public z와 print가 있다. 세 자식 생성자 모두 자기 객체의 y, z에 접근 가능하지만 x에는 직접 접근할 수 없다.

| 상속 방식 | 부모 public 멤버 | 부모 protected 멤버 | 부모 private 멤버 직접 접근 |
| --- | --- | --- | --- |
| public | public | protected | 불가 |
| protected | protected | protected | 불가 |
| private | private | private | 불가 |

- Child1 객체는 main에서 print(), z를 사용할 수 있다.
- Child2와 Child3 객체는 main에서 부모의 print(), z를 직접 사용할 수 없다.
- **private 상속이 부모의 private 데이터에 접근 권한을 주는 것은 아니다.** 위 표는 접근 가능한 부모 public/protected 멤버의 취급을 나타낸다.
- protected로 데이터를 공개할지는 설계 선택이다. private을 유지하고 필요한 함수를 제공할 수도 있다.

### 생성·소멸 순서

```text
Child1 생성: Parent 생성자 → Child1 생성자
Child1 소멸: Child1 소멸자 → Parent 소멸자

지역 객체를 c1, c2, c3 순서로 생성했다면:
c3(자식 → 부모) → c2(자식 → 부모) → c1(자식 → 부모) 순서로 소멸
```

자료의 실행 결과에는 `cout << c1.z`의 출력인 3이 빠져 있다.

Phone 예제에서는 SmartPhone이 Phone(num)으로 전화번호를 초기화하고, 물려받은 call()과 자기 기능 webBrowsing()을 사용한다. 자식에서 전화번호를 직접 만져야 할 때만 protected 접근이 필요하다.

## 오늘 핵심만 복습

| 질문 | 기억할 답 |
| --- | --- |
| 왜 this.x가 아니라 this->x? | this는 포인터이기 때문 |
| private인데 p.x를 왜 읽지? | 같은 클래스의 멤버 함수는 다른 동일 클래스 객체의 private에도 접근 가능 |
| return x는 복사인데 왜 const? | 반환값 복사와 함수 안에서 원본을 수정하지 않는 약속은 별개 |
| 복사 생성에 =를 쓰면 얕은 복사? | 아님. 작성된 복사 생성자가 복사 방식을 결정 |
| 참조로 반환하면 항상 복사 안 하나? | 받는 쪽도 참조로 받아야 원본의 별명으로 유지 |
| new 없이 포함한 Score도 delete? | 필요 없음. Student와 함께 자동 소멸 |
| cnt와 num이 왜 둘 다 필요? | 번호 발급용 공유 상태와 객체별 번호 저장은 다른 역할 |
| 포함과 상속의 차이? | Student has-a Score / SmartPhone is-a Phone |
| 상속 시 생성·소멸 순서? | 생성은 부모부터, 소멸은 자식부터 |

