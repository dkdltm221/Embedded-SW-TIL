using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Input;

namespace MVVM
{
    class SaveCmd : ICommand
    {
        private readonly Action execute;
        public SaveCmd(Action execute)
        {
            this.execute = execute; //Action에 핸들러 등록
        }
        public event EventHandler? CanExecuteChanged; //이벤트 델리게이트(명령어와 연결된 버튼 이벤트 감지)

        public bool CanExecute(object? parameter)
        {
            return true;
        }

        public void Execute(object? parameter)
        {
            execute();
        }
    }
}
