#ifndef PIXMAP_H_INCLUDED
#define PIXMAP_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Pixmap* CALL bmCreatePixmap(const Memblock* memblock);
EXPORT Pixmap* CALL bmCreateEmptyPixmap(int width, int height);
EXPORT Pixmap* CALL bmLoadPixmap(const char* filename);
EXPORT void CALL bmDeletePixmap(Pixmap* pixmap);
EXPORT int CALL bmGetPixmapWidth(const Pixmap* pixmap);
EXPORT int CALL bmGetPixmapHeight(const Pixmap* pixmap);
EXPORT int CALL bmGetPixmapColor(const Pixmap* pixmap, int x, int y);
EXPORT void CALL bmSetPixmapColor(Pixmap* pixmap, int x, int y, int color);

#ifndef SWIG
Pixmap* _CreateEmptyPixmapFromData(const unsigned char* data, size_t len);
const void* _GetPixmapPtr(const Pixmap* pixmap);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PIXMAP_H_INCLUDED */
