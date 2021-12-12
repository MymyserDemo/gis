#pragma once

#include <typeinfo>
#include <string.h>
#include "BaseClass.h"
#include "HybridInterface.h"

/**
* デバッグログクラス.
* アプリ側のテキスト出力関数をハイブリッド側のデバッグ出力機能に登録するクラスです.
*/
class DebugLogger : public BaseClass
{
public:
  // コンストラクター
  DebugLogger();
  // デストラクター
  ~DebugLogger();
  // デバッグ出力関数をハイブリッド側に登録する
  void setLogger(void (*logger)(LoggerArgument));
  // ハイブリッド側から呼ばれるのログ出力関数
  void logger(const char *className, const char *functionName, const char *message);
protected:
  // アプリ側のログ出力関数
  void (*_pLogger)(LoggerArgument);
};
