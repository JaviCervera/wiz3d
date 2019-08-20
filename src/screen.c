#include "spark_config.h"

#ifndef PLATFORM_NULL

#include "draw.h"
#include "platform.h"
#include "screen.h"
#include "time.h"

static void* _screen_ptr = NULL;
static int _screen_fps = 0;
static int _screen_fpscounter = 0;
static float _screen_fpstime = 0;

EXPORT void CALL SetScreen(int width, int height, bool_t fullscreen, bool_t resizable) {
  /* unload fonts */
  _UnloadFonts();

  /* close screen if opened */
  if (_screen_ptr) p_CloseScreen(_screen_ptr);

  /* open screen */
  _screen_ptr = p_OpenScreen(width, height, fullscreen, 0, TRUE, resizable);

  /* set default font */
  SetDefaultFont();
}

EXPORT void CALL RefreshScreen() {
  /* refresh screen */
  p_RefreshScreen(_screen_ptr);

  /* update delta time */
  UpdateTimer();

  /* update fps */
  ++_screen_fpscounter;
  _screen_fpstime += GetDeltaTime();
  if (_screen_fpstime >= 1) {
    _screen_fps = _screen_fpscounter;
    _screen_fpscounter = 0;
    _screen_fpstime -= 1;
  }
}

EXPORT void CALL SetScreenTitle(const char* title) {
  p_SetScreenTitle(_screen_ptr, title);
}

EXPORT int CALL GetScreenWidth() {
  return p_GetScreenWidth(_screen_ptr);
}

EXPORT int CALL GetScreenHeight() {
  return p_GetScreenHeight(_screen_ptr);
}

EXPORT int CALL GetScreenFPS() {
  return _screen_fps;
}

EXPORT bool_t CALL IsScreenOpened() {
  return p_IsScreenOpened(_screen_ptr);
}

EXPORT int CALL GetDesktopWidth() {
  return p_GetDesktopWidth();
}

EXPORT int CALL GetDesktopHeight() {
  return p_GetDesktopHeight();
}

void* _GetScreenPtr() {
  return _screen_ptr;
}

#endif /* PLATFORM_NULL */
