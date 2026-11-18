using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace MVVM
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void myButton_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("버튼 클릭");
            string txt =(string)((Button)sender).Content;
            MessageBox.Show(txt);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            tb.Text = "new Text";
        }
    }
}