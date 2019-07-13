#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

EXPORT void CALL log_info(const char* msg);
EXPORT void CALL log_warning(const char* msg);
EXPORT void CALL log_error(const char* msg);

#ifndef SWIG
void _log_setfilename(const char* filename);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LOG_H_INCLUDED */
