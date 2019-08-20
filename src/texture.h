#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Texture* CALL spCreateTexture(const Pixmap* pixmap);
EXPORT Texture* CALL spCreateEmptyTexture(int width, int height);
EXPORT Texture* CALL spLoadTexture(const char* filename);
#ifndef SWIG
void RetainTexture(Texture* texture);
void ReleaseTexture(Texture* texture);
#endif
EXPORT void CALL spDeleteTexture(Texture* texture);
EXPORT int CALL spGetTextureWidth(const Texture* texture);
EXPORT int CALL spGetTextureHeight(const Texture* texture);
EXPORT void CALL spSetTexturePixels(Texture* texture, const Pixmap* pixmap);
EXPORT void CALL spSetTextureFilter(bool_t filter);

#ifndef SWIG
const void* _GetTexturePtr(const Texture* texture);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TEXTURE_H_INCLUDED */
