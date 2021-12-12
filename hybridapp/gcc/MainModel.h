#pragma once

#include "BaseModel.h"
#include "DebugLogger.h"

class MainModel : public BaseModel, public DebugLogger
{
public:
  MainModel();
  virtual ~MainModel();
  virtual void initialize();
  virtual void finalize();
};
