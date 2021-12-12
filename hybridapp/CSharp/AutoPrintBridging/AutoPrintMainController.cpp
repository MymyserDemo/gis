/** *******************************************************
 * ハイブリッド側メインコントローラー.
 ******************************************************* */
#include "AutoPrintMainController.h"

using std::string;
using std::bind;
using std::ref;

/**
 * コンストラクタ.
 */
AutoPrintMainController::AutoPrintMainController() {
  instance = nullptr;
  // メインモデルクラス作成
  _mainModel = new MainModel();
}

/**
 * デストラクタ.
 */
AutoPrintMainController::~AutoPrintMainController() {
}

/**
 * ログ出力関数設定.
 * @param pLogger アプリ側ログ出力関数
 */
void AutoPrintMainController::setLoggerCallback(void (*pLogger)(LoggerArgument)) {
  // 自クラス
  setLogger(pLogger);
  // メインモデル
  if(_mainModel == nullptr) {
	setErrorCode(MAIN_CONTROLLER_CLASSNAME, ERRORCODE001);
    return;
  }
  _mainModel->setLogger(pLogger);
}

/**
 * エラー出力関数設定.
 * @param pError アプリ側エラー出力関数
 */
void AutoPrintMainController::setErrorCallback(void (*pError)(ErrorArgument)) {
  // 自クラス
  setError(pError);
  // メインモデル
  if (_mainModel == nullptr) {
    setErrorCode(MAIN_CONTROLLER_CLASSNAME, ERRORCODE003);
    return;
  }
  _mainModel->setError(pError);
}

/**
 * 終了処理.
 */
void AutoPrintMainController::finalize() {
  // メインモデル終了処理
  if(_mainModel == nullptr) {
    setErrorCode(MAIN_CONTROLLER_CLASSNAME, ERRORCODE006);
  }
  else {
    // メインモデル削除
    _mainModel->finalize();
    delete _mainModel;
    _mainModel = nullptr;
  }
  // ロードデータ情報テーブル破棄
  size_t num = _loadDataList.size();
  for (size_t i = 0; i < num; i++) {
    _loadDataList[i].finalize();
  }
  _loadDataList.clear();
  _loadDataList.shrink_to_fit();
  logger(MAIN_CONTROLLER_CLASSNAME, (const char *)__func__,  "");
}

/**
 * 初期処理.
 */
void AutoPrintMainController::initialize(const char *path) {
  logger(MAIN_CONTROLLER_CLASSNAME, (const char *)__func__, path);
  if (instance == nullptr) {
	  setErrorCode(MAIN_CONTROLLER_CLASSNAME, ERRORCODE008);
    return;
  }
  // メインモデル初期処理
  _mainModel->initialize();
  // ポイントリストロード開始
  loadCsv(POINT_LIST,
	  path,
	  bind(
		  &AutoPrintMainController::dataListInitialize,
		  ref(instance), std::placeholders::_1
	  )
  );
}

/**
 * ファイルロード開始.
 * @param dataName ロードデータ名称
 * @param fileName ファイルパス
 * @param viewPutCallback View表示コールバック
 */
void AutoPrintMainController::loadCsv(
  const char *dataName,
  const char *fileName,
  VIEWPUTCALLBACK viewPutCallback
) {
  logger(MAIN_CONTROLLER_CLASSNAME, (const char *)__func__, "");
  if(dataName == nullptr) {
    setErrorCode(MAIN_CONTROLLER_CLASSNAME, ERRORCODE009);
    return;
  }
  if(fileName == nullptr) {
    setErrorCode(MAIN_CONTROLLER_CLASSNAME, ERRORCODE00A);
    return;
  }
  if (instance == nullptr) {
    setErrorCode(MAIN_CONTROLLER_CLASSNAME, ERRORCODE00B);
    return;
  }
  // ロード完了時コールバック宣言
  CSVLOADERCALLBACK csvLoaderCallback = bind(&AutoPrintMainController::loadCsvComplete, ref(instance), std::placeholders::_1, std::placeholders::_2);
  // アプリ側ローダーコンポーネント作成
  CsvLoader *loader;
  loader = new CsvLoader((char *)dataName, fileName, csvLoaderCallback, viewPutCallback);
  loader->setInstance(loader);
  // ロード開始
  loader->bridgingLoadCsv();
}

/**
 * CSVファイル読み込み完了.
 * @param data ロードデータ
 * @param loader ロードデータ情報
 */
void AutoPrintMainController::loadCsvComplete(
  char *data,
  CsvLoader loader
) {
  logger(MAIN_CONTROLLER_CLASSNAME, (const char *)__func__, "");
  // エラーチェック
  if(_mainModel == nullptr) {
    setErrorCode(MAIN_CONTROLLER_CLASSNAME, ERRORCODE00C);
    return;
  }
  if(data == nullptr) {
    setErrorCode(MAIN_CONTROLLER_CLASSNAME, ERRORCODE00D);
    return;
  }
  // ロードデータ情報テーブル追加
  LoadDataList loadData;
  loadData.setDataName(loader.getDataName());
  // ロードデータ変換
  bool rc = _mainModel->loadCsvComplete(&loadData, data);
  if(!rc) {
    setErrorCode(MAIN_CONTROLLER_CLASSNAME, ERRORCODE00E);
  }
  // リストに保管する
  _loadDataList.push_back(loadData);
  // Viewへ出力
  loader.viewPutCallback(loader.getDataName());
}

/**
* データリストView出力.
* @param dataName ロードデータ名称
*/
void AutoPrintMainController::dataListInitialize(string dataName) {
	logger(MAIN_CONTROLLER_CLASSNAME, (const char *)__func__, "");
	// ロードデータ情報テーブル検索
	LoadDataList loadData = _mainModel->serachLoadDataList(_loadDataList, dataName);
	if (loadData.getDataName() == "") {
		setErrorCode(MAIN_CONTROLLER_CLASSNAME, ERRORCODE00F);
		return;
	}
	// タイトル行取得
	char *titleRow = _mainModel->getLoadCsvHeader(loadData, FORMAT_DATALISTHEADER, VIEW_COLUMN_NUM);
	// ポイントリストヘッダー表示
	bridgingDataListAddHeader(titleRow);
	delete titleRow;
	// 行データ取得
	char *rowData = _mainModel->getLoadCsvData(loadData, FORMAT_DATALIST, VIEW_COLUMN_NUM);
	// ポイントリストデータ表示
	bridgingDataListAddData(rowData);
	delete rowData;
}

/**
 * ロードデータ情報テーブルレコード検索.
 * @param dataName     データ名称
 * @param keyword      検索キーワード
 * @param start        検索開始位置
 * @param direction    検索方向
 * @param column       検索列
 */
size_t AutoPrintMainController::serachLoadDataListRecord(
  std::string dataName,
  std::string keyword,
  size_t start,
  bool direction,
  size_t column
) {
  logger(MAIN_CONTROLLER_CLASSNAME, (const char *)__func__, "");
  // エラーチェック
  if(_mainModel == nullptr) {
    setErrorCode(MAIN_CONTROLLER_CLASSNAME, ERRORCODE013);
    return -1;
  }
  return _mainModel->serachLoadDataListRecord(
    _loadDataList,
    dataName,
    keyword,
    start,
    direction,
    column
  );
}

/**
 * データテーブル詳細データ取得.
 * @param dataName     データ名称
 * @param recId レコードID
 */
char *AutoPrintMainController::getLoadDataDetail(
  // データ名称
  string dataName,
  // レコードID
  size_t recId
) {
  logger(MAIN_CONTROLLER_CLASSNAME, (const char *)__func__, "");
  // ロードデータ情報テーブル検索
  LoadDataList loadData = _mainModel->serachLoadDataList(_loadDataList, dataName);
  if(loadData.getDataName() == "") {
    setErrorCode(MAIN_CONTROLLER_CLASSNAME, ERRORCODE014);
    return (char *)"";
  }
  // エラーチェック
  if(_mainModel == nullptr) {
    setErrorCode(MAIN_CONTROLLER_CLASSNAME, ERRORCODE015);
    return (char *)"";
  }
  return _mainModel->getLoadDataDetail(loadData, recId);
}
