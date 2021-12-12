using System;
using System.Windows.Forms;

namespace WindowsFormsApplication
{
    public partial class MainView : Form
    {
        public void loggerOutput(string classname, string functionname, string messgae)
        {
            Console.WriteLine(classname + ":" + functionname + ":" + messgae);
        }

        public void errorOutput(string classname, int errorCode)
        {
            Console.WriteLine("Error " + classname + ":" + errorCode);
        }

        public MainView()
        {
            InitializeComponent();
        }

        private void MainView_Load(object sender, EventArgs e)
        {

        }
    }
}
