#include "micron_config.h"
#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "../lib/stb/stretchy_buffer.h"
#include "color.h"
#ifdef USE_DEFAULT_FONT
#include "default_font.h"
#endif
#include "font.h"
#include "platform.h"
#include "screen.h"
#include "texture.h"
#include "util.h"
#include <string.h>

struct loadedfont_t
{
  char name[STRING_SIZE];
  float height;
  struct font_t* font;
};

static void* _screen_ptr = NULL;
static float _screen_delta = 0;
static float _screen_lasttime = 0;
static int _screen_fps = 0;
static int _screen_fpscounter = 0;
static float _screen_fpstime = 0;
static struct loadedfont_t* _screen_loadedfonts = NULL;
#ifdef USE_DEFAULT_FONT
static struct font_t* _default_font = NULL;
#endif
static struct font_t* _screen_font = NULL;

EXPORT void CALL screen_set(int width, int height, bool_t fullscreen, bool_t resizable)
{
  int i;

  /* unload fonts */
  for (i = 0; i < sb_count(_screen_loadedfonts); ++i)
    font_release(_screen_loadedfonts[i].font);
    sb_free(_screen_loadedfonts);
#ifdef USE_DEFAULT_FONT
  if (_default_font) font_release(_default_font);
#endif

  /* close screen if opened */
  if (_screen_ptr) p_close_screen(_screen_ptr);

  /* open screen */
  _screen_ptr = p_open_screen(width, height, fullscreen, 0, TRUE, resizable);

  /* load default font */
#ifdef USE_DEFAULT_FONT
  _default_font = _font_loadbase64(DEFAULT_FONT, DEFAULT_FONT_BLOCKSIZE, 14);
  _screen_font = _default_font;
#else
  _screen_font = NULL;
#endif
}

EXPORT void CALL screen_refresh()
{
  /* refresh screen */
  p_refresh_screen(_screen_ptr);

  /* update delta time */
  _screen_delta = p_get_time() - _screen_lasttime;
  _screen_lasttime = p_get_time();

  /* update fps */
  ++_screen_fpscounter;
  _screen_fpstime += _screen_delta;
  if (_screen_fpstime >= 1)
  {
    _screen_fps = _screen_fpscounter;
    _screen_fpscounter = 0;
    _screen_fpstime -= 1;
  }
}

EXPORT void CALL screen_settitle(const char* title)
{
  p_set_screen_title(_screen_ptr, title);
}

EXPORT void CALL screen_setup2d()
{
  lgfx_setup2d(screen_width(), screen_height());
}

EXPORT void CALL screen_setviewport(int x, int y, int w, int h)
{
  lgfx_setviewport(x, y, w, h);
}

EXPORT void CALL screen_setresolution(int w, int h)
{
  lgfx_setresolution(w, h);
}

EXPORT void CALL screen_setdrawcolor(int color)
{
  lgfx_setcolor(
    color_red(color) / 255.0f,
    color_green(color) / 255.0f,
    color_blue(color) / 255.0f,
    color_alpha(color) / 255.0f);
}

EXPORT void CALL screen_setdrawfont(const char* filename, float height)
{
  struct font_t* font = NULL;
  int i;

  /* search for already loaded font */
  for (i = 0; i < sb_count(_screen_loadedfonts); ++i)
  {
    if (strcmp(_screen_loadedfonts[i].name, filename) == 0 && _screen_loadedfonts[i].height == height)
    {
      _screen_font = _screen_loadedfonts[i].font;
      return;
    }
  }

  /* load font */
  font = font_load(filename, height);
  if (font)
  {
    struct loadedfont_t data;

    strncpy(data.name, filename, STRING_SIZE);
    data.name[STRING_SIZE-1] = 0;
    data.height = height;
    data.font = font;
    sb_push(_screen_loadedfonts, data);
    _screen_font = font;
  }
}

EXPORT void CALL screen_clear(int color)
{
  lgfx_clearcolorbuffer(
    color_red(color) / 255.0f,
    color_green(color) / 255.0f,
    color_blue(color) / 255.0f
  );
}

#ifdef USE_DEFAULT_FONT
EXPORT void CALL screen_setdrawfontdefault()
{
  _screen_font = _default_font;
}
#endif

EXPORT void CALL screen_drawpoint(float x, float y)
{
  lgfx_drawpoint(x, y);
}

EXPORT void CALL screen_drawline(float x1, float y1, float x2, float y2)
{
  lgfx_drawline(x1, y1, x2, y2);
}

EXPORT void CALL screen_drawellipse(float x, float y, float width, float height)
{
  lgfx_drawoval(x, y, width, height);
}

EXPORT void CALL screen_drawrect(float x, float y, float width, float height)
{
  lgfx_drawrect(x, y, width, height);
}

EXPORT void CALL screen_drawtexture(const struct texture_t* tex, float x, float y, float width, float height)
{
  const ltex_t* ltex = (const ltex_t*)_texture_ptr(tex);
  ltex_bindcolor(ltex);
  lgfx_drawrect(x, y, width != 0 ? width : ltex->width, height != 0 ? height : ltex->height);
}

EXPORT void CALL screen_drawtext(const char* text, float x, float y)
{
  font_draw(_screen_font, text, x, y);
}

EXPORT int CALL screen_width()
{
  return p_screen_width(_screen_ptr);
}

EXPORT int CALL screen_height()
{
  return p_screen_height(_screen_ptr);
}

EXPORT float CALL screen_delta()
{
  return _screen_delta;
}

EXPORT int CALL screen_fps()
{
  return _screen_fps;
}

EXPORT bool_t CALL screen_opened()
{
  return p_screen_opened(_screen_ptr);
}

EXPORT int CALL screen_desktopwidth()
{
  return p_desktop_width();
}

EXPORT int CALL screen_desktopheight()
{
  return p_desktop_height();
}

EXPORT float CALL screen_textwidth(const char* text)
{
  return font_textwidth(_screen_font, text);
}

EXPORT float CALL screen_textheight(const char* text)
{
  return font_textheight(_screen_font, text);
}

void* _screen_pointer()
{
  return _screen_ptr;
}
