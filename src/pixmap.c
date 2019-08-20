#include "../lib/stb/stb_image.h"
#include "memblock.h"
#include "pixmap.h"
#include "util.h"

typedef struct SPixmap {
  int* pixels;
  int width;
  int height;
} Pixmap;

EXPORT Pixmap* CALL spCreatePixmap(const Memblock* memblock) {
  return _CreateEmptyPixmapFromData((const unsigned char*)memblock, spGetMemblockSize(memblock));
}

EXPORT Pixmap* CALL spCreateEmptyPixmap(int width, int height) {
  Pixmap* pixmap = _Alloc(Pixmap);
  pixmap->pixels = _AllocMany(int, width * height);
  pixmap->width = width;
  pixmap->height = height;
  return pixmap;
}

EXPORT Pixmap* CALL spLoadPixmap(const char* filename) {
  Memblock* memblock;
  Pixmap* pixmap = NULL;

  memblock = spLoadMemblock(filename);
  if (memblock) {
    pixmap = spCreatePixmap(memblock);
    spDeleteMemblock(memblock);
  }

  return pixmap;
}

EXPORT void CALL spDeletePixmap(Pixmap* pixmap) {
  free(pixmap->pixels);
  free(pixmap);
}

EXPORT int CALL spGetPixmapWidth(const Pixmap* pixmap) {
  return pixmap->width;
}

EXPORT int CALL spGetPixmapHeight(const Pixmap* pixmap) {
  return pixmap->height;
}

EXPORT int CALL spGetPixmapColor(const Pixmap* pixmap, int x, int y) {
  return pixmap->pixels[y*pixmap->width + x];
}

EXPORT void CALL spSetPixmapColor(Pixmap* pixmap, int x, int y, int color) {
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
