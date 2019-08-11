#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define _Min(A, B)       (A < B ? A : B)
#define _Max(A, B)       (A > B ? A : B)
#define _Clamp(A, B, C)  _Min(_Max(A, B), C)
#define _Alloc(T)        ((T*)malloc(sizeof(T)))
#define _AllocMany(T,N)   ((T*)malloc(N*sizeof(T)))

void StripExt(const char* filename, char* out, size_t len);
void ExtractExt(const char* filename, char* out, size_t len);
void StripDir(const char* filename, char* out, size_t len);
void ExtractDir(const char* filename, char* out, size_t len);
bool_t GetDirContents(const char* path, char* out, size_t len);
void GetCurrentDir(char* out, size_t len);
bool_t ChangeDir(const char* path);
int StringCompareLower(char const *a, char const *b);
void WriteString(const char* str, const char* filename, bool_t append);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* UTIL_H_INCLUDED */
