using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication {
    class MainView {
        /** 
        * ログ出力コールバック.
        * Hybrid側の内部から呼ばれるアプリ側のログ出力処理.
        * @param classname Hybrid側から渡されるクラス名.
        * @param functionname  Hybrid側から渡される関数名.
        * @param messgae  Hybrid側から渡されるメッセージ.
        */
        public void loggerOutput(string classname, string functionname, string messgae) {
            Console.WriteLine(classname + ":" + functionname + ":" + messgae);
        }
        /** 
        * エラー出力コールバック.
        * Hybrid側の内部から呼ばれるアプリ側のエラー出力処理.
        * @param classname Hybrid側から渡されるクラス名.
        * @param errorCode  Hybrid側から渡されるエラーコード.
        */
        public void errorOutput(string classname, int errorCode) {
            Console.WriteLine("Error " + classname + ":" + errorCode);
        }
    }
}
