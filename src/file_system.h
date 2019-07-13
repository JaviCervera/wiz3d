#ifndef FILE_SYSTEM_H_INCLUDED
#define FILE_SYSTEM_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

bool_t fs_addpak(const char* pakname);
bool_t fs_fileinpak(const char* filename);
size_t fs_filesize(const char* filename);
bool_t fs_filecontents(const char* filename, void* buffer);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FILE_SYSTEM_H_INCLUDED */
