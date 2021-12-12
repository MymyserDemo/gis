using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace ConsoleApplication
{
    class Program
    {
        [DllImport("Common.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void MainControllerCreate();

        [DllImport("Common.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void MainControllerDelete();

        [DllImport("Common.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void MainControllerInitialize();

        [DllImport("Common.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void MainControllerFinalize();

        delegate void CallBackFunction(string classname, string functionname);

        [DllImport("Common.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void MainControllerSetLogger(CallBackFunction callback);

        static void loggerOutput(string classname, string functionname)
        {
            Console.WriteLine(classname +":" + functionname);
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Application Start.");

            MainControllerCreate();

            MainControllerSetLogger(loggerOutput);

            MainControllerInitialize();

            MainControllerFinalize();

            MainControllerDelete();

            Console.WriteLine("Application End.");
        }
    }
}
