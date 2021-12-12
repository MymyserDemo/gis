/**
* Hybrid側のC++をC#から利用するためのインターフェース定義.
* C++ -> C -> C#の流れでCで定義されたインターフェースを介して
* C++ と C# が連携しています。
*/
#pragma once

#include "AutoPrintMainController.h"

// ログ出力関数の定義
typedef  void(__stdcall *LoggerCallbackFunction)(const char *className, const char *functionName, const char *message);
// エラー出力関数の定義
typedef  void(__stdcall *ErrorCallbackFunction)(const char *className, int errorCode);
// CSVファイルロード関数
typedef  char *(__stdcall *LoadCSVCallbackFunction)(const char *filePaht);

// アプリ側から参照できるようCのインターフェースを定義
extern "C" {
  __declspec(dllexport) void MainControllerCreate();
  __declspec(dllexport) void MainControllerInitialize(const char *path);
  __declspec(dllexport) void MainControllerFinalize();
  __declspec(dllexport) void MainControllerSetLogger(LoggerCallbackFunction callback);
  __declspec(dllexport) void MainControllerSetError(ErrorCallbackFunction callback);
  __declspec(dllexport) void MainControllerSetLoadCSV(LoadCSVCallbackFunction callback);
  __declspec(dllexport) void MainControllerSetErrorCode(const char *classNm, unsigned char errorCd);
  __declspec(dllexport) void MainControllerSetDataListAddHeader(void(*callback)(char *));
  __declspec(dllexport) void MainControllerSetDataListAddData(void(*callback)(char *));
}