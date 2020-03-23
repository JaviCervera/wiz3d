#ifndef PIXMAP_H_INCLUDED
#define PIXMAP_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Pixmap* CALL wzCreatePixmap(const Memblock* memblock);
EXPORT Pixmap* CALL wzCreateEmptyPixmap(int width, int height);
EXPORT Pixmap* CALL wzLoadPixmap(const char* filename);
EXPORT void CALL wzDeletePixmap(Pixmap* pixmap);
EXPORT int CALL wzGetPixmapWidth(const Pixmap* pixmap);
EXPORT int CALL wzGetPixmapHeight(const Pixmap* pixmap);
EXPORT int CALL wzGetPixmapColor(const Pixmap* pixmap, int x, int y);
EXPORT void CALL wzSetPixmapColor(Pixmap* pixmap, int x, int y, int color);

#ifndef SWIG
Pixmap* _CreateEmptyPixmapFromData(const unsigned char* data, size_t len);
const void* _GetPixmapPtr(const Pixmap* pixmap);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PIXMAP_H_INCLUDED */
