/** *******************************************************
 * レイヤ管理コンポーネント.
 ******************************************************* */
#include "LayerManager.h"

using std::string;
using std::bind;
using std::ref;

/**
 * コンストラクタ.
 * @param mainModel メインモデルインスタンス
 */
LayerManager::LayerManager(MainModel *mainModel) {
  _mainModel = mainModel;
}

/**
 * デストラクタ.
 */
LayerManager::~LayerManager() {
}

/**
 * 初期処理.
 */
void LayerManager::initialize() {
  logger(LAYER_MANAGER_CLASSNAME, (const char *)__func__, "");
}

/**
 * 終了処理.
 */
void LayerManager::finalize() {
  // マップデータを破棄
  size_t num = mapData.size();
  for(size_t i = 0; i < num; i++) {
    mapData[i].finalize();
  }
  mapData.clear();
  mapData.shrink_to_fit();
  logger(LAYER_MANAGER_CLASSNAME, (const char *)__func__, "");
}

/**
 * レイヤ情報設定.
 * @param rowData マップデータ
 */
void LayerManager::setLayer(char *rowData) {
  std::string err;
  logger(LAYER_MANAGER_CLASSNAME, (const char *)__func__, "");
  // 引数チェック
  if(rowData == nullptr) {
    setErrorCode(LAYER_MANAGER_CLASSNAME, ERRORCODE001);
    return;
  }
  // レイヤー数のループ
  auto jsonRowData = json11::Json::parse(rowData, err);
  for (auto &k : jsonRowData.array_items()) {
    if(k == nullptr || k[LAYER_MANAGER_LAYERNAME].string_value().empty()) {
      break;
    }
    // レイヤ情報作成
    MapData *map = new MapData();
    map->setLayerName(k[LAYER_MANAGER_LAYERNAME].string_value());
    map->setOnDisplay(k[LAYER_MANAGER_ONDISPLAY].string_value());
    map->setLayerType(k[LAYER_MANAGER_LAYERTYPE].string_value());
    map->setFileName (k[LAYER_MANAGER_FILENAME].string_value());
    mapData.push_back(*map);
  }
  // 地図データ読み込み
  _mapDataLoad();
}

/**
 * ポイントリストレイヤ情報設定.
 * @param layerName レイヤ名称
 * @param rowData マップデータ
 */
void LayerManager::pointListSetLayer(const char *layerName, char *rowData) {
  std::string err;
  logger(LAYER_MANAGER_CLASSNAME, (const char *)__func__, "");
  // 引数チェック
  if(layerName == nullptr || rowData == nullptr) {
    setErrorCode(LAYER_MANAGER_CLASSNAME, ERRORCODE002);
    return;
  }
  // レイヤ情報作成
  MapData *map = new MapData();
  map->setLayerName(layerName);
  map->setOnDisplay(TRUE_STRING);
  map->setLayerType(CSVPOINT);
  map->setFileName(NOTHING);
  auto jsonRowData = json11::Json::parse(rowData, err);
  // データ件数のループ
  for (auto &k : jsonRowData.array_items()) {
    if(k == nullptr) {
      break;
    }
    // 座標の登録
    map->pointData.x.push_back(stof(k["x"].string_value()));
    map->pointData.y.push_back(stof(k["y"].string_value()));
  }
  // マップデータコンポーネントに登録
  mapData.push_back(*map);
}

/**
 * 地図データ読み込み.
 */
void LayerManager::_mapDataLoad() {
  logger(LAYER_MANAGER_CLASSNAME, (const char *)__func__, "");
  // ロード完了時コールバック宣言
  CSVLOADERCALLBACK csvLoaderCallback = bind(&LayerManager::_mapDataLoadComplete, ref(instance), std::placeholders::_1, std::placeholders::_2);
  VIEWPUTCALLBACK viewPutCallback = bind(&LayerManager::_mapDataInitialize, ref(instance), std::placeholders::_1);
  // レイヤー数のループ
  size_t num = mapData.size();
  for(size_t i = 0; i < num; i++) {
    logger(LAYER_MANAGER_CLASSNAME, (const char *)__func__, mapData[i].getFileName().c_str());
    // データファイルの無いレイヤー
    if(mapData[i].getFileName() == NOTHING) {
      continue;
    }
    // CSV形式の点・線データファイル
    else if(mapData[i].getLayerType() == CSVPOINT || mapData[i].getLayerType() == CSVLINE) {
      // c_strを使う時は一旦新規に確保した変数にいれなければならない
      string *layerNameS = new string();
      *layerNameS = mapData[i].getLayerName();
      string *fileNameS = new string();
      *fileNameS = mapData[i].getFileName();
      // アプリ側CSVローダーコンポーネント作成
      CsvLoader *csvLoader = new CsvLoader(
        layerNameS->c_str(),
        fileNameS->c_str(),
        csvLoaderCallback,
        viewPutCallback
      );
      csvLoader->setInstance(csvLoader);
      // ロード開始
      csvLoader->bridgingLoadCsv();
    }
    // GeoJson形式のデータファイル
    else if(mapData[i].getLayerType() == GEOJSON) {
      // Geojson
      string *geoJsonFIle = new string();
      *geoJsonFIle = mapData[i].getFileName();
      bridgingPutGeoJson(geoJsonFIle->c_str(), i);
    }
    // 対象外のデータファイル
    else {
      setErrorCode(LAYER_MANAGER_CLASSNAME, ERRORCODE003);
    }
  }
}

/**
 * マップデータファイル読み込み完了.
 * @param data ロードデータ
 * @param loader ロードデータ情報
 */
void LayerManager::_mapDataLoadComplete(char *data, CsvLoader loader) {
  logger(LAYER_MANAGER_CLASSNAME, (const char *)__func__, "");
  // 引数チェック
  if(data == nullptr) {
    setErrorCode(LAYER_MANAGER_CLASSNAME, ERRORCODE004);
    return;
  }
  // ロードデータ情報テーブル追加
  LoadDataList loadData;
  loadData.setDataName(loader.getDataName());
  // ロードデータ変換
  bool rc = _mainModel->loadCsvComplete(&loadData, data);
  if(!rc) {
    setErrorCode(LAYER_MANAGER_CLASSNAME, ERRORCODE005);
    return;
  }
  string layerName(loader.getDataName());
  size_t num = mapData.size();
  size_t i = 0;
  for(; i < num; i++) {
    // 対象のレイヤを検索
    if(mapData[i].getLayerName() != layerName) {
      continue;
    }
    break;
  }
  if(num == i) {
    // レイヤが見つからない
    setErrorCode(LAYER_MANAGER_CLASSNAME, ERRORCODE006);
    return;
  }
  // レイヤの種別を取得
  string layerType = mapData[i].getLayerType();
  if(layerType == CSVPOINT) {
    // ポイント情報設定
    _mainModel->setPointData(loadData, mapData[i].pointData);
  }
  else if(layerType == CSVLINE) {
    // ライン情報設定
    _mainModel->setLineData(loadData, mapData[i].lineData);
  }
  else {
    // 種別が見つからない
    setErrorCode(LAYER_MANAGER_CLASSNAME, ERRORCODE007);
    return;
  }
  // Viewへ出力
  loader.viewPutCallback(loader.getDataName());
}

/**
 * マップデータView出力.
 * @param layerName レイヤ名称
 */
void LayerManager::_mapDataInitialize(string layerName) {
  logger(LAYER_MANAGER_CLASSNAME, (const char *)__func__, "");
  size_t num = mapData.size();
  size_t i = 0;
  for(; i < num; i++) {
    // 対象のレイヤを検索
    if(mapData[i].getLayerName() != layerName) {
      continue;
    }
    break;
  }
  char *data = NULL;
  // レイヤの種別を取得
  string layerType = mapData[i].getLayerType();
  if(layerType == CSVPOINT) {
    // ポイント情報取得
    data = _mainModel->getPointData(mapData[i].pointData);
    // ポイント表示
    bridgingPutPoint(data, i);
    delete data;
  }
  else if(layerType == CSVLINE) {
    // ライン情報取得
    data = _mainModel->getLineData(mapData[i].lineData);
    // ライン表示
    bridgingPutLine(data, i);
    delete data;
  }
  else {
    // 種別が見つからない
    setErrorCode(LAYER_MANAGER_CLASSNAME, ERRORCODE008);
  }
}
