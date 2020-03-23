#include "../src/wiz3d.h"

int main() {
    /* Data */
    Texture* texture;

    /* Setup */
    wzInitWiz3D();
    wzSetScreen(800, 600, FALSE, FALSE);
    wzSetScreenTitle("Texture 2D");

    /* Load texture */
    wzSetTextureFilter(FALSE);
    texture = wzLoadTexture("data/smile.png");

    /* Main loop */
    while (wzIsScreenOpened() && !wzIsKeyPressed(KEY_ESC)) {
        wzSetup2D();
        wzClearScreen(COLOR_BLACK);
        wzDrawTexture(texture, (wzGetScreenWidth() - wzGetTextureWidth(texture)) / 2, (wzGetScreenHeight() - wzGetTextureHeight(texture)) / 2, 0, 0);
        wzRefreshScreen();
    }

    /* Shutdown */
    wzShutdownWiz3D();
}
