#pragma once
#include "MainController.h"

typedef  void(__stdcall *CallBackFunction)(const char *classname, const char *functionname);

extern "C" {
	__declspec(dllexport) void MainControllerCreate();
	__declspec(dllexport) void MainControllerDelete();
	__declspec(dllexport) void MainControllerInitialize();
	__declspec(dllexport) void MainControllerFinalize();
	__declspec(dllexport) void MainControllerSetLogger(CallBackFunction callback);
}
