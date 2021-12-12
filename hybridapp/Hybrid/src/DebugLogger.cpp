#include "DebugLogger.h"

// コンストラクター
DebugLogger::DebugLogger() {
//  _pLogger = nullptr;
}

// デストラクター
DebugLogger::~DebugLogger() {
  _pLogger = nullptr;
}

// デバッグ出力関数をハイブリッド側に登録する
void DebugLogger::setLogger(void (*pLogger)(LoggerArgument)) {
  _pLogger = pLogger;
}

// ハイブリッド側から呼ばれるのログ出力関数
void DebugLogger::logger(const char *className, const char *functionName, const char *message) {
  if (_pLogger == nullptr) {
    return;
  }
  LoggerArgument loggerArgument;
  // ログ出力を呼び出したクラスの名前
  if(className == nullptr) {
    loggerArgument.className = "";
    loggerArgument.classNameLength = 0;
  }
  else {
    loggerArgument.className = className;
    loggerArgument.classNameLength = strlen(className);
  }
  // ログ出力を呼び出した関数の名前
  if(functionName == nullptr) {
    loggerArgument.functionName = "";
    loggerArgument.functionNameLength = 0;
  }
  else {
    loggerArgument.functionName = functionName;
    loggerArgument.functionNameLength = strlen(functionName);
  }
  // ログ出力を呼び出した時のメッセージ
  if(message == nullptr) {
    loggerArgument.message = "";
    loggerArgument.messageLength = 0;
  }
  else {
    loggerArgument.message = message;
    loggerArgument.messageLength = strlen(message);
  }
  // アプリ側のログ出力関数を呼び出す
  _pLogger(loggerArgument);
}
