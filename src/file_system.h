#ifndef FILE_SYSTEM_H_INCLUDED
#define FILE_SYSTEM_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

bool_t AddPackage(const char* pakname);
bool_t IsFilePacked(const char* filename);
size_t GetFileSize(const char* filename);

#ifndef SWIG
bool_t _GetFileContents(const char* filename, void* buffer);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FILE_SYSTEM_H_INCLUDED */
