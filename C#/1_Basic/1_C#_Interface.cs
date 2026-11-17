using System;
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

