#include "DebugLogger.h"

DebugLogger::DebugLogger()
{
  _pLogger = 0;
}

DebugLogger::~DebugLogger()
{
  _pLogger = 0;
}

void DebugLogger::setLogger(void (*pLogger)(LOGGER_ARGUMENTS))
{
  _pLogger = pLogger;
}

void DebugLogger::logger(LOGGER_ARGUMENTS)
{
  if(_pLogger != 0)
  {
    _pLogger(className, functionName);
  }
}
