#include "MainController.h"

MainController::MainController()
{
  _mainModel = new MainModel();
}

MainController::~MainController()
{
}

void MainController::setLogger(void (*pLogger)(LOGGER_ARGUMENTS))
{
  DebugLogger::setLogger(pLogger);

  if(_mainModel != 0)
  {
    _mainModel->setLogger(pLogger);
  }
}

void MainController::initialize()
{
  logger(CLASS_AND_FUNCTION_NAME);
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
  logger(CLASS_AND_FUNCTION_NAME);
}
