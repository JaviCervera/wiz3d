#ifndef PIXMAP_H_INCLUDED
#define PIXMAP_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Pixmap* CALL CreatePixmap(const Memblock* memblock);
EXPORT Pixmap* CALL CreateEmptyPixmap(int width, int height);
EXPORT Pixmap* CALL LoadPixmap(const char* filename);
EXPORT void CALL DeletePixmap(Pixmap* pixmap);
EXPORT int CALL GetPixmapWidth(const Pixmap* pixmap);
EXPORT int CALL GetPixmapHeight(const Pixmap* pixmap);
EXPORT int CALL GetPixmapColor(const Pixmap* pixmap, int x, int y);
EXPORT void CALL SetPixmapColor(Pixmap* pixmap, int x, int y, int color);

#ifndef SWIG
Pixmap* _CreateEmptyPixmapFromData(const unsigned char* data, size_t len);
const void* _GetPixmapPtr(const Pixmap* pixmap);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PIXMAP_H_INCLUDED */
