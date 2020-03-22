#include "../src/beam.h"
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
    bmInitBeam();
    bmSetScreen(800, 600, FALSE, TRUE);
    bmSetScreenTitle("Fog");

    /* Setup lighting */
    dir_light = bmCreateLight(LIGHT_DIRECTIONAL);
    bmTurnLight(dir_light, 45, 45);

    /* Create and position viewer */
    viewer = bmCreateViewer();
    bmSetViewerClearColor(viewer, COLOR_DARKGRAY);
    bmSetViewerPosition(viewer, 0, 0, -7);
    bmSetViewerDistance(viewer, 1, 5000);
    bmSetViewerFogEnabled(viewer, TRUE);
    bmSetViewerFogDistance(viewer, 0, 20);

    /* Create billboards */
    x = -7;
    z = NUM_CUBES / 16 * 2 - 2;
    for (i = 0; i < NUM_CUBES; i += 2) {
        Object* cube;

        if (i == 0) {
            cube = bmCreateCube();
            bmSetMaterialDiffuse(bmGetObjectMaterial(cube, 0), COLOR_BROWN);
        } else {
            cube = bmCloneObject(cubes[0]);
        }
        bmSetObjectPosition(cube, x, -1.5f, z);
        cubes[i] = cube;

        cube = bmCloneObject(cubes[0]);
        bmSetObjectPosition(cube, x, 1.5f, z);
        cubes[i+1] = cube;
        
        x += 2;
        if (x > 7) {
            x = -7;
            z -= 2;
        }
    }

    /* Main loop */
    while (bmIsScreenOpened() && !bmIsKeyPressed(KEY_ESC)) {
        /* Turn objects */
        for (i = 0; i < NUM_CUBES; ++i) {
            bmTurnObject(cubes[i], 0, ROTATION_SPEED * bmGetDeltaTime(), 0);
        }

        /* Draw scene */
        bmPrepareViewer(viewer);
        for (i = 0; i < NUM_CUBES; ++i) {
            bmDrawObject(cubes[i]);
        }

        /* Draw UI */
        sprintf(str, "%i FPS", bmGetScreenFPS());
        bmSetup2D();
        bmDrawText(str, 4, 4);
        bmRefreshScreen();
    }

    /* Shutdown */
    bmShutdownBeam();
}
