#pragma once

#include <typeinfo>

#include "BaseClass.h"

#define LOGGER_ARGUMENTS  const char* className, const char* functionName
#define CLASS_AND_FUNCTION_NAME (const char *)typeid(*this).name(), (const char *)__func__

class DebugLogger : public BaseClass
{
public:
  DebugLogger();
  virtual ~DebugLogger();
  virtual void setLogger(void (*logger)(LOGGER_ARGUMENTS));
protected:
  void (*_pLogger)(LOGGER_ARGUMENTS);
  virtual void logger(LOGGER_ARGUMENTS);
};
