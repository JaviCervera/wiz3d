#include "../src/wiz3d.h"
#include <stdio.h>

int main() {
    /* Data */
    Viewer* viewer;
    Object* md2;
    bool_t walking;
    bool_t space_down;
    char str[STRING_SIZE];

    /* Setup */
    wzInitWiz3D();
    wzSetScreen(800, 600, FALSE, TRUE);
    wzSetScreenTitle("MD2 Animation");

    /* Create and position viewer */
    viewer = wzCreateViewer();
    wzSetViewerClearColor(viewer, COLOR_DARKGRAY);
    wzSetViewerPosition(viewer, 0, 2, -4);
    wzSetViewerRotation(viewer, 15, 0, 0);

    /* Load MD2 */
    md2 = wzLoadObject("data/german.md2");
    wzSetObjectAnimMode(md2, ANIM_LOOP);
    wzTurnObject(md2, 0, 90, 0);
    wzSetMaterialTexture(wzGetObjectMaterial(md2, 0), wzLoadTexture("data/german.png")); /* This shouldn't be necessary */

    /* Main loop */
    while (wzIsScreenOpened() && !wzIsKeyPressed(KEY_ESC)) {
        /* Update animation */
        if (wzIsKeyPressed(KEY_SPACE)) {
            if (!space_down) walking = !walking;
            space_down = TRUE;
        } else {
            space_down = FALSE;
        }
        if (walking) wzSetObjectAnimRange(md2, 31, 0); /* 51 */
        else wzSetObjectAnimRange(md2, 0, 25);

        /* Draw scene */
        wzPrepareViewer(viewer);
        wzDrawObject(md2);

        /* Draw UI */
        wzSetup2D();
        sprintf(str, "%i FPS", wzGetScreenFPS());
        wzDrawText(str, 4, 4);
        sprintf(str, "Frame: %i", wzGetObjectFrame(md2));
        wzDrawText(str, 4, 16);
        wzRefreshScreen();
    }

    /* Shutdown */
    wzShutdownWiz3D();
}
