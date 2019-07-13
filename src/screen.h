#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include "micron_config.h"
#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct texture_t;

EXPORT void CALL screen_set(int width, int height, bool_t fullscreen, bool_t resizable);
EXPORT void CALL screen_refresh();
EXPORT void CALL screen_settitle(const char* title);
EXPORT void CALL screen_setup2d();
EXPORT void CALL screen_setviewport(int x, int y, int w, int h);
EXPORT void CALL screen_setresolution(int w, int h);
EXPORT void CALL screen_setdrawcolor(int color);
EXPORT void CALL screen_setdrawfont(const char* filename, float height);
#ifdef USE_DEFAULT_FONT
EXPORT void CALL screen_setdrawfontdefault();
#endif
EXPORT void CALL screen_clear(int color);
EXPORT void CALL screen_drawpoint(float x, float y);
EXPORT void CALL screen_drawline(float x1, float y1, float x2, float y2);
EXPORT void CALL screen_drawellipse(float x, float y, float width, float height);
EXPORT void CALL screen_drawrect(float x, float y, float width, float height);
EXPORT void CALL screen_drawtexture(const struct texture_t* tex, float x, float y, float width, float height);
EXPORT void CALL screen_drawtext(const char* text, float x, float y);
EXPORT int CALL screen_width();
EXPORT int CALL screen_height();
EXPORT float CALL screen_delta();
EXPORT int CALL screen_fps();
EXPORT bool_t CALL screen_opened();

EXPORT int CALL screen_desktopwidth();
EXPORT int CALL screen_desktopheight();

EXPORT float CALL screen_textwidth(const char* text);
EXPORT float CALL screen_textheight(const char* text);

#ifndef SWIG
void* _screen_pointer();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SCREEN_H_INCLUDED */
