/* 과제 : 상속 */
//학생 : 번호, 이름, 학과, 수강과목...
//       내정보확인(), 수강신청(), 수강취소(), 수강목록()...
//교수 : 번호, 이름, 학과, 강의과목들
//       내정보확인(), 오픈(), 오픈취소(), 오픈목록()
//교직원 : 사번, 이름, 소속 부서, 직무
//       내정보확인(), 신입사원관리(), 

//공통 : 부모클래스로 대체_번호, 이름, 학과(부서), 내정보확인()

#include <iostream>
using namespace std;

class Person {
protected:
    int number;
    string name, department;
public:
    Person() :number(0), name(""), department("") {}
    Person(int number, string name, string department) {
        this->number = number;
        this->name = name;
        this->department = department;
    }
    ~Person() {
        cout << "Person 객체 소멸" << endl;
    }

    void printMyInfo() {
        cout << "===Info===" << endl;
        cout << "number : " << number << endl;
        cout << "name : " << name << endl;
        cout << "department : " << department << endl;
        cout << "==========" << endl;
    }
};

//student(수강목록 - string[] / 수강신청(string 과목명), 수강취소(string 과목명), 수강목록() - print)
class Student : public Person {
public:
    string ListCourse[10];
    int index;

    Student(int number, string name, string department) {
        this->number = number;
        this->name = name;
        this->department = department;

        index = 0;
        for (int i = 0; i < 10; i++) {
            ListCourse[i] = "";
        }
    }
    ~Student() {
        cout << "Student 객체 소멸" << endl;
    }

    void registration(string name) {
        for (int i = 0; i < index; i++) {
            if (ListCourse[i] == name) {
                cout << "학생 : 이미 신청한 과목입니다." << endl;
                return;
            }
        }
        if (index >= 10) {
            cout << "학생 : 수강 목록이 초과되었습니다." << endl;
            return;
        }
        ListCourse[index++] = name;
        cout << "학생 : 과목 신청 완료" << endl;
    }
    void QutRegistration(string name) {
        int target_index = -1;
        for (int i = 0; i < index; i++) {
            if (ListCourse[i] == name) {
                target_index = i;
                break;
            }
        }
        if (target_index == -1) {
            cout << "학생 : 과목을 찾지 못했습니다." << endl;
            return;
        }

        for (int i = target_index; i < index - 1; i++) {
            ListCourse[i] = ListCourse[i + 1];
        }
        index--;
        cout << "학생 : 과목 삭제 완료" << endl;
    }
    void PrintList() {
        for (int i = 0; i < index; i++) {
            cout << "과목 " << i + 1 << " : " << ListCourse[i] << endl;
        }
        cout << "학생 : 과목 출력 완료" << endl;
    }
};

//Prof(강의목록 - string[]/ 오픈(string 과목명) - 강의과목 등록, 오픈취소(string 과목명), 수강목록() - print)
class Prof : public Person {
public:
    string ListCourse[10];
    int index;

    Prof(int number, string name, string department) {
        this->number = number;
        this->name = name;
        this->department = department;

        index = 0;
        for (int i = 0; i < 10; i++) {
            ListCourse[i] = "";
        }
    }
    ~Prof() {
        cout << "Prof 객체 소멸" << endl;
    }

    void Open(string name) {
        for (int i = 0; i < index; i++) {
            if (ListCourse[i] == name) {
                cout << "교수 : 이미 오픈한 과목입니다." << endl;
                return;
            }
        }
        if (index >= 10) {
            cout << "교수 : 수강 목록이 초과되었습니다." << endl;
            return;
        }
        ListCourse[index++] = name;
        cout << "교수 : 과목 오픈 완료" << endl;
    }
    void QuitOpen(string name) {
        int target_index = -1;
        for (int i = 0; i < index; i++) {
            if (ListCourse[i] == name) {
                target_index = i;
            }
        }
        if (target_index == -1) {
            cout << "교수 : 과목을 찾지 못했습니다." << endl;
            return;
        }

        for (int i = target_index; i < index - 1; i++) {
            ListCourse[i] = ListCourse[i + 1];
        }
        index--;
        cout << "교수 : 과목 삭제 완료" << endl;
    }
    void PrintList() {
        for (int i = 0; i < index; i++) {
            cout << "과목 " << i + 1 << " : " << ListCourse[i] << endl;
        }
        cout << "교수 : 과목 출력 완료" << endl;
    }
};
//staff(직무 - string, 신입사원관리(int 사번) - 메시지 출력(누구누구 사원 관리함) 
class Staff : public Person {
public:
    string Position;
    Staff(int number, string name, string department) {
        this->number = number;
        this->name = name;
        this->department = department;
        this->Position = department;
    }
    ~Staff() {
        cout << "Staff 객체 소멸" << endl;
    }

    void managing(int number) {
        cout << "신입사원 관리 : " << number << "를 관리했습니다." << endl;
    }
};


int main() {
    //모든 경우 확인할 수 있도록 생성형 aI 통해 생성(클래스는 직접 작성)
    // ===== Person =====
    cout << "##### Person #####" << endl;
    Person p1;                                // 기본 생성자
    p1.printMyInfo();
    Person p2(1001, "김철수", "컴퓨터공학과"); // 매개변수 생성자
    p2.printMyInfo();

    // ===== Student =====
    cout << "\n##### Student #####" << endl;
    Student stu(2024001, "이영희", "컴퓨터공학과");
    stu.printMyInfo();                        // 부모 클래스 메서드

    stu.registration("자료구조");              // 신청
    stu.registration("알고리즘");
    stu.registration("운영체제");
    stu.registration("자료구조");              // 중복 신청 -> 실패
    stu.PrintList();

    stu.QutRegistration("알고리즘");            // 취소
    stu.QutRegistration("네트워크");            // 없는 과목 -> 실패
    stu.PrintList();

    // ===== Prof =====
    cout << "\n##### Prof #####" << endl;
    Prof prof(3001, "박교수", "컴퓨터공학과");
    prof.printMyInfo();

    prof.Open("C++프로그래밍");                // 오픈
    prof.Open("데이터베이스");
    prof.Open("C++프로그래밍");                // 중복 오픈 -> 실패
    prof.PrintList();

    prof.QuitOpen("데이터베이스");              // 오픈 취소
    prof.QuitOpen("인공지능");                  // 없는 과목 -> 실패
    prof.PrintList();

    // ===== Staff =====
    cout << "\n##### Staff #####" << endl;
    Staff staff(5001, "최직원", "인사팀");
    staff.printMyInfo();
    cout << "직무 : " << staff.Position << endl;
    staff.managing(5002);                      // 신입사원 관리

    // ===== 동적 할당 (소멸자 호출 확인) =====
    cout << "\n##### 동적 할당 #####" << endl;
    Student* sp = new Student(2024002, "정학생", "수학과");
    sp->registration("미적분");
    sp->PrintList();
    delete sp;                                 // Student -> Person 순으로 소멸

    cout << "\n##### main 종료 (지역 객체 소멸) #####" << endl;
    return 0;
}