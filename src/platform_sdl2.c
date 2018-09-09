#include "../lib/sdl2/SDL.h"
#include "input.h"
#include "platform.h"
#include "util.h"

static char _p_textinput[256] = { 0 };

struct p_window_t
{
  SDL_Window*   window;
  SDL_GLContext context;
  bool_t        closePressed;
};

bool_t p_init()
{
  /*SDL_SetMainReady();*/
  return SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) == 0;
}

void p_shutdown()
{
  SDL_Quit();
}

float p_get_time()
{
  return SDL_GetTicks() / 1000.0f;
}

void p_set_cursor_visible(void* win, bool_t visible)
{
  SDL_ShowCursor(visible);
}

void p_set_cursor_position(void* win, int x, int y)
{
  SDL_WarpMouseInWindow(((struct p_window_t*)win)->window, x, y);
}

int p_cursor_x(void* win)
{
  int x;
  SDL_GetMouseState(&x, NULL);
  return x;
}

int p_cursor_y(void* win)
{
  int y;
  SDL_GetMouseState(NULL, &y);
  return y;
}

bool_t p_mouse_button_down(void* win, int button)
{
  if ( button == 0 ) return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1);
  else if ( button == 1 ) return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3);
  else if ( button == 2 ) return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(2);
  else return 0;
}

bool_t p_key_down(void* win, int key)
{
  return (bool_t)SDL_GetKeyboardState(NULL)[SDL_GetScancodeFromKey(key)];
}

int p_desktop_width()
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return mode.w;
}

int p_desktop_height()
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return mode.h;
}

void* p_open_screen(int width, int height, bool_t fullscreen, int samples, bool_t vsync, bool_t resizable)
{
  Uint32 flags;
  struct p_window_t* win;

  /* gl attributes */
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, (samples > 0) ? 1 : 0);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, samples);
  
  /* flags */
  flags = SDL_WINDOW_OPENGL;
  if ( fullscreen ) flags |= SDL_WINDOW_FULLSCREEN;
  if ( resizable ) flags |= SDL_WINDOW_RESIZABLE;

  /* create window object */
  win = _alloc(struct p_window_t);
  win->closePressed = FALSE;
  win->window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
  win->context = SDL_GL_CreateContext(win->window);
  SDL_GL_MakeCurrent(win->window, win->context);
  
  /* set vsync */
  SDL_GL_SetSwapInterval(vsync);
  
  return win;
}

void p_close_screen(void* win)
{
  struct p_window_t* pwin;
  pwin = (struct p_window_t*)win;
  SDL_GL_DeleteContext(pwin->context);
  SDL_DestroyWindow(pwin->window);
  free(pwin);
}

bool_t p_screen_opened(void* win)
{
  return win && !((struct p_window_t*)win)->closePressed;
}

void p_refresh_screen(void* win)
{
  struct p_window_t* pwin;
  SDL_Event event;
  
  pwin = (struct p_window_t*)win;
  
  /* poll events */
  while ( SDL_PollEvent(&event) )
  {
    switch ( event.type ) {
    case SDL_WINDOWEVENT:
      if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) pwin->closePressed = TRUE;
      break;
    case SDL_QUIT:
      break;
    case SDL_TEXTINPUT:
      strcat(_p_textinput, event.text.text);
    }
  }

  /* refresh screen */
  SDL_GL_SwapWindow(pwin->window);
}

void p_set_screen_title(void* win, const char* title)
{
  SDL_SetWindowTitle(((struct p_window_t*)win)->window, title);
}

int p_screen_width(void* win)
{
  int w;
  SDL_GetWindowSize(((struct p_window_t*)win)->window, &w, NULL);
  return w;
}

int p_screen_height(void* win)
{
  int h;
  SDL_GetWindowSize(((struct p_window_t*)win)->window, NULL, &h);
  return h;
}

void p_messagebox(const char* title, const char* message)
{
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, NULL);
}

void p_starttextinput()
{
  SDL_StartTextInput();
}

const char* p_stoptextinput()
{
  SDL_StopTextInput();
  return _p_textinput;
}
