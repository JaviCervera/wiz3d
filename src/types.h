#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#ifdef _WIN32
#if defined(DLLEXPORT)
#define EXPORT __declspec(dllexport)
#elif defined(DLLIMPORT)
#define EXPORT __declspec(dllimport)
#else
#define EXPORT
#endif
#define CALL __stdcall
#else
#define EXPORT
#define CALL
#endif

#define FALSE           0
#define TRUE            1

typedef char bool_t;

#include <stdlib.h>

#endif /* TYPES_H_INCLUDED */
