#include "../src/beam.h"

#define ROTATION_SPEED 32
#define TEXT "Hello, world!"

int main()
{
  /* setup */
  InitBeam();
  SetScreen(800, 600, FALSE, FALSE);

  /* main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC))
  {
    Setup2D();
    SetDrawColor(COLOR_YELLOW);
    ClearScreen(MultiplyColor(COLOR_BLUE, 0.5f));
    DrawText(TEXT, (GetScreenWidth() - GetTextWidth(TEXT)) / 2, (GetScreenHeight() - GetTextHeight(TEXT)) / 2);
    RefreshScreen();
  }

  /* shutdown */
  ShutdownBeam();
}
