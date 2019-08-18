#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "beam_config.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL Setup2D();
EXPORT void CALL SetViewport(int x, int y, int w, int h);
EXPORT void CALL SetResolution(int w, int h);
EXPORT void CALL SetDrawColor(int color);
EXPORT void CALL SetDrawFont(const char* filename, float height);
EXPORT void CALL SetDefaultFont();
EXPORT void CALL ClearScreen(int color);
EXPORT void CALL DrawPoint(float x, float y);
EXPORT void CALL DrawLine(float x1, float y1, float x2, float y2);
EXPORT void CALL DrawEllipse(float x, float y, float width, float height);
EXPORT void CALL DrawRect(float x, float y, float width, float height);
EXPORT void CALL DrawTexture(const Texture* tex, float x, float y, float width, float height);
EXPORT void CALL DrawText(const char* text, float x, float y);

EXPORT float CALL GetTextWidth(const char* text);
EXPORT float CALL GetTextHeight(const char* text);

#ifndef SWIG
EXPORT void CALL _UnloadFonts();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DRAW_H_INCLUDED */
