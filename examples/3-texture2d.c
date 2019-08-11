#include "../src/beam.h"

int main()
{
  /* data */
  struct STexture* texture;

  /* setup */
  InitBeam();
  SetScreen(800, 600, FALSE, FALSE);
  SetScreenTitle("Texture 2D");

  /* load texture */
  SetTextureFilter(FALSE);
  texture = LoadTexture("data/smile.png");

  /* main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC))
  {
    Setup2D();
    ClearScreen(COLOR_BLACK);
    DrawTexture(texture, (GetScreenWidth() - GetTextureWidth(texture)) / 2, (GetScreenHeight() - GetTextureHeight(texture)) / 2, 0, 0);
    RefreshScreen();
  }

  /* shutdown */
  ShutdownBeam();
}
