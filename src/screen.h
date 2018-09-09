#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

void screen_set(int width, int height, bool_t fullscreen, bool_t resizable);
void screen_refresh();
void screen_settitle(const char* title);
void screen_setup2d();
void screen_setviewport(int x, int y, int w, int h);
void screen_setresolution(int w, int h);
void screen_setdrawcolor(int color);
void screen_setdrawfont(const char* filename, float height);
void screen_setdrawfontdefault();
void screen_clear(int color);
void screen_drawtext(const char* text, float x, float y);
int screen_width();
int screen_height();
float screen_delta();
int screen_fps();
bool_t screen_opened();

int screen_desktopwidth();
int screen_desktopheight();

float screen_textwidth(const char* text);
float screen_textheight(const char* text);

#ifndef SWIG
void* _screen_pointer();
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SCREEN_H_INCLUDED */
