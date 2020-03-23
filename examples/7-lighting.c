#include "../src/wiz3d.h"
#include "../src/util.h"
#include <stdio.h>

#define NUM_LIGHTS_ 3
#define NUM_SPHERES 81
#define ROTATION_SPEED 32

int main() {
    /* Data */
    Viewer* viewer;
    Light* lights[NUM_LIGHTS_];
    Object* spheres[NUM_SPHERES];
    int x, z;
    int i;
    char str[STRING_SIZE];

    /* Setup */
    wzInitWiz3D();
    wzSetScreen(800, 600, FALSE, TRUE);
    wzSetScreenTitle("Lighting");

    /* Create and position viewer */
    viewer = wzCreateViewer();
    wzSetViewerClearColor(viewer, COLOR_BLACK);
    wzSetViewerPosition(viewer, 0, 32, -90);
    wzSetViewerRotation(viewer, 16, 0, 0);

    /* Setup lighting */
    wzSetAmbientColor(COLOR_BLACK);
    lights[0] = wzCreateLight(LIGHT_POINT);
    wzSetLightLinearAttenuation(lights[0], 0.05f);
    wzSetLightColor(lights[0], COLOR_RED);
    wzSetLightSpecularColored(lights[0], FALSE);
    wzSetLightRotation(lights[0], 0, 0);
    lights[1] = wzCreateLight(LIGHT_POINT);
    wzSetLightLinearAttenuation(lights[1], 0.05f);
    wzSetLightColor(lights[1], COLOR_GREEN);
    wzSetLightSpecularColored(lights[1], FALSE);
    wzSetLightRotation(lights[1], 0, 120);
    lights[2] = wzCreateLight(LIGHT_POINT);
    wzSetLightLinearAttenuation(lights[2], 0.05f);
    wzSetLightColor(lights[2], COLOR_BLUE);
    wzSetLightSpecularColored(lights[2], FALSE);
    wzSetLightRotation(lights[2], 0, 240);

    /* Create spheres */
    x = -32; z = -32;
    for (i = 0; i < NUM_SPHERES; ++i) {
        if (i == 0) {
            Material* material;
            spheres[i] = wzLoadObject("data/sphere.assbin");
            wzSetObjectScale(spheres[i], 2, 2, 2);
            material = wzGetObjectMaterial(spheres[i], 0);
            wzSetMaterialDiffuse(material, COLOR_WHITE);
            wzSetMaterialSpecular(material, COLOR_WHITE);
            wzSetMaterialShininess(material, 0.95f);
        } else {
            spheres[i] = wzCloneObject(spheres[0]);
        }
        wzSetObjectPosition(spheres[i], x, 0, z);
        x += 8;
        if (x > 32) {
            x = -32;
            z += 8;
        }
    }

    /* Main loop */
    while (wzIsScreenOpened() && !wzIsKeyPressed(KEY_ESC)) {
        wzPrepareViewer(viewer);

        /* Update lights */
        for (i = 0; i < NUM_LIGHTS_; ++i) {
            wzTurnLight(lights[i], 0, -ROTATION_SPEED * wzGetDeltaTime());
            wzSetLightPosition(lights[i], 0, 0, 0);
            wzMoveLight(lights[i], 0, 0, -48);
        }

        /* Draw scene */
        for (i = 0; i < NUM_SPHERES; ++i) {
            wzDrawObject(spheres[i]);
        }

        /* Draw UI */
        wzSetup2D();
        sprintf(str, "%i FPS", wzGetScreenFPS());
        wzDrawText(str, 4, 4);
        wzRefreshScreen();
    }

    /* Shutdown */
    wzShutdownWiz3D();
}
