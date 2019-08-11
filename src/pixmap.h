#ifndef PIXMAP_H_INCLUDED
#define PIXMAP_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct SMemblock;
struct SPixmap;

EXPORT struct SPixmap* CALL CreatePixmap(const struct SMemblock* memblock);
EXPORT struct SPixmap* CALL CreateEmptyPixmap(int width, int height);
EXPORT struct SPixmap* CALL LoadPixmap(const char* filename);
EXPORT void CALL DeletePixmap(struct SPixmap* pixmap);
EXPORT int CALL GetPixmapWidth(const struct SPixmap* pixmap);
EXPORT int CALL GetPixmapHeight(const struct SPixmap* pixmap);
EXPORT int CALL GetPixmapColor(const struct SPixmap* pixmap, int x, int y);
EXPORT void CALL SetPixmapColor(struct SPixmap* pixmap, int x, int y, int color);

#ifndef SWIG
struct SPixmap* _CreateEmptyPixmapFromData(const unsigned char* data, size_t len);
const void* _GetPixmapPtr(const struct SPixmap* pixmap);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PIXMAP_H_INCLUDED */
