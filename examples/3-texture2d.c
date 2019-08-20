#include "../src/spark.h"

int main() {
  /* Data */
  Texture* texture;

  /* Setup */
  spInitSpark();
  spSetScreen(800, 600, FALSE, FALSE);
  spSetScreenTitle("Texture 2D");

  /* Load texture */
  spSetTextureFilter(FALSE);
  texture = spLoadTexture("data/smile.png");

  /* Main loop */
  while (spIsScreenOpened() && !spIsKeyPressed(KEY_ESC)) {
    spSetup2D();
    spClearScreen(COLOR_BLACK);
    spDrawTexture(texture, (spGetScreenWidth() - spGetTextureWidth(texture)) / 2, (spGetScreenHeight() - spGetTextureHeight(texture)) / 2, 0, 0);
    spRefreshScreen();
  }

  /* Shutdown */
  spShutdownSpark();
}
