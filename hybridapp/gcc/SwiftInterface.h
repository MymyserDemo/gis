#pragma once

typedef struct _LoggerArugument {
    const char *className;
    size_t classNameLength;
    const char *functionName;
    size_t functionNameLength;
    const char *message;
    size_t messageLength;
} LoggerAurgument;

