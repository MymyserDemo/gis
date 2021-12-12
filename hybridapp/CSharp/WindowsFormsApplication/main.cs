using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;
/**
* Visual Studio用アプリケーションメイン.
*/
namespace WindowsFormsApplication
{
  /**
  * アプリメインクラス.
  */
  static class main
  {
    // Hybrid側の内部から呼ばれるアプリ側のログ出力関数
    delegate void loggerFunction(string classname, string functionname, string messgae);
    // Hybrid側の内部から呼ばれるアプリ側のエラーログ出力関数
    delegate void errorFunction(string classname, int errorCode);
    // Hybrid側の内部から呼ばれるアプリ側のファイルロード関数
    delegate string loadCSVFunction(string filePath);

    // Hybrid側のDLLの定義
    [DllImport("Bridging.dll", CallingConvention = CallingConvention.Cdecl)]
    private extern static void MainControllerCreate();

    [DllImport("Bridging.dll", CallingConvention = CallingConvention.Cdecl)]
    private extern static void MainControllerInitialize();

    [DllImport("Bridging.dll", CallingConvention = CallingConvention.Cdecl)]
    private extern static void MainControllerFinalize();

    [DllImport("Bridging.dll", CallingConvention = CallingConvention.Cdecl)]
    private extern static void MainControllerSetLogger(loggerFunction callback);

    [DllImport("Bridging.dll", CallingConvention = CallingConvention.Cdecl)]
    private extern static void MainControllerSetError(errorFunction callback);

    [DllImport("Bridging.dll", CallingConvention = CallingConvention.Cdecl)]
    private extern static void MainControllerSetLoadCSV(loadCSVFunction callback);

    [DllImport("Bridging.dll", CallingConvention = CallingConvention.Cdecl)]
    private extern static void MainControllerSetErrorCode(string classNm, char errorCd);

    // メインビューインスタンス
    static MainView _mainView;

    // アプリ側ファイルロード関数
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

    // アプリ側メイン
    [STAThread]
    static void Main() {
      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);

      // メインビュー作成
      _mainView = new MainView();

      // Hybrid側のメインコントローラーを作成
      MainControllerCreate();

      // ログ出力関数をHybrid側に設定する
      MainControllerSetLogger(_mainView.loggerOutput);

      // エラーログ出力関数をHybrid側に設定する
      MainControllerSetError(_mainView.errorOutput);

      // ファイルロード関数を側に設定する
      MainControllerSetLoadCSV(loadCSV);

      // Hybrid側のメインコントローラー初期処理
      MainControllerInitialize();

      // メインビュー実行
      Application.Run(_mainView);
      
      // Hybrid側メインコントローラー終了処理
      MainControllerFinalize();
    }
  }
}
