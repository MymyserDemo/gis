/** *******************************************************
 * ロードデータ一覧.
 ******************************************************* */
#pragma once

#include <vector>
#include <string>
#include "RowData.h"

class LoadDataList {
public:
  // 行データ
  VectorRowData rowData;
  // コンストラクタ
  LoadDataList();
  // デストラクタ
  ~LoadDataList();
  // 初期処理
  void initialize();
  // 終了処理
  void finalize();
  // データ名称設定
  void setDataName(const char *);
  // データ名称取得
  std::string getDataName();
  // ヘッダー設定
  void setHeader(RowData *);
  // ヘッダー取得
  RowData *getHeader();
  // エラー情報設定
  void setError(bool);
  // エラー情報取得
  bool getError();
private:
  // データ名称
  std::string _dataName;
  // ヘッダーデータ
  RowData * _header;
  // エラー状態
  bool _error;
};
using VectorLoadDataList = std::vector<LoadDataList>;
