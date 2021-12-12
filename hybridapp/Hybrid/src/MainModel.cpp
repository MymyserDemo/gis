/** *******************************************************
 * ハイブリッド側メインメインモデル.
 ******************************************************* */
#include "MainModel.h"

using std::ostringstream;
using std::string;
using std::to_string;
using std::stod;
using std::stoi;

/**
 * コンストラクタ.
 */
MainModel::MainModel() {
}

/**
 * デストラクタ.
 */
MainModel::~MainModel() {
}

/**
 * 初期処理.
 */
void MainModel::initialize() {
  logger(MAIN_MODEL_CLASSNAME, (const char *)__func__, "");
}

/**
 * 終了処理.
 */
void MainModel::finalize() {
  logger(MAIN_MODEL_CLASSNAME, (const char *)__func__, "");
}

/**
 * CSVファイル読み込み完了.
 * @param loadDataList ロードデータ情報
 * @param data ロードデータ
 * @return 成否
 */
bool MainModel::loadCsvComplete(
  LoadDataList *loadDataList,
  char *data
) {
  char *rowPointerTop;
  char *rowPointerBtm;
  char *columnPointerTop;
  char *columnPointerBtm;
  char *columnString;
  size_t strLength;
  size_t delimiterRow = strlen(CRLF);
  size_t delimiterColumn = strlen(COMMA_STRING);
  RowData *rowData;

  logger(MAIN_MODEL_CLASSNAME, (const char *)__func__, "");
  // 引数のチェック
  if(loadDataList == nullptr || data == nullptr) {
    setErrorCode(MAIN_MODEL_CLASSNAME, ERRORCODE001);
    return false;
  }
  rowPointerTop = data;
  bool headFlag = true;
  // 行を分割するループ
  while(*rowPointerTop != 0) {
   // 改行コードで分割
    rowPointerBtm = strstr(rowPointerTop, CRLF);
    if(rowPointerBtm == nullptr) {
      break;
    }
    *rowPointerBtm = 0;
    rowData = new RowData();
    columnPointerTop = rowPointerTop;
    // 列を分割するループ
    while(*columnPointerTop != 0) {
      if(*columnPointerTop == COMMA_CODE) {
        // データが入っていない列
        columnPointerBtm = columnPointerTop;
        columnString = new char[1]();
        columnString[0] = 0;
      } else {
        // コンマで分割
        columnPointerBtm = strstr(columnPointerTop, COMMA_STRING);
        if(columnPointerBtm == nullptr) {
          // 最後の列
          strLength = strlen(columnPointerTop);
        } else {
          strLength = columnPointerBtm - columnPointerTop;
        }
        // 列のデータを新しい文字列に複製
        columnString = new char[strLength + 1]();
		hybridStrncopy(columnString, strLength + 1, columnPointerTop, strLength);
        columnString[strLength] = 0;
      }
      // 配列にカラムを追加
      rowData->column.push_back(columnString);
      // 末尾か確認
      if((columnPointerTop + strLength + 1) >= rowPointerBtm) {
        break;
      }
      columnPointerTop = columnPointerBtm + delimiterColumn;
    }
    // 配列に行を追加
    if(headFlag) {
      headFlag = false;
      loadDataList->setHeader(rowData);
    } else {
      loadDataList->rowData.push_back(*rowData);
    }
    rowPointerTop = rowPointerBtm + delimiterRow;
  }
  return true;
}

/**
 * ロードデータ情報テーブル検索.
 * @param loadDataList ロードデータ情報テーブル
 * @param dataName データ名称
 * @return 検索結果
 */
LoadDataList MainModel::serachLoadDataList(
  const VectorLoadDataList &loadDataList,
  string dataName
) {
  logger(MAIN_MODEL_CLASSNAME, (const char *)__func__, "");
  for(LoadDataList x : loadDataList) {
    if(dataName == x.getDataName()) {
      return x;
    }
  }
  setErrorCode(MAIN_MODEL_CLASSNAME, ERRORCODE002);
  LoadDataList noData;
  noData.setError(false);
  return noData;
}

/**
 * ロードデータ情報テーブルレコード検索.
 * @param loadDataList ロードデータ情報テーブル
 * @param dataName     データ名称
 * @param keyword      検索キーワード
 * @param start        検索開始位置
 * @param direction    検索方向
 * @param column       検索列
 * @return 検索結果
 */
size_t MainModel::serachLoadDataListRecord(
  const VectorLoadDataList &loadDataList,
  string dataName,
  string keyword,
  size_t start,
  bool direction,
  size_t column
) {
  logger(MAIN_MODEL_CLASSNAME, (const char *)__func__, "");
  if(dataName.empty()) {
    setErrorCode(MAIN_MODEL_CLASSNAME, ERRORCODE003);
    return -10;
  }
  if(keyword.empty()) {
    setErrorCode(MAIN_MODEL_CLASSNAME, ERRORCODE004);
    return -11;
  }
  LoadDataList data = serachLoadDataList(loadDataList, dataName);
  if(!data.getError()) {
    setErrorCode(MAIN_MODEL_CLASSNAME, ERRORCODE005);
    return -12;
  }
  size_t i = start;
  size_t num = data.rowData.size();
  size_t increment;
  if(direction) {
    increment = 1;
  }
  else {
    increment = -1;
  }
  while(i < num) {
    if(data.rowData[i].column[column].find(keyword) != string::npos) {
      return i;
    }
    i = i + increment;
  }
  return -13;
}

/**
 * 文字列書式設定.
 * @param data 置き換える文字列
 * @param dataFormat 変換書式
 * @param placeholder 置き換え元の文字列
 * @return 設定結果文字列
 */
string MainModel::formatting(string data, const char *dataFormat, string placeholder) {
  string result(dataFormat);
  string::size_type pos(result.find(placeholder));
  // 置き換える
  while(pos != string::npos) {
    result.replace(pos, placeholder.length(), data);
    pos = result.find( placeholder, pos + data.length());
  }
  return result;
}

/**
 * データテーブルヘッダー取得.
 * 取得する列数を指定できる
 * @param loadData ロードデータ情報
 * @param dataFormat データフォーマット
 * @param limit 取得する列数 0で全て
 * @return ヘッダー文字列
 */
char *MainModel::getLoadCsvHeader(
  LoadDataList &loadData,
  const char *dataFormat,
  size_t limit
) {
  ostringstream ostr;
  string placefolder(PLACEHOLDER_STRING);
  bool flag = true;

  logger(MAIN_MODEL_CLASSNAME, (const char *)__func__, "");
  ostr << LEFT_CURLY_BRACKET_STRING;
  ostr << DATASTRING << COLON << LEFT_SQUARE_BRACKET;
  // 列のループ
  size_t num = loadData.getHeader()->column.size();
  if(num > limit && limit > 0) {
    num = limit;
  }
  for(size_t i = 0; i < num; i++) {
    // 分割
    string result = formatting(loadData.getHeader()->column[i], dataFormat, placefolder);
    if(flag) {
      flag = false;
    } else {
      ostr << COMMA_STRING;
    }
    ostr << result;
  }
  ostr << RIGHT_SQUARE_BRACKET;
  ostr << RIGHT_CURLY_BRACKET_STRING;
  size_t length = ostr.str().size() + 1;
  char *result = new char[length]();
  hybridStrncopy(result, length, (char *)ostr.str().c_str(), ostr.str().size());
  return result;
}

/**
 * データテーブル行データ取得.
 * @param loadData ロードデータ情報
 * @param dataFormat データフォーマット
 * @param limit 取得する列数 0で全て
 * @return 全行文字列
 */
char *MainModel::getLoadCsvData(
  LoadDataList &loadData,
  const char *dataFormat,
  size_t limit
) {
  ostringstream ostr;
  string placeholder(PLACEHOLDER_STRING);

  logger(MAIN_MODEL_CLASSNAME, (const char *)__func__, "");
  ostr << LEFT_SQUARE_BRACKET;
  bool flag1 = true;
  // 行数のループ
  size_t rnum = loadData.rowData.size();
  for(size_t i = 0; i < rnum; i++) {
    if(flag1) {
      flag1 = false;
    } else {
      ostr << COMMA_STRING;
    }
    ostr << LEFT_CURLY_BRACKET_STRING;
    // レコードID設定
    ostr << "\"recid\": " << to_string(i) << ",";
    bool flag2 = true;
    // 列数のループ
	size_t cnum = loadData.rowData[i].column.size();
    if(cnum > limit && limit > 0) {
      cnum = limit;
    }
    for(size_t j = 0; j < cnum; j++) {
      string result = formatting(loadData.rowData[i].column[j], dataFormat, placeholder);
      if(flag2) {
        flag2 = false;
      } else {
        ostr << COMMA_STRING;
      }
      // 列指定
      ostr << "\"" << loadData.getHeader()->column[j] << "\"" << COLON << result;
    }
    ostr << RIGHT_CURLY_BRACKET_STRING;
  }
  ostr << RIGHT_SQUARE_BRACKET;
  size_t length = ostr.str().size() + 1;
  char *result = new char[length]();
  hybridStrncopy(result, length, (char *)ostr.str().c_str(), ostr.str().size());
  return result;
}

/**
 * ポイントデータ設定.
 * @param loadData ロードデータ情報
 * @param pointData ポイントデータ
 */
void MainModel::setPointData(
  LoadDataList &loadData,
  MapPoint &pointData
) {
  logger(MAIN_MODEL_CLASSNAME, (const char *)__func__, "");
  // 行数のループ
  size_t rnum = loadData.rowData.size();
  for(size_t i = 0; i < rnum; i++) {
    // 列数のループ
	  size_t cnum = loadData.rowData[i].column.size();
    if(cnum < 2)
    {
      setErrorCode(MAIN_MODEL_CLASSNAME, ERRORCODE006);
      return;
    }
    pointData.id.push_back(i);
    pointData.name.push_back(loadData.rowData[i].column[0]);
    pointData.x.push_back(std::stod(loadData.rowData[i].column[1]));
    pointData.y.push_back(std::stod(loadData.rowData[i].column[2]));
    if(cnum < 4) {
      // 回転角のないデータ
      pointData.rotation.push_back(0);
    }
    else {
      // 回転角のあるデータ
      pointData.rotation.push_back(std::stod(loadData.rowData[i].column[3]));
    }
  }
}

/**
 * ラインデータ設定.
 * @param loadData ロードデータ情報
 * @param pointData ラインデータ
 */
void MainModel::setLineData(
  LoadDataList &loadData,
  MapLine &lineData
) {
  logger(MAIN_MODEL_CLASSNAME, (const char *)__func__, "");
  // 行数のループ
  size_t rnum = loadData.rowData.size();
  for(size_t i = 0; i < rnum; i++) {
    // 列数のループ
	size_t cnum = loadData.rowData[i].column.size();
    if(cnum < 9) {
      setErrorCode(MAIN_MODEL_CLASSNAME, ERRORCODE007);
      return;
    }
    lineData.x1.push_back(stod(loadData.rowData[i].column[1]));
    lineData.y1.push_back(stod(loadData.rowData[i].column[2]));
    lineData.x2.push_back(stod(loadData.rowData[i].column[4]));
    lineData.y2.push_back(stod(loadData.rowData[i].column[5]));
    lineData.lineColor.push_back(loadData.rowData[i].column[6]);
    lineData.lineWidth.push_back(stod(loadData.rowData[i].column[7]));
    lineData.layerNo.push_back(stoi(loadData.rowData[i].column[8]));
  }
}

/**
 * ポイント情報取得.
 * @param pointData ポイントデータリスト
 * @return 全点文字列
 */
char *MainModel::getPointData(MapPoint &pointData) {
  ostringstream ostr;
  bool flag = true;

  logger(MAIN_MODEL_CLASSNAME, (const char *)__func__, "");
  ostr << LEFT_CURLY_BRACKET_STRING;
  ostr << DATASTRING << COLON << LEFT_SQUARE_BRACKET;
  // 点数のループ
  size_t num = pointData.x.size();
  for(size_t i = 0; i < num; i++) {
    if(flag) {
      flag = false;
    } else {
      ostr << COMMA_STRING;
    }
    ostr << LEFT_CURLY_BRACKET_STRING;
    ostr << "\"x\":" << std::to_string(pointData.x[i]);
    ostr << ",\"y\":" << std::to_string(pointData.y[i]);
    ostr << ",\"name\":\"" << pointData.name[i] << "\"";
    ostr << ",\"rotation\":" << std::to_string(pointData.rotation[i]);
    ostr << RIGHT_CURLY_BRACKET_STRING;
  }
  ostr << RIGHT_SQUARE_BRACKET;
  ostr << RIGHT_CURLY_BRACKET_STRING;
  size_t length = ostr.str().size() + 1;
  char *result = new char[length]();
  hybridStrncopy(result, length, (char *)ostr.str().c_str(), ostr.str().size());
  return result;
}

/**
 * ライン情報取得.
 * @param lineData ラインデータリスト
 * @return 全線文字列
 */
char *MainModel::getLineData(MapLine &lineData) {
  ostringstream ostr;
  bool flag = true;

  logger(MAIN_MODEL_CLASSNAME, (const char *)__func__, "");
  ostr << LEFT_CURLY_BRACKET_STRING;
  ostr << DATASTRING << COLON << LEFT_SQUARE_BRACKET;
  // ライン数のループ
  size_t num = lineData.x1.size();
  for(size_t i = 0; i < num; i++) {
    if(flag) {
      flag = false;
    } else {
      ostr << COMMA_STRING;
    }
    ostr << LEFT_CURLY_BRACKET_STRING;
    ostr << "\"x1\":" << to_string(lineData.x1[i]) << ",\"y1\":" << to_string(lineData.y1[i]) << COMMA_STRING;
    ostr << "\"x2\":" << to_string(lineData.x2[i]) << ",\"y2\":" << to_string(lineData.y2[i]) << COMMA_STRING;
    ostr << "\"lineColor\":\"" << lineData.lineColor[i] << "\"" << COMMA_STRING;
    ostr << "\"lineWidth\":" << std::to_string(lineData.lineWidth[i]) << COMMA_STRING;
    ostr << "\"layerNo\":" << std::to_string(lineData.layerNo[i]);
    ostr << RIGHT_CURLY_BRACKET_STRING;
  }
  ostr << RIGHT_SQUARE_BRACKET;
  ostr << RIGHT_CURLY_BRACKET_STRING;
  size_t length = ostr.str().size() + 1;
  char *result = new char[length]();
  hybridStrncopy(result, length, (char *)ostr.str().c_str(), ostr.str().size());
  return result;
}

/**
 * データテーブル詳細データ取得.
 * @param loadData ロードデータ情報
 * @param recId レコードID
 * @return レコード全項目文字列
 */
char *MainModel::getLoadDataDetail(
  LoadDataList &loadData,
  size_t recId
) {
  ostringstream ostr;

  logger(MAIN_MODEL_CLASSNAME, (const char *)__func__, "");
  // 列数のループ
  size_t cnum = loadData.rowData[recId].column.size();
  bool flag2 = true;
  for(size_t j = 0; j < cnum; j++) {
    if(flag2) {
      flag2 = false;
    } else {
      ostr << COMMA_STRING;
    }
    // 列指定
    ostr << loadData.getHeader()->column[j] << COMMA_STRING;
    ostr << loadData.rowData[recId].column[j];
  }
  size_t length = ostr.str().size() + 1;
  char *result = new char[length]();
  hybridStrncopy(result, length, (char *)ostr.str().c_str(), ostr.str().size());
  return result;
}

/**
 * 文字列のコピー.
 * 2017/04/01現在strncpy_sがAndroid NDKのライブラリに存在しないため独自に実装します.
 * @param d コピー先
 * @param dlen コピー先領域サイズ
 * @param s コピー元
 * @para, slen コピー元領域サイズ
 */
void MainModel::hybridStrncopy(char *d, size_t dlen, char *s, size_t slen) {
  for (size_t i = 0; i < dlen; i++) {
    if (i >= slen) {
      break;
    }
    d[i] = s[i];
  }
}
