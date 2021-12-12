#include "DebugLogger.h"

DebugLogger::DebugLogger()
{
  _pLogger = 0;
}

DebugLogger::~DebugLogger()
{
  _pLogger = 0;
}

void DebugLogger::setLogger(void (*pLogger)(LoggerAurgument))
{
  _pLogger = pLogger;
}

void DebugLogger::logger(const char *className, const char *functionName, const char *message)
{
  if(_pLogger != 0)
  {
      LoggerAurgument loggerArgument;
      
      if(className == "")
      {
          loggerArgument.className = "";
          loggerArgument.classNameLength = 0;
      }
      else
      {
          loggerArgument.className = className;
          loggerArgument.classNameLength = strlen(className);
      }
      
      if(functionName == "")
      {
          loggerArgument.functionName = "";
          loggerArgument.functionNameLength = 0;
      }
      else
      {
          loggerArgument.functionName = functionName;
          loggerArgument.functionNameLength = strlen(functionName);
      }
      
      if(message == "")
      {
          loggerArgument.message = "";
          loggerArgument.messageLength = 0;
      }
      else
      {
          loggerArgument.message = message;
          loggerArgument.messageLength = strlen(message);
      }
      _pLogger(loggerArgument);
  }
}
