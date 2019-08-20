#include "../src/spark.h"

#define ROTATION_SPEED 32
#define TEXT "Hello, world!"

int main() {
  /* Setup */
  spInitSpark();
  spSetScreen(800, 600, FALSE, FALSE);
  spSetScreenTitle(TEXT);

  /* Main loop */
  while (spIsScreenOpened() && !spIsKeyPressed(KEY_ESC))
  {
    spSetup2D();
    spSetDrawColor(COLOR_YELLOW);
    spClearScreen(spMultiplyColor(COLOR_BLUE, 0.5f));
    spDrawText(TEXT, (spGetScreenWidth() - spGetTextWidth(TEXT)) / 2, (spGetScreenHeight() - spGetTextHeight(TEXT)) / 2);
    spRefreshScreen();
  }

  /* Shutdown */
  spShutdownSpark();
}
