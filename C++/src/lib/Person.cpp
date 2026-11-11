
#include "Person.h"
/// Person 멤버 함수 구현 //////
string Person::toString() const{
  //to_string(숫자) : 숫자를 문자열로 변환
	return to_string(num) + " / " + name + " / " + tel;  
}

void Person::setTel(string tel) {
	this->tel = tel;
}
int Person::getNum() {
	return num;
}

/// PersonArr 멤버 함수 구현 //////

//배열에 Person 주소를 끝에 추가
bool PersonArr::addPerson(Person* p) {
	if (p != nullptr && cnt < 10) {
		arr[cnt++] = p;
		return true;
	}
	return false;
}
// arr 인덱스로 Person주소를 반환
Person* PersonArr :: getPerson(int idx){
    if (idx < 0 || idx >= cnt) return nullptr;
    return arr[idx];
}
//번호로 검색을 해서 방번호 반환 | 검색할 사람 번호받아서 getperseon으로 검색해서 리턴하는식
int PersonArr :: getPersonIdx(int num){
    for(int i=0;i<cnt;i++){
        if(arr[i]->getNum() == num)
            return i;
    }
    return -1;
}
//요소 개수 반환
int PersonArr ::  getCnt(){
    return cnt;
}
//삭제할 방번호를 파람으로 받아서(위 두함수사용) 해당 방의 Person객체 메모리 해제, 방을 한칸씩 앞으로 이동
//cnt감소로직 필요
void PersonArr :: delPerson(int idx){
    if (idx < 0 || idx >= cnt) return;
    delete arr[idx];
    for(int i=idx;i<cnt-1;i++){
        arr[i] = arr[i+1];
    }
    cnt--;
    arr[cnt] = nullptr;
}



/// PersonService 멤버 함수 구현 //////

void PersonService::add() {
	int num, idx=0;
	string name, tel;
	cout << "=== add ===" << endl;
	
	while (idx>=0) {
		cout << "num:";
		if (!(cin >> num)) return;
		idx = arr.getPersonIdx(num);
	}
	cout << "name:";
	if (!(cin >> name)) return;
	cout << "tel:";
	if (!(cin >> tel)) return;
	Person* p = new Person(num, name, tel);
	if (!arr.addPerson(p)) {
		delete p; // 배열이 가득 차서 추가하지 못한 객체 해제
		cout << "저장 공간이 가득 찼습니다." << endl;
	}
}
void PersonService :: get(){
    int num;
    if (!(cin >> num)) return;
    int bang = arr.getPersonIdx(num);
    if(bang <0) {
        cout << "없어요" << endl;
        return;
    }
    cout << arr.getPerson(bang)->toString() << endl;

} //번호로 검색기능

// 번호로 검색해서 전화번호 수정기능
void PersonService :: edit(){
    cout << "번호 입력해주세요" <<endl;
    int num;
    if (!(cin >> num)) return;
    int number = arr.getPersonIdx(num);
    if(number < 0) {
        cout << "없어요" << endl;
        return;
    }
    cout << "변경하실 번호입력해주세용" << endl;
    string tel;
    if (!(cin >> tel)) return;
    Person* p = arr.getPerson(number);
    p->setTel(tel);
} 
void del();  // 번호 검색 삭제기능
void printAll(); //배열의 모든요소 출력기능
