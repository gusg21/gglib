#include "log.h"

#include <raylib.h>

void Log_Info(const char* info) { TraceLog(LOG_INFO, info); }

void Log_Warn(const char* warning) { TraceLog(LOG_WARNING, warning); }

void Log_Err(const char* error) { TraceLog(LOG_ERROR, error); }
