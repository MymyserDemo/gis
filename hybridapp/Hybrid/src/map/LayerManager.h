/** *******************************************************
 * レイヤ管理コンポーネント.
 ******************************************************* */
#pragma once

#include "HybridInterface.h"
#include "BaseController.h"
#include "ErrorController.h"
#include "DebugLogger.h"
#include "json11/json11.hpp"
#include "MainModel.h"
#include "MapData.h"
#include <string>
#include <vector>

#define LAYER_MANAGER_CLASSNAME "LayerManager"

#define LAYER_MANAGER_LAYERNAME "layerName"
#define LAYER_MANAGER_ONDISPLAY "onDisplay"
#define LAYER_MANAGER_LAYERTYPE "layerType"
#define LAYER_MANAGER_FILENAME  "fileName"

#define FORMAT_DATALIST "\"%s\""
#define FORMAT_POINT "%s"

#define NOTHING "NOTHING"
#define CSVPOINT "CSVPOINT"
#define CSVLINE "CSVLINE"
#define GEOJSON "GEOJSON"
#define TRUE_STRING "TRUE"

class LayerManager : public BaseController, public DebugLogger, public ErrorController {
public:
  // 自クラスインスタンス
  LayerManager *instance;
  // 地図データ
  std::vector<MapData> mapData;
  // コンストラクタ
  LayerManager(MainModel *);
  // デストラクタ
  ~LayerManager();
  // 初期処理
  void initialize();
  // 終了処理
  void finalize();
  // レイヤ情報設定
  void setLayer(
    // マップデータ
    char *
  );
  // ポイントリストレイヤ情報設定
  void pointListSetLayer(
    // レイヤ名称
    const char *,
    // マップデータ
    char *
  );
private:
  // メインモデルのインスタンス
  MainModel * _mainModel;
  // 地図データ読み込み
  void _mapDataLoad();
  // マップデータファイル読み込み完了
  void _mapDataLoadComplete(
  // ロードデータ
  char *,
    // ロードデータ情報
    CsvLoader
  );
  // マップデータView出力
  void _mapDataInitialize(
    // ロードデータ情報
    std::string
  );
};
