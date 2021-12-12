#pragma once

#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
#include "BaseModel.h"
#include "ErrorController.h"
#include "DebugLogger.h"
#include "HybridInterface.h"
#include "LoadDataList.h"
#include "map/MapData.h"

#define MAIN_MODEL_CLASSNAME "MainModel"
#define COMMA_STRING ","
#define COMMA_CODE ','
#define LEFT_CURLY_BRACKET_STRING "{"
#define RIGHT_CURLY_BRACKET_STRING "}"
#define LEFT_SQUARE_BRACKET "["
#define RIGHT_SQUARE_BRACKET "]"
#define PLACEHOLDER_STRING "%s"
#define PLACEHOLDER_DECIMAL "%d"
#define CRLF "\r\n"
#define COLON ":"
#define SEMICOLON ";"
#define DATASTRING "\"data\""
/**
 * メインモデル.
 */
class MainModel : public BaseModel, public DebugLogger, public ErrorController
{
public :
  // コンストラクタ
  MainModel();
  // デストラクタ
  ~MainModel();
  // 初期処理
  void initialize();
  // 終了処理
  void finalize();
  // 文字列書式設定
  std::string formatting(
    // 文字列
    std::string,
    // 書式
    const char *,
    // 置き換え対象文字列
    std::string
  );
  // CSVファイル読み込み完了
  bool loadCsvComplete(
    // ロードデータ情報
    LoadDataList *,
    // ロードデータ
    char *
  );
  // ロードデータ情報テーブル検索
  LoadDataList serachLoadDataList(
    // ロードデータ情報テーブル
    const VectorLoadDataList&,
    // データ名称
    std::string
  );
  // ロードデータ情報テーブルレコード検索
  size_t serachLoadDataListRecord(
    // ロードデータ情報テーブル
    const VectorLoadDataList&,
    // データ名称
    std::string,
    // 検索キーワード
    std::string,
    // 検索開始位置
	size_t,
    // 検索方向
    bool,
    // 検索列
	size_t
  );
  // データテーブルヘッダー取得
  char *getLoadCsvHeader(
    // ロードデータ情報
    LoadDataList &,
    // データフォーマット
    const char *,
    // 取得する列数
	size_t
  );
  // データテーブル行データ取得
  char *getLoadCsvData(
    // ロードデータ情報
    LoadDataList &,
    // データフォーマット
    const char *,
    // 取得する列数
	size_t
  );
  // ポイントデータ設定
  void setPointData(
    // ロードデータ情報
    LoadDataList &,
    // ラインデータ情報
    MapPoint &
  );
  // ラインデータ設定
  void setLineData(
    // ロードデータ情報
    LoadDataList &,
    // ラインデータ情報
    MapLine &
  );
  // ポイント情報取得
  char *getPointData(
    // ポイント情報
    MapPoint &
  );
  // ライン情報取得
  char *getLineData(
    // ライン情報
    MapLine &
  );
  // データテーブル行データ取得.
  char *getLoadDataDetail(
    // ロードデータ情報
    LoadDataList &,
    // レコードID
	size_t
  );
  // 文字列のコピー.
  // 2017/04/01現在strncpy_sがAndroid NDKのライブラリに存在しないため独自に実装します.
  void hybridStrncopy(
    // コピー先
    char *d,
    // コピー先領域サイズ
    size_t dlen,
    // コピー元
    char *s,
    // コピー元領域サイズ
    size_t slen
  );
};
