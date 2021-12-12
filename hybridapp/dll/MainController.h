#pragma once

#include "BaseController.h"
#include "DebugLogger.h"
#include "MainModel.h"

class MainController : public BaseController, public DebugLogger
{
public:
  MainController();
  virtual ~MainController();
  virtual void setLogger(void (*logger)(LOGGER_ARGUMENTS));
  virtual void  initialize();
  virtual void  finalize();
private:
  MainModel* _mainModel;

};
