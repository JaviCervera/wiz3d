#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "types.h"

#define FILTER_NONE 0
#define FILTER_LINEAR 1
#define FILTER_MIPMAP 2

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Texture* CALL wzCreateTexture(const Pixmap* pixmap);
EXPORT Texture* CALL wzCreateEmptyTexture(int width, int height);
EXPORT Texture* CALL wzLoadTexture(const char* filename);
#ifndef SWIG
void RetainTexture(Texture* texture);
void ReleaseTexture(Texture* texture);
#endif
EXPORT void CALL wzDeleteTexture(Texture* texture);
EXPORT int CALL wzGetTextureWidth(const Texture* texture);
EXPORT int CALL wzGetTextureHeight(const Texture* texture);
EXPORT void CALL wzSetTexturePixels(Texture* texture, const Pixmap* pixmap);

EXPORT int CALL wzGetTextureFilter();
EXPORT void CALL wzSetTextureFilter(int filter);

#ifndef SWIG
const void* _GetTexturePtr(const Texture* texture);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TEXTURE_H_INCLUDED */
