#include "../lib/base64/base64.h"
#include "../lib/litelibs/litegfx.h"
#include "../lib/stb_truetype.h"
#include "font.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

struct font_t
{
  size_t          refcount;
  ltex_t*         tex;
  stbtt_bakedchar glyphs[256];
  float           height;
};

struct font_t* font_load(const char* filename, float height)
{
  FILE* f;
  long len;
  unsigned char* buffer;
  struct font_t* font;
  int w, h;
  unsigned char* alphabuffer;
  unsigned char* colorbuffer;
  int i;

  /* read file */
  f = fopen(filename, "rb");
  if ( !f ) return NULL;
  fseek(f, 0, SEEK_END);
  len = ftell(f);
  fseek(f, 0, SEEK_SET);
  buffer = _allocnum(unsigned char, len);
  fread(buffer, sizeof(char), len, f);
  fclose(f);

  /* load data */
  font = _font_loadfrommemory(buffer, height);
  free(buffer);

  return font;
}

void font_retain(struct font_t* font)
{
  ++font->refcount;
}

void font_release(struct font_t* font)
{
  if ( --font->refcount == 0 )
  {
    ltex_free(font->tex);
    free(font);
  }
}

float font_height(struct font_t* font)
{
  return font->height;
}

float font_textwidth(struct font_t* font, const char* text)
{
  float x = 0, y = 0;
  stbtt_aligned_quad q = { 0 };
  size_t len, i;
  
  len = strlen(text);
  for ( i = 0; i < len; ++i )
  {
    stbtt_GetBakedQuad(font->glyphs, font->tex->width, font->tex->height, text[i], &x, &y, &q, TRUE);
  }
  return q.x1;
}

float font_textheight(struct font_t* font, const char* text)
{
  float x = 0, y = 0, miny = 999999, maxy = -999999;
  stbtt_aligned_quad q = { 0 };
  size_t len, i;
  
  len = strlen(text);
  for ( i = 0; i < len; ++i )
  {
    stbtt_GetBakedQuad(font->glyphs, font->tex->width, font->tex->height, text[i], &x, &y, &q, TRUE);
    miny = miny < q.y0 ? miny : q.y0;
    maxy = maxy > q.y1 ? maxy : q.y1;
  }
  return maxy - miny;
}

void font_draw(struct font_t* font, const char* text, float x, float y)
{
  size_t len, i;

  y += font_textheight(font, text);
  len = strlen(text);
  for ( i = 0; i < len; ++i )
  {
    stbtt_aligned_quad q;
    stbtt_GetBakedQuad(font->glyphs, font->tex->width, font->tex->height, text[i], &x, &y, &q, TRUE);
    ltex_drawrotsized(font->tex, q.x0, q.y0, 0, 0, 0, q.x1 - q.x0, q.y1 - q.y0, q.s0, q.t0, q.s1, q.t1);
  }
}

struct font_t* _font_loadbase64(const char* data, size_t size, float height)
{
  unsigned char* buffer;
  struct font_t* font;

  /* get data from base64 block */
  buffer = _allocnum(unsigned char, BASE64_DECODE_OUT_SIZE(size));
  base64_decode(data, size, buffer);

  /* load data */
  font = _font_loadfrommemory(buffer, height);
  free(buffer);

  return font;
}

struct font_t* _font_loadfrommemory(const unsigned char* data, float height)
{
  struct font_t* font;
  int w, h;
  unsigned char* alphabuffer;
  unsigned char* colorbuffer;
  int i;

  /* create font object */
  font = _alloc(struct font_t);
  font->refcount = 1;
  font->height = height;

  /* bake font into alpha buffer */
  w = h = 256;
  alphabuffer = _allocnum(unsigned char, w * h);
  while ( stbtt_BakeFontBitmap(data, 0, height, alphabuffer, w, h, 0, sizeof(font->glyphs) / sizeof(font->glyphs[0]), font->glyphs) <= 0 )
  {
    if ( w == h ) w *= 2;
    else h *= 2;
    alphabuffer = (unsigned char*)realloc(alphabuffer, w * h);
  }

  /* copy into color buffer */
  colorbuffer = _allocnum(unsigned char, w*h*4);
  memset(colorbuffer, 255, w*h*4);
  for ( i = 0; i < w*h; ++i ) colorbuffer[i*4 + 3] = alphabuffer[i];
  free(alphabuffer);

  /* create texture */
  font->tex = ltex_alloc(w, h, FALSE);
  ltex_setpixels(font->tex, colorbuffer);
  free(colorbuffer);

  return font;
}
