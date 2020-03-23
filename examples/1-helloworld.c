#include "../src/wiz3d.h"

#define ROTATION_SPEED 32
#define TEXT "Hello, world!"

int main() {
    /* Setup */
    wzInitWiz3D();
    wzSetScreen(800, 600, FALSE, FALSE);
    wzSetScreenTitle(TEXT);

    /* Main loop */
    while (wzIsScreenOpened() && !wzIsKeyPressed(KEY_ESC))
    {
        wzSetup2D();
        wzSetDrawColor(COLOR_YELLOW);
        wzClearScreen(wzMultiplyColor(COLOR_BLUE, 0.5f));
        wzDrawText(TEXT, (wzGetScreenWidth() - wzGetTextWidth(TEXT)) / 2, (wzGetScreenHeight() - wzGetTextHeight(TEXT)) / 2);
        wzRefreshScreen();
    }

    /* Shutdown */
    wzShutdownWiz3D();
}
