#pragma once

#include <iostream>
#include <string>
#include "HybridInterface.h"

#define MAIN_VIEW_CLASSNAME "MainView"

/**
 * メインビュー.
 */
class MainView {
public:
  // コンストラクタ
  MainView();
  // デストラクタ
  ~MainView();
  // 初期処理
  void initialize();
  // 終了処理
  void finalize();
  // ログ画面出力
  void viewLogOutput(LoggerArgument);
  // エラー画面出力
  void viewErrorOutput(ErrorArgument);
  // キーボード入力
  char viewInput();
};
