using System;
using System.Collections.Generic;
/*
namespace interface2
{
    // DB 작업 기능만 정의하고, 각 DB 클래스에서 구현한다.
    internal interface DB
    {
        void insert();
        void select();
        void update();
        void delete();
    }

    class OracleDB : DB
    {
        public void insert() { Console.WriteLine("OracleDB: 데이터 추가"); }
        public void select() { Console.WriteLine("OracleDB: 데이터 조회"); }
        public void update() { Console.WriteLine("OracleDB: 데이터 수정"); }
        public void delete() { Console.WriteLine("OracleDB: 데이터 삭제"); }
    }

    class MySqlDB : DB
    {
        public void insert() { Console.WriteLine("MySqlDB: 데이터 추가"); }
        public void select() { Console.WriteLine("MySqlDB: 데이터 조회"); }
        public void update() { Console.WriteLine("MySqlDB: 데이터 수정"); }
        public void delete() { Console.WriteLine("MySqlDB: 데이터 삭제"); }
    }

    class Dao
    {
        // 구체적인 DB 클래스 대신 인터페이스에 의존하여 결합도를 낮춘다.
        private readonly DB db;

        public Dao(DB db)
        {
            this.db = db;
        }

        public void get() { db.select(); }
        public void add() { db.insert(); }
        public void edit() { db.update(); }
        public void delete() { db.delete(); }
    }

    class Program
    {
        static void Main()
        {
            // 전달하는 DB 구현만 바꾸면 같은 Dao를 사용할 수 있다.
            Dao oracleDao = new Dao(new OracleDB());
            oracleDao.add();
            oracleDao.get();
            oracleDao.edit();
            oracleDao.delete();

            Dao mySqlDao = new Dao(new MySqlDB());
            mySqlDao.add();
            mySqlDao.get();
            mySqlDao.edit();
            mySqlDao.delete();
        }
    }
}
*/

/*
namespace interface3
{
    //C#은 클래스는 다중 상속 불가 => 다이아모든 골 다중 상속 문제
    //인터페이스는 다중 상속 가능. 인터페이스는 멤버 변수가 없고, 
    //메서드는 하위에서 합법적으로 오버라이딩 가능
    //여러 개의 인터페이스 기능을 한 번에 받는 파워풀한 객체를 만들 수 있음
    //복합기 예제: 프린트,복사,팩스
    internal interface Printer
    {
        void print();
    }
    internal interface Copym
    {
        void copy();
    }
    internal interface Fax
    {
        void fax();
    }

    class 복합기1 : Printer,Copym // 복합기1: 출력,복사만됨
    {
        public void print()
        {
            Console.WriteLine("복합기1: 출력");
        }

        public void copy()
        {
            Console.WriteLine("복합기1: 복사");
        }
    }
    
    class 복합기2: Printer,Copym,Fax
    {
        public void print()
        {
            Console.WriteLine("복합기2: 출력");
        }

        public void copy()
        {
            Console.WriteLine("복합기2: 복사");
        }

        public void fax()
        {
            Console.WriteLine("복합기2: 팩스 전송");
        }
    }
    
}

*/

// 주소록 예제: 실행부와 관련 클래스
namespace ListTest
{
    // 실행부: 주소록 메뉴
    class Program
    {
        static void Main()
        {
            Service service = new();
            bool flag = true;
            int m = 0;
            while (flag)
            {
                Console.Write("1.추가 2.번호로검색 3.전화번호수정 4.번호로삭제 5.전체목록 6.종료");
                m = Convert.ToInt32(Console.ReadLine());
                switch (m)
                {
                    case 1:
                        service.addPerson();
                        break;
                    case 2:
                        // TODO: 번호로 검색
                        break;
                    case 3:
                        // TODO: 전화번호 수정
                        break;
                    case 4:
                        // TODO: 번호로 삭제
                        break;
                    case 5:
                        service.printPersons();
                        break;
                    case 6:
                        flag = false;
                        break;
                }
            }
        }
    }

    // 1. 데이터: 번호, 이름, 전화번호
    class Person
    {
        private static int cnt;
        public int Num { set; get; } //중복안됨. 자동할당
        public string Name { set; get; }
        public string Tel { set; get; }

        public Person()
        {
            Name = string.Empty;
            Tel = string.Empty;
        }

        public Person(string name, string tel)
        {
            Num = ++cnt;
            Name = name;
            Tel = tel;
        }
        // List.IndexOf는 == 연산자가 아니라 Equals로 동등성을 비교한다.
        public override bool Equals(object obj)
        {
            return obj is Person other && Num == other.Num;
        }

        public override int GetHashCode()
        {
            return Num.GetHashCode();
        }

        public static bool operator ==(Person left, Person right)
        {
            if (ReferenceEquals(left, right)) return true;
            if (left is null || right is null) return false;
            return left.Num == right.Num;
        }

        public static bool operator !=(Person left, Person right)
        {
            return !(left == right);
        }

        public override string ToString()
        {
            return $"{Num} / {Name} / {Tel}";
        }
    }

    // 2. 저장소: 사람 목록 관리
    class AddressBook
    {
        private List<Person> list = new();

        public void add(Person p)
        {
            list.Add(p);
        }

        // 번호가 일치하는 사람의 인덱스를 반환한다. 없으면 -1이다.
        public int getIdx(int num)
        {
            Person target = new();
            target.Num = num;
            int idx = list.IndexOf(target);
            if(idx>=0){
                return list[idx];
            }
            return null;
        }

        //수정
        public bool update(Person p){
            int idx = list.IndexOf(p);
            if(idx>=0)
            {
                list[idx].Tel = p.Tel;
                return true;
            }
            return false;
        }
        public bool delete(int num){
            Person x = new();
            x.Num = num;
            return list.Remove(x);
        }
        //번호로 삭제


        public void printAll()
        {
            foreach (Person p in list)
            {
                Console.WriteLine(p);
            }
        }
    }

    // 3. 서비스: 사용자 입력과 출력
    class Service
    {
        private AddressBook ab = new();

        public void addPerson()
        {
            Console.WriteLine("=== 추가 ===");
            Console.Write("name:");
            string name = Console.ReadLine();
            Console.Write("tel:");
            string tel = Console.ReadLine();
            ab.add(new Person(name, tel));
        }

        public void printPersons()
        {
            Console.WriteLine("=== 전체 목록 ===");
            ab.printAll();
        }
    }

}
