#include "../lib/stb/stb_image.h"
#include "memblock.h"
#include "pixmap.h"
#include "util.h"

typedef struct SPixmap {
    int* pixels;
    int width;
    int height;
} Pixmap;

EXPORT Pixmap* CALL wzCreatePixmap(const Memblock* memblock) {
    return _CreateEmptyPixmapFromData((const unsigned char*)memblock, wzGetMemblockSize(memblock));
}

EXPORT Pixmap* CALL wzCreateEmptyPixmap(int width, int height) {
    Pixmap* pixmap = _Alloc(Pixmap);
    pixmap->pixels = _AllocMany(int, width * height);
    pixmap->width = width;
    pixmap->height = height;
    return pixmap;
}

EXPORT Pixmap* CALL wzLoadPixmap(const char* filename) {
    Memblock* memblock;
    Pixmap* pixmap = NULL;

    memblock = wzLoadMemblock(filename);
    if (memblock) {
        pixmap = wzCreatePixmap(memblock);
        wzDeleteMemblock(memblock);
    }

    return pixmap;
}

EXPORT void CALL wzDeletePixmap(Pixmap* pixmap) {
    free(pixmap->pixels);
    free(pixmap);
}

EXPORT int CALL wzGetPixmapWidth(const Pixmap* pixmap) {
    return pixmap->width;
}

EXPORT int CALL wzGetPixmapHeight(const Pixmap* pixmap) {
    return pixmap->height;
}

EXPORT int CALL wzGetPixmapColor(const Pixmap* pixmap, int x, int y) {
    return pixmap->pixels[y*pixmap->width + x];
}

EXPORT void CALL wzSetPixmapColor(Pixmap* pixmap, int x, int y, int color) {
    pixmap->pixels[y*pixmap->width + x] = color;
}

Pixmap* _CreateEmptyPixmapFromData(const unsigned char* data, size_t len) {
    unsigned char* buffer;
    int w, h;
    Pixmap* pixmap;

    /* load buffer */
    buffer = stbi_load_from_memory(data, len, &w, &h, NULL, 4);
    if (!buffer) return NULL;

    /* create pixmap */
    pixmap = _Alloc(Pixmap);
    pixmap->pixels = (int*)buffer;
    pixmap->width = w;
    pixmap->height = h;

    return pixmap;
}

const void* _GetPixmapPtr(const Pixmap* pixmap) {
    return pixmap->pixels;
}
