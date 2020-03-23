#include "../src/wiz3d.h"
#include "../src/util.h"
#include <stdio.h>

int main() {
    /* Data */
    Viewer* viewer;
    Light* dir_light;
    Object* cube;
    Material* mat;
    char str[STRING_SIZE];

    /* Setup */
    wzInitWiz3D();
    wzSetScreen(800, 600, FALSE, TRUE);
    wzSetScreenTitle("Specular");

    /* Create and position viewer */
    viewer = wzCreateViewer();
    wzSetViewerClearColor(viewer, COLOR_DARKGRAY);
    wzSetViewerPosition(viewer, 0, 0, -6);

    /* Setup lighting */
    dir_light = wzCreateLight(LIGHT_DIRECTIONAL);
    wzTurnLight(dir_light, 30, 20);

    /* Create a cube */
    cube = wzCreateCube();
    mat = wzGetObjectMaterial(cube, 0);
    wzTurnObject(cube, 45, 45, 0);
    wzSetMaterialDiffuse(mat, COLOR_ORANGE);
    wzSetMaterialShininess(mat, 0);

    /* Main loop */
    while (wzIsScreenOpened() && !wzIsKeyPressed(KEY_ESC)) {
        /* Update shininess */
        if (wzIsKeyPressed(KEY_LEFT)) wzSetMaterialShininess(mat, _Clamp(wzGetMaterialShininess(mat) - 0.2f * wzGetDeltaTime(), 0, 1));
        if (wzIsKeyPressed(KEY_RIGHT)) wzSetMaterialShininess(mat, _Clamp(wzGetMaterialShininess(mat) + 0.2f * wzGetDeltaTime(), 0, 1));

        /* Draw scene */
        wzPrepareViewer(viewer);
        wzDrawObject(cube);

        /* Draw ui */
        wzSetup2D();
        sprintf(str, "%i FPS", wzGetScreenFPS());
        wzDrawText(str, 4, 4);
        sprintf(str, "Shininess: %f (LEFT and RIGHT to change)", wzGetMaterialShininess(mat));
        wzDrawText(str, 4, 16);
        wzRefreshScreen();
    }

    /* Shutdown */
    wzShutdownWiz3D();
}
