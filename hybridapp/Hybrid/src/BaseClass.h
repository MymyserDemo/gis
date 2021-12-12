#pragma once

/**
 * 基本クラス.
 * 全てのクラスの継承元となるクラスです.
 */
class BaseClass
{
public:
  // コンストラクター
  BaseClass();
  // デストラクター
  virtual ~BaseClass();
  // 初期処理
  virtual void initialize();
  // 終了処理
  virtual void finalize();
};
