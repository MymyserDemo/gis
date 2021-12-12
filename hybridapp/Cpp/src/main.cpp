/**
 * g++(gcc)用アプリケーションメイン.
 */
#include <fstream>
#include "MainController.h"
#include "MainView.h"
#include "json11/json11.hpp"

#define MAIN_NAME "main"

// Hybrid側のメインコントローラー
static MainController *_mainController;
// Native側のメインビュー
static MainView *_mainView;

/**
 * ログ画面出力.
 * ログを画面に標準出力します.
 * @param loggerArgument ログに表示する内容.
 */
void logger(LoggerArgument loggerArgument) {
  if(_mainView == NULL) {
    return;
  }
  // この関数を呼び出したHybrid側のクラス名、関数名、メッセージを標準出力する
  _mainView->viewLogOutput(loggerArgument);
}

/**
 * ログ出力.
 * アプリ側から呼ばれるログ出力.
 * @param functionName ログを出力した関数名
 * @param ログメッセージ
 */
void bridgingLogOutput(const char *functionName, const char *message) {
  LoggerArgument loggerArgument;
  loggerArgument.className = MAIN_NAME;
  loggerArgument.functionName = functionName;
  loggerArgument.message = message;
  logger(loggerArgument);
}

/**
 * エラー画面出力.
 * エラーを画面に標準出力します.
 * @param errorArgument ログに表示する内容.
 */
void error(ErrorArgument errorArgument) {
	if (_mainView == NULL) {
		return;
	}
	// この関数を呼び出したHybrid側のクラス名、エラーコードを標準出力する
	_mainView->viewErrorOutput(errorArgument);
}

/**
 * エラー出力.
 * アプリ側から呼ばれるエラー出力.
 * @param errorCode エラー番号
 */
void bridgingErrorOutput(unsigned char errorCode) {
  ErrorArgument errorArgument;
  errorArgument.className = MAIN_NAME;
  errorArgument.errorCode = errorCode;
  error(errorArgument);
}

/**
 * CSVファイルロード完了.
 * CSVファイルがロードされた後にハイブリッド側のコールバックを実行します.
 * @param data ロードデータ
 * @param loader ロードデータ情報
 */
void bridgingLoadCsvComplete(char *data, CsvLoader loader) {
  bridgingLogOutput(__func__, "");
  // Hybrid側コールバック
  loader.csvLoaderCallback(data, loader);
  // CSVファイルロードコンポーネント削除
   delete loader.getInstance();
}

// JSONのparse時のエラー
static std::string parseError;

/**
 * アプリメイン.
 * アプリ起動時に最初に実行されるメイン処理.
 * @return 実行結果
 */
int main() {
  char keyCode;

  // メインコントローラーインスタンス作成
  _mainController = new MainController();
  // 自インスタンスを保管
  _mainController->instance = _mainController;
  // メインビューインスタンス作成
  _mainView = new MainView();
  // ログ出力関数をHybrid側に設定する
  _mainController->setLoggerCallback(logger);
  // エラー出力関数をHybrid側に設定する
  _mainController->setErrorCallback(error);
  // 初期処理
  _mainController->initialize();
  // キーボード入力待ち
  keyCode = _mainView->viewInput();
  // 終了処理
  _mainController->finalize();

  return 0;
}

/**
 * Hybrid側から呼ばれるCSVファイルロード開始.
 */
void CsvLoader::bridgingLoadCsv() {
  _mainController->logger(MAIN_NAME, (const char *)__func__, _filePath);
  // ファイルをバイナリで読み込む
  std::ifstream ifs(_filePath, std::ios_base::binary);
  if (ifs.fail()) {
    bridgingErrorOutput(1);
    return;
  }
  // ファイルサイズを算出
  int begin = ifs.tellg();
  ifs.seekg(0, ifs.end);
  int end = ifs.tellg();
  int size = end - begin;
  // 先頭に戻り読み込む
  ifs.clear();
  ifs.seekg(0, ifs.beg);
  char *str = new char[size + 1];
  str[size] = '\0';
  ifs.read(str, size);
  // ロード完了
  bridgingLoadCsvComplete(str, *this);
}

/**
 * Hybrid側から呼ばれるアプリ側のデータリストタイトル行追加.
 * @param data タイトルデータ
 */
void bridgingDataListAddHeader(char *data) {
  auto jsonData = json11::Json::parse(data, parseError);
  bridgingLogOutput(__func__, jsonData.dump().c_str());
}

/**
 * Hybrid側から呼ばれるアプリ側のデータリスト行データ追加.
 * @param data 行データ
 */
void bridgingDataListAddData(char *data) {
  auto jsonData = json11::Json::parse(data, parseError);
  bridgingLogOutput(__func__, jsonData.dump().c_str());
}

/**
 * Hybrid側から呼ばれるアプリ側のオプション1表示.
 * @param data 行データ
 */
void bridgingOption1(char *data) {
  auto jsonData = json11::Json::parse(data, parseError);
  bridgingLogOutput(__func__, jsonData.dump().c_str());
}

/**
 * Hybrid側から呼ばれるアプリ側のオプション2表示.
 * @param data 行データ
 */
void bridgingOption2(char *data) {
  auto jsonData = json11::Json::parse(data, parseError);
  bridgingLogOutput(__func__, jsonData.dump().c_str());
}

/**
 * Hybrid側から呼ばれるアプリ側のオプション3表示.
 * @param data 行データ
 */
void bridgingOption3(char *data) {
  auto jsonData = json11::Json::parse(data, parseError);
  bridgingLogOutput(__func__, jsonData.dump().c_str());
}

/**
 * Hybrid側から呼ばれるアプリ側のポイント表示.
 * @param data ポイントデータ
 */
void bridgingPutPoint(char *data, size_t layerNo) {
  auto jsonData = json11::Json::parse(data, parseError);
  bridgingLogOutput(__func__, jsonData.dump().c_str());
}

/**
 * Hybrid側から呼ばれるアプリ側のライン表示.
 * @param data ラインデータ
 */
void bridgingPutLine(char *data, size_t layerNo) {
  auto jsonData = json11::Json::parse(data, parseError);
  bridgingLogOutput(__func__, jsonData.dump().c_str());
}

/**
 * Hybrid側から呼ばれるアプリ側のGeoJson表示.
 * @param data GeoJsonファイルパス
 */
void bridgingPutGeoJson(const char *data, size_t layerNo) {
  bridgingLogOutput(__func__, data);
}
