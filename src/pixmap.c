#include "../lib/stb/stb_image.h"
#include "memblock.h"
#include "pixmap.h"
#include "util.h"

typedef struct SPixmap
{
  int* pixels;
  int width;
  int height;
} Pixmap;

EXPORT Pixmap* CALL CreatePixmap(int width, int height)
{
  Pixmap* pixmap = _Alloc(struct SPixmap);
  pixmap->pixels = _AllocMany(int, width * height);
  pixmap->width = width;
  pixmap->height = height;
  return pixmap;
}

EXPORT Pixmap* CALL CreatePixmapFromMemblock(const struct SMemblock* memblock)
{
  return _CreatePixmapFromData((const unsigned char*)memblock, GetMemblockSize(memblock));
}

EXPORT Pixmap* CALL LoadPixmap(const char* filename)
{
  unsigned char* buffer;
  int w, h;
  Pixmap* pixmap;

  /* load buffer */
  buffer = stbi_load(filename, &w, &h, NULL, 4);
  if (!buffer) return NULL;

  /* create pixmap */
  pixmap = _Alloc(struct SPixmap);
  pixmap->pixels = (int*)buffer;
  pixmap->width = w;
  pixmap->height = h;

  return pixmap;
}

EXPORT void CALL DeletePixmap(Pixmap* pixmap)
{
  free(pixmap->pixels);
  free(pixmap);
}

EXPORT int CALL GetPixmapWidth(const Pixmap* pixmap)
{
  return pixmap->width;
}

EXPORT int CALL GetPixmapHeight(const Pixmap* pixmap)
{
  return pixmap->height;
}

EXPORT int CALL GetPixmapColor(const Pixmap* pixmap, int x, int y)
{
  return pixmap->pixels[y*pixmap->width + x];
}

EXPORT void CALL SetPixmapColor(Pixmap* pixmap, int x, int y, int color)
{
  pixmap->pixels[y*pixmap->width + x] = color;
}

Pixmap* _CreatePixmapFromData(const unsigned char* data, size_t len)
{
  unsigned char* buffer;
  int w, h;
  Pixmap* pixmap;

  /* load buffer */
  buffer = stbi_load_from_memory(data, len, &w, &h, NULL, 4);
  if (!buffer) return NULL;

  /* create pixmap */
  pixmap = _Alloc(struct SPixmap);
  pixmap->pixels = (int*)buffer;
  pixmap->width = w;
  pixmap->height = h;

  return pixmap;
}

const void* _GetPixmapPtr(const Pixmap* pixmap)
{
  return pixmap->pixels;
}
