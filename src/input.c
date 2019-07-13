#include "input.h"
#include "platform.h"
#include "screen.h"

EXPORT void CALL input_setmousevisible(bool_t visible)
{
  p_set_cursor_visible(_screen_pointer(), visible);
}

EXPORT void CALL input_setmouseposition(int x, int y)
{
  p_set_cursor_position(_screen_pointer(), x, y);
}

EXPORT int CALL input_mousex()
{
  return p_cursor_x(_screen_pointer());
}

EXPORT int CALL input_mousey()
{
  return p_cursor_y(_screen_pointer());
}

EXPORT bool_t CALL input_mousedown(int b)
{
  return p_mouse_button_down(_screen_pointer(), b);
}

EXPORT bool_t CALL input_keydown(int k)
{
  return p_key_down(_screen_pointer(), k);
}
