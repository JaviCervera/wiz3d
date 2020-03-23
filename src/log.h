#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL wzLogInfo(const char* msg);
EXPORT void CALL wzLogWarning(const char* msg);
EXPORT void CALL wzLogError(const char* msg);

#ifndef SWIG
void _SetLogFilename(const char* filename);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LOG_H_INCLUDED */
