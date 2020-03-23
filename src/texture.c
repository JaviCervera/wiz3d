#include "../lib/litelibs/litegfx.h"
#include "pixmap.h"
#include "texture.h"
#include "util.h"

static int _texture_filter = FILTER_MIPMAP;

typedef struct STexture {
    int refcount; /* use int instead of size_t because non counted textures can have negative values here */
    ltex_t* ptr;
} Texture;

EXPORT Texture* CALL wzCreateTexture(const Pixmap* pixmap) {
    Texture* tex;
    tex = wzCreateEmptyTexture(wzGetPixmapWidth(pixmap), wzGetPixmapHeight(pixmap));
    if (tex) wzSetTexturePixels(tex, pixmap);
    return tex;
}

EXPORT Texture* CALL wzCreateEmptyTexture(int width, int height) {
    Texture* tex = _Alloc(Texture);
    tex->refcount = 0;
    tex->ptr = ltex_alloc(width, height, _texture_filter);
    return tex;
}

EXPORT Texture* CALL wzLoadTexture(const char* filename) {
    Pixmap* pixmap;
    Texture* tex;

    /* load pixmap */
    pixmap = wzLoadPixmap(filename);
    if (!pixmap) return NULL;

    /* create texture */
    tex = wzCreateTexture(pixmap);

    /* delete pixmap */
    wzDeletePixmap(pixmap);

    return tex;
}

void RetainTexture(Texture* texture) {
    ++texture->refcount;
}

void ReleaseTexture(Texture* texture) {
    if (--texture->refcount == 0) {
        wzDeleteTexture(texture);
    }
}

EXPORT void CALL wzDeleteTexture(Texture* texture) {
    ltex_free(texture->ptr);
    free(texture);
}

EXPORT int CALL wzGetTextureWidth(const Texture* texture) {
    return texture->ptr->width;
}

EXPORT int CALL wzGetTextureHeight(const Texture* texture) {
    return texture->ptr->height;
}

EXPORT void CALL wzSetTexturePixels(Texture* texture, const Pixmap* pixmap) {
    if (texture->ptr->width == wzGetPixmapWidth(pixmap) && texture->ptr->height == wzGetPixmapHeight(pixmap)) {
        ltex_setpixels(texture->ptr, _GetPixmapPtr(pixmap));
    }
}

EXPORT int CALL wzGetTextureFilter() {
    return _texture_filter;
}

EXPORT void CALL wzSetTextureFilter(int filter) {
    _texture_filter = filter;
}

const void* _GetTexturePtr(const Texture* texture) {
    return texture ? texture->ptr : NULL;
}
