#ifndef FILE_SYSTEM_H_INCLUDED
#define FILE_SYSTEM_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT bool_t CALL spAddPackage(const char* pakname);
EXPORT bool_t CALL spIsFilePacked(const char* filename);
EXPORT size_t CALL spGetFileSize(const char* filename);

#ifndef SWIG
bool_t _GetFileContents(const char* filename, void* buffer);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FILE_SYSTEM_H_INCLUDED */
