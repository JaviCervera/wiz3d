#include "../lib/litelibs/litegfx.h"
#include "pixmap.h"
#include "texture.h"
#include "util.h"

static bool_t _texture_filtering = TRUE;

typedef struct STexture {
  int refcount; /* use int instead of size_t because non counted textures can have negative values here */
  ltex_t* ptr;
} Texture;

EXPORT Texture* CALL CreateTexture(int width, int height) {
  Texture* tex = _Alloc(Texture);
  tex->refcount = 0;
  tex->ptr = ltex_alloc(width, height, _texture_filtering);
  return tex;
}

EXPORT Texture* CALL CreateTextureFromMemblock(const struct SMemblock* memblock) {
  struct SPixmap* pixmap;
  Texture* tex;

  /* create pixmap */
  pixmap = CreatePixmapFromMemblock(memblock);

  /* create texture */
  tex = CreateTextureFromPixmap(pixmap);

  /* delete pixmap */
  DeletePixmap(pixmap);

  return tex;
}

EXPORT Texture* CALL CreateTextureFromPixmap(const struct SPixmap* pixmap) {
  Texture* tex;
  tex = CreateTexture(GetPixmapWidth(pixmap), GetPixmapHeight(pixmap));
  if (tex) SetTexturePixels(tex, pixmap);
  return tex;
}

EXPORT Texture* CALL LoadTexture(const char* filename) {
  struct SPixmap* pixmap;
  Texture* tex;

  /* load pixmap */
  pixmap = LoadPixmap(filename);
  if (!pixmap) return NULL;

  /* create texture */
  tex = CreateTextureFromPixmap(pixmap);

  /* delete pixmap */
  DeletePixmap(pixmap);

  return tex;
}

void RetainTexture(Texture* texture) {
  ++texture->refcount;
}

void ReleaseTexture(Texture* texture) {
  if (--texture->refcount == 0) {
    DeleteTexture(texture);
  }
}

EXPORT void CALL DeleteTexture(Texture* texture) {
  ltex_free(texture->ptr);
  free(texture);
}

EXPORT int CALL GetTextureWidth(const Texture* texture) {
  return texture->ptr->width;
}

EXPORT int CALL GetTextureHeight(const Texture* texture) {
  return texture->ptr->height;
}

EXPORT void CALL SetTexturePixels(Texture* texture, const struct SPixmap* pixmap) {
  if (texture->ptr->width == GetPixmapWidth(pixmap) && texture->ptr->height == GetPixmapHeight(pixmap)) {
    ltex_setpixels(texture->ptr, _GetPixmapPtr(pixmap));
  }
}

EXPORT void CALL SetTextureFilter(bool_t filter) {
  _texture_filtering = filter;
}

const void* _GetTexturePtr(const Texture* texture) {
  return texture ? texture->ptr : NULL;
}
