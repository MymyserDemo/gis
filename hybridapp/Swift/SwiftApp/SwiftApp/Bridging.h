/**
* Hybrid側とのインターフェース定義.
*/

#include <stddef.h>

/**
 * ログ出力メッセージ.
 */
typedef struct _LoggerArugument {
    // ログを出力するクラス名称
    const char *className;
    size_t classNameLength;
    // ログを出力する関数名称
    const char *functionName;
    size_t functionNameLength;
    // 任意のメッセージ
    const char *message;
    size_t messageLength;
} LoggerArgument;

/**
 * エラー情報.
 */
typedef struct _ErrorArugument {
    // エラーが発生したクラス名称
    const char *className;
    size_t classNameLength;
    // エラーコード
    unsigned char errorCode;
} ErrorArgument;

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
