#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct SMemblock;
struct SPixmap;
struct STexture;

EXPORT struct STexture* CALL CreateTexture(const struct SPixmap* pixmap);
EXPORT struct STexture* CALL CreateEmptyTexture(int width, int height);
EXPORT struct STexture* CALL LoadTexture(const char* filename);
#ifndef SWIG
void RetainTexture(struct STexture* texture);
void ReleaseTexture(struct STexture* texture);
#endif
EXPORT void CALL DeleteTexture(struct STexture* texture);
EXPORT int CALL GetTextureWidth(const struct STexture* texture);
EXPORT int CALL GetTextureHeight(const struct STexture* texture);
EXPORT void CALL SetTexturePixels(struct STexture* texture, const struct SPixmap* pixmap);
EXPORT void CALL SetTextureFilter(bool_t filter);

#ifndef SWIG
const void* _GetTexturePtr(const struct STexture* texture);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TEXTURE_H_INCLUDED */
