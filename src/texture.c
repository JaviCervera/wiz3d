#include "../lib/litelibs/litegfx.h"
#include "pixmap.h"
#include "texture.h"
#include "util.h"

static bool_t _texture_filtering = TRUE;

typedef struct STexture {
  int refcount; /* use int instead of size_t because non counted textures can have negative values here */
  ltex_t* ptr;
} Texture;

EXPORT Texture* CALL spCreateTexture(const Pixmap* pixmap) {
  Texture* tex;
  tex = spCreateEmptyTexture(spGetPixmapWidth(pixmap), spGetPixmapHeight(pixmap));
  if (tex) spSetTexturePixels(tex, pixmap);
  return tex;
}

EXPORT Texture* CALL spCreateEmptyTexture(int width, int height) {
  Texture* tex = _Alloc(Texture);
  tex->refcount = 0;
  tex->ptr = ltex_alloc(width, height, _texture_filtering);
  return tex;
}

EXPORT Texture* CALL spLoadTexture(const char* filename) {
  Pixmap* pixmap;
  Texture* tex;

  /* load pixmap */
  pixmap = spLoadPixmap(filename);
  if (!pixmap) return NULL;

  /* create texture */
  tex = spCreateTexture(pixmap);

  /* delete pixmap */
  spDeletePixmap(pixmap);

  return tex;
}

void RetainTexture(Texture* texture) {
  ++texture->refcount;
}

void ReleaseTexture(Texture* texture) {
  if (--texture->refcount == 0) {
    spDeleteTexture(texture);
  }
}

EXPORT void CALL spDeleteTexture(Texture* texture) {
  ltex_free(texture->ptr);
  free(texture);
}

EXPORT int CALL spGetTextureWidth(const Texture* texture) {
  return texture->ptr->width;
}

EXPORT int CALL spGetTextureHeight(const Texture* texture) {
  return texture->ptr->height;
}

EXPORT void CALL spSetTexturePixels(Texture* texture, const Pixmap* pixmap) {
  if (texture->ptr->width == spGetPixmapWidth(pixmap) && texture->ptr->height == spGetPixmapHeight(pixmap)) {
    ltex_setpixels(texture->ptr, _GetPixmapPtr(pixmap));
  }
}

EXPORT void CALL spSetTextureFilter(bool_t filter) {
  _texture_filtering = filter;
}

const void* _GetTexturePtr(const Texture* texture) {
  return texture ? texture->ptr : NULL;
}
