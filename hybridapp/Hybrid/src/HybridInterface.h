#pragma once

#include <string.h>
#include <string>
#include <functional>

/**
 * ログ出力メッセージ.
 */
typedef struct _LoggerArugument {
  // ログを出力するクラス名称
  const char *className;
  size_t classNameLength;
  // ログを出力する関数名称
  const char *functionName;
  size_t functionNameLength;
  // 任意のメッセージ
  const char *message;
  size_t messageLength;
} LoggerArgument;

/**
* エラー情報.
*/
typedef struct _ErrorArugument {
	// エラーが発生したクラス名称
	const char *className;
	size_t classNameLength;
	// エラーコード
	unsigned char errorCode;
} ErrorArgument;

/**
 * ハイブリッドインターフェース汎用文字列.
 */
typedef struct _HybridString {
  char *hybridString;
  size_t hybridStringLength;
} HybridString;

/**
 * CSVファイルロードコンポーネント.
 */
struct CsvLoader {
  // アプリ側から呼ばれるHybrid側のコールバックの定義.
  typedef std::function<void(char *, CsvLoader)> _CSVLOADERCALLBACK;
  // ロード後にViewへ出力するコールバックの定義.
  typedef std::function<void(std::string)> _VIEWPUTCALLBACK;
  // コンストラクタ
  CsvLoader(
    // データ名称
    const char *dataName,
    // ファイルパス
    const char *filePath,
    // ロード完了時実行コールバック
    _CSVLOADERCALLBACK &csvLoaderCallbackFunction,
    // View表示コールバック
    _VIEWPUTCALLBACK   &viewPutCallbackFunction
  ):
    // データ名称
    _dataName(dataName),
    // ファイルパス
    _filePath(filePath),
    // ロード完了時実行コールバック
    csvLoaderCallback(csvLoaderCallbackFunction),
    // View表示コールバック
    viewPutCallback(viewPutCallbackFunction)
  {}
  // インスタンスセット
  void setInstance(CsvLoader *instance) { _instance = instance; };
  // インスタンスゲット
  CsvLoader *getInstance() { return _instance; };
  // データ名称ゲット
  const char *getDataName() { return _dataName; };
  // アプリ側CSVファイルロード
  void bridgingLoadCsv();
  // ハイブリッド側から指定されたロード完了時のコールバック
  _CSVLOADERCALLBACK csvLoaderCallback;
  // ハイブリッド側から指定されたView出力のコールバック
  _VIEWPUTCALLBACK viewPutCallback;
private:
  // CSVファイルロードコンポーネントインスタンス
  CsvLoader * _instance;
  // データ名称
  const char * _dataName;
  // ファイルパス
  const char * _filePath;
};
// アプリ側から呼ばれるHybrid側のロード完了後コールバックの定義.
typedef std::function<void(char *, CsvLoader)> CSVLOADERCALLBACK;
// アプリ側から呼ばれるHybrid側のView出力コールバックの定義.
typedef std::function<void(std::string)> VIEWPUTCALLBACK;

/** *******************************************************
 * ハイブリッド側から呼び出すアプリ側の関数
 ******************************************************* */
  // Hybrid側から呼ばれるアプリ側のデータリストタイトル行追加
  void bridgingDataListAddHeader(
    // タイトルデータ
    char *
  );
  // Hybrid側から呼ばれるアプリ側のデータリスト行データ追加
  void bridgingDataListAddData(
    // 行データ
    char *
  );
  // Hybrid側から呼ばれるアプリ側のオプション1表示
  void bridgingOption1(
    // 行データ
    char *
  );
  // Hybrid側から呼ばれるアプリ側のオプション2表示
  void bridgingOption2(
    // 行データ
    char *
  );
  // Hybrid側から呼ばれるアプリ側のオプション3表示
  void bridgingOption3(
    // 行データ
    char *
  );
  // Hybrid側から呼ばれるアプリ側のポイント表示
  void bridgingPutPoint(
    // ポイントデータ
    char *,
    // レイヤ番号
	size_t
  );
  // Hybrid側から呼ばれるアプリ側のライン表示
  void bridgingPutLine(
    // ラインデータ
    char *,
    // レイヤ番号
	size_t
  );
  // Hybrid側から呼ばれるアプリ側のGeoJson表示
  void bridgingPutGeoJson(
    // GeoJsonファイルパス
    const char *,
    // レイヤ番号
	size_t
  );
