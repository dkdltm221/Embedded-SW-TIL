/*
C#에서 델리게이트(Delegate)와 이벤트(Event)는 객체 간의 '연락망'과 같습니다. 
특히 "어떤 일이 일어났을 때 자동으로 알려주는" 기능을 구현할 때 필수적입니다.
*/

/*
class Program
{
    // 1. 델리게이트 정의 (함수 모양을 정함)
    public delegate void MyHandler(string message);
    
    static void SayHello(string msg) => Console.WriteLine($"Hello, {msg}");
    static void SayBye(string msg) => Console.WriteLine($"Bye, {msg}");

    static void Main()
    {
        // 2. 델리게이트 변수에 메서드 담기
        MyHandler handler = SayHello;
        handler += SayBye; // 메서드 추가 가능 (멀티캐스트)

        // 3. 델리게이트 호출
        handler("사용자님!");
    }
}
*/
/*
//Action 사용법
using System;

class Program
{
    static void Main()
    {
        // 1. 매개변수가 없는 Action: 작업 시작을 알림
        Action startLog = () => Console.WriteLine("작업을 시작합니다..."); //익명함수

        // 2. 매개변수가 있는 Action: 완료된 메시지를 전달
        Action<string> completeLog = (msg) => Console.WriteLine($"완료: {msg}");

        // 3. 실행
        startLog();
        ProcessData("데이터 처리", completeLog);
    }

    static void ProcessData(string taskName, Action<string> onComplete)
    {
        Console.WriteLine($"{taskName} 중...");
        // 작업이 끝난 후, 전달받은 Action 실행
        onComplete("성공적으로 마무리되었습니다.");
    }
}
*/

/*
Func 사용법
using System;

class Program
{
    static void Main()
    {
        // 1. Func 정의: int를 받아서 string을 반환
        Func<int, string> getGrade = (score) =>
        {
            if (score >= 90) return "VIP";
            if (score >= 60) return "일반";
            return "신규";
        };

        // 2. 실행
        int myScore = 85;
        string grade = getGrade(myScore); // 결과를 변수에 담을 수 있음!

        Console.WriteLine($"점수: {myScore}, 등급: {grade}");
    }
}
*/

// 문제점: 외부에서의 변경
//event 키워드가 없는 경우
//event를 안 쓰고 그냥 델리게이트를 공개하면, 외부에서 객체의 내부 상태를 마음대로 조작할 수 있습니다.
// 이벤트를 사용하기전 
/*
public class AddressBook
{
    // 그냥 public 델리게이트 (event 키워드 없음)
    public Action<Contact> OnContactAdded;
}

// 외부 프로그램(Program.cs)에서...
var book = new AddressBook();

// 1. 실수로 혹은 악의적으로 기존 구독자를 다 지워버릴 수 있음!
book.OnContactAdded = null;

// 2. 클래스 내부가 아닌데도 강제로 이벤트를 발생시킬 수 있음!
book.OnContactAdded.Invoke(new Contact("해커", "000"));
*/

// event 키워드가 있는 경우 (안전함)

// event를 붙이면 컴파일러가 외부 접근을 엄격하게 제한합니다.

/*
public class AddressBook
{
    // event 키워드 사용
    public event Action<Contact> OnContactAdded;
}

// 외부 프로그램(Program.cs)에서...
var book = new AddressBook();

// 성공: 구독(+)과 해지(-)는 가능
book.OnContactAdded += (c) => Console.WriteLine("추가됨");

// 오류: 외부에서 null 대입 불가 (Compile Error!)
// book.OnContactAdded = null;

// 오류: 외부에서 직접 호출 불가 (Compile Error!)
// book.OnContactAdded.Invoke(...);
*/
/**
 이벤트 (Event): "델리게이트를 안전하게 사용하는 포장지"
 용도: 델리게이트 -> 메서드 자체를 인자로 넘기는 콜백(Callback)
    이벤트->버튼 클릭, 상태 변화 알림 등 통보(Notification)


 **/
 /*
 public class Player
{
    // 이벤트 선언 (델리게이트 타입을 이벤트로 포장)
    public event Action OnDie;

    public void Hit(int damage)
    {
        Console.WriteLine($"공격받음! 현재 체력: {damage}");
        if (damage <= 0)
        {
            // 이벤트 발생 (구독자들에게 통보)
            OnDie?.Invoke();
        }
    }
}

class Program
{
    static void Main()
    {
        Player player = new Player();

        // 이벤트 구독 (구독자가 스스로 알아서 연결)
        player.OnDie += () => Console.WriteLine("캐릭터 사망! 게임 오버!");

        player.Hit(10);
        player.Hit(0); // 여기서 OnDie 이벤트 발생
    }
}
*/
/*
public class Player
{
    // 이벤트 선언 (델리게이트 타입을 이벤트로 포장)
    public event Action OnDie;

    public void Hit(int damage)
    {
        Console.WriteLine($"공격받음! 현재 체력: {damage}");
        if (damage <= 0)
        {
            // 이벤트 발생 (구독자들에게 통보)
            OnDie?.Invoke();
        }
    }
}

class Program
{
    static void Main()
    {
        Player player = new Player();

        // 이벤트 구독 (구독자가 스스로 알아서 연결)
        player.OnDie += () => Console.WriteLine("캐릭터 사망! 게임 오버!");

        player.Hit(10);
        player.Hit(0); // 여기서 OnDie 이벤트 발생
    }
}
public class Order
{
    public event EventHandler<OrderEventArgs> OrderCompleted;

    public void CompleteOrder()
    {
        OrderEventArgs args = new OrderEventArgs
        {
            OrderId = 1001,
            Price = 50000
        };

        OrderCompleted?.Invoke(this, args);
    }
}
class Program
{
    static void Main()
    {
        Order order = new Order();
        
				//EventHandler 델리게이트에 구현한 이벤트 핸들러 함수 등록
        order.OrderCompleted += OnOrderCompleted; 

        order.CompleteOrder(); //이벤트 발생
    }

    //이벤트 핸들러로 사용할 함수 정의
    static void OnOrderCompleted(object sender, OrderEventArgs e)
    {
        Console.WriteLine($"주문번호: {e.OrderId}");
        Console.WriteLine($"주문금액: {e.Price}");
    }
}
*/