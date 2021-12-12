/** *******************************************************
 * ロードデータ一覧.
 ******************************************************* */
#include "LoadDataList.h"

/**
 * コンストラクタ.
 */
LoadDataList::LoadDataList() {
  _dataName = {0};
  _error = true;
}

/**
 * デストラクタ.
 */
LoadDataList::~LoadDataList() {
}

/**
 * 初期処理.
 */
void LoadDataList::initialize() {
}

/**
 * 終了処理.
 */
void LoadDataList::finalize() {
  // ヘッダーを破棄
  if(_header != nullptr) {
    _header->column.clear();
    _header->column.shrink_to_fit();
    _header = nullptr;
  }
  // 行データ破棄
  size_t num = rowData.size();
  for(size_t i = 0; i < num; i++) {
    rowData[i].finalize();
  }
  rowData.clear();
  rowData.shrink_to_fit();
}

/**
 * エラー情報設定.
 */
void LoadDataList::setError(bool error) { _error = error; }

/**
 * エラー情報取得.
 */
bool LoadDataList::getError() { return _error; }

/**
 * データ名称設定.
 */
void LoadDataList::setDataName(const char *val) {
  std::string str(val);
  _dataName = str;
}

/**
 * データ名称取得.
 */
std::string LoadDataList::getDataName() {
  return _dataName;
}

/**
 * ヘッダー設定.
 */
void LoadDataList::setHeader(RowData *header) {
  _header = header;
}

/**
 * ヘッダー取得.
 */
RowData *LoadDataList::getHeader() {
  return _header;
}
