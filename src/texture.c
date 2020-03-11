#include "../lib/litelibs/litegfx.h"
#include "pixmap.h"
#include "texture.h"
#include "util.h"

static int _texture_filter = FILTER_MIPMAP;

typedef struct STexture {
  int refcount; /* use int instead of size_t because non counted textures can have negative values here */
  ltex_t* ptr;
} Texture;

EXPORT Texture* CALL bmCreateTexture(const Pixmap* pixmap) {
  Texture* tex;
  tex = bmCreateEmptyTexture(bmGetPixmapWidth(pixmap), bmGetPixmapHeight(pixmap));
  if (tex) bmSetTexturePixels(tex, pixmap);
  return tex;
}

EXPORT Texture* CALL bmCreateEmptyTexture(int width, int height) {
  Texture* tex = _Alloc(Texture);
  tex->refcount = 0;
  tex->ptr = ltex_alloc(width, height, _texture_filter);
  return tex;
}

EXPORT Texture* CALL bmLoadTexture(const char* filename) {
  Pixmap* pixmap;
  Texture* tex;

  /* load pixmap */
  pixmap = bmLoadPixmap(filename);
  if (!pixmap) return NULL;

  /* create texture */
  tex = bmCreateTexture(pixmap);

  /* delete pixmap */
  bmDeletePixmap(pixmap);

  return tex;
}

void RetainTexture(Texture* texture) {
  ++texture->refcount;
}

void ReleaseTexture(Texture* texture) {
  if (--texture->refcount == 0) {
    bmDeleteTexture(texture);
  }
}

EXPORT void CALL bmDeleteTexture(Texture* texture) {
  ltex_free(texture->ptr);
  free(texture);
}

EXPORT int CALL bmGetTextureWidth(const Texture* texture) {
  return texture->ptr->width;
}

EXPORT int CALL bmGetTextureHeight(const Texture* texture) {
  return texture->ptr->height;
}

EXPORT void CALL bmSetTexturePixels(Texture* texture, const Pixmap* pixmap) {
  if (texture->ptr->width == bmGetPixmapWidth(pixmap) && texture->ptr->height == bmGetPixmapHeight(pixmap)) {
    ltex_setpixels(texture->ptr, _GetPixmapPtr(pixmap));
  }
}

EXPORT int CALL bmGetTextureFilter() {
  return _texture_filter;
}

EXPORT void CALL bmSetTextureFilter(int filter) {
  _texture_filter = filter;
}

const void* _GetTexturePtr(const Texture* texture) {
  return texture ? texture->ptr : NULL;
}
