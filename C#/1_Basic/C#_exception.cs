using System;
using System.Collections.Generic;
using System.Text;

namespace exception2
{
    internal class MyData
    {
        private string[] data = new string[3];

        public readonly int cnt; //선언시 또는 생성자에서만 값 할당 가능. 읽기 전용

        public MyData(){
            cnt = data.Length;

        }

        //인덱서
        public string this[int idx]
        {
            set{ 
                if(idx<0|| idx >=data.Length){
                    throw new Exception("잘못된 배열 인덱스");
                }
                data[idx] = value;
            }
            get{
                if(idx<0|| idx >=data.Length){
                    throw new Exception("잘못된 배열 인덱스");
                } 
                return data[idx];
            }
        }
    }
}

MyData data = new();
data[0] = "aaa";
data[1] = "bbb";
data[2] = "ccc";
data[3] = "ddd";
try{
    for(int i=0;i<data.cnt+1;i++){
        Console.WriteLine(data[i]);
    }
    
}catch (Exception ex){
     Console.WriteLine(ex.Message);
}