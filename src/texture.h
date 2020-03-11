#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "types.h"

#define FILTER_NONE 0
#define FILTER_LINEAR 1
#define FILTER_MIPMAP 2

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Texture* CALL bmCreateTexture(const Pixmap* pixmap);
EXPORT Texture* CALL bmCreateEmptyTexture(int width, int height);
EXPORT Texture* CALL bmLoadTexture(const char* filename);
#ifndef SWIG
void RetainTexture(Texture* texture);
void ReleaseTexture(Texture* texture);
#endif
EXPORT void CALL bmDeleteTexture(Texture* texture);
EXPORT int CALL bmGetTextureWidth(const Texture* texture);
EXPORT int CALL bmGetTextureHeight(const Texture* texture);
EXPORT void CALL bmSetTexturePixels(Texture* texture, const Pixmap* pixmap);

EXPORT int CALL bmGetTextureFilter();
EXPORT void CALL bmSetTextureFilter(int filter);

#ifndef SWIG
const void* _GetTexturePtr(const Texture* texture);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TEXTURE_H_INCLUDED */
