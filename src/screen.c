#include "../lib/litelibs/litegfx.h"
#include "../lib/litelibs/litemath3d.h"
#include "../lib/stretchy_buffer.h"
#include "color.h"
#include "default_font.h"
#include "font.h"
#include "light.h"
#include "object.h"
#include "physics.h"
#include "platform.h"
#include "screen.h"
#include "util.h"
#include <string.h>

struct loadedfont_t
{
  char           name[STRING_SIZE];
  float          height;
  struct font_t* font;
};

static void* _screen_ptr = NULL;
static float _screen_delta = 0;
static float _screen_lasttime = 0;
static int _screen_fps = 0;
static int _screen_fpscounter = 0;
static float _screen_fpstime = 0;
static struct loadedfont_t* _screen_loadedfonts = NULL;
static struct font_t* _default_font = NULL;
static struct font_t* _screen_font = NULL;

void screen_set(int width, int height, bool_t fullscreen, bool_t resizable)
{
  int i;

  /* unload fonts */
  for (i = 0; i < sb_count(_screen_loadedfonts); ++i)
    font_release(_screen_loadedfonts[i].font);
    sb_free(_screen_loadedfonts);
  if ( _default_font ) font_release(_default_font);

  /* close screen if opened */
  if ( _screen_ptr ) p_close_screen(_screen_ptr);

  /* open screen */
  _screen_ptr = p_open_screen(width, height, fullscreen, 0, TRUE, resizable);

  /* load default font */
  _default_font = _font_loadbase64(DEFAULT_FONT, DEFAULT_FONT_BLOCKSIZE, 12);
  _screen_font = _default_font;
}

void screen_refresh()
{
  int v, i;
  float print_y;

  /* update physics */
  _physics_update(_screen_delta);

  /* refresh screen */
  p_refresh_screen(_screen_ptr);

  /* update delta time */
  _screen_delta = p_get_time() - _screen_lasttime;
  _screen_lasttime = p_get_time();

  /* update fps */
  ++_screen_fpscounter;
  _screen_fpstime += _screen_delta;
  if ( _screen_fpstime >= 1 )
  {
    _screen_fps = _screen_fpscounter;
    _screen_fpscounter = 0;
    _screen_fpstime -= 1;
  }
}

void screen_settitle(const char* title)
{
  p_set_screen_title(_screen_ptr, title);
}

void screen_setup2d()
{
  lgfx_setup2d(screen_width(), screen_height());
}

void screen_setviewport(int x, int y, int w, int h)
{
  lgfx_setviewport(x, y, w, h);
}

void screen_setresolution(int w, int h)
{
  lgfx_setresolution(w, h);
}

void screen_setdrawcolor(int color)
{
  lgfx_setcolor(
    color_red(color) / 255.0f,
    color_green(color) / 255.0f,
    color_blue(color) / 255.0f,
    color_alpha(color) / 255.0f);
}

void screen_setdrawfont(const char* filename, float height)
{
  struct font_t* font = NULL;
  int i;

  /* search for already loaded font */
  for ( i = 0; i < sb_count(_screen_loadedfonts); ++i )
  {
    if ( strcmp(_screen_loadedfonts[i].name, filename) == 0 && _screen_loadedfonts[i].height == height )
    {
      _screen_font = _screen_loadedfonts[i].font;
      return;
    }
  }

  /* load font */
  font = font_load(filename, height);
  if ( font )
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

void screen_clear(int color)
{
  lgfx_clearcolorbuffer(
    color_red(color) / 255.0f,
    color_green(color) / 255.0f,
    color_blue(color) / 255.0f
  );
}

void screen_setdrawfontdefault()
{
  _screen_font = _default_font;
}

void screen_drawtext(const char* text, float x, float y)
{
  font_draw(_screen_font, text, x, y);
}

int screen_width()
{
  return p_screen_width(_screen_ptr);
}

int screen_height()
{
  return p_screen_height(_screen_ptr);
}

float screen_delta()
{
  return _screen_delta;
}

int screen_fps()
{
  return _screen_fps;
}

bool_t screen_opened()
{
  return p_screen_opened(_screen_ptr);
}

int screen_desktopwidth()
{
  return p_desktop_width();
}

int screen_desktopheight()
{
  return p_desktop_height();
}

float screen_textwidth(const char* text)
{
  return font_textwidth(_screen_font, text);
}

float screen_textheight(const char* text)
{
  return font_textheight(_screen_font, text);
}

void* _screen_pointer()
{
  return _screen_ptr;
}
