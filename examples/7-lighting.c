#include "../src/beam.h"
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
    bmInitBeam();
    bmSetScreen(800, 600, FALSE, TRUE);
    bmSetScreenTitle("Lighting");

    /* Create and position viewer */
    viewer = bmCreateViewer();
    bmSetViewerClearColor(viewer, COLOR_BLACK);
    bmSetViewerPosition(viewer, 0, 32, -90);
    bmSetViewerRotation(viewer, 16, 0, 0);

    /* Setup lighting */
    bmSetAmbientColor(COLOR_BLACK);
    lights[0] = bmCreateLight(LIGHT_POINT);
    bmSetLightLinearAttenuation(lights[0], 0.05f);
    bmSetLightColor(lights[0], COLOR_RED);
    bmSetLightSpecularColored(lights[0], FALSE);
    bmSetLightRotation(lights[0], 0, 0);
    lights[1] = bmCreateLight(LIGHT_POINT);
    bmSetLightLinearAttenuation(lights[1], 0.05f);
    bmSetLightColor(lights[1], COLOR_GREEN);
    bmSetLightSpecularColored(lights[1], FALSE);
    bmSetLightRotation(lights[1], 0, 120);
    lights[2] = bmCreateLight(LIGHT_POINT);
    bmSetLightLinearAttenuation(lights[2], 0.05f);
    bmSetLightColor(lights[2], COLOR_BLUE);
    bmSetLightSpecularColored(lights[2], FALSE);
    bmSetLightRotation(lights[2], 0, 240);

    /* Create spheres */
    x = -32; z = -32;
    for (i = 0; i < NUM_SPHERES; ++i) {
        if (i == 0) {
            Material* material;
            spheres[i] = bmLoadObject("data/sphere.assbin");
            bmSetObjectScale(spheres[i], 2, 2, 2);
            material = bmGetObjectMaterial(spheres[i], 0);
            bmSetMaterialDiffuse(material, COLOR_WHITE);
            bmSetMaterialSpecular(material, COLOR_WHITE);
            bmSetMaterialShininess(material, 0.95f);
        } else {
            spheres[i] = bmCloneObject(spheres[0]);
        }
        bmSetObjectPosition(spheres[i], x, 0, z);
        x += 8;
        if (x > 32) {
            x = -32;
            z += 8;
        }
    }

    /* Main loop */
    while (bmIsScreenOpened() && !bmIsKeyPressed(KEY_ESC)) {
        bmPrepareViewer(viewer);

        /* Update lights */
        for (i = 0; i < NUM_LIGHTS_; ++i) {
            bmTurnLight(lights[i], 0, -ROTATION_SPEED * bmGetDeltaTime());
            bmSetLightPosition(lights[i], 0, 0, 0);
            bmMoveLight(lights[i], 0, 0, -48);
        }

        /* Draw scene */
        for (i = 0; i < NUM_SPHERES; ++i) {
            bmDrawObject(spheres[i]);
        }

        /* Draw UI */
        bmSetup2D();
        sprintf(str, "%i FPS", bmGetScreenFPS());
        bmDrawText(str, 4, 4);
        bmRefreshScreen();
    }

    /* Shutdown */
    bmShutdownBeam();
}
