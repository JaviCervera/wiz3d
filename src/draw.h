#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "wiz3d_config.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL wzSetup2D();
EXPORT void CALL wzSetViewport(int x, int y, int w, int h);
EXPORT void CALL wzSetResolution(int w, int h);
EXPORT void CALL wzSetDrawColor(int color);
EXPORT void CALL wzSetDrawFont(const char* filename, float height);
EXPORT void CALL wzSetDefaultFont();
EXPORT void CALL wzClearScreen(int color);
EXPORT void CALL wzDrawPoint(float x, float y);
EXPORT void CALL wzDrawLine(float x1, float y1, float x2, float y2);
EXPORT void CALL wzDrawEllipse(float x, float y, float width, float height);
EXPORT void CALL wzDrawRect(float x, float y, float width, float height);
EXPORT void CALL wzDrawTexture(const Texture* tex, float x, float y, float width, float height);
EXPORT void CALL wzDrawText(const char* text, float x, float y);

EXPORT float CALL wzGetTextWidth(const char* text);
EXPORT float CALL wzGetTextHeight(const char* text);

#ifndef SWIG
EXPORT void CALL _UnloadFonts();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DRAW_H_INCLUDED */
