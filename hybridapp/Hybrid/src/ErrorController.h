#pragma once

#include "HybridInterface.h"

/**
 * エラー処理.
 */
class ErrorController
{
public:
  // エラー発生クラス名
  const char *className;
  // エラーコード
  unsigned char errorCode;
  // コンストラクター
  ErrorController();
  // デストラクター
  ~ErrorController();
  // 初期処理
  void initialize();
  // 終了処理
  void finalize();
  // エラー出力関数をハイブリッド側に登録する
  void setError(void(*errorOutput)(ErrorArgument));
  // アプリ側のエラー出力関数
  void(*_pErrorOutput)(ErrorArgument);
  // ハイブリッド側から呼ばれるのエラー出力関数
  void errorOutput();
  // エラーコード設定
  void setErrorCode(const char *classNm, unsigned char errorCd);
  // エラーコード
  static const unsigned char ERRORCODE001 = 0x01;
  static const unsigned char ERRORCODE002 = 0x02;
  static const unsigned char ERRORCODE003 = 0x03;
  static const unsigned char ERRORCODE004 = 0x04;
  static const unsigned char ERRORCODE005 = 0x05;
  static const unsigned char ERRORCODE006 = 0x06;
  static const unsigned char ERRORCODE007 = 0x07;
  static const unsigned char ERRORCODE008 = 0x08;
  static const unsigned char ERRORCODE009 = 0x09;
  static const unsigned char ERRORCODE00A = 0x0A;
  static const unsigned char ERRORCODE00B = 0x0B;
  static const unsigned char ERRORCODE00C = 0x0C;
  static const unsigned char ERRORCODE00D = 0x0D;
  static const unsigned char ERRORCODE00E = 0x0E;
  static const unsigned char ERRORCODE00F = 0x0F;
  static const unsigned char ERRORCODE010 = 0x10;
  static const unsigned char ERRORCODE011 = 0x11;
  static const unsigned char ERRORCODE012 = 0x12;
  static const unsigned char ERRORCODE013 = 0x13;
  static const unsigned char ERRORCODE014 = 0x14;
  static const unsigned char ERRORCODE015 = 0x15;
  static const unsigned char ERRORCODE016 = 0x16;
};
