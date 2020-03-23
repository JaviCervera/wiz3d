#include "../src/wiz3d.h"
#include <stdio.h>

#define ROTATION_SPEED 90

int main() {
    /* Data */
    Viewer* viewer;
    Light* dir_light;
    Object* triangle;
    Material* material;
    char str[STRING_SIZE];

    /* Setup */
    wzInitWiz3D();
    wzSetScreen(800, 600, FALSE, TRUE);
    wzSetScreenTitle("Triangle");

    /* Create and position viewer */
    viewer = wzCreateViewer();
    wzSetViewerClearColor(viewer, COLOR_WHITE);
    wzSetViewerPosition(viewer, 0, 0, -2);

    /* Create a triangle */
    triangle = wzCreateTriangle();
    material = wzGetObjectMaterial(triangle, 0);
    wzSetMaterialFlags(material, wzGetMaterialFlags(material) - FLAG_CULL);
    wzSetMaterialDiffuse(material, COLOR_ORANGE);

    /* Main loop */
    while (wzIsScreenOpened() && !wzIsKeyPressed(KEY_ESC)) {
        wzTurnObject(triangle, 0, ROTATION_SPEED * wzGetDeltaTime(), 0);

        /* Draw scene */
        wzPrepareViewer(viewer);
        wzDrawObject(triangle);

        /* Draw UI */
        sprintf(str, "%i FPS", wzGetScreenFPS());
        wzSetup2D();
        wzDrawText(str, 4, 4);
        wzRefreshScreen();
    }

    /* Shutdown */
    wzShutdownWiz3D();
}
