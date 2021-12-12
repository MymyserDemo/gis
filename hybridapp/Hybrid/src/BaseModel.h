#pragma once

#include "BaseClass.h"

/**
 * 基本モデルクラス.
 * 全てのモデルクラスの継承元となるクラスです.
 */
class BaseModel : public BaseClass
{
public:
  // コンストラクター
  BaseModel();
  // デストラクター
  virtual ~BaseModel();
};
