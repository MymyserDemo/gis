#include "MainController.h"

MainController::MainController()
{
  _mainModel = new MainModel();
}

MainController::~MainController()
{
}

void MainController::setLogger(void (*pLogger)(LoggerAurgument))
{
  DebugLogger::setLogger(pLogger);

  if(_mainModel != 0)
  {
    _mainModel->setLogger(pLogger);
  }
}

void MainController::initialize()
{
    logger(CLASS_FUNCTION_NAME,  "");
    
  if(_mainModel != 0)
  {
    _mainModel->initialize();
  }
}

void MainController::finalize()
{
  if(_mainModel != 0)
  {
    _mainModel->finalize();
    delete _mainModel;
   _mainModel = 0;
  }
  logger(CLASS_FUNCTION_NAME,  "");
}

MainController* _mainController;

extern "C" void mainControllerCreateCpp(void)
{
    _mainController = new MainController();
}

extern "C" void mainControllerRemoveCpp(void)
{
    if(_mainController != 0)
    {
        delete _mainController;
        _mainController = 0;
    }
}

extern "C" void mainControllerInitializeCpp(void)
{
    if(_mainController != 0)
    {
        _mainController->initialize();
    }
}

extern "C" void mainControllerFinalizeCpp(void)
{
    if(_mainController != 0)
    {
        _mainController->finalize();
    }
}

extern "C" void mainControllerSetLoggerCpp(void (*pLogger)(LoggerAurgument))
{
    if(_mainController != 0)
    {
        _mainController->setLogger(pLogger);
    }
}
