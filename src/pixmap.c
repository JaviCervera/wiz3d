#include "../lib/stb/stb_image.h"
#include "memory.h"
#include "pixmap.h"
#include "util.h"

struct pixmap_t
{
  int* pixels;
  int width;
  int height;
};

EXPORT struct pixmap_t* CALL pixmap_new(int width, int height)
{
  struct pixmap_t* pixmap = _alloc(struct pixmap_t);
  pixmap->pixels = _allocnum(int, width * height);
  pixmap->width = width;
  pixmap->height = height;
  return pixmap;
}

EXPORT struct pixmap_t* CALL pixmap_newfrommemory(const struct memory_t* memory)
{
  return _pixmap_newfromdata((const unsigned char*)memory, memory_size(memory));
}

EXPORT struct pixmap_t* CALL pixmap_load(const char* filename)
{
  unsigned char* buffer;
  int w, h;
  struct pixmap_t* pixmap;

  /* load buffer */
  buffer = stbi_load(filename, &w, &h, NULL, 4);
  if (!buffer) return NULL;

  /* create pixmap */
  pixmap = _alloc(struct pixmap_t);
  pixmap->pixels = (int*)buffer;
  pixmap->width = w;
  pixmap->height = h;

  return pixmap;
}

EXPORT void CALL pixmap_delete(struct pixmap_t* pixmap)
{
  free(pixmap->pixels);
  free(pixmap);
}

EXPORT int CALL pixmap_width(const struct pixmap_t* pixmap)
{
  return pixmap->width;
}

EXPORT int CALL pixmap_height(const struct pixmap_t* pixmap)
{
  return pixmap->height;
}

EXPORT int CALL pixmap_color(const struct pixmap_t* pixmap, int x, int y)
{
  return pixmap->pixels[y*pixmap->width + x];
}

EXPORT void CALL pixmap_setcolor(struct pixmap_t* pixmap, int x, int y, int color)
{
  pixmap->pixels[y*pixmap->width + x] = color;
}

struct pixmap_t* _pixmap_newfromdata(const unsigned char* data, size_t len)
{
  unsigned char* buffer;
  int w, h;
  struct pixmap_t* pixmap;

  /* load buffer */
  buffer = stbi_load_from_memory(data, len, &w, &h, NULL, 4);
  if (!buffer) return NULL;

  /* create pixmap */
  pixmap = _alloc(struct pixmap_t);
  pixmap->pixels = (int*)buffer;
  pixmap->width = w;
  pixmap->height = h;

  return pixmap;
}

const void* _pixmap_ptr(const struct pixmap_t* pixmap)
{
  return pixmap->pixels;
}