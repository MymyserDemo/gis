/** *******************************************************
 * 行データ.
 ******************************************************* */
#include "RowData.h"

/**
 * コンストラクタ.
 */
RowData::RowData() {
}

/**
 * デストラクタ.
 */
RowData::~RowData() {
}

/**
 * 初期処理.
 */
void RowData::initialize() {
}

/**
 * 終了処理.
 */
void RowData::finalize() {
  // データ破棄
  column.clear();
  column.shrink_to_fit();
}

