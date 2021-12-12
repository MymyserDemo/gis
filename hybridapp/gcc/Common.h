#pragma once

#include <string.h>
#include "SwiftInterface.h"

void mainControllerCreate(void);
void mainControllerCreateCpp(void);

void mainControllerRemove(void);
void mainControllerRemoveCpp(void);

void mainControllerInitialize(void);
void mainControllerInitializeCpp(void);

void mainControllerFinalize(void);
void mainControllerFinalizeCpp(void);

typedef void (*SETLOGGER)(LoggerAurgument);
void mainControllerSetLogger(SETLOGGER);
void mainControllerSetLoggerCpp(SETLOGGER);
