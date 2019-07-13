#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "micron_config.h"
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
float font_height(const struct font_t* font);
float font_textwidth(const struct font_t* font, const char* text);
float font_textheight(const struct font_t* font, const char* text);
void font_draw(const struct font_t* font, const char* text, float x, float y);

#ifdef USE_DEFAULT_FONT
struct font_t* _font_loadbase64(const char* data, size_t size, float height);
#endif

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FONT_H_INCLUDED */
