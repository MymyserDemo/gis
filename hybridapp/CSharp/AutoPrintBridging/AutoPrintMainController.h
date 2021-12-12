﻿/** *******************************************************
 * ハイブリッド側メインコントローラー.
 ******************************************************* */
#pragma once

#include "HybridInterface.h"
#include "BaseController.h"
#include "ErrorController.h"
#include "DebugLogger.h"
#include "MainModel.h"
#include "LoadDataList.h"
#include "json11/json11.hpp"

#define MAIN_CONTROLLER_CLASSNAME "AutoPrintMainController"
#define FORMAT_DATALISTHEADER "{\"field\":\"%s\",\"caption\":\"%s\"}"
#define FORMAT_DATALIST "\"%s\""
#define FORMAT_OPTIONHEADER "{\"label\":\"%s\"}"
#define FORMAT_OPTION "\"%s\""
#define POINT_LIST "PointList"
// ビュー側に渡す一覧データのカラム数
#define VIEW_COLUMN_NUM 7

class AutoPrintMainController : public BaseController, public DebugLogger, public ErrorController
{
public:
  // 自インスタンス
  AutoPrintMainController *instance;
  // コンストラクター
  AutoPrintMainController();
  // デストラクター
  ~AutoPrintMainController();
  // ログ出力関数設定
  void setLoggerCallback(void (*logger)(LoggerArgument));
  // ログ出力関数設定
  void setErrorCallback(void (*error)(ErrorArgument));
  // CSVファイル読み込み完了
  void loadCsvComplete(
    // ロードデータ
    char *,
    // CSVファイルロードコンポーネント
    CsvLoader
  );
  // データリストView出力
  void dataListInitialize(
    // データ名称
    std::string
  );
  // 初期処理
  void initialize(const char *path);
  // 終了処理
  void finalize();
  // ロードデータ情報テーブルレコード検索
  size_t serachLoadDataListRecord(
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
  // データテーブル詳細データ取得.
  char *getLoadDataDetail(
    // データ名称
    std::string,
    // レコードID
	size_t
  );
private:
  // メインモデルのインスタンス
  MainModel * _mainModel;
  // ロードデータ情報テーブル
  VectorLoadDataList _loadDataList;
  // CSVファイルロード開始
  void loadCsv(
    // データ名称
    const char *,
    // ファイルパス
    const char *,
    // View表示コールバック
    VIEWPUTCALLBACK
  );
};
