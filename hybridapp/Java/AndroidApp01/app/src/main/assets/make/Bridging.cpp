/**
* Hybrid側のC++をJavaScriptから利用するためのインターフェース定義.
*/
#include "Bridging.h"
#include "MainController.h"

// モジュール名
#define MODULE_NAME "BridgingCpp"
// Cインターフェースのメインコントローラーのインスタンス
static MainController * _mainController;

/** **************************************************
 * JSからC++呼び出し
 ************************************************** */
extern "C" {
  // ログ出力
  void bridgingLogOutput(const char *functionName, const char *message) {
    EM_ASM_(
      {
        mainViewLogOutput(
          Module.Pointer_stringify($0) + ":" +
          Module.Pointer_stringify($1) + ":" +
          Module.Pointer_stringify($2)
        );
      },
      MODULE_NAME,
      functionName,
      message
    );
  }

  // Hybrid側メインコントローラー処理開始
  void bridgingMainControllerStart(void) {
    bridgingLogOutput(__func__, "");
    // メインコントローラーインスタンス作成
    _mainController = new MainController();
    // メインコントローラーインスタンス格納
    _mainController->instance = _mainController;
    // ログ出力設定
    _mainController->setLoggerCallback(bridgingSetLoggerCallback);
    // エラー出力設定
    _mainController->setErrorCallback(bridgingSetErrorCallback);
    // メインコントローラー初期処理
    _mainController->initialize();
  }

  // Cインターフェースメインコントローラー終了処理
  void bridgingMainControllerStop(void) {
    bridgingLogOutput(__func__, "");
    if(_mainController == NULL) {
        return;
    }
    // メインコントローラー終了処理
    _mainController->finalize();
    delete _mainController;
    _mainController = NULL;
  }

  // CSVファイルロード完了
  void bridgingLoadCsvComplete(
    // ロードデータ
    char *data,
    // ロードデータ情報
    CsvLoader loader
  ) {
    bridgingLogOutput(__func__, "");
    // Hybrid側コールバック
    loader.csvLoaderCallback(data, loader);
  }

  /**
   * ロードデータ情報テーブルレコード検索.
   * @param dataName     データ名称
   * @param keyword      検索キーワード
   * @param start        検索開始位置
   * @param direction    検索方向
   * @param column       検索列
   */
  size_t bridgingSerachLoadDataListRecord(
    char *dataName,
    char *keyword,
    size_t start,
    bool direction,
    size_t column
  ) {
    bridgingLogOutput(__func__, "");
    // エラーチェック
    if(_mainController == NULL) {
      return -1;
    }
    return _mainController->serachLoadDataListRecord(
      dataName,
      keyword,
      start,
      direction,
      column
    );
  }

  /**
   * データテーブル詳細データ取得.
   * @param dataName   データ名称
   * @param recId      レコードID
   */
  char *bridginggetLoadDataDetail(
    char *dataName,
    size_t recId
  ) {
    bridgingLogOutput(__func__, "");
    // エラーチェック
    if(_mainController == NULL) {
      return (char *)"";
    }
    char *result = _mainController->getLoadDataDetail(
      dataName,
      recId
    );
    return result;
  }
}

/* ********************************************************
 * CSVファイルロードコンポーネント
 ******************************************************* */

// Hybrid側から呼ばれるCSVファイルロード開始
void CsvLoader::bridgingLoadCsv() {
  bridgingLogOutput(__func__, "");
  EM_ASM_ARGS({
      commonFileLoad($0, $1);
    },
    _filePath,
    this
  );
  return;
}

/** *******************************************************
 * C++からJSを呼び出す時の引数変換
 ******************************************************* */

// Hybrid側から呼ばれるアプリ側のログ表示コールバック関数
void bridgingSetLoggerCallback(LoggerArgument loggerArgument) {
  EM_ASM_({
      var logMessage =
        Module.Pointer_stringify($0) + ":" +
        Module.Pointer_stringify($1) + ":" +
        Module.Pointer_stringify($2);
      mainViewLogOutput(logMessage);
    },
    loggerArgument.className,
    loggerArgument.functionName,
    loggerArgument.message
  );
}

// Hybrid側から呼ばれるアプリ側のエラー表示コールバック関数
void bridgingSetErrorCallback(ErrorArgument errorArgument) {
  EM_ASM_({
      var errorMessage =
        "Error:" +
        Module.Pointer_stringify($0) + ":" +
        $1;
      mainViewLogOutput(errorMessage);
    },
    errorArgument.className,
    errorArgument.errorCode
  );
}

// Hybrid側から呼ばれるアプリ側のデータリストタイトル行追加
void bridgingDataListAddHeader(
  // ロードデータ
  char *data
) {
  bridgingLogOutput(__func__, "");
  EM_ASM_({
      mainViewDataListAddHeader(Module.Pointer_stringify($0));
    },
    data
  );
}

// Hybrid側から呼ばれるアプリ側のデータリスト行データ追加
void bridgingDataListAddData(
  // ロードデータ
  char *data
) {
  bridgingLogOutput(__func__, "");
  EM_ASM_({
      mainViewDataListAddData(Module.Pointer_stringify($0));
    },
    data
  );
}

/**
 * Hybrid側から呼ばれるアプリ側のオプション1表示.
 * @param data 行データ
 */
void bridgingOption1(char *data) {
  bridgingLogOutput(__func__, "");
  EM_ASM_({
      mainViewOption1(Module.Pointer_stringify($0));
    },
    data
  );
}

/**
 * Hybrid側から呼ばれるアプリ側のオプション2表示.
 * @param data 行データ
 */
void bridgingOption2(char *data) {
  bridgingLogOutput(__func__, "");
  EM_ASM_({
      mainViewOption2(Module.Pointer_stringify($0));
    },
    data
  );
}

/**
 * Hybrid側から呼ばれるアプリ側のオプション3表示.
 * @param data 行データ
 */
void bridgingOption3(char *data) {
  bridgingLogOutput(__func__, "");
  EM_ASM_({
      mainViewOption3(Module.Pointer_stringify($0));
    },
    data
  );
}

/**
 * Hybrid側から呼ばれるアプリ側のポイント表示.
 * @param data ポイントデータ
 * @param layerNo レイヤ番号
 */
void bridgingPutPoint(char *data, size_t layerNo) {
  bridgingLogOutput(__func__, "");
  EM_ASM_({
      mainViewPutPoint(Module.Pointer_stringify($0), $1);
    },
    data,
    layerNo
  );
}

/**
 * Hybrid側から呼ばれるアプリ側のライン表示.
 * @param data ラインデータ
 * @param layerNo レイヤ番号
 */
void bridgingPutLine(char *data, size_t layerNo) {
  bridgingLogOutput(__func__, "");
  EM_ASM_({
      mainViewPutLine(Module.Pointer_stringify($0), $1);
    },
    data,
    layerNo
  );
}

/**
 * Hybrid側から呼ばれるアプリ側のGeoJson表示.
 * @param data GeoJsonファイルパス
 * @param layerNo レイヤ番号
 */
void bridgingPutGeoJson(const char *data, size_t layerNo) {
  bridgingLogOutput(__func__, "");
  EM_ASM_({
      mainViewPutGeoJson(Module.Pointer_stringify($0), $1);
    },
    data,
    layerNo
  );
}
