/** *******************************************************
 * 行データ.
 ******************************************************* */
#pragma once

#include <cstdint>
#include <vector>
#include <string>

class RowData {
public:
  // コンストラクタ
  RowData();
  // デストラクタ
  ~RowData();
  // 初期処理
  void initialize();
  // 終了処理
  void finalize();
  // 列データ
  std::vector<std::string> column;
};
using VectorRowData = std::vector<RowData>;
