#include "../src/beam.h"

int main() {
  /* Data */
  Texture* texture;

  /* Setup */
  bmInitBeam();
  bmSetScreen(800, 600, FALSE, FALSE);
  bmSetScreenTitle("Texture 2D");

  /* Load texture */
  bmSetTextureFilter(FALSE);
  texture = bmLoadTexture("data/smile.png");

  /* Main loop */
  while (bmIsScreenOpened() && !bmIsKeyPressed(KEY_ESC)) {
    bmSetup2D();
    bmClearScreen(COLOR_BLACK);
    bmDrawTexture(texture, (bmGetScreenWidth() - bmGetTextureWidth(texture)) / 2, (bmGetScreenHeight() - bmGetTextureHeight(texture)) / 2, 0, 0);
    bmRefreshScreen();
  }

  /* Shutdown */
  bmShutdownBeam();
}
