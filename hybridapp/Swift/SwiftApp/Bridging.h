/**
* Hybrid側とのインターフェース定義.
*/

#include "HybridInterface.h"

// Hybrid側メインコントローラー作成
void mainControllerCreate(void);

// Hybrid側メインコントローラー初期処理
void mainControllerInitialize(void);

// Hybrid側メインコントローラー終了処理
void mainControllerFinalize(void);

// Hybrid側メインコントローラーログ出力コールバック設定
void mainControllerSetLogger(void (*callback)(LoggerArgument));

// Hybrid側メインコントローラーエラー出力コールバック設定
void mainControllerSetError(void (*callback)(ErrorArgument));

// エラーコード設定
void mainControllerSetErrorCode(const char *className,  unsigned char errorCode);
