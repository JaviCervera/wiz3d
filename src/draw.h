#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "beam_config.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL bmSetup2D();
EXPORT void CALL bmSetViewport(int x, int y, int w, int h);
EXPORT void CALL bmSetResolution(int w, int h);
EXPORT void CALL bmSetDrawColor(int color);
EXPORT void CALL bmSetDrawFont(const char* filename, float height);
EXPORT void CALL bmSetDefaultFont();
EXPORT void CALL bmClearScreen(int color);
EXPORT void CALL bmDrawPoint(float x, float y);
EXPORT void CALL bmDrawLine(float x1, float y1, float x2, float y2);
EXPORT void CALL bmDrawEllipse(float x, float y, float width, float height);
EXPORT void CALL bmDrawRect(float x, float y, float width, float height);
EXPORT void CALL bmDrawTexture(const Texture* tex, float x, float y, float width, float height);
EXPORT void CALL bmDrawText(const char* text, float x, float y);

EXPORT float CALL bmGetTextWidth(const char* text);
EXPORT float CALL bmGetTextHeight(const char* text);

#ifndef SWIG
EXPORT void CALL _UnloadFonts();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DRAW_H_INCLUDED */
