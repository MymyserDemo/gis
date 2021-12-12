/**
 * Hybrid側のC++をC#から利用するためのインターフェース定義.
 * C++ -> C -> C#の流れでCで定義されたインターフェースを介して
 * C++ と C# が連携しています。
 */
#include "Bridging.h"

// 自オブジェクト名称
#define CLASSNAME "Bridging"

// Hybrid側メインコントローラー
static MainController* _mainController;
// Hybrid側から呼ばれるCSVファイルロード関数
static LoadCSVCallbackFunction loadCsvCallback;

/**
 * Hybrid側メインコントローラーを作成.
 */
void MainControllerCreate() {
  _mainController = new MainController();
  _mainController->instance = _mainController;
}

/**
 * Hybrid側メインコントローラーの初期処理.
 */
void  MainControllerInitialize()
{
  if (_mainController == nullptr) {
    return;
  }
  _mainController->initialize();
}

/**
 * Hybrid側メインコントローラーの終了処理.
 */
void  MainControllerFinalize() {
  if (_mainController == nullptr) {
    return;
  }
  _mainController->finalize();
  delete _mainController;
  _mainController = nullptr;
}

// Hybrid側内部から呼ばれるログ出力コールバック関数の定義
static LoggerCallbackFunction _loggerCallback;
// Hybrid側内部から呼ばれるエラー出力コールバック関数の定義
static ErrorCallbackFunction _errorCallback;

/**
 * Hybrid側から呼ばれるログ出力コールバック関数の引数と.
 * アプリ側(C#)のコールバック関数の引数の違いを変換します.
 * @param loggerArgument ログに表示する内容.
 */
void loggerCallbackCpp(LoggerArgument loggerArgument) {
  if (_loggerCallback == nullptr) {
    return;
  }
  _loggerCallback(loggerArgument.className, loggerArgument.functionName, loggerArgument.message);
}

/**
 * Hybrid側から呼ばれるエラー出力コールバック関数の引数と.
 * アプリ側(C#)のコールバック関数の引数の違いを変換します.
 * @param errorArgument エラー情報.
 */
void errorCallbackCpp(ErrorArgument errorArgument) {
  if (_errorCallback == nullptr) {
    return;
  }
  _errorCallback(errorArgument.className, (int)errorArgument.errorCode);
}

/**
 * Hybrid側メインコントローラーにログ出力コールバック関数を設定します.
 * @param callback コールバック関数.
 */
void MainControllerSetLogger(LoggerCallbackFunction callback) {
  if (_mainController == nullptr) {
    return;
  }
  if (callback == nullptr) {
    return;
  }
  _loggerCallback = callback;
  _mainController->setLoggerCallback(loggerCallbackCpp);
}

/**
 * Hybrid側メインコントローラーにエラー出力コールバック関数を設定します.
 * @param callback コールバック関数.
 */
void MainControllerSetError(ErrorCallbackFunction callback) {
  if (_mainController == nullptr) {
    return;
  }
  if (callback == nullptr) {
    return;
  }
  _errorCallback = callback;
  _mainController->setError(errorCallbackCpp);
}

/** 
 * Hybrid側から呼ばれるアプリ側のファイルロード関数を設定します.
 *
 */
void MainControllerSetLoadCSV(LoadCSVCallbackFunction callback) {
  if (_mainController == nullptr) {
    return;
  }
  if (callback == nullptr) {
    return;
  }
  loadCsvCallback = callback;
}

/**
 * Hybrid側エラー処理を実行します.
 * @param classNm エラーが発生したクラス名.
 * @param errorCd エラーコード.
 */
void MainControllerSetErrorCode(const char *classNm, unsigned char errorCd) {
  if (_mainController == nullptr) {
    return;
  }
  _mainController->setErrorCode(classNm, errorCd);
}

/**
 * CSVファイルロード完了.
 * CSVファイルがロードされた後にハイブリッド側のコールバックを実行します.
 * @param data ロードデータ
 * @param loader ロードデータ情報
 */
void bridgingLoadCsvComplete(char *data, CsvLoader loader) {
  _loggerCallback(CLASSNAME, (const char *)__func__, "");
  // Hybrid側コールバック
  loader.csvLoaderCallback(data, loader);
  // CSVファイルロードコンポーネント削除
  delete loader.getInstance();
}

/**
 * Hybrid側から呼ばれるCSVファイルロード開始.
 */
void CsvLoader::bridgingLoadCsv() {
  _loggerCallback(CLASSNAME, (const char *)__func__, _filePath);
  bridgingLoadCsvComplete(loadCsvCallback(_filePath), *this);
}

/**
 * Hybrid側から呼ばれるアプリ側のデータリストタイトル行追加.
 * @param data タイトルデータ
 */
void bridgingDataListAddHeader(char *data) {
  _loggerCallback(CLASSNAME, (const char *)__func__, data);
}

/**
 * Hybrid側から呼ばれるアプリ側のデータリスト行データ追加.
 * @param data 行データ
 */
void bridgingDataListAddData(char *data) {
  _loggerCallback(CLASSNAME, (const char *)__func__, data);
}

/**
 * Hybrid側から呼ばれるアプリ側のオプション1表示.
 * @param data 行データ
 */
void bridgingOption1(char *data) {
  _loggerCallback(CLASSNAME, (const char *)__func__, data);
}

/**
 * Hybrid側から呼ばれるアプリ側のオプション2表示.
 * @param data 行データ
 */
void bridgingOption2(char *data) {
  _loggerCallback(CLASSNAME, (const char *)__func__, data);
}

/**
 * Hybrid側から呼ばれるアプリ側のオプション3表示.
 * @param data 行データ
 */
void bridgingOption3(char *data) {
  _loggerCallback(CLASSNAME, (const char *)__func__, data);
}

/**
* Hybrid側から呼ばれるアプリ側のポイント表示.
* @param data ポイントデータ
*/
void bridgingPutPoint(char *data, size_t layerNo) {
  _loggerCallback(CLASSNAME, (const char *)__func__, data);
}

/**
 * Hybrid側から呼ばれるアプリ側のライン表示.
 * @param data ラインデータ
 */
void bridgingPutLine(char *data, size_t layerNo) {
  _loggerCallback(CLASSNAME, (const char *)__func__, data);
}

/**
 * Hybrid側から呼ばれるアプリ側のGeoJson表示.
 * @param data GeoJsonファイルパス
 */
void bridgingPutGeoJson(const char *data, size_t layerNo) {
  _loggerCallback(CLASSNAME, (const char *)__func__, data);
}
