#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "wiz3d_config.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SWIG

Font* CreateFontFromMemblock(const Memblock* memblock, float height);
Font* LoadFont(const char* filename, float height);
void RetainFont(Font* font);
void ReleaseFont(Font* font);
float GetFontHeight(const Font* font);
float GetFontTextWidth(const Font* font, const char* text);
float GetFontTextHeight(const Font* font, const char* text);
void DrawFont(const Font* font, const char* text, float x, float y);

#ifdef USE_DEFAULT_FONT
Font* _LoadBase64Font(const char* data, size_t size, float height);
#endif

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FONT_H_INCLUDED */
