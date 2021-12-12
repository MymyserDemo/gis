#include <iostream>

#include "DebugLogger.h"
#include "MainController.h"

using namespace std;

void logger(LOGGER_ARGUMENTS)
{
  cout << className << ":" << functionName << endl;
}

int main()
{
  MainController mainController;

  mainController.setLogger(logger);

  mainController.initialize();

  mainController.finalize();

  return 0;
}
