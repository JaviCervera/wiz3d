#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef SWIG
struct font_t;

struct font_t* font_load(const char* filename, float height);
void font_retain(struct font_t* font);
void font_release(struct font_t* font);
float font_height(struct font_t* font);
float font_textwidth(struct font_t* font, const char* text);
float font_textheight(struct font_t* font, const char* text);
void font_draw(struct font_t* font, const char* text, float x, float y);
void font_default();

struct font_t* _font_loadbase64(const char* data, size_t size, float height);
struct font_t* _font_loadfrommemory(const unsigned char* data, float height);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FONT_H_INCLUDED */
