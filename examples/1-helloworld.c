#include "../src/beam.h"

#define ROTATION_SPEED 32
#define TEXT "Hello, world!"

int main() {
  /* Setup */
  bmInitBeam();
  bmSetScreen(800, 600, FALSE, FALSE);
  bmSetScreenTitle(TEXT);

  /* Main loop */
  while (bmIsScreenOpened() && !bmIsKeyPressed(KEY_ESC))
  {
    bmSetup2D();
    bmSetDrawColor(COLOR_YELLOW);
    bmClearScreen(bmMultiplyColor(COLOR_BLUE, 0.5f));
    bmDrawText(TEXT, (bmGetScreenWidth() - bmGetTextWidth(TEXT)) / 2, (bmGetScreenHeight() - bmGetTextHeight(TEXT)) / 2);
    bmRefreshScreen();
  }

  /* Shutdown */
  bmShutdownBeam();
}
