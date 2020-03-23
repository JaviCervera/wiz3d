#ifndef FILE_SYSTEM_H_INCLUDED
#define FILE_SYSTEM_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT bool_t CALL wzAddPackage(const char* pakname);
EXPORT bool_t CALL wzIsFilePacked(const char* filename);
EXPORT size_t CALL wzGetFileSize(const char* filename);

#ifndef SWIG
bool_t _GetFileContents(const char* filename, void* buffer);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FILE_SYSTEM_H_INCLUDED */
