#include "../src/beam.h"

#define ROTATION_SPEED 32
#define TEXT "Hello, world!"

int main()
{
  /* setup */
  beam_init();
  screen_set(800, 600, FALSE, FALSE);

  /* main loop */
  while (screen_opened() && !input_keydown(KEY_ESC))
  {
    screen_setup2d();
    screen_setdrawcolor(COLOR_YELLOW);
    screen_clear(color_multiply(COLOR_BLUE, 0.5f));
    screen_drawtext(TEXT, (screen_width() - screen_textwidth(TEXT)) / 2, (screen_height() - screen_textheight(TEXT)) / 2);
    screen_refresh();
  }

  /* shutdown */
  beam_finish();
}
