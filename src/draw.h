#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "spark_config.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL spSetup2D();
EXPORT void CALL spSetViewport(int x, int y, int w, int h);
EXPORT void CALL spSetResolution(int w, int h);
EXPORT void CALL spSetDrawColor(int color);
EXPORT void CALL spSetDrawFont(const char* filename, float height);
EXPORT void CALL spSetDefaultFont();
EXPORT void CALL spClearScreen(int color);
EXPORT void CALL spDrawPoint(float x, float y);
EXPORT void CALL spDrawLine(float x1, float y1, float x2, float y2);
EXPORT void CALL spDrawEllipse(float x, float y, float width, float height);
EXPORT void CALL spDrawRect(float x, float y, float width, float height);
EXPORT void CALL spDrawTexture(const Texture* tex, float x, float y, float width, float height);
EXPORT void CALL spDrawText(const char* text, float x, float y);

EXPORT float CALL spGetTextWidth(const char* text);
EXPORT float CALL spGetTextHeight(const char* text);

#ifndef SWIG
EXPORT void CALL _UnloadFonts();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DRAW_H_INCLUDED */
