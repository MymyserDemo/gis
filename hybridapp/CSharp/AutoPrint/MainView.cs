using System;
using System.Windows.Forms;

namespace AutoPrint {
    // メイン画面
    public partial class MainView : Form {
        // カスタムイベント（ロード開始）
        public event EventHandler loadStart;

        // カスタムイベント（ロード開始）
        protected virtual void OnloadStart(EventArgs e) {
            if(loadStart != null) {
                loadStart(this, e);
            }
        }

        // ログ出力
        public void loggerOutput(string classname, string functionname, string messgae) {
            Console.WriteLine(classname + ":" + functionname + ":" + messgae);
        }

        // データヘッダー出力
        public void dataListAddHeader(string data) {
            MessageBox.Show(data,
                "Debug",
                MessageBoxButtons.OK,
                MessageBoxIcon.Information
            );
        }

        // データ主力
        public void dataListAddData(string data) {
            Console.WriteLine("dataListAddData:" + data);
        }

        // エラーログ出力
        public void errorOutput(string classname, int errorCode) {
            Console.WriteLine("Error " + classname + ":" + errorCode);
        }

        // メインビュー
        public MainView() {
            InitializeComponent();
        }

        // カスタムイベント（ロード開始）
        private void MainView_Load(object sender, EventArgs e) {
        }
        
        // 実行ボタンクリックイベントハンドラ
        private void buttonExecute_Click(object sender, EventArgs e) {
            loggerOutput(this.ToString(), System.Reflection.MethodBase.GetCurrentMethod().Name, "");
            webBrowser.Print();
        }

        // 参照ボタンクリックイベントハンドラ
        private void buttonReference_Click(object sender, EventArgs e) {
            FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
            folderBrowserDialog.Description = "フォルダー選択";
            folderBrowserDialog.RootFolder = System.Environment.SpecialFolder.MyComputer;
            if (folderBrowserDialog.ShowDialog() == DialogResult.OK) {
                textBoxLocate.Text = folderBrowserDialog.SelectedPath;
                OnloadStart(new EventArgs());
            }
            folderBrowserDialog.Dispose();
        }

        // データファイル位置取得
        public string getPaht() {
            return textBoxLocate.Text;
        }
    }
}
