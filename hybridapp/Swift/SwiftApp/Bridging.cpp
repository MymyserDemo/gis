#include "MainController.h"

// Cインターフェースのメインコントローラーのインスタンス
static MainController* _mainController;

extern "C" {
  // Cインターフェースメインコントローラー作成
  void mainControllerCreate(void) {
    _mainController = new MainController();
  }

  // Cインターフェースメインコントローラー初期処理
  void mainControllerInitialize(void) {
    if(_mainController == NULL) {
        return;
    }
    _mainController->initialize();
  }

  // Cインターフェースメインコントローラー終了処理
  void mainControllerFinalize(void) {
    if(_mainController == NULL) {
        return;
    }
    _mainController->finalize();
    delete _mainController;
    _mainController = NULL;
  }

  // Cインターフェースログ出力関数設定
  void mainControllerSetLogger(void (*pLogger)(LoggerArgument)) {
    if(_mainController == NULL) {
        return;
    }
    _mainController->setLogger(pLogger);
  }

  // Cインターフェースエラー出力関数設定
  void mainControllerSetError(void (*pError)(ErrorArgument)) {
    if(_mainController == NULL) {
      return;
    }
    _mainController->setError(pError);
  }
    
    // Cインターフェースエラーコード設定
    void mainControllerSetErrorCode(const char *className,  unsigned char errorCode) {
        if(_mainController == NULL) {
            return;
        }
        _mainController->setErrorCode(className, errorCode);
    }
}
