#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define min(A, B)       (A < B ? A : B)
#define max(A, B)       (A > B ? A : B)
#define clamp(A, B, C)  min(max(A, B), C)
#define alloc(T)        ((T*)malloc(sizeof(T)))
#define allocnum(T,S)   ((T*)malloc(S*sizeof(T)))

void string_write(const char* str, const char* filename, bool_t append);

void dir_strip(const char* filename, char* out, size_t len);
void dir_extract(const char* filename, char* out, size_t len);
bool_t dir_contents(const char* path, char* out, size_t len);
void dir_current(char* out, size_t len);
bool_t dir_change(const char* path);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* UTIL_H_INCLUDED */
