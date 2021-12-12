/**
* Hybrid側のC++をJavaScriptから利用するためのインターフェース定義.
*/
#pragma once
#include "HybridInterface.h"
#include "ErrorController.h"
#include "DebugLogger.h"
#include <emscripten.h>

/** *******************************************************
 * JSからC++呼び出し
 ******************************************************* */

extern "C" {
  // ログ出力
  void bridgingLogOutput(const char *, const char *);
  // Hybrid側メインコントローラー処理開始
  void bridgingMainControllerStart(void);
  // Hybrid側メインコントローラー終了処理
  void bridgingMainControllerStop(void);
  // CSVファイルロード完了
  void bridgingLoadCsvComplete(char *, CsvLoader);
  // ロードデータ情報テーブルレコード検索
  size_t bridgingSerachLoadDataListRecord(
    char *,
    char *,
    size_t,
    bool,
    size_t
  );
  // データテーブル詳細データ取得.
  char *bridginggetLoadDataDetail(char *, size_t);
}

/** *******************************************************
 * C++からJSを呼び出す関数
 ******************************************************* */
// データリストタイトル行追加
void bridgingDataListAddHeader(
  // タイトル行データ
  char *
);
// データリスト行データ追加
void bridgingDataListAddData(
  // 行データ
  char *
);
// Hybrid側から呼ばれるアプリ側のログ表示コールバック
void bridgingSetLoggerCallback(LoggerArgument);
// Hybrid側から呼ばれるアプリ側のエラー表示コールバック
void bridgingSetErrorCallback(ErrorArgument);
