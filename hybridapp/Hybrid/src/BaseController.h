#pragma once

#include "BaseClass.h"

/**
 * 基本コントローラークラス.
 * 全てのコントローラークラスの継承元となるクラスです.
 */
class BaseController : public BaseClass
{
public:
  // コンストラクター
  BaseController();
  // デストラクター
  virtual ~BaseController();
};
