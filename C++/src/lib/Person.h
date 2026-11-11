
#pragma once
#include <string>
#include <iostream>
using namespace std;



class Person {
private:
	int num;
	string name;
	string tel;
public:
	Person():num(0), name(""), tel("") {}
	Person(int num, string name, string tel) :num(num), name(name), tel(tel) {}
	string toString() const;
	void setTel(string tel);
	int getNum();
};


//전화번호로만 수정
//Person객체를 배열로 저장, 삭제,검색
class PersonArr {  //dao. 배열에 추가, 검색, 수정, 삭제
private:
	Person* arr[10];  //Person 주소 갖음. 소멸자에서 Person*를 해제
	int cnt;   //요소 개수
public:
  //생성자
	PersonArr() :arr{}, cnt(0) {}
	
	//소멸자 arr방에 저장된 주소를 해제
	~PersonArr(){
        for (int i = 0; i < cnt; i++) {
            delete arr[i]; // new로 생성한 Person 각각 해제
        }
    }
	
	//배열에 Person 주소를 끝에 추가
	bool addPerson(Person* p);
	
	// arr 인덱스로 Person주소를 반환
	Person* getPerson(int idx);
	
	//번호로 검색을 해서 방번호 반환 | 검색할 사람 번호받아서 getperseon으로 검색해서 리턴하는식
	int getPersonIdx(int num);
	
	//요소 개수 반환
	int getCnt();
	
	//삭제할 방번호를 파람으로 받아서(위 두함수사용) 해당 방의 Person객체 메모리 해제, 방을 한칸씩 앞으로 이동
    //cnt감소로직 필요
	void delPerson(int idx);
};
//말 그대로 service main - service - arr
class PersonService {
private:
	PersonArr arr;  //포함관계. has a 관계 
public:
	void add(); //외부에서 사람정보 1개 추가
	void get(); //번호로 검색기능
	void edit(); // 번호로 검색해서 전화번호 수정기능
	void del();  // 번호 검색 삭제기능
	void printAll(); //배열의 모든요소 출력기능
};
