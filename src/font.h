#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "beam_config.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SWIG
struct SFont;
struct SMemblock;

struct SFont* CreateFontFromMemblock(const struct SMemblock* memblock, float height);
struct SFont* LoadFont(const char* filename, float height);
void RetainFont(struct SFont* font);
void ReleaseFont(struct SFont* font);
float GetFontHeight(const struct SFont* font);
float GetFontTextWidth(const struct SFont* font, const char* text);
float GetFontTextHeight(const struct SFont* font, const char* text);
void DrawFont(const struct SFont* font, const char* text, float x, float y);

#ifdef USE_DEFAULT_FONT
struct SFont* _LoadBase64Font(const char* data, size_t size, float height);
#endif

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FONT_H_INCLUDED */
