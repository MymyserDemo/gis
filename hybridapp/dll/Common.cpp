#include "Common.h"

MainController* _mainController;

void MainControllerCreate()
{
	_mainController = new MainController();
}

void MainControllerDelete()
{
	delete _mainController;
}

void  MainControllerInitialize()
{
	if (_mainController != 0)
	{
		_mainController->initialize();
	}
}

void  MainControllerFinalize()
{
	if (_mainController != 0)
	{
		_mainController->finalize();
	}
}

void MainControllerSetLogger(CallBackFunction callback)
{
	if (_mainController == 0)
	{
		return;
	}
	if (callback == 0)
	{
		return;
	}
	_mainController->setLogger(callback);
}
