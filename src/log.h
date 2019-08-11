#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL LogInfo(const char* msg);
EXPORT void CALL LogWarning(const char* msg);
EXPORT void CALL LogError(const char* msg);

#ifndef SWIG
void _SetLogFilename(const char* filename);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LOG_H_INCLUDED */
