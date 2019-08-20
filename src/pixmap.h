#ifndef PIXMAP_H_INCLUDED
#define PIXMAP_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Pixmap* CALL spCreatePixmap(const Memblock* memblock);
EXPORT Pixmap* CALL spCreateEmptyPixmap(int width, int height);
EXPORT Pixmap* CALL spLoadPixmap(const char* filename);
EXPORT void CALL spDeletePixmap(Pixmap* pixmap);
EXPORT int CALL spGetPixmapWidth(const Pixmap* pixmap);
EXPORT int CALL spGetPixmapHeight(const Pixmap* pixmap);
EXPORT int CALL spGetPixmapColor(const Pixmap* pixmap, int x, int y);
EXPORT void CALL spSetPixmapColor(Pixmap* pixmap, int x, int y, int color);

#ifndef SWIG
Pixmap* _CreateEmptyPixmapFromData(const unsigned char* data, size_t len);
const void* _GetPixmapPtr(const Pixmap* pixmap);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PIXMAP_H_INCLUDED */
