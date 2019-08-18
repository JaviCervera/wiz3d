#include "../src/beam.h"

int main() {
  /* Data */
  Texture* texture;

  /* Setup */
  InitBeam();
  SetScreen(800, 600, FALSE, FALSE);
  SetScreenTitle("Texture 2D");

  /* Load texture */
  SetTextureFilter(FALSE);
  texture = LoadTexture("data/smile.png");

  /* Main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC)) {
    Setup2D();
    ClearScreen(COLOR_BLACK);
    DrawTexture(texture, (GetScreenWidth() - GetTextureWidth(texture)) / 2, (GetScreenHeight() - GetTextureHeight(texture)) / 2, 0, 0);
    RefreshScreen();
  }

  /* Shutdown */
  ShutdownBeam();
}
