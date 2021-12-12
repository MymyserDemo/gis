/**
 * エラー処理.
 */

#include "ErrorController.h"

/**
 * コンストラクター.
 */
ErrorController::ErrorController() {
  _pErrorOutput = NULL;
}

/**
 * デストラクター.
 */
ErrorController::~ErrorController() {
  _pErrorOutput = NULL;
}

/**
 * 初期処理.
 */
void ErrorController::initialize() {
}

/**
 * 終了処理.
 */
void ErrorController::finalize() {
}

// エラーコード設定
void ErrorController::setErrorCode(const char *classNm, unsigned char errorCd) {
  className = classNm;
  errorCode = errorCd;
  errorOutput();
}

// エラー出力関数をハイブリッド側に登録する
void ErrorController::setError(void(*pErrorOutput)(ErrorArgument)) {
	_pErrorOutput = pErrorOutput;
}

// ハイブリッド側から呼ばれるのエラー出力関数
void ErrorController::errorOutput() {
  if (_pErrorOutput == NULL) {
    return;
  }
  ErrorArgument errorArgument;
  // エラー出力を呼び出したクラスの名前
  if (className == NULL) {
    errorArgument.className = "";
    errorArgument.classNameLength = 0;
  }
  else {
    errorArgument.className = className;
    errorArgument.classNameLength = strlen(className);
  }
  // エラーコード
  errorArgument.errorCode = errorCode;
  // アプリ側のエラー出力関数を呼び出す
  _pErrorOutput(errorArgument);
}
