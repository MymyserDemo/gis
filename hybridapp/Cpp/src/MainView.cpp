/**
 * メインビュー.
 */
#include "MainView.h"

using namespace std;

/**
 * コンストラクタ.
 */
MainView::MainView() {
}

/**
 * デストラクタ.
 */
MainView::~MainView() {
}

/**
 * 初期処理.
 */
void MainView::initialize() {
}

/**
 * 修了処理.
 */
void MainView::finalize() {
}

/**
 * ログ画面出力.
* @param loggerArgument ログに表示する内容.
 */
void MainView::viewLogOutput(LoggerArgument loggerArgument) {
  cout
    << loggerArgument.className
    << ":"
    << loggerArgument.functionName
    << ":"
    << loggerArgument.message
    << endl;
}

/**
* エラー画面出力.
* @param errorArgument エラー内容.
*/
void MainView::viewErrorOutput(ErrorArgument errorArgument) {
	cout
		<< "Error "
		<< errorArgument.className
		<< ":"
		<< hex << (int)errorArgument.errorCode
		<< endl;
}

/**
 * キーボード入力.
* @return キーボード入力されたキーコード.
 */
char MainView::viewInput() {
  cout << endl << "Press any key" << endl;
  char c;
  cin.get( c );
  return c;
}
