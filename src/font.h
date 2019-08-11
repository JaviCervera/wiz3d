#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "beam_config.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SWIG
struct Font;

struct Font* LoadFont(const char* filename, float height);
void RetainFont(struct Font* font);
void ReleaseFont(struct Font* font);
float GetFontHeight(const struct Font* font);
float GetFontTextWidth(const struct Font* font, const char* text);
float GetFontTextHeight(const struct Font* font, const char* text);
void DrawFont(const struct Font* font, const char* text, float x, float y);

#ifdef USE_DEFAULT_FONT
struct Font* _LoadBase64Font(const char* data, size_t size, float height);
#endif

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FONT_H_INCLUDED */
