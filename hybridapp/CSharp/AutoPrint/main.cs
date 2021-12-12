using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;
/**
* Visual Studio用アプリケーションメイン.
*/
namespace AutoPrint
{
    /**
    * アプリメインクラス.
    */
    static class main
    {
        // 自クラスの名称
        const string CLASS_NAME = "main";
        // Hybrid側の内部から呼ばれるアプリ側のログ出力関数
        delegate void loggerFunction(string classname, string functionname, string messgae);
        // Hybrid側の内部から呼ばれるアプリ側のエラーログ出力関数
        delegate void errorFunction(string classname, int errorCode);
        // Hybrid側の内部から呼ばれるアプリ側のファイルロード関数
        delegate string loadCSVFunction(string filePath);
        // Hybrid側の内部から呼ばれるアプリ側のデータヘッダー表示関数
        delegate void dataListAddHeader(string data);
        // Hybrid側の内部から呼ばれるアプリ側のデータ表示関数
        delegate void dataListAddData(string data);

        // Hybrid側のDLLの定義
        [DllImport("AutoPrintBridging.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void MainControllerCreate();

        [DllImport("AutoPrintBridging.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void MainControllerFinalize();

        [DllImport("AutoPrintBridging.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void MainControllerSetLogger(loggerFunction callback);

        [DllImport("AutoPrintBridging.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void MainControllerSetError(errorFunction callback);

        [DllImport("AutoPrintBridging.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void MainControllerSetLoadCSV(loadCSVFunction callback);

        [DllImport("AutoPrintBridging.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void MainControllerSetErrorCode(string classNm, char errorCd);

        [DllImport("AutoPrintBridging.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void MainControllerSetDataListAddHeader(dataListAddHeader callback);

        [DllImport("AutoPrintBridging.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void MainControllerSetDataListAddData(dataListAddData callback);

        [DllImport("AutoPrintBridging.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void MainControllerInitialize(string path);

        // メインビューインスタンス
        static MainView _mainView;

        // アプリ側ファイルロード
        static string loadCSV(string filePath)
        {
            System.IO.StreamReader sr = new System.IO.StreamReader(
              filePath,
              System.Text.Encoding.GetEncoding("shift_jis")
            );
            string text = sr.ReadToEnd();
            sr.Close();
            return text;
        }

        // カスタムイベント（ロード開始）ハンドラー
        static private void loadStart(object sender, EventArgs e)
        {
            _mainView.loggerOutput(CLASS_NAME, System.Reflection.MethodBase.GetCurrentMethod().Name, _mainView.getPaht());
            string filePath = _mainView.getPaht() + "\\app\\data\\pointlistsjis.csv";
            // Hybrid側のメインコントローラー初期処理
            MainControllerInitialize(filePath);
        }

        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            // メインビュー作成
            _mainView = new MainView();

            // イベントハンドラーを追加する
            _mainView.loadStart += new EventHandler(loadStart);

            // Hybrid側のメインコントローラーを作成
            MainControllerCreate();

            // ログ出力関数をHybrid側に設定する
            MainControllerSetLogger(_mainView.loggerOutput);

            // エラーログ出力関数をHybrid側に設定する
            MainControllerSetError(_mainView.errorOutput);

            // データヘッダー表示関数をハイブリッド側に設定する
            MainControllerSetDataListAddHeader(_mainView.dataListAddHeader);

            // データ表示関数をハイブリッド側に設定する
            MainControllerSetDataListAddData(_mainView.dataListAddData);

            // ファイルロード関数をハイブリッド側に設定する
            MainControllerSetLoadCSV(loadCSV);

            // メインビュー実行
            Application.Run(_mainView);

            // Hybrid側メインコントローラー終了処理
            MainControllerFinalize();
        }
    }
}
