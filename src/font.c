#include "spark_config.h"
#ifdef USE_DEFAULT_FONT
#include "../lib/base64/base64.h"
#endif
#include "../lib/litelibs/litegfx.h"
#include "../lib/stb/stb_truetype.h"
#include "font.h"
#include "memblock.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

typedef struct SFont
{
  size_t          refcount;
  ltex_t*         tex;
  stbtt_bakedchar glyphs[94];
  float           height;
  float           maxheight;
} Font;


Font* CreateFontFromMemblock(const Memblock* memblock, float height) {
  Font* font;
  int w, h;
  unsigned char* alphabuffer;
  unsigned char* colorbuffer;
  size_t len, i;
  float x = 0, y = 0;
  float miny = 999999, maxy = -999999;
  stbtt_aligned_quad q;

  /* create font object */
  font = _Alloc(Font);
  font->refcount = 1;
  font->height = height;

  /* bake font into alpha buffer */
  w = h = 256;
  alphabuffer = _AllocMany(unsigned char, w * h);
  while (stbtt_BakeFontBitmap(
      (const unsigned char*)memblock,
      0,
      height,
      alphabuffer,
      w,
      h,
      32,
      sizeof(font->glyphs) / sizeof(font->glyphs[0]),
      font->glyphs) <= 0) {
    if (w == h) w *= 2;
    else h *= 2;
    alphabuffer = (unsigned char*)realloc(alphabuffer, w * h);
  }

  /* copy into color buffer */
  colorbuffer = _AllocMany(unsigned char, w*h*4);
  memset(colorbuffer, 255, w*h*4);
  for (i = 0; i < w*h; ++i) colorbuffer[i*4 + 3] = alphabuffer[i];
  free(alphabuffer);

  /* create texture */
  font->tex = ltex_alloc(w, h, FALSE);
  ltex_setpixels(font->tex, colorbuffer);
  free(colorbuffer);

  /* get max char height */
  font->maxheight = -999999;
  len = sizeof(font->glyphs) / sizeof(font->glyphs[0]);
  for (i = 0; i < len; ++i) {
    stbtt_GetBakedQuad(font->glyphs, font->tex->width, font->tex->height, i, &x, &y, &q, TRUE);
    miny = _Min(miny, q.y0);
    maxy = _Max(maxy, q.y1);
  }
  font->maxheight = maxy - miny;

  return font;
}

Font* LoadFont(const char* filename, float height) {
  Memblock* memblock;
  Font* font = NULL;

  memblock = spLoadMemblock(filename);
  if (memblock) {
    font = CreateFontFromMemblock(memblock, height);
    spDeleteMemblock(memblock);
  }

  return font;
}

void RetainFont(Font* font) {
  ++font->refcount;
}

void ReleaseFont(Font* font) {
  if (--font->refcount == 0) {
    ltex_free(font->tex);
    free(font);
  }
}

float GetFontHeight(const Font* font) {
  return font->height;
}

float GetFontTextWidth(const Font* font, const char* text) {
  float x = 0, y = 0;
  stbtt_aligned_quad q = { 0 };
  size_t len, i;

  len = strlen(text);
  for (i = 0; i < len; ++i) {
    stbtt_GetBakedQuad(font->glyphs, font->tex->width, font->tex->height, _Min(text[i] - 32, 94), &x, &y, &q, TRUE);
  }
  return q.x1;
}

float GetFontTextHeight(const Font* font, const char* text) {
  float x = 0, y = 0, miny = 999999, maxy = -999999;
  stbtt_aligned_quad q = { 0 };
  size_t len, i;

  len = strlen(text);
  for (i = 0; i < len; ++i) {
    stbtt_GetBakedQuad(font->glyphs, font->tex->width, font->tex->height, _Min(text[i] - 32, 94), &x, &y, &q, TRUE);
    miny = _Min(miny, q.y0);
    maxy = _Max(maxy, q.y1);
  }
  return maxy - miny;
}

void DrawFont(const Font* font, const char* text, float x, float y) {
  size_t len, i;

  y += font->maxheight;
  len = strlen(text);
  for (i = 0; i < len; ++i) {
    stbtt_aligned_quad q;
    stbtt_GetBakedQuad(font->glyphs, font->tex->width, font->tex->height, _Min(text[i] - 32, 94), &x, &y, &q, TRUE);
    ltex_drawrotsized(font->tex, q.x0, q.y0, 0, 0, 0, q.x1 - q.x0, q.y1 - q.y0, q.s0, q.t0, q.s1, q.t1);
  }
}

#ifdef USE_DEFAULT_FONT
Font* _LoadBase64Font(const char* data, size_t size, float height) {
  Memblock* memblock;
  Font* font;

  memblock = spCreateMemblock(BASE64_DECODE_OUT_SIZE(size));
  base64_decode(data, size, (unsigned char*)memblock);
  font = CreateFontFromMemblock(memblock, height);
  spDeleteMemblock(memblock);

  return font;
}
#endif
