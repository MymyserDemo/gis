/** *******************************************************
 * マップデータコンポーネント.
 ******************************************************* */
#pragma once

#include <string>
#include <vector>

/**
 * 点データ.
 */
class MapPoint {
public:
  std::vector<size_t> id;
  std::vector<std::string> name;
  std::vector<double> x;
  std::vector<double> y;
  std::vector<double> rotation;
};

/**
 * 線データ.
 */
class MapLine {
public:
  std::vector<size_t> id;
  std::vector<double> x1;
  std::vector<double> y1;
  std::vector<double> x2;
  std::vector<double> y2;
  std::vector<std::string> lineColor;
  std::vector<double> lineWidth;
  std::vector<size_t> layerNo;
};

/**
 * マップデータコンポーネント.
 */
class MapData {
private:
  // レイヤー名
  std::string _layerName;
  // 画面表示
  std::string _onDisplay;
  // レイヤータイプ
  std::string _layerType;
  // データファイル名
  std::string _fileName;
public:
  // 点データ
  MapPoint pointData;
  // 線データ
  MapLine lineData;
  // レイヤー名
  void setLayerName(std::string layerName) { _layerName = layerName; };
  std::string getLayerName() { return _layerName; };
  // 画面表示
  void setOnDisplay(std::string onDisplay) { _onDisplay = onDisplay; };
  std::string getOnDisplay() { return _onDisplay; };
  // レイヤータイプ
  void setLayerType(std::string layerType) { _layerType = layerType; };
  std::string getLayerType() { return _layerType; };
  // データファイル名
  void setFileName(std::string fileName) { _fileName = fileName; };
  std::string getFileName() { return _fileName; };
  // 初期処理
  void initialize() {
  };
  // 終了処理
  void finalize() {
    // 点マップデータを破棄
    pointData.id.clear();
    pointData.id.shrink_to_fit();
    pointData.x.clear();
    pointData.x.shrink_to_fit();
    pointData.y.clear();
    pointData.y.shrink_to_fit();
    // 線マップデータを破棄
    lineData.id.clear();
    lineData.id.shrink_to_fit();
    lineData.x1.clear();
    lineData.y1.shrink_to_fit();
    lineData.x2.clear();
    lineData.y2.shrink_to_fit();
    lineData.lineColor.clear();
    lineData.lineColor.shrink_to_fit();
    lineData.lineWidth.clear();
    lineData.lineWidth.shrink_to_fit();
    lineData.layerNo.clear();
    lineData.layerNo.shrink_to_fit();
  };
};
