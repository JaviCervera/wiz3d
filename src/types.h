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

#define FALSE                     0
#define TRUE                        1

typedef int bool_t;

struct SFont;
struct SLight;
struct SMaterial;
struct SMemblock;
struct SMesh;
struct SObject;
struct SPixmap;
struct STexture;
struct SViewer;
typedef struct SFont Font;
typedef struct SLight Light;
typedef struct SMaterial Material;
typedef struct SMemblock Memblock;
typedef struct SMesh Mesh;
typedef struct SObject Object;
typedef struct SPixmap Pixmap;
typedef struct STexture Texture;
typedef struct SViewer Viewer;

#include <stdlib.h>

#endif /* TYPES_H_INCLUDED */
