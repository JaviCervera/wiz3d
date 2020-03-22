#include "../src/beam.h"
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
    bmInitBeam();
    bmSetScreen(800, 600, FALSE, TRUE);
    bmSetScreenTitle("Specular");

    /* Create and position viewer */
    viewer = bmCreateViewer();
    bmSetViewerClearColor(viewer, COLOR_DARKGRAY);
    bmSetViewerPosition(viewer, 0, 0, -6);

    /* Setup lighting */
    dir_light = bmCreateLight(LIGHT_DIRECTIONAL);
    bmTurnLight(dir_light, 30, 20);

    /* Create a cube */
    cube = bmCreateCube();
    mat = bmGetObjectMaterial(cube, 0);
    bmTurnObject(cube, 45, 45, 0);
    bmSetMaterialDiffuse(mat, COLOR_ORANGE);
    bmSetMaterialShininess(mat, 0);

    /* Main loop */
    while (bmIsScreenOpened() && !bmIsKeyPressed(KEY_ESC)) {
        /* Update shininess */
        if (bmIsKeyPressed(KEY_LEFT)) bmSetMaterialShininess(mat, _Clamp(bmGetMaterialShininess(mat) - 0.2f * bmGetDeltaTime(), 0, 1));
        if (bmIsKeyPressed(KEY_RIGHT)) bmSetMaterialShininess(mat, _Clamp(bmGetMaterialShininess(mat) + 0.2f * bmGetDeltaTime(), 0, 1));

        /* Draw scene */
        bmPrepareViewer(viewer);
        bmDrawObject(cube);

        /* Draw ui */
        bmSetup2D();
        sprintf(str, "%i FPS", bmGetScreenFPS());
        bmDrawText(str, 4, 4);
        sprintf(str, "Shininess: %f (LEFT and RIGHT to change)", bmGetMaterialShininess(mat));
        bmDrawText(str, 4, 16);
        bmRefreshScreen();
    }

    /* Shutdown */
    bmShutdownBeam();
}
