#include "../src/wiz3d.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_CUBES (16 * 50)
#define ROTATION_SPEED 32

int main() {
    /* Data */
    Light* dir_light;
    Viewer* viewer;
    Object* cubes[NUM_CUBES];
    int x, z;
    int i;
    char str[STRING_SIZE];

    /* Setup */
    wzInitWiz3D();
    wzSetScreen(800, 600, FALSE, TRUE);
    wzSetScreenTitle("Fog");

    /* Setup lighting */
    dir_light = wzCreateLight(LIGHT_DIRECTIONAL);
    wzTurnLight(dir_light, 45, 45);

    /* Create and position viewer */
    viewer = wzCreateViewer();
    wzSetViewerClearColor(viewer, COLOR_DARKGRAY);
    wzSetViewerPosition(viewer, 0, 0, -7);
    wzSetViewerDistance(viewer, 1, 5000);
    wzSetViewerFogEnabled(viewer, TRUE);
    wzSetViewerFogDistance(viewer, 0, 20);

    /* Create billboards */
    x = -7;
    z = NUM_CUBES / 16 * 2 - 2;
    for (i = 0; i < NUM_CUBES; i += 2) {
        Object* cube;

        if (i == 0) {
            cube = wzCreateCube();
            wzSetMaterialDiffuse(wzGetObjectMaterial(cube, 0), COLOR_BROWN);
        } else {
            cube = wzCloneObject(cubes[0]);
        }
        wzSetObjectPosition(cube, x, -1.5f, z);
        cubes[i] = cube;

        cube = wzCloneObject(cubes[0]);
        wzSetObjectPosition(cube, x, 1.5f, z);
        cubes[i+1] = cube;
        
        x += 2;
        if (x > 7) {
            x = -7;
            z -= 2;
        }
    }

    /* Main loop */
    while (wzIsScreenOpened() && !wzIsKeyPressed(KEY_ESC)) {
        /* Turn objects */
        for (i = 0; i < NUM_CUBES; ++i) {
            wzTurnObject(cubes[i], 0, ROTATION_SPEED * wzGetDeltaTime(), 0);
        }

        /* Draw scene */
        wzPrepareViewer(viewer);
        for (i = 0; i < NUM_CUBES; ++i) {
            wzDrawObject(cubes[i]);
        }

        /* Draw UI */
        sprintf(str, "%i FPS", wzGetScreenFPS());
        wzSetup2D();
        wzDrawText(str, 4, 4);
        wzRefreshScreen();
    }

    /* Shutdown */
    wzShutdownWiz3D();
}
