using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Windows.Input;
using MVVM.Models;
using System.Collections.ObjectModel;
namespace MVVM
{
    internal class MainViewModel :INotifyPropertyChanged
    {   

        public event PropertyChangedEventHandler? PropertyChanged;
        public ICommand Save { get; }

        

        private bool isMale;
        public bool IsMale
        {
            get => isMale;
            set
            {
                isMale = value;
                if(isMale)
                {
                    Result = "male";
                }
                OnPropertyChanged(nameof(IsMale));
            }
        }
        private bool isFemale;
        public bool IsFemale
        {
            get => isFemale;
            set
            {
                isFemale = value;
                if(isFemale)
                {
                    Result = "female";
                }
                OnPropertyChanged(nameof(IsFemale));
            }
        }
        private string result;
        public string Result
        {
            get => result;
            set
            {
                result = value;
                OnPropertyChanged(nameof(Result));
            }
        }
        private string name;

        public string Name
        {
            get => name;
            set
            {
                name = value;
                OnPropertyChanged(nameof(Name));
            }

        }
        private int num;

        public int Num
        {
            get => num;

            set
            {
                num = value;
                OnPropertyChanged(nameof(Num));
            }
        }

        public MainViewModel()
        {
            name = "aaa";
            num = 1;
            Save = new SaveCmd(save);
        }
        private ObservableCollection<Person> persons = new ObservableCollection<Person>();

        public ObservableCollection<Person> Persons { get; }
            = new ObservableCollection<Person>();
        private void save()
        {
            Persons.Add(new Person(Name, Num));
        }
       

        //이벤트 발생 함수
        private void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
    }
}

namespace MVVM.Models
{
    public class Person
    {
        public string Name { get; set; } = "";
        public int Num { get; set; }

        public Person() { }

        public Person(string name, int num)
        {
            Name = name;
            Num = num;
        }

        public override string ToString()
        {
            return Name + " / " + Num;
        }
    }
}