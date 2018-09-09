#include "input.h"
#include "platform.h"
#include "screen.h"

void input_setmousevisible(bool_t visible)
{
  p_set_cursor_visible(_screen_pointer(), visible);
}

void input_setmouseposition(int x, int y)
{
  p_set_cursor_position(_screen_pointer(), x, y);
}

int input_mousex()
{
  return p_cursor_x(_screen_pointer());
}

int input_mousey()
{
  return p_cursor_y(_screen_pointer());
}

bool_t input_mousedown(int b)
{
  return p_mouse_button_down(_screen_pointer(), b);
}

bool_t input_keydown(int k)
{
  return p_key_down(_screen_pointer(), k);
}
