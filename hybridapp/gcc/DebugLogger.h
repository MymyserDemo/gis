#pragma once

#include <typeinfo>
#include <string.h>
#include "BaseClass.h"
#include "SwiftInterface.h"

#define CLASS_FUNCTION_NAME (const char*)typeid(*this).name(), (const char *)__func__

class DebugLogger : public BaseClass
{
public:
  DebugLogger();
  virtual ~DebugLogger();
  virtual void setLogger(void (*logger)(LoggerAurgument));
protected:
  void (*_pLogger)(LoggerAurgument);
  virtual void logger(const char *className, const char *functionName, const char *message);
};
