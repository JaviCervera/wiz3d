#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT Texture* CALL CreateTexture(const Pixmap* pixmap);
EXPORT Texture* CALL CreateEmptyTexture(int width, int height);
EXPORT Texture* CALL LoadTexture(const char* filename);
#ifndef SWIG
void RetainTexture(Texture* texture);
void ReleaseTexture(Texture* texture);
#endif
EXPORT void CALL DeleteTexture(Texture* texture);
EXPORT int CALL GetTextureWidth(const Texture* texture);
EXPORT int CALL GetTextureHeight(const Texture* texture);
EXPORT void CALL SetTexturePixels(Texture* texture, const Pixmap* pixmap);
EXPORT void CALL SetTextureFilter(bool_t filter);

#ifndef SWIG
const void* _GetTexturePtr(const Texture* texture);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TEXTURE_H_INCLUDED */
